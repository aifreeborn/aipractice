ifeq ($(KERNELRELEASE), )
KERNEL_DIR ?= /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

modules:
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) modules

clean:
	rm -rf *.o .*.cmd *.mod.* modules.order Module.symvers .tmp_versions

clobber : clean
	-rm *.ko
else
obj-m := aivserial.o
endif
