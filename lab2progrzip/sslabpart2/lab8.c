#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>


#include<linux/signal.h>
#include<linux/pid_namespace.h>
#include<linux/cdev.h>
#include<linux/proc_fs.h>
#include<linux/slab.h>


static int __init memory_usage_init(void) {
    struct task_struct *task;
    
    printk(KERN_INFO "Process Memory Usage:\n");
    printk(KERN_INFO "PID\tRSS (bytes)\tVSZ (bytes)\tCMD\n");
    
    for_each_process(task) {
        struct mm_struct *mm = get_task_mm(task);
        if (mm != NULL) {
            unsigned long rss = get_mm_rss(mm);
            unsigned long vsz = mm->total_vm << (PAGE_SHIFT - 10); // Convert pages to bytes
            printk(KERN_INFO "%d\t%lu\t%lu\t%s\n", task->pid, rss, vsz, task->comm);
            mmput(mm);
        }
    }
    
    return 0;
}

static void __exit memory_usage_exit(void) {
    printk(KERN_INFO "Memory usage module unloaded\n");
}

module_init(memory_usage_init);
module_exit(memory_usage_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Memory Usage Kernel Module");
MODULE_AUTHOR("Your Name");

