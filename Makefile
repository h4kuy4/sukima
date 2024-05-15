CURRENT_PATH := $(shell pwd)
LINUX_KERNEL := $(shell uname -r)
LINUX_KERNEL_PATH := ${LINUX_KERNEL_PATH}

obj-m += sukima_res.o
sukima_res-objs += sukima_dev.o sukima.o utils.o syscall_hook.o

# EXTRA_CFLAGS:= -DSILENT

all:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) modules

clean:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) clean
