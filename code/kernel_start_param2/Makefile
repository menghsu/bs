#for Cross-compile
#KERNELDIR= 
#INSTALLDIR := 
#CROSS_COMPILE = arm-none-linux-gnueabi-
#ARCH = arm

#for Local compile
KERNELDIR = /lib/modules/$(shell uname -r)/build
ARCH = x86
CROSS_COMPILE = 

PWD := $(shell pwd)

MODULE_NAME = hello_linux


obj-m := $(MODULE_NAME).o

.PHONY: modules modules_install clean

modules:
	ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) $(MAKE) -C $(KERNELDIR) M=$(PWD) modules

modules_install:
	sudo cp $(MODULE_NAME).ko $(INSTALLDIR)

clean:
	@rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions *.symvers *.order .*.o.d
