#include<linux/module.h>
#include<linux/moduleparam.h>

MODULE_LICENSE("GPL");
int type=1;

static int add(int a,int b);

static int __init hello_init(void)
{
  printk("the module type is %d\n",type);
  printk("Hello World\n");
  return 0;
}

static int add(int a,int b)
{
  printk("inside Add function\n");
  return (a+b);
}
EXPORT_SYMBOL_GPL(add);

static void __exit hello_exit(void)
{
  printk("Cleanup module, the module type is %d\n",type);
  printk("Goodbye\n");
}

module_init(hello_init);
module_exit(hello_exit);
