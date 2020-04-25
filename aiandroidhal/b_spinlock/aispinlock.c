#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <asm/uaccess.h>
#include <asm/atomic.h>
#include <linux/delay.h>

MODULE_LICENSE("GPL");

#define DEVICE_NAME "ai_spin_lock"
static char *data = "read\n";
static char flag = 1;
static DEFINE_SPINLOCK(lock);

static ssize_t ai_spin_lock_read(struct file *filep, char __user *buf, size_t count, loff_t *ppos)
{
	int size = strlen(data);

	if (copy_to_user(buf, (void *)data, size)) {
		return -EINVAL;
	}

	if (flag) {
		flag = 0;
		if (spin_trylock(&lock)) {
			mdelay(10000);
			spin_unlock(&lock);
		} else {
			return -EBUSY;
		}

		return size;
	} else {
		flag = 1;
		return 0;
	}
}

static ssize_t ai_spin_lock_write(struct file *filep, const char __user *buf, size_t count, loff_t *ppos)
{
	char data[10] = {0};

	memset(data, 0, sizeof(data));
	if (copy_from_user(data, buf, count))
		return -EINVAL;

	if (strncmp("lock\n", data, strlen("lock\n")) == 0) {
		spin_lock(&lock);
		spin_unlock(&lock);
	} else if (strncmp("trylock\n", data, strlen("trylock\n")) == 0) {
		if (spin_trylock(&lock)) {
			printk("spin lock available.\n");
			spin_unlock(&lock);
		} else {
			printk("spin lock unavailable.\n");
			return -EBUSY;
		}
	}

	return count;
}

static struct file_operations dev_fops = {
	.owner = THIS_MODULE,
	.read = ai_spin_lock_read,
	.write = ai_spin_lock_write
};

static struct miscdevice misc = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = DEVICE_NAME,
	.fops = &dev_fops
};

static int __init ai_spin_lock_init(void)
{
	int ret = -1;

	ret = misc_register(&misc);

	printk("ai_spin_lock_init success!");
	return ret;
}

static void __exit ai_spin_lock_exit(void)
{
	misc_deregister(&misc);
	printk("ai_spin_lock_exit success!");
}

module_init(ai_spin_lock_init);
module_exit(ai_spin_lock_exit);
