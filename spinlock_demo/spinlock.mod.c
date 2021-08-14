#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0x1e2a3dfd, "module_layout" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0xdf5f66fb, "cdev_del" },
	{ 0x25768acf, "class_destroy" },
	{ 0xd4cb57eb, "device_destroy" },
	{ 0xeb9d30e1, "device_create" },
	{ 0xe3283a3, "__class_create" },
	{ 0xadecc241, "cdev_add" },
	{ 0xbf9f160b, "cdev_init" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0x51a910c0, "arm_copy_to_user" },
	{ 0xc5850110, "printk" },
	{ 0x8e865d3c, "arm_delay_ops" },
	{ 0xae577d60, "_raw_spin_lock" },
	{ 0xb1ad28e0, "__gnu_mcount_nc" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "A89585A1FB866C3175CA10F");
