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
ssize_t NAME_write(struct file* filp, const char __user *ubuf, size_t count, loff_t *offp);
ssize_t NAME_read(struct file* filp, char __user *ubuf, size_t count, loff_t *offp);

//operations that driver provides
static struct file_operations fops =
{
	.owner  =  THIS_MODULE,
	.open   =  NAME_open,
	.read   =  NAME_read,
	.write  =  NAME_write,
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

ssize_t NAME_read(struct file* filp, char __user *ubuf, size_t count, loff_t *offp)
{
  char kbuf[100] = "I am sending from kernel buffer";
  int result;
  ssize_t retval;
  result=copy_to_user(ubuf,kbuf,sizeof(kbuf));

  if(result==0)
  {
    printk(KERN_ALERT "Copy to user space is successfully written: %d\n",sizeof(kbuf));
    return sizeof(kbuf);
  }
  else
  {
    printk(KERN_ALERT "Error writing data to user\n");
    retval = -EFAULT;
    return retval;
  }
}

ssize_t NAME_write(struct file* filp, const char __user *ubuf, size_t count, loff_t *offp)
{
  char kbuf[100];
  int result;
  ssize_t retval;

  result=copy_from_user(kbuf,ubuf,count);

  if(result==0)
  {
    printk(KERN_ALERT "Message from the user.....\n: %s\n",kbuf);
    printk(KERN_ALERT "\n%d bytes of data successfully written\n",count);
    return count;
  }
  else
  {
    printk(KERN_ALERT "Error writing data\n");
    retval = -EFAULT;
    return retval;
  }
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
MODULE_DESCRIPTION("Q2 Char Device Drivers open,close,read and write");
