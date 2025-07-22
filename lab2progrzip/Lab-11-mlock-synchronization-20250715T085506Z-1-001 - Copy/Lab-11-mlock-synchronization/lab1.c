#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kthread.h> // Required for kernel threads
#include <linux/delay.h>  // Required for msleep
#include <linux/mutex.h>  // Required for mutex

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("LKM with Mutex Synchronization");

static DEFINE_MUTEX(counter_mutex); // Define a mutex

static int shared_counter = 0;

// Thread function that increments the shared counter
static int increment_thread(void *data) {
    int i;
    for (i = 0; i < 5; i++) {
        mutex_lock(&counter_mutex); // Acquire the mutex

        shared_counter++; // Increment the shared counter
        printk(KERN_INFO "Incremented: %d\n", shared_counter);

        mutex_unlock(&counter_mutex); // Release the mutex

        msleep(1000); // Sleep for 1 second
    }
    return 0;
}

static int __init mutex_example_init(void) {
    printk(KERN_INFO "Initializing Mutex Example LKM...\n");

    // Create and start two kernel threads
    kthread_run(increment_thread, NULL, "thread1");
    kthread_run(increment_thread, NULL, "thread2");

    return 0;
}

static void __exit mutex_example_exit(void) {
    printk(KERN_INFO "Exiting Mutex Example LKM...\n");
}

module_init(mutex_example_init);
module_exit(mutex_example_exit);

