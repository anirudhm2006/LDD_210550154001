#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>

static char* charvar;
static int num1,num2;

module_param(charvar,charp,S_IRUGO);
module_param(num1,int,S_IRUGO);
module_param(num2,int,S_IRUGO);

int add(int num1, int num2)
{
  return (num1 + num2);
}

int sub(int num1, int num2)
{
  return (num1 - num2);
}

int mul(int num1, int num2)
{
  return (num1 * num2);
}

int div(int num1, int num2)
{
  return (num1 / num2);
}

static int __init param_init(void)
{
  printk("In init function\n");
  printk("value of int argument1 = %d\n",num1);
  printk("value of int argument2 = %d\n",num2);
  printk("value of char argument = %s\n",charvar);
  
  if(*charvar=='a')
  {
    printk("addition = %d\n",add(num1,num2));
  }

  if(*charvar=='s')
  {
    printk("subtraction = %d\n",sub(num1,num2));
  }

  if(*charvar=='m')
  {
    printk("multiplication = %d\n",mul(num1,num2));
  }  
  
  if(*charvar=='d')
  {
    printk("division = %d\n",div(num1,num2));
  }
 
  return 0;
}
static void __exit param_exit(void)
{
  printk("In exit function\n");
  printk("Goodbye\n");
}

module_init(param_init);
module_exit(param_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ANIRUDH");
MODULE_DESCRIPTION("Module programming assignment Q3");


