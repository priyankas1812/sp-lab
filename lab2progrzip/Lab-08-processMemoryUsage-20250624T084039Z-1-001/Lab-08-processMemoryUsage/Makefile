
ifneq	($(KERNELRELEASE),)
obj-m	:= mem1.o 

else
KDIR	:= /lib/modules/$(shell uname -r)/build
PWD	:= $(shell pwd)
default:	
	$(MAKE) HOSTCC=x86_64-linux-gnu-gcc-11 CC=x86_64-linux-gnu-gcc-11 -C $(KDIR) M=$(PWD) modules 
	rm -r -f .tmp_versions *.mod.c .*.cmd *.o *.symvers 

endif
