#include <linux/module.h>
#include <linux/init.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Manish Surolia");
MODULE_DESCRIPTION("Linux Kernel module with parameter callbacks");

int arg = 0;

static int notify_param(const char *val, const struct kernel_param *kp)
{
    int res = param_set_int(val, kp);
    if (!res) {
        pr_info("Call back function called..\n");
        pr_info("New value of arg = %d\n", arg);
        return 0;
    }
    return -1;
}

const struct kernel_param_ops my_param_ops =
{
    .set = &notify_param,
    .get = &param_get_int,
};

module_param_cb(arg, &my_param_ops, &arg, S_IRUSR|S_IWUSR);

static int __init my_module_init(void)
{
    printk("Hello, Linux Kernel, arg = %d\n", arg);
    return 0;
}

static void __exit my_module_exit(void)
{
    printk("Bye, Linux Kernel, arg = %d\n", arg);
    return;
}

module_init(my_module_init);
module_exit(my_module_exit);
