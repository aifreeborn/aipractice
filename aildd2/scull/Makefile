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
	rm -rf *.o modules.order Module.symvers *.mod.* .tmp_versions .*.cmd

clobber: clean
	rm *.ko
else
	scull-objs := main.o pipe.o
	obj-m := scull.o
endif
