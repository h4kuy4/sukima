CURRENT_PATH := $(shell pwd)
LINUX_KERNEL := $(shell uname -r)
LINUX_KERNEL_PATH := ${LINUX_KERNEL_PATH}/lib/modules/6.6.28/build/

obj-m += sumika.o
sumika-objs := sumika_dev.o

# EXTRA_CFLAGS:= -DSILENT

all:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) modules

clean:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) clean
