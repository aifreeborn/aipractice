#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/types.h>
#include <linux/moduleparam.h>
#include <linux/slab.h>
#include <linux/errno.h>
#include <linux/semaphore.h>
#include <asm/uaccess.h>
#include "scull.h"

int scull_major = SCULL_MAJOR;
int scull_minor = 0;
int scull_nr_devs = SCULL_NR_DEVS;
int scull_quantum = SCULL_QUANTUM;
int scull_qset = SCULL_QSET;
struct scull_dev *scull_devices;

module_param(scull_major, int, S_IRUGO);
module_param(scull_minor, int, S_IRUGO);
module_param(scull_nr_devs, int, S_IRUGO);
module_param(scull_quantum, int, S_IRUGO);
module_param(scull_qset, int, S_IRUGO);


static int scull_trim(struct scull_dev *dev)
{
	struct scull_qset *next, *dptr;
	int qset = dev->qset;
	int i;

	for (dptr = dev->data; dptr; dptr = next) {
		if (dptr->data) {
			for (i = 0; i < qset; i++)
				kfree(dptr->data[i]);
			kfree(dptr->data);
			dptr->data = NULL;
		}
		next = dptr->next;
		kfree(dptr);
	}
	dev->size = 0;
	dev->quantum = scull_quantum;
	dev->qset = scull_qset;
	dev->data = NULL;
	return 0;
}

static int scull_open(struct inode *inode, struct file *filep)
{
	struct scull_dev *dev = NULL;

	dev = container_of(inode->i_cdev, struct scull_dev, cdev);
	filep->private_data = dev;

	if ((filep->f_flags & O_ACCMODE) == O_WRONLY) {
		if (down_interruptible(&dev->sem))
			return -ERESTARTSYS;
		scull_trim(dev);
		up(&dev->sem);
	}

	printk(KERN_INFO "scull_open success.\n");
	return 0;
}

static int scull_release(struct inode *inode, struct file *filep)
{
	printk(KERN_INFO "scull_release success.\n");
	return 0;
}

static struct scull_qset *scull_follow(struct scull_dev *dev, int n)
{
	struct scull_qset *qs = dev->data;

	if (!qs) {
		qs = dev->data = kmalloc(sizeof(struct scull_qset), GFP_KERNEL);
		if (qs == NULL)
			return NULL;
		memset(qs, 0, sizeof(struct scull_qset));
	}

	while (n--) {
		if (!qs->next) {
			qs->next = kmalloc(sizeof(struct scull_qset), GFP_KERNEL);
			if (qs->next == NULL)
				return NULL;
			memset(qs->next, 0, sizeof(struct scull_qset));
		}
		qs = qs->next;
	}
	return qs;
}

static ssize_t scull_read(struct file *filep, char __user *buff,
		           size_t count, loff_t *offp)
{
	struct scull_dev *dev = filep->private_data;
	struct scull_qset *dptr;
	int quantum = dev->quantum;
	int qset = dev->qset;
	int item_size = quantum * qset;
	int item, s_pos, q_pos, rest;
	ssize_t retval = 0;

	if (down_interruptible(&dev->sem))
		return -ERESTARTSYS;
	if (*offp >= dev->size)
		goto out;
	if (*offp + count > dev->size)
		count = dev->size - *offp;

	item = (long)*offp / item_size;
	rest = (long)*offp % item_size;
	s_pos = rest / quantum;
	q_pos = rest % quantum;

	dptr = scull_follow(dev, item);
	if (dptr == NULL || !dptr->data || !dptr->data[s_pos])
		goto out;

	if (count > quantum - q_pos)
		count = quantum - q_pos;
	if (copy_to_user(buff, dptr->data[s_pos] + q_pos, count)) {
		retval = -EFAULT;
		goto out;
	}
	*offp += count;
	retval = count;

out:
	up(&dev->sem);
	return retval;
}

static ssize_t scull_write(struct file *filep, const char __user *buff,
		            size_t count, loff_t *offp)
{
	struct scull_dev *dev = filep->private_data;
	struct scull_qset *dptr = NULL;
	int quantum = dev->quantum;
	int qset = dev->qset;
	int item_size = quantum * qset;
	int item, s_pos, q_pos, rest;
	ssize_t retval = -ENOMEM;

	if (down_interruptible(&dev->sem))
		return -ERESTARTSYS;

	item = (long)*offp / item_size;
	rest = (long)*offp % item_size;
	s_pos = rest / quantum;
	q_pos = rest % quantum;

	dptr = scull_follow(dev, item);
	if (dptr == NULL)
		goto out;
	if (!dptr->data) {
		dptr->data = kmalloc(qset * sizeof(char *), GFP_KERNEL);
		if (!dptr->data)
			goto out;
		memset(dptr->data, 0, qset * sizeof(char *));
	}
	if (!dptr->data[s_pos]) {
		dptr->data[s_pos] = kmalloc(quantum, GFP_KERNEL);
		if (!dptr->data[s_pos])
			goto out;
	}

	if (count > quantum - q_pos)
		count = quantum - q_pos;
	if (copy_from_user(dptr->data[s_pos] + q_pos, buff, count)) {
		retval = -EFAULT;
		goto out;
	}
	*offp += count;
	retval = count;

	if (dev->size < *offp)
		dev->size = *offp;

out:
	up(&dev->sem);
	return retval;
}

static long scull_ioctl(struct file *filep, unsigned int cmd, unsigned long arg)
{

	return 0;
}

static loff_t scull_llseek(struct file *filep, loff_t off, int whence)
{

	return 0;
}

struct file_operations scull_fops = {
	.owner = THIS_MODULE,
	.llseek = scull_llseek,
	.read = scull_read,
	.write = scull_write,
	.unlocked_ioctl = scull_ioctl,
	.open = scull_open,
	.release = scull_release,
};

/* set up the char_dev structure for this device */
static void scull_setup_cdev(struct scull_dev *dev, int index)
{
	int err;
	dev_t devno = MKDEV(scull_major, scull_minor + index);

	cdev_init(&dev->cdev, &scull_fops);
	dev->cdev.owner = THIS_MODULE;
	dev->cdev.ops = &scull_fops;
	err = cdev_add(&dev->cdev, devno, 1);
	if (err)
		printk(KERN_NOTICE "Error %d adding scull%d\n", err, index);
}

static void scull_cleanup_module(void)
{
	int i;
	dev_t devno = MKDEV(scull_major, scull_minor);

	if (scull_devices) {
		for (i = 0; i < scull_nr_devs; i++) {
			scull_trim(scull_devices + i);
			cdev_del(&scull_devices[i].cdev);
		}
		kfree(scull_devices);
	}
	unregister_chrdev_region(devno, scull_nr_devs);
}

static int __init scull_init(void)
{
	int result, i;
	dev_t dev = 0;

	if (scull_major) {
		dev = MKDEV(scull_major, scull_minor);
		result = register_chrdev_region(dev, scull_minor, "scull");
	} else {
		result = alloc_chrdev_region(&dev, scull_minor,
				                     scull_nr_devs, "scull");
		scull_major = MAJOR(dev);
	}
	if (result < 0) {
		printk(KERN_WARNING "scull: can't get major %d\n", scull_major);
		return result;
	}

	scull_devices = kmalloc(scull_nr_devs * sizeof(struct scull_dev), GFP_KERNEL);
	if (!scull_devices) {
		result = -ENOMEM;
		goto fail;
	}
	memset(scull_devices, 0, scull_nr_devs * sizeof(struct scull_dev));

	/* Initialize echo device */
	for (i = 0; i < scull_nr_devs; i++) {
		scull_devices[i].quantum = scull_quantum;
		scull_devices[i].qset = scull_qset;
		sema_init(&scull_devices[i].sem, 1);
		scull_setup_cdev(&scull_devices[i], i);
	}

	printk(KERN_ALERT "hello scull_init\n");
	return 0;
fail:
	scull_cleanup_module();
	return result;
}

static void __exit scull_exit(void)
{
	scull_cleanup_module();
	printk(KERN_ALERT "goodbye scull_exit\n");
}

module_init(scull_init);
module_exit(scull_exit);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("takeno");
