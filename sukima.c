#include <linux/device.h>
#include <linux/device/class.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

#include "sukima.h"

int __init sukima_init(void) {
    // register device
    major_num = register_chrdev(0, DEVICE_NAME, &sumika_fo);
    if (major_num < 0) {
        return major_num;
    }

    // create device class
    module_class = class_create(CLASS_NAME);
    if (IS_ERR(module_class)) {
        unregister_chrdev(major_num, DEVICE_NAME);
        return PTR_ERR(module_class);
    }

    // create device inode
    module_device = device_create(module_class, NULL, MKDEV(major_num, 0), NULL, DEVICE_NAME);
    if (IS_ERR(module_device)) {
        class_destroy(module_class);
        unregister_chrdev(major_num, DEVICE_NAME);
        return PTR_ERR(module_device);
    }

    // change permission
    __file = filp_open(DEVICE_PATH, O_RDONLY, 0);
    if (IS_ERR(__file)) {
        device_destroy(module_class, MKDEV(major_num, 0));
        class_destroy(module_class);
        unregister_chrdev(major_num, DEVICE_NAME);
        return PTR_ERR(__file);
    }
    __inode = file_inode(__file);
    __inode->i_mode |= 0666;
    filp_close(__file, NULL);

    LOG_I("Sukima Init!");

    return 0;
}

void __exit sukima_exit(void) {
    device_destroy(module_class, MKDEV(major_num, 0));
    class_destroy(module_class);
    unregister_chrdev(major_num, DEVICE_NAME);
    LOG_I("Sukima Exit!");
    return;
}

module_init(sukima_init);
module_exit(sukima_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("hakuya");
