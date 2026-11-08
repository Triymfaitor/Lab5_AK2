#include <linux/init.h>
#include <linux/module.h>
#include "hello1.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Viacheslav");
MODULE_DESCRIPTION("Hello2 module that calls hello1's function");

static uint count = 1;
module_param(count, uint, 0660);
MODULE_PARM_DESC(count, "Number of times to print 'Hello, world!'");

static int __init hello2_init(void)
{
    int i;
    
    if (count == 0 || (count >= 5 && count <= 10)) {
        pr_warn("Warning: count=%u is unusual, continuing...\n", count);
    } else if (count > 10) {
        pr_err("Error: count too large (%u)\n", count);
        return -EINVAL;
    }

    for (i = 0; i < count; i++) {
        print_hello();
    }
    pr_info("hello2 loaded with count=%u\n", count);
    return 0;
}

static void __exit hello2_exit(void)
{
    pr_info("hello2 unloaded\n");
}

module_init(hello2_init);
module_exit(hello2_exit);
