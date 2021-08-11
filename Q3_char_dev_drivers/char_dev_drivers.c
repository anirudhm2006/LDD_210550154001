#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>

static int __init CharDevice_init(void);
static void __exit CharDevice_exit(void);

dev_t dev=0;

//init module
static int __init CharDevice_init(void)
{
	int result;
	result=alloc_chrdev_region(&dev,0,1,"MyCharDevice");//dynamically allocate major and minor numbers
	if(result<0)
	{
	  printk("\nCannot allocate major and minor numbers to the device\n");
	  return (-1);
	}
	
	printk(KERN_ALERT "Major number = %d, Minor number = %d\n",MAJOR(dev),MINOR(dev));
        printk(KERN_ALERT "Device inserted successfully");
	return 0;	
}

//cleanup module
static void __exit CharDevice_exit(void)
{
	unregister_chrdev_region(dev,1);//unregister device region	
	printk("\n unregistered the driver that was allocated ,kernel removed successfully.....Goodbye......\n");
	return;
}

//MACROS
module_init(CharDevice_init);
module_exit(CharDevice_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ANIRUDH");
MODULE_DESCRIPTION("Q3 Char Device Drivers allocate major and minor numbers dynamically");

