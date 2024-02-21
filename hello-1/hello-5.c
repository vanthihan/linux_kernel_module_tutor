/*
 *  hello-5.c - Testing with passing argument passing to modules
*/

#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>   /* For ARRAY_SIZE() */
#include <linux/moduleparam.h>
#include <linux/printk.h>
#include <linux/stat.h>

MODULE_LICENSE("GPL");

static short int myshort = 0x01;
static int myint = 0x0A;
static long int mylong = 9999;
static char *mystring = "yeah";
static int myintarray[2] = { 1, 2 };
static int arr_argc = 0x00;

/*
    module_param(variable_name, type, permission)
    Ex: module_param(foo, int, 0000);
*/

module_param(myshort, short, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(myshort, "Description for a myshort variable");

module_param(myint, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(myint, "Description for a myint variable");

module_param(mylong, long, S_IRUSR);
MODULE_PARM_DESC(mylong, "Description for a mylong variable");

module_param(mystring, charp, 0000);
MODULE_PARM_DESC(mystring, "Description for a mystring variable");

/* module_param_array(name, type, num, perm);
* The first param is the parameter's (in this case the array's) name.
* The second param is the data type of the elements of the array.
* The third argument is a pointer to the variable that will store the number
* of elements of the array initialized by the user at module loading time.
* The fourth argument is the permission bits.
*/
module_param_array(myintarray, int, &arr_argc, 0000);
MODULE_PARM_DESC(myintarray, "An array of integers");

static int __init init_hello_5(void)
{
    int i;

    pr_info("Hello, world 5\n=============\n");
    pr_info("myshort is a short integer: %hd\n", myshort);
    pr_info("myint is an integer: %d\n", myint);
    pr_info("mylong is a long integer: %ld\n", mylong);
    pr_info("mystring is a string: %s\n", mystring);

    for (i = 0; i < ARRAY_SIZE(myintarray); i++)
        pr_info("myintarray[%d] = %d\n", i, myintarray[i]);

    pr_info("got %d arguments for myintarray.\n", arr_argc);
    return 0;

}

static void __exit cleanup_hello_5(void)
{
    pr_info("cleanup_hello_5()\n");
}


module_init(init_hello_5);
module_exit(cleanup_hello_5);

