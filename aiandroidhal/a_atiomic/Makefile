DRV_NAME = aiatomic
APP_NAME = test_aiatomic

KERNEL_DIR = /lib/modules/$(shell uname -r)/build
PWD = $(shell pwd)
CC = gcc

ifeq ($(KERNELRELEASE), )
all:
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) modules
	$(CC) -static -o $(APP_NAME) $(APP_NAME).c

clean:
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) clean
	-rm $(APP_NAME)

aiclean:
	-rm *.o *.order *.symvers
	-rm *.mod.c

else
	obj-m += $(DRV_NAME).o

endif
