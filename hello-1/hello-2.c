/*
 *  hello-2.c - Demonstrating the module_init() and module_exit() macros.
 *  
 */

#include <linux/init.h>     /* Need for macros usage */
#include <linux/module.h>   /* All module needed */
#include <linux/printk.h>   /* Need for pr_info() */

static int __init hello_2_init(void)
{
    pr_info("Hellp, word 2\n");
    return 0;
}

static void __exit hello_2_exit(void)
{
    pr_info("Goodbye work 2\n");
}

module_init(hello_2_init);
module_exit(hello_2_exit);

MODULE_LICENSE("GPL");