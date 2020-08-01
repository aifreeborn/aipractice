DEBUG = y

ifeq ($(DEBUG), y)
	DEBFLAGS = -O -g -DSCULL_DEBUG
else
	DEBFLAGS = -O2
endif

KBUILD_CFLAGS += $(DEBFLAGS)

ifeq ($(KERNELRELEASE), )
KERNELDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

.PHONY : modules clean

modules:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

clean:
	rm -rf *.o *.order *.symvers *.mod.c

clobber: clean
	rm *.ko
else
	obj-m := scull.o
endif
