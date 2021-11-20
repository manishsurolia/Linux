#include <linux/module.h>
#include <linux/init.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Manish");
MODULE_DESCRIPTION("A Hello World LKM");

static int __init ModuleInit(void)
{
    printk("Hello, kernel");
    return 0;
}

static void __exit ModuleExit(void)
{
    printk("Goodbye, kernel\n");
}

module_init(ModuleInit);
module_exit(ModuleExit);
