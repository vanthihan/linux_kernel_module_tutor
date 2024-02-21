/*
 *  stop.c - Illustration of multi filed modules
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

static void __exit exit_module_2(void)
{
    pr_info("Exit module from stop.c\n");
}

module_exit(exit_module_2);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Grasshopper");
MODULE_DESCRIPTION("This is a test for multiple filed module");