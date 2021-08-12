#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>

static int intvar = 10;

module_param(intvar, int, S_IRUGO);

static int __init param_init(void)
{
  printk("We are in init function\n");
  printk("The value of intvar is: %d\n",intvar);
  return 0;
}

static void __exit param_exit(void)
{
  printk("Goodbye\n");
}

module_init(param_init);
module_exit(param_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ANIRUDH");
MODULE_DESCRIPTION("Module programming assignment Q2");
