#include "spinlock.h"

#define LOCK 0
#define UNLOCK 1
#define MINORS 1

#define DELAY 3000
//struct tasklet_struct spinlock_tasklet;
spinlock_t slock;
int major;
int minor=0;
dev_t devicenum;

struct cdev spinlock_cdev;
struct class *spinlock_class;
struct device *spinlock_device;

ssize_t spinlock_read(struct file *filp, char __user *ubuf, size_t count, loff_t *offp)
{
  static unsigned int fake_val=20;

  spin_lock(&slock);
  printk("Inside Read function\n");
  mdelay(DELAY);
  fake_val++;
  copy_to_user(ubuf,&fake_val,sizeof(fake_val));
  spin_unlock(&slock);
  return sizeof(fake_val);
  
  }

  struct file_operations spinlock_fops = {

    .owner = THIS_MODULE,
    .read = spinlock_read
};

static int __init spinlock_init(void)
{
  printk("Inside init function\n");
  alloc_chrdev_region(&devicenum,minor,MINORS,DRIVER_NAME);
  major = MAJOR(devicenum);
  printk("Major Number = %d\n",major);
  printk("MAJOR\n");
  cdev_init(&spinlock_cdev,&spinlock_fops);
  cdev_add(&spinlock_cdev,devicenum,1);
  spinlock_class = class_create(THIS_MODULE,DRIVER_NAME);
  spinlock_device = device_create(spinlock_class,NULL,devicenum,NULL,"my_sample_cdev");
  spin_lock_init(&slock);
  return 0;
}

static void __exit spinlock_exit(void)
{
  printk("Inside exit function\n");
  device_destroy(spinlock_class,devicenum);
  class_destroy(spinlock_class);
  cdev_del(&spinlock_cdev);
  unregister_chrdev_region(devicenum,MINORS);
}

module_init(spinlock_init);
module_exit(spinlock_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ANIRUDH");
MODULE_DESCRIPTION("Sync Spinlock program");


