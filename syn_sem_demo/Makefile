##ifneq($(KERNELRELEASE),)
	obj-m:=sync_sem.o

##else
	KDIR=/lib/modules/$(shell uname -r)/build/
	PWD:=$(shell pwd)

default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
	gcc -o Application Application.c

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
	rm Application

install:
	$(MAKE) -C $(KDIR) M=$(PWD) modules_install

#endif

