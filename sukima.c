#include <linux/device.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/version.h>

#if LINUX_VERSION_CODE == KERNEL_VERSION(6, 6, 28)
#include <linux/device/class.h>
#endif

#include "log.h"
#include "sukima.h"
#include "syscall_hook.h"

int __init sukima_init(void) {
    // register device
    major_num = register_chrdev(0, DEVICE_NAME, &sumika_fo);
    if (major_num < 0) {
        return major_num;
    }

#if LINUX_VERSION_CODE == KERNEL_VERSION(5, 4, 275)
    module_class = class_create(THIS_MODULE, CLASS_NAME);
#else
    module_class = class_create(CLASS_NAME);
#endif
    if (IS_ERR(module_class)) {
        unregister_chrdev(major_num, DEVICE_NAME);
        return PTR_ERR(module_class);
    }

    module_device = device_create(module_class, NULL, MKDEV(major_num, 0), NULL, DEVICE_NAME);
    if (IS_ERR(module_device)) {
        class_destroy(module_class);
        unregister_chrdev(major_num, DEVICE_NAME);
        return PTR_ERR(module_device);
    }

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

    syscall_hook_init();

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
