obj-m := netlink_kern.o
KERNELBUILD := /lib/modules/`uname -r`/build
default:
	make -C $(KERNELBUILD) M=$(shell pwd) modules
	gcc -o client client.c
clean:
	rm -rf *.o .depend .*.cmd *.ko *.mod.c .tmp_versions *.symvers .*.d *.unsigned *.order client
