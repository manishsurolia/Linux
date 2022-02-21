#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched/signal.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Manish Surolia");
MODULE_DESCRIPTION("Print a task details");

char * get_task_state(long state)
{
    switch (state) {
        case TASK_RUNNING:
            return "TASK_RUNNING";
        case TASK_INTERRUPTIBLE:
            return "TASK_INTERRUPTIBLE";
        case TASK_UNINTERRUPTIBLE:
            return "TASK_UNINTERRUPTIBLE";
        case __TASK_STOPPED:
            return "__TASK_STOPPED";
        case __TASK_TRACED:
            return "__TASK_TRACED";
        default:
            return "UNKNOWN TYPE";
    }
}

static void print_task_info(unsigned int tgid)
{
    struct task_struct *the_process;
    struct task_struct *the_thread;
    char comm[TASK_COMM_LEN];

    rcu_read_lock();
    for_each_process(the_process) {
        if (task_tgid_nr(the_process) == tgid) {
            pr_info("process node: %p\n", the_process);
            for_each_thread(the_process, the_thread) {
                pr_info("thread node: %p\t Name: %s\t PID:[%d]\t TGID:[%d]\t STATE:[%s]\n",
                        the_thread, get_task_comm(comm, the_thread),
                        task_pid_nr(the_thread), task_tgid_nr(the_thread),
                        get_task_state(the_thread->state));
            }
            break;
        }
    }
    rcu_read_unlock();
    return;
}

unsigned int arg;
static int notify_param(const char *val, const struct kernel_param *kp)
{
    int res = param_set_int(val, kp);
    if (!res) {
        print_task_info(arg);
        return 0;
    }
    return -1;
}

const struct kernel_param_ops my_module_param_ops =
{
    .set = notify_param,
    .get = param_get_int,
};
module_param_cb(arg, &my_module_param_ops, &arg, S_IRUSR|S_IWUSR);

static int __init my_module_init(void)
{
    printk("Hello, Linux Kernel");
    return 0;
}

static void __exit my_module_exit(void)
{
    printk("Bye, Linux Kernel");
    return;
}

module_init(my_module_init);
module_exit(my_module_exit);
