/*
 * hello-1.c - Starting for kernel module example
*/

#include <linux/module.h>   /* This header need for all modules */
#include <linux/printk.h>   /* Using for pr_info() */

int init_module(){
    pr_info("Hello Word 1.\n");

    /* Done nothing here */
    return 0;
}

void cleanup_module(){
    pr_info("Clean up module - Bye Hello Word 1.\n");

    /* Done nothing here */
}

MODULE_LICENSE("GPL");