#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/wait.h>
#include <linux/cdev.h>
#include <linux/kfifo.h>
#include <linux/ioctl.h>
#include <linux/uaccess.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/wait.h>
#include <linux/sched.h>
#include <linux/poll.h>
#include "aivserial.h"

#define AI_VSERIAL_NAME "aivserial"

struct aivserial_dev {
	unsigned int baud;
	struct aivserial_option opt; 
	struct cdev cdev;
	wait_queue_head_t rwqh;
	wait_queue_head_t wwqh;
	struct fasync_struct *fapp;
	struct proc_dir_entry *pdir;
	struct proc_dir_entry *pdat;
};

static int aivserial_major = 250;
static int aivserial_minor = 0;
static int aivserial_nr_devs = 1;
static struct aivserial_dev aivserial_dev;
DEFINE_KFIFO(aivserial_fifo, char, 32);

static int aivserial_open(struct inode *inode, struct file *filp)
{

	return 0;
}

static int aivserial_fasync(int fd, struct file *filp, int on);

static int aivserial_release(struct inode *inode, struct file *filp)
{
	aivserial_fasync(-1, filp, 0);
	return 0;
}

static ssize_t aivserial_read(struct file *filp, char __user *buf, size_t cnt, loff_t *pos)
{
	int ret;
	unsigned int copied = 0;

	if (kfifo_is_empty(&aivserial_fifo)) {
		if (filp->f_flags & O_NONBLOCK)
			return -EAGAIN;

		// kfifo空的时候将当前进程放到等待队列并休眠
		if (wait_event_interruptible(aivserial_dev.rwqh, !kfifo_is_empty(&aivserial_fifo)))
			return -ERESTARTSYS;
	}

	ret = kfifo_to_user(&aivserial_fifo, buf, cnt, &copied);

	if (!kfifo_is_full(&aivserial_fifo)) {
		wake_up_interruptible(&aivserial_dev.wwqh);
		kill_fasync(&aivserial_dev.fapp, SIGIO, POLL_OUT);
	}

	return ret == 0 ? copied : ret;
}

static ssize_t aivserial_write(struct file *filp, const char __user *buf, size_t cnt, loff_t *pos)
{
	int ret;
	unsigned int copied = 0;

	if (kfifo_is_full(&aivserial_fifo)) {
		if (filp->f_flags & O_NONBLOCK)
			return -EAGAIN;

		if (wait_event_interruptible(aivserial_dev.wwqh, !kfifo_is_full(&aivserial_fifo)))
			return -ERESTARTSYS;
	}

	ret = kfifo_from_user(&aivserial_fifo, buf, cnt, &copied);
	if (!kfifo_is_empty(&aivserial_fifo)) {
		wake_up_interruptible(&aivserial_dev.rwqh);
		kill_fasync(&aivserial_dev.fapp, SIGIO, POLL_IN);
	}

	return ret == 0 ? copied : ret;
}

static long aivserial_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	if (_IOC_TYPE(cmd) != AI_VSERIAL_MAGIC)
		return -ENOTTY;

	switch (cmd) {
	case AI_VSERIAL_SET_BAUD:
		aivserial_dev.baud = arg;
		break;
	case AI_VSERIAL_GET_BAUD:
		arg = aivserial_dev.baud;
		break;
	case AI_VSERIAL_SET_FFMT:
		if (copy_from_user(&aivserial_dev.opt,
					       (struct aivserial_option __user *)arg,
						   sizeof(struct aivserial_option)))
			return -EFAULT;
		break;
	case AI_VSERIAL_GET_FFMT:
		if (copy_to_user((struct aivserial_option __user *)arg,
						 &aivserial_dev.opt,
                         sizeof(struct aivserial_option)))
			return -EFAULT;
		break;
	default:
		return -ENOTTY;
	}

	return 0;
}

static unsigned int aivserial_poll(struct file *filp, struct poll_table_struct *table)
{
	int mask = 0;

	poll_wait(filp, &aivserial_dev.rwqh, table);
	poll_wait(filp, &aivserial_dev.wwqh, table);

	if (!kfifo_is_empty(&aivserial_fifo))
		mask |= POLLIN | POLLRDNORM;
	if (!kfifo_is_full(&aivserial_fifo))
		mask |= POLLOUT | POLLWRNORM;

	return mask;
}

static ssize_t aivserial_aio_read(struct kiocb *iocb, const struct iovec *iov,
		                          unsigned long nr_segs, loff_t pos)
{
	size_t read = 0;
	unsigned long i;
	ssize_t ret;

	for (i = 0; i < nr_segs; i++) {
		ret = aivserial_read(iocb->ki_filp, iov[i].iov_base, iov[i].iov_len, &pos);
		if (ret < 0)
			break;
		read += ret;
	}

	return read ? read : -EFAULT;
}

static ssize_t aivserial_aio_write(struct kiocb *iocb, const struct iovec *iov,
		                           unsigned long nr_segs, loff_t pos)
{
	size_t written = 0;
	unsigned long i;
	ssize_t ret;

	for (i = 0; i < nr_segs; i++) {
		ret = aivserial_write(iocb->ki_filp, iov[i].iov_base, iov[i].iov_len, &pos);
		if (ret < 0)
			break;
		written += ret;
	}

	return written ? written : -EFAULT;
}

static int aivserial_fasync(int fd, struct file *filp, int on)
{
	return fasync_helper(fd, filp, on, &aivserial_dev.fapp);
}

static struct file_operations aivserial_fops = {
	.owner = THIS_MODULE,
	.open = aivserial_open,
	.release = aivserial_release,
	.read = aivserial_read,
	.write = aivserial_write,
	.unlocked_ioctl = aivserial_ioctl,
	.poll = aivserial_poll,
	.aio_read = aivserial_aio_read,
	.aio_write = aivserial_aio_write,
	.fasync = aivserial_fasync
};

static int aivserial_data_show(struct seq_file *m, void *v)
{
	struct aivserial_dev *dev = m->private;

	seq_printf(m, "baudrate: %d\n", dev->baud);
	return seq_printf(m, "frame format: %d%c%d\n", dev->opt.datab,
			          dev->opt.parity == 0 ? 'N' : dev->opt.parity == 1 ? 'O': 'E',
					  dev->opt.stopb);
}

static int aivserial_proc_open(struct inode *inode, struct file *filp)
{
	return single_open(filp, aivserial_data_show,
			           container_of(inode, struct proc_inode, vfs_inode)->pde->data);
}

static struct file_operations aivserial_proc_fops = {
	.owner = THIS_MODULE,
	.open = aivserial_proc_open,
	.release = single_release,
	.read = seq_read,
	.llseek = seq_lseek
};

static int __init aivserial_init(void)
{
	int ret;
	dev_t dev;

	if (aivserial_major) {
		dev = MKDEV(aivserial_major, aivserial_minor);
		ret = register_chrdev_region(dev, aivserial_nr_devs, AI_VSERIAL_NAME);
	} else {
		ret = alloc_chrdev_region(&dev, aivserial_minor,
				                  aivserial_nr_devs, AI_VSERIAL_NAME);
		aivserial_major = MAJOR(dev);
	}
	if (ret < 0) {
		printk("register_chrdev_region failed!\n");
		goto reg_err;
	}

	cdev_init(&aivserial_dev.cdev, &aivserial_fops);
	aivserial_dev.cdev.owner = THIS_MODULE;
	aivserial_dev.baud = 115200;
	aivserial_dev.opt.datab = 8;
	aivserial_dev.opt.parity = 0;
	aivserial_dev.opt.stopb = 1;

	ret = cdev_add(&aivserial_dev.cdev, dev, aivserial_nr_devs);
	if (ret) {
		printk("cdev_add failed\n");
		goto cdev_add_err;
	}

	aivserial_dev.pdir = proc_mkdir("aivserial", NULL);
	if (!aivserial_dev.pdir)
		goto proc_mkdir_err;
	aivserial_dev.pdat = proc_create_data("info", 0, aivserial_dev.pdir,
			                              &aivserial_proc_fops, &aivserial_dev);
	if (!aivserial_dev.pdat)
		goto proc_create_data_err;

	init_waitqueue_head(&aivserial_dev.rwqh);
	init_waitqueue_head(&aivserial_dev.wwqh);

	printk("aivserial_init success!\n");
	return 0;

proc_create_data_err:
	remove_proc_entry("aivserial", NULL);
proc_mkdir_err:
	cdev_del(&aivserial_dev.cdev);
cdev_add_err:
	unregister_chrdev_region(dev, aivserial_nr_devs);
reg_err:
	return ret;
}

static void __exit aivserial_exit(void)
{
	dev_t dev;

	dev = MKDEV(aivserial_major, aivserial_minor);

	remove_proc_entry("info", aivserial_dev.pdir);
	remove_proc_entry("aivserial", NULL);
	cdev_del(&aivserial_dev.cdev);
	unregister_chrdev_region(dev, aivserial_nr_devs);
	printk("aivserial_exit success!\n");
}

module_init(aivserial_init);
module_exit(aivserial_exit);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("takeno");
MODULE_DESCRIPTION("aivserial by myself");
