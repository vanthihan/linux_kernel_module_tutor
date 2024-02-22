/*
 *  chardev.c - Creates a read-only char device that says how many times
 *  we have read from the dev file
 */

#include <linux/atomic.h>
#include <linux/cdev.h>
#include <linux/delay.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h> /* for sprintf() */
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/types.h>
#include <linux/uaccess.h> /* for get_user and put_user */
#include <linux/version.h>

#include <asm/errno.h>

/* Function prototypes */
static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char __user *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char __user *, size_t, loff_t *);

#define SUCCESS 0
#define DEVICE_NAME "thiscdev"
#define BUF_LEN 80  /* Max length of the message from the device */
#define INIT_VALUE 0

/* Global variables */
static int major = INIT_VALUE; /* Major number assign to device driver */

enum {
    CDEV_NOT_USED       = 0,
    CDEV_EXCLUSIVE_OPEN = 1,
};

/* Used to prevent multiple access to device */
static atomic_t already_open = ATOMIC_INIT(CDEV_NOT_USED);

static char msg[BUF_LEN + 1];

static struct class *cls;

static struct file_operations chardev_fops = {
    .read = device_read,
    .write = device_write,
    .open = device_open,
    .release = device_release,
};


static int __init chardev_init(void){
    major = register_chrdev(0, DEVICE_NAME, &chardev_fops);

    if(major < 0){
        pr_alert("Registering char device failed with %d\n", major);
        return major;
    }

    pr_info("Newly registered char device has major number is %d\n", major);

#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 4, 0)
    cls = class_create(DEVICE_NAME);
#else
    cls = class_create(THIS_MODULE, DEVICE_NAME);
#endif

    device_create(cls, NULL, MKDEV(major, 0), NULL, DEVICE_NAME);

    pr_info("Device created on /dev/%s\n", DEVICE_NAME);

    return SUCCESS;
}

static void __exit chardev_exit(void){
    pr_info("Existing /dev/%s ....\n", DEVICE_NAME);

    device_destroy(cls, MKDEV(major, 0));
    class_destroy(cls);

    /* Unregister the device */
    unregister_chrdev(major, DEVICE_NAME);
    pr_info("Existed\n");
}

/* Methods */

/*  Called when a process tries to open this device file 
 *  Ex: "sudo cat /dev/chardev/"
 */
static int device_open(struct inode *inode, struct file *file){
    static int counter = 0;

    if(atomic_cmpxchg(&already_open, CDEV_NOT_USED, CDEV_EXCLUSIVE_OPEN))
        return -EBUSY;

    sprintf(msg, "You seem to access this amaze device %d time :)\n", counter++);   //Load string into msg array

    try_module_get(THIS_MODULE); /* Increment the reference count of current module */

    return SUCCESS;
}


/*  Called when process closes the device file */
static int device_release(struct inode *inode, struct file *file){
    /* When this one call, next caller to open this device and be allowed */
    atomic_set(&already_open, CDEV_NOT_USED);

    /* Decrement the usage count, or else once you opened the file, you will never get rid of the module. */
    module_put(THIS_MODULE);

    return SUCCESS;
}

/*  Called when device is opened and process want to read from it. */
static ssize_t device_read(struct file *file, char __user *buffer, size_t length, loff_t *offset){
    int bytes_read = 0;     //Number of bytes actually written to the buffer
    const char *msg_ptr = msg;

    if(!*(msg_ptr + *offset)) {     //At end of the msg
        *offset = 0;    //Reset the offset
        return 0;   //Signify end of file
    }

    msg_ptr += *offset;

    //Actually put the data into the buffer
    while(length && *msg_ptr){
        /* The buffer is in the user data segment, not the kernel
        * segment so "*" assignment won't work. We have to use
        * put_user which copies data from the kernel data segment to
        * the user data segment.
        */

       put_user(*(msg_ptr++), buffer++);
       length--;
       bytes_read++;
    }

    offset += bytes_read;

    //Most read function return number of bytes read
    return bytes_read;
}

/* Called when a process writes to dev file: echo "hi" > /dev/hello */
static ssize_t device_write(struct file *filp, const char __user *buff, size_t length, loff_t *off){
    pr_alert("Sorry, this operation is not supported.\n");
    return -EINVAL;
}

module_init(chardev_init);
module_exit(chardev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Grasshopper");
MODULE_DESCRIPTION("Example for on device module");
