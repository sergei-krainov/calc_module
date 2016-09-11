#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>

#include <linux/fs.h>

int calc_open(struct inode *inodp, struct file *filp) {
	printk(KERN_INFO "Entering function %s\n", __FUNCTION__ );
    return 0;
}
ssize_t calc_read(struct file *filp, char __user *buffer, size_t length, loff_t *offset) {
	printk(KERN_INFO "Entering function %s\n", __FUNCTION__ );
	return 0;
}

ssize_t calc_write(struct file *filp, const char __user *buffer, size_t length, loff_t *offset) {
	printk(KERN_INFO "Entering function %s\n", __FUNCTION__ );
	//return length;
	return length;
}

int calc_release(struct inode *inodp, struct file *filp) {
	printk(KERN_INFO "Entering function %s\n", __FUNCTION__ );
	return 0;
}

struct file_operations calc_fops = {
    .owner   = THIS_MODULE,
    .open    = calc_open,
    .read    = calc_read,
    .write   = calc_write,
    .release = calc_release,
};

struct file_operations *p = &calc_fops;

const char dev_name[] = "Calculator device module";

static int calc_init(void) {
    printk(KERN_INFO "Calc init\n");
    printk(KERN_INFO "Initialization using function %s\n", __FUNCTION__ );
    
    register_chrdev( 242       /* Major number */,
                     dev_name  /* Name */,
                     p /* File operations*/);
    
    return 0;
}

static void calc_exit(void) {
    printk(KERN_INFO "Exiting with function %s\n", __FUNCTION__ );
    printk(KERN_INFO "Calc exit\n");
    
    unregister_chrdev(242, dev_name);
}

module_init(calc_init);
module_exit(calc_exit);

