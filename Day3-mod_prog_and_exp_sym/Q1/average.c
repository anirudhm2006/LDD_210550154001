#include<linux/module.h>
#include<linux/moduleparam.h>
#include<linux/init.h>
#include "header.h"

MODULE_LICENSE("GPL");

static int add(int a,int b);
int a_test=10, b_test=20;

static int __init hello_init(void)
{
  int Average;
  printk("In init module, the module parameter is %d\n",a_test);
  printk("Hello World\n");
  Average = add(a_test,b_test)/2;
  printk("The average is %d\n",Average);
  return 0;
}

static void __exit hello_exit(void)
{
  printk("Cleanup module, the module type is %d\n",a_test);
  printk("Goodbye\n");
}

module_init(hello_init);
module_exit(hello_exit);
