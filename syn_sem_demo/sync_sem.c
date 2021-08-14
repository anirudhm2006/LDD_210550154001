#include "sync_sem.h"

#define LOCK 0
#define UNLOCK 1
#define MINORS 1

#define DELAY 3000
struct semaphore sample_sem;
int major;
int minor=0;
dev_t devicenum;

struct cdev sync_sem_cdev;
struct class *sync_sem_class;
struct device *sync_sem_device;

ssize_t sync_sem_read(struct file *filp, char __user *ubuf, size_t count, loff_t *offp)
{
  static unsigned int fake_val=20;
  printk("Inside Read function\n");
  
  if(down_interruptible(&sample_sem))
    return -ERESTARTSYS;

  msleep(DELAY);
  fake_val++;
  copy_to_user(ubuf,&fake_val,sizeof(fake_val));
  up(&sample_sem);
  return fake_val;
  
  }

  struct file_operations sync_sem_fops = {

    .owner = THIS_MODULE,
    .read = sync_sem_read
};

static int __init sync_sem_init(void)
{
  alloc_chrdev_region(&devicenum,minor,MINORS,DRIVER_NAME);
  major = MAJOR(devicenum);
  cdev_init(&sync_sem_cdev,&sync_sem_fops);
  cdev_add(&sync_sem_cdev,devicenum,1);
  sync_sem_class = class_create(THIS_MODULE,DRIVER_NAME);
  sync_sem_device = device_create(sync_sem_class,NULL,devicenum,NULL,"my_sample_cdev");
  sema_init(&sample_sem,UNLOCK);
  return 0;
}

static void __exit sync_sem_exit(void)
{
  printk("Inside exit function\n");
  device_destroy(sync_sem_class,devicenum);
  class_destroy(sync_sem_class);
  cdev_del(&sync_sem_cdev);
  unregister_chrdev_region(devicenum,MINORS);
}

module_init(sync_sem_init);
module_exit(sync_sem_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ANIRUDH");
MODULE_DESCRIPTION("Sync Sem program");

