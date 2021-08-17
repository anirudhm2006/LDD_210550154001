#include <linux/init.h>
#include <linux/timer.h>
#include <linux/module.h>
#include <linux/kernel.h>

static struct timer_list my_timer;

static void my_timer_callback(struct timer_list *timer)
{
  printk("%s has called (%ld)\n",__func__,jiffies);
  mod_timer(&my_timer,jiffies+msecs_to_jiffies(2000));
}

static int __init my_init(void)
{
  int ret;
  printk("%s: Timer module loaded\n",__func__);
  timer_setup(&my_timer, my_timer_callback,0);
  printk("%s: Setup timer to fire in 2 secs (%ld)\n",__func__,jiffies);
  ret = mod_timer(&my_timer,jiffies + msecs_to_jiffies(2000));
  
  if(ret)
     printk("%s: Timer firing failed\n",__func__);
  return 0;
}

static void __exit my_exit(void)
{
  int ret;
  ret = del_timer(&my_timer);
  
  if(ret)
     printk("%s: Timer is still in use...\n",__func__);

  printk("%s: Timer module unloaded\n",__func__); 
}

module_init(my_init);
module_exit(my_exit);
MODULE_AUTHOR("ANIRUDH");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Kernel Timer demonstration");
