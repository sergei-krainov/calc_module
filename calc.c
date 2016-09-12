#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/moduleparam.h>

#include <linux/fs.h>

MODULE_LICENSE("GPL");

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

/* struct file_operations *p = &calc_fops; */

/* const char dev_name[] = "calc-dev"; */
#define DEV_NAME "calc-dev"
#define INT_SIZE sizeof(int)
static int Major;

static char *fl1 = 0;
static char *fl2 = 0;
static char *fl3 = 0;
static char *fl4 = 0;

module_param(fl1, charp, S_IRUGO);
module_param(fl2, charp, S_IRUGO);
module_param(fl3, charp, S_IRUGO);
module_param(fl4, charp, S_IRUGO);

static int calc_init(void) {
    printk(KERN_INFO "Calc init\n");
    printk(KERN_INFO "Initialization using function %s\n", __FUNCTION__ );
    
    Major = register_chrdev( 0          /* Major number */,
                             DEV_NAME   /* Name */,
                             &calc_fops /* File operations */);
                             
    if ( Major < 0 ) {
		printk(KERN_INFO "Can't get Major number, error %d\n", Major);
		
		return Major;
	}
	
	printk(KERN_INFO "file number 1 is %s\n", fl1);
	printk(KERN_INFO "file number 2 is %s\n", fl2);
	printk(KERN_INFO "file number 3 is %s\n", fl3);
	printk(KERN_INFO "file number 4 is %s\n", fl4);                 
    printk(KERN_INFO "Normally shell script should do 'mknod /dev/%s c %d 0'.\n", DEV_NAME, Major);
    
    
    return 0;
}

static void calc_exit(void) {
    printk(KERN_INFO "Exiting with function %s\n", __FUNCTION__ );
    printk(KERN_INFO "Calc exit\n");
    
    unregister_chrdev(Major, DEV_NAME);
}

module_init(calc_init);
module_exit(calc_exit);

