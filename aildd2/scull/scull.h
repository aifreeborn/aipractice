#ifndef SCULL_H_
#define SCULL_H_

#include <linux/cdev.h>

#undef PDEBUG
#ifdef SCULL_DEBUG
#    ifdef __KERNEL__
#        define PDEBUG(fmt, args...) printk(KERN_DEBUG "scull: " fmt, ## args)
#    else
#        define PDEBUG(fmt, args...) fprintf(stderr, fmt, ## args)
#    endif
#else
#    define PDEBUG(fmt, args...)
#endif

#undef PDEBUGG
#define PDEBUGG(fmt, args...)

#ifndef SCULL_MAJOR
#define SCULL_MAJOR 0
#endif

#ifndef SCULL_NR_DEVS
#define SCULL_NR_DEVS 4
#endif

#ifndef SCULL_QUANTUM
#define SCULL_QUANTUM 4000
#endif

#ifndef SCULL_QSET
#define SCULL_QSET 1000
#endif

struct scull_qset {
	void **data;
	struct scull_qset *next;
};

struct scull_dev {
	struct scull_qset *data;
	int quantum;
	int qset;
	unsigned long size;
	unsigned int access_key;
	struct semaphore sem;
	struct cdev cdev;
};

#endif /* SCULL_H_ */
