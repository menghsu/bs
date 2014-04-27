MODULE_NAME=module_param.o
ifneq ($(KERNELRELEASE),)
	procfs-objs := $(MODULE_NAME)
	obj-m := $(MODULE_NAME)
else
	K_VER ?= $(shell uname -r)
	K_DIR := /lib/modules/$(K_VER)/build
	M_DIR := $(shell pwd)
all:
	make -C $(K_DIR) M=$(M_DIR)
clean:
	rm -rf *.o *.ko *.symvers *.order *mod.c *~ *.out
endif
