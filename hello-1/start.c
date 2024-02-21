/*
 *  start.c - Illustration of multi filed modules
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

static int __init init_module_1(void)
{
    pr_info("Hello, world - This is kernel speaking\n");

    return 0;
}

module_init(init_module_1);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Grasshopper");
MODULE_DESCRIPTION("This is a test for multiple filed module");