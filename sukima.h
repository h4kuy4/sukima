#include <linux/fs.h>
#include <linux/kern_levels.h>
#include <linux/printk.h>

#define MODULE_NAME "sukima"

#ifndef SILENT
#define LOG_I(...)            \
    printk(KERN_INFO "[INFO]" \
                     "[" MODULE_NAME "] " __VA_ARGS__)
#define LOG_D(...)              \
    printk(KERN_DEBUG "[DEBUG]" \
                      "[" MODULE_NAME "] " __VA_ARGS__)
#define LOG_W(...)               \
    printk(KERN_WARNING "[WARN]" \
                        "[" MODULE_NAME "] " __VA_ARGS__)
#define LOG_E(...)            \
    printk(KERN_ERR "[ERROR]" \
                    "[" MODULE_NAME "] " __VA_ARGS__)
#else
#define LOG_I(...)
#define LOG_D(...)
#define LOG_W(...)
#define LOG_E(...)
#endif

#define DEVICE_NAME "sukima"
#define CLASS_NAME "sukima"
#define DEVICE_PATH "/dev/sukima"

static int            major_num;
static struct class  *module_class  = NULL;
static struct device *module_device = NULL;
static struct file   *__file        = NULL;
static struct inode  *__inode       = NULL;

int __init  sukima_init(void);
void __exit sukima_exit(void);

int     sukima_open(struct inode *, struct file *);
ssize_t sukima_read(struct file *, char __user *, size_t, loff_t *);
ssize_t sukima_write(struct file *, const char __user *, size_t, loff_t *);
int     sukima_release(struct inode *, struct file *);
long    sukima_ioctl(struct file *, unsigned int, unsigned long);

static struct file_operations sumika_fo = {
    .owner          = THIS_MODULE,
    .unlocked_ioctl = sukima_ioctl,
    .open           = sukima_open,
    .read           = sukima_read,
    .write          = sukima_write,
    .release        = sukima_release,
};
