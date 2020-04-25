DRV_NAME = aispinlock
APP_NAME = test_aispinlock

KERNERL_DIR = /lib/modules/$(shell uname -r)/build
PWD = $(shell pwd)
CC = gcc

ifeq ($(KERNELRELEASE), )
all:
	$(MAKE) -C $(KERNERL_DIR) M=$(PWD) modules
	$(CC) -static -o $(APP_NAME) $(APP_NAME).c

clean:
	$(MAKE) -C $(KERNERL_DIR) M=$(PWD) clean
	-rm $(APP_NAME)
aiclean:
	-rm *.o *.order *.symvers
	-rm *.mod.c

else
	obj-m += $(DRV_NAME).o
endif
