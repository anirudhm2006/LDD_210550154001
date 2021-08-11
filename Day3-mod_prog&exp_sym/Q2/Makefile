##ifneq($(KERNELRELEASE).)
	obj-m:= average.o add.o #./average/average.o

##else
	KDIR=/lib/modules/$(shell uname -r)/build
	PWD:= $(shell pwd)

default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
	rm -rf /lib/modules/$(shell uname -r)/extra/*
##endif

install:
	$(MAKE) -C $(KDIR) M=$(PWD) modules_install
	depmod -a
