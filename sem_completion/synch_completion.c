#include "synch_completion.h"


#define NMINORS 1

//declaring variable of type struct completion to perform operations
struct completion synch_completion;

//declare a kernel buffer
char kbuf[100];

int major;
int minor=0;
dev_t deviceno;
struct cdev synch_completion_cdev;
struct class *synch_completion_class;
struct device *synch_completion_device;

//read call
ssize_t synch_completion_read(struct file *filp, char __user *ubuf, size_t count, loff_t *offp)
{
	int cnt,len;
	printk("In read function\n");
	
	wait_for_completion(&synch_completion);
	
	//send data to the user
	len = strlen(kbuf);
	cnt = copy_to_user(ubuf,kbuf,len);
	
	//clear the data buffer
	memset(kbuf, 0, sizeof(kbuf));
	
	//returning the no. of bytes written
	return len - cnt;
	
}

ssize_t synch_completion_write(struct file *filp, const char __user *ubuf, size_t count, loff_t *offp)
{
	int cnt;
	printk("In write function\n");
	
	//retrieve data to the user
	cnt = copy_from_user(kbuf,ubuf,count);
	
	msleep(5000); //Introducing the psuedo delay
	complete(&synch_completion);
	
	//returning the no. of bytes read
	return count - cnt;
	
}

//struct file operations
struct file_operations synch_completion_fops = 
{
	.owner = THIS_MODULE,
	.read = synch_completion_read,
	.write = synch_completion_write,
};

//INIT function
static int __init synch_completion_init(void)
{
	printk("In init function\n");
	alloc_chrdev_region(&deviceno, minor,NMINORS, DRIVER_NAME); //allocating major number dynamically
	major = MAJOR(deviceno);
	
	cdev_init(&synch_completion_cdev,&synch_completion_fops);
	cdev_add(&synch_completion_cdev, deviceno, 1);
	
	synch_completion_class = class_create(THIS_MODULE, DRIVER_NAME);
	synch_completion_device = device_create(synch_completion_class, NULL, deviceno, NULL, "sample_cdev");
	
	//Initialization of completion variable
	init_completion(&synch_completion);
	return 0;
}


//EXIT function
static void __exit synch_completion_exit(void)
{
	printk("In exit function\n");
	device_destroy(synch_completion_class, deviceno);
	class_destroy(synch_completion_class);
	
	//unregistering the driver
	cdev_del(&synch_completion_cdev);
	unregister_chrdev_region(deviceno,NMINORS);
}

module_init(synch_completion_init);
module_exit(synch_completion_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ANIRUDH");
MODULE_DESCRIPTION("Syn completions");
	
	
