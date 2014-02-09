obj-m := imp1_k.o
KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
MAKE := make
default:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
clean:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean
