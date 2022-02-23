#include <linux/module.h>
#include <linux/init.h>
#include <linux/mm_types.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Manish Surolia");
MODULE_DESCRIPTION("Print page related details");

static int __init my_module_init(void)
{
    printk("Hello, Linux Kernel");
    printk("Size of 'struct page' is : %lu bytes", sizeof(struct page));
    return 0;
}

static void __exit my_module_exit(void)
{
    printk("Bye, Linux Kernel");
    return;
}

module_init(my_module_init);
module_exit(my_module_exit);
