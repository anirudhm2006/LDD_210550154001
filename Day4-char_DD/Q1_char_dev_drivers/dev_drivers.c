#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>

#define NAME MyCharDevice


static int __init CharDevice_init(void);
static void __exit CharDevice_exit(void);
//Function prototypes
static int NAME_open(struct inode *inode,struct file *file);
static int NAME_release(struct inode *inode,struct file *file);

//operations that driver provides
static struct file_operations fops =
{
	.owner  =  THIS_MODULE,
	.open   =  NAME_open,
	//.read   =  NAME_read,
	//.write  =  NAME_write,
	.release=  NAME_release,
};

//structure for a character driver
static struct cdev *my_cdev;

//init module
static int __init CharDevice_init(void)
{
	int result;
	int MAJOR,MINOR;
	dev_t Mydev;
	Mydev = MKDEV(255,0);//creating device number
	MAJOR=MAJOR(Mydev);
	MINOR=MINOR(Mydev);
	printk("\n MAJOR NO. is %d.... MINOR NO. is %d\n",MAJOR,MINOR);
	result=register_chrdev_region(Mydev,1,"MyCharDevice");//register device region
	if(result<0)
	{
	  printk("\nThe region requested is not obtainable\n");
	  return (-1);
	}
	
	my_cdev = cdev_alloc();//allocate memory to char device structure
	my_cdev->ops = &fops;//link for file operations to the char device
	
	result=cdev_add(my_cdev,Mydev,1);//notifythe kernel about the new device
	if(result<0)
	{
	  printk("\n The char device has not been created\n");
	  unregister_chrdev_region(Mydev,1);
	  return (-1);
	}
	return 0;
	
}

//cleanup module
static void __exit CharDevice_exit(void)
{
	dev_t Mydev;
	int MAJOR,MINOR;
	Mydev=MKDEV(255,0);
	MAJOR=MAJOR(Mydev);
	MINOR=MINOR(Mydev);
	printk("\n MAJOR NO. is %d.... MINOR NO. is %d\n",MAJOR,MINOR);
	unregister_chrdev_region(Mydev,1);//unregister device region
	cdev_del(my_cdev);
	printk("\n unregistered the stuff that was allocated .....Goodbye for ever......\n");
	return;
}


//open system call
int NAME_open(struct inode *inode, struct file *file)
{
	printk("\n This is kernel OPEN call.....\n");
	return 0;
}

//close system call
int NAME_release(struct inode *inode, struct file *file)
{
	printk("\n This is kernel CLOSE call.....\n");
	return 0;
}

//MACROS
module_init(CharDevice_init);
module_exit(CharDevice_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ANIRUDH");
MODULE_DESCRIPTION("Q1 Char Device Drivers open and close");