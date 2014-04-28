ifneq ($(KERNELRELEASE),)
	procfs-objs := transform.o
	obj-m := transform.o
else
	K_VER ?= $(shell uname -r)
	K_DIR := /lib/modules/$(K_VER)/build
	M_DIR := $(shell pwd)
all:
	make -C $(K_DIR) M=$(M_DIR)
	g++ -o client client.cpp
clean:
	rm -rf *.o *.ko *.symvers *.order *mod.c *~ *.out client
endif
