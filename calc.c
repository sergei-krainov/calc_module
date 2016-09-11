#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>

static int calc_init(void) {
    printk(KERN_INFO "Calc init\n");
    printk(KERN_INFO "Initialization using function %s\n", __FUNCTION__ );
    return 0;
}

static void calc_exit(void) {
	printk(KERN_INFO "Exiting with function %s\n", __FUNCTION__ );
    printk(KERN_INFO "Calc exit\n");
}

module_init(calc_init);
module_exit(calc_exit);
