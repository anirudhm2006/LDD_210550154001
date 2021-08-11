#include <linux/init.h>
#include <linux/module.h>

static int hello_init(void)
{
	printk("Hello World\n");
	return 0;
}

static void hello_cleanup(void)
{
	printk("Goodbye\n");
}

module_init(hello_init);
module_exit(hello_cleanup);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ANIRUDH");
MODULE_DESCRIPTION("A simple Hello WOrld LKM!");

