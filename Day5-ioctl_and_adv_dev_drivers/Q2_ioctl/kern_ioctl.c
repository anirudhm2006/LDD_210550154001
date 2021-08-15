#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/ioctl.h>

#include "ioctl.h"

#define NAME MyCharDevice

int ouput;

static int __init CharDevice_init(void);
static void __exit CharDevice_exit(void);

//Function prototypes
static int NAME_open(struct inode *inode,struct file *file);
static int NAME_release(struct inode *inode,struct file *file);
ssize_t NAME_write(struct file *filp, const char __user *ubuf, size_t count, loff_t *offp);
ssize_t NAME_read(struct file *filp, char __user *ubuf, size_t count, loff_t *offp);
static long NAME_ioctl(struct file *filp, unsigned int cmd, unsigned long arg);


//operations that driver provides
static struct file_operations fops =
{
	.owner  =  THIS_MODULE,
	.open   =  NAME_open,
	.read   =  NAME_read,
	.write  =  NAME_write,
	.release=  NAME_release,
	.unlocked_ioctl = NAME_ioctl,
};

//structure data
static struct data {
	int n1;
	int n2;
	int oper;
};

//structure for a character driver
static struct cdev *my_cdev;

//init module
static int __init CharDevice_init(void)
{
	int result;
	int MAJOR,MINOR;
	dev_t Mydev;
	Mydev = MKDEV(255,0);//creating device number statistically
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

//read call
ssize_t NAME_read(struct file *filp, char __user *ubuf, size_t count, loff_t *offp)
{
	char kbuf[100] = "I am sending from kernel buffer";
	int  result;
	ssize_t retval;
	result=copy_to_user(ubuf, kbuf,sizeof(kbuf));
	if(result == 0)
	{
	  printk("copy to user space is done: %d\n",sizeof(kbuf));
	  return sizeof(kbuf);
	}
	else
	{
	printk("Error writing to user\n");
	retval = -EFAULT;
	return retval;
	}
}

//write call
ssize_t NAME_write(struct file *filp, const char __user *ubuf, size_t count, loff_t *offp)
{
	char kbuf[100];
	int  result;
	ssize_t retval;
	result=copy_from_user(kbuf, ubuf,count);
	if(result == 0)
	{
	  printk("message from user : %s\n",kbuf);
	  printk("\n%dbytes of data sucessfully written\n",count);
	  return count;
	}
	else
	{
	printk("Error writing data\n");
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

//IOCTL Functionality
static long NAME_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	char ubuf[50];
	struct data *senddata;
	printk("IOCTL Function\n");
	switch(cmd){
	            
	        case data_send:
	            senddata = (struct data *)ubuf;
	            copy_from_user(ubuf, (struct data *)arg, sizeof(struct data));
	            printk("Data from ioctl using structure....\n");
	            printk("n1 is : %d\n",senddata->n1);
	            printk("n2 is : %d\n",senddata->n2);
	            printk("oper is : %d\n",senddata->oper);
	            if(senddata->oper == 1)
	            {
	            ouput=(senddata->n1)+(senddata->n2);
	            printk("Addition is : %d\n",ouput);//printing the values in kernel
	            }
	            else if(senddata->oper==2)
	            {
	            ouput=(senddata->n1)-(senddata->n2);
	            printk("Subtraction is :%d\n",ouput);
	            }
	            else if(senddata->oper==3)
	            {
	            ouput=(senddata->n1)*(senddata->n2);
	            printk("Multiplication is :%d\n",ouput);
	            }
	            else if(senddata->oper==4)
	            {
	            ouput=(senddata->n1)/(senddata->n2);
	            printk("Division is :%d\n",ouput);
	            }
	            
	            //copy_to_user((int*)arg, &ouput, sizeof(ouput));
	            break;
	        
	        default:
	            printk("command not found\n");
	            return (-EINVAL);
	        
	        }
	           
	            return 0;
}

//MACROSs
module_init(CharDevice_init);
module_exit(CharDevice_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ANIRUDH");
MODULE_DESCRIPTION("passing a structure using IOCTL to the driver having 3 elements and perform operations of program1");




