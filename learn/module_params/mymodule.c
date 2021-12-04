#include <linux/module.h>
#include <linux/init.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Manish");
MODULE_DESCRIPTION("Module with parameters");

static int num = 5;
module_param(num, int, 0660);

static char *str = "string arg";
module_param(str, charp, 0660);

static int __init my_module_init(void)
{
   printk("Hello, Linux Kernel. num = %d, str = %s\n", num, str);
   return 0;
}

static void __exit my_module_exit(void)
{
    printk("Bye, Linux Kernel. num = %d, str = %s\n", num, str);
    return;
}

module_init(my_module_init);
module_exit(my_module_exit);

