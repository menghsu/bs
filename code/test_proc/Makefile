ifneq ($(KERNELRELEASE),)
	procfs-objs := test_procfs.o
	obj-m := test_procfs.o
else
	K_VER ?= $(shell uname -r)
	K_DIR := /lib/modules/$(K_VER)/build
	M_DIR := $(shell pwd)
all:
	make -C $(K_DIR) M=$(M_DIR)
clean:
	rm -rf *.o *.ko *.symvers *.order *mod.c
endif
