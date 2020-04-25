#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <asm/uaccess.h>
#include <linux/sched.h>
#include <linux/poll.h>

MODULE_LICENSE("GPL");

#define DEVICE_NAME "ai_poll_select"
#define MAX_BUFFER_SZIE 20

static char buffer[MAX_BUFFER_SZIE] = {0};
static int buffer_char_count = 0;
// 等待队列
static wait_queue_head_t ai_queue;
static struct semaphore sem;

ssize_t ai_poll_select_read(struct file *fp, char __user *buf, size_t cnt, loff_t *ppos)
{
	ssize_t res = 0;

	if (buffer_char_count > 0) {
		if (down_interruptible(&sem)) {
			return -ERESTARTSYS;
		}
		if (copy_to_user(buf, buffer, buffer_char_count)) {
			return -EINVAL;
		}
		wake_up_interruptible(&ai_queue);
		res = buffer_char_count;
		buffer_char_count = 0;
		up(&sem);
	} else {
		return 0;
	}

	return res;
}

static ssize_t ai_poll_select_wirte(struct file *fp, const char __user *buf, size_t cnt, loff_t *ppos)
{
	ssize_t res = 0;

	if (down_interruptible(&sem)) {
		return -ERESTARTSYS;
	}
	wait_event_interruptible(ai_queue, buffer_char_count == 0);
	if (cnt > sizeof(buffer)) {
		cnt = sizeof(buffer);
	}
	if (copy_from_user(buffer, buf, cnt)) {
		return -EINVAL;
	}
	res = cnt;
	buffer_char_count = cnt;
	up(&sem);

	return res;
}

unsigned int ai_poll_select_poll(struct file *fp, struct poll_table_struct *wait)
{
	unsigned int mask = 0;

	if (down_interruptible(&sem)) {
		return -ERESTARTSYS;
	}
	poll_wait(fp, &ai_queue, wait);

	if (buffer_char_count > 0) {
		mask |= POLLIN | POLLRDNORM;
	}

	if (buffer_char_count == 0) {
		mask |= POLLOUT | POLLWRNORM;
	}

	up(&sem);
	return mask;
}

static struct file_operations dev_fops = {
	.owner = THIS_MODULE,
	.read = ai_poll_select_read,
	.write = ai_poll_select_wirte,
	.poll = ai_poll_select_poll
};

static struct miscdevice misc = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = DEVICE_NAME,
	.fops = &dev_fops
};

static int __init ai_demo_init(void)
{
	int ret = -1;

	ret = misc_register(&misc);
	init_waitqueue_head(&ai_queue);
	sema_init(&sem, 1);
	printk("ai_demo_init success!\n");
	return ret;
}

static void __exit ai_demo_exit(void)
{
	misc_deregister(&misc);
	printk("ai_demo_exit success\n");
}

module_init(ai_demo_init);
module_exit(ai_demo_exit);
