#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/gfp.h>
#include <linux/mm.h>
#include <asm/uaccess.h>

#define AILLSEEK_MAJOR 250
#define AILLSEEK_MINOR 0
#define AILLSEEK_DEV_CNT 1
#define AILLSEEK_NAME "aillseek"

struct aillseek_dev {
	unsigned char *buf;
	struct cdev cdev;
};

static int aillseek_major = AILLSEEK_MAJOR;
static int aillseek_minor = AILLSEEK_MINOR;
static int aillseek_nr_devs = AILLSEEK_DEV_CNT;
static struct aillseek_dev aillseek_dev;

static int aillseek_open(struct inode *inode, struct file *filp)
{
	return 0;
}

static int aillseek_release(struct inode *inode, struct file *filp)
{
	return 0;
}

static int aillseek_mmap(struct file *filp, struct vm_area_struct *vma)
{
	if (remap_pfn_range(vma, vma->vm_start, 
				        virt_to_phys(aillseek_dev.buf) >> PAGE_SHIFT,
						vma->vm_end - vma->vm_start,
						vma->vm_page_prot))
		return -EAGAIN;

	return 0;
}

static ssize_t aillseek_read(struct file *filp, char __user *buf, size_t cnt, loff_t *loff)
{
	int ret;
	size_t len = (cnt > PAGE_SIZE) ? PAGE_SIZE : cnt;

	if (*loff + len > PAGE_SIZE)
		len = PAGE_SIZE - *loff;

	ret = copy_to_user(buf, aillseek_dev.buf + *loff, len);
	*loff += len - ret;
	
	return len - ret;
}

static loff_t aillseek_llseek(struct file *filp, loff_t loff, int whence)
{
	loff_t new_pos;

	switch (whence) {
	case SEEK_SET:
		new_pos = loff;
		break;
	case SEEK_CUR:
		new_pos = filp->f_pos + loff;
		break;
	case SEEK_END:
		new_pos = PAGE_SIZE + loff;
		break;
	default:
		return -EINVAL;
	}

	if (new_pos < 0 || new_pos > PAGE_SIZE)
		return -EINVAL;
	filp->f_pos = new_pos;

	return new_pos;
}

static struct file_operations aillseek_fops = {
	.owner = THIS_MODULE,
	.open = aillseek_open,
	.release = aillseek_release,
	.mmap = aillseek_mmap,
	.read = aillseek_read,
	.llseek = aillseek_llseek
};

static int __init aillseek_init(void)
{
	int ret = -1;
	dev_t dev;
	unsigned long addr = 0;

	if (aillseek_major) {
		dev = MKDEV(aillseek_major, aillseek_minor);
		ret = register_chrdev_region(dev, aillseek_nr_devs, AILLSEEK_NAME);
	} else {
		ret = alloc_chrdev_region(&dev, aillseek_minor, aillseek_nr_devs, AILLSEEK_NAME);
		aillseek_major = MAJOR(dev);
	}
	if (ret < 0) {
		printk("register_chrdev_region fail!\n");
		goto reg_err;
	}

	cdev_init(&aillseek_dev.cdev, &aillseek_fops);
	aillseek_dev.cdev.owner = THIS_MODULE;
	ret = cdev_add(&aillseek_dev.cdev, dev, aillseek_nr_devs);
	if (ret < 0) {
		printk("cdev_add fail!\n");
		goto cdev_add_err;
	}

	addr = __get_free_page(GFP_KERNEL);
	if (!addr) {
		printk("__get_free_page failed!\n");
		goto get_free_page_err;
	}

	aillseek_dev.buf = (unsigned char *)addr;
	memset(aillseek_dev.buf, 0, PAGE_SIZE);

	printk("aillseek_init success!\n");
	return 0;

get_free_page_err:
	cdev_del(&aillseek_dev.cdev);
cdev_add_err:
	unregister_chrdev_region(dev, aillseek_nr_devs);
reg_err:
	return ret;
}

static void __exit aillseek_exit(void)
{
	dev_t dev;

	dev = MKDEV(aillseek_major, aillseek_minor);

	free_page((unsigned long)aillseek_dev.buf);
	cdev_del(&aillseek_dev.cdev);
	unregister_chrdev_region(dev, aillseek_nr_devs);
	printk("aillseek_exit success\n");
}

module_init(aillseek_init);
module_exit(aillseek_exit);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("takeno");
MODULE_DESCRIPTION("aillseek");
