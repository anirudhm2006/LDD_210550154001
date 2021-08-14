#define DRIVER_NAME "synch_completion"
#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/semaphore.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/delay.h>

