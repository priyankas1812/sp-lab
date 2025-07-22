#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <linux/uaccess.h>

#define MAX_PROCESS_COUNT 100 // Maximum number of tracked processes
#define MAX_PROCESS_NAME_LENGTH 256 // Maximum process name length


struct process_info {
    pid_t pid;
    char name[MAX_PROCESS_NAME_LENGTH];
};

static struct process_info *process_info_data[MAX_PROCESS_COUNT];
static int process_info_count = 0;

static int __init task_details_lkm_init(void) {
  struct task_struct *task;
      printk(KERN_INFO "Initializing LKM for kernel status...\n");
      
        for_each_process(task) {
     if (process_info_count < MAX_PROCESS_COUNT) {
            struct process_info *info = kmalloc(sizeof(struct process_info), GFP_KERNEL);

            if (info) {
                info->pid = task->pid;
                snprintf(info->name, MAX_PROCESS_NAME_LENGTH, "%s", task->comm);
                process_info_data[process_info_count++] = info;
            }
        }  
    }
    // Print process information
    printk(KERN_INFO "LKM initialized: Tracking running processes and their names\n");
    printk(KERN_INFO "Number of running processes: %d\n", process_info_count);
    for (int i = 0; i < process_info_count; i++) {
        printk(KERN_INFO "Process %d: %s (PID %d)\n", i + 1, process_info_data[i]->name, process_info_data[i]->pid);
    }

    return 0; // Module loaded successfully
}

static void __exit task_details_lkm_exit(void) {
      printk(KERN_INFO "Exiting LKM...\n");

    // Clean up allocated process info data
    for (int i = 0; i < process_info_count; i++) {
        kfree(process_info_data[i]);
    }

    printk(KERN_INFO "LKM exited\n");
}

module_init(task_details_lkm_init);
module_exit(task_details_lkm_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("LKM for printing task details in a proc file");

