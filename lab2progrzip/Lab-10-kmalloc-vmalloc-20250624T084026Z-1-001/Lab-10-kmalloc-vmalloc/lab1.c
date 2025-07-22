#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <linux/uaccess.h>
#include <linux/vmalloc.h>

     char *kmalloc_ptr;
    char *vmalloc_ptr;
static int __init task_details_lkm_init(void) {


    printk(KERN_INFO "Initializing memory allocation LKM...\n");

    // Allocate memory using kmalloc
    kmalloc_ptr = kmalloc(1024, GFP_KERNEL); // Allocate 1KB of memory
    if (!kmalloc_ptr) {
        printk(KERN_ERR "Failed to allocate memory using kmalloc\n");
        return -ENOMEM;
    }

    // Allocate memory using vmalloc
    vmalloc_ptr = vmalloc(4096); // Allocate 4KB of memory using vmalloc
    if (!vmalloc_ptr) {
        printk(KERN_ERR "Failed to allocate memory using vmalloc\n");
        kfree(kmalloc_ptr); // Release previously allocated kmalloc memory
        return -ENOMEM;
    }

    printk(KERN_INFO "Memory allocation using kmalloc and vmalloc successful\n");
    

    return 0; // Module loaded successfully
}

static void __exit task_details_lkm_exit(void) {
    // Release the allocated memory
    kfree(kmalloc_ptr);
    vfree(vmalloc_ptr);
    printk(KERN_INFO "Exiting memory allocation LKM...\n");
}

module_init(task_details_lkm_init);
module_exit(task_details_lkm_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("LKM for printing task details in a proc file");

