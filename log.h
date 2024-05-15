#pragma once

#include <linux/kern_levels.h>
#include <linux/printk.h>

#include "sukima.h"

#ifndef SILENT
#define LOG_I(fmt, ...)                        \
    printk(KERN_INFO "[INFO]"                  \
                     "[" MODULE_NAME "] " fmt, \
           ##__VA_ARGS__)
#define LOG_D(fmt, ...)                         \
    printk(KERN_DEBUG "[DEBUG]"                 \
                      "[" MODULE_NAME "] " fmt, \
           ##__VA_ARGS__)
#define LOG_W(fmt, ...)                           \
    printk(KERN_WARNING "[WARN]"                  \
                        "[" MODULE_NAME "] " fmt, \
           ##__VA_ARGS__)
#define LOG_E(fmt, ...)                       \
    printk(KERN_ERR "[ERROR]"                 \
                    "[" MODULE_NAME "] " fmt, \
           ##__VA_ARGS__)
#else
#define LOG_I(...)
#define LOG_D(...)
#define LOG_W(...)
#define LOG_E(...)
#endif
