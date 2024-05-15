#include <asm/pgtable.h>
#include <asm/syscall.h>
#include <asm/unistd_64.h>
#include <linux/kallsyms.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/syscalls.h>
#include <linux/unistd.h>
#include <linux/utsname.h>

#include "log.h"
#include "syscall_hook.h"
#include "utils.h"

void **syscall_table;

sys_call_ptr_t orgi_handler[NR_syscalls];
pre_hook_ptr_t pre_hook[NR_syscalls];
pos_hook_ptr_t pos_hook[NR_syscalls];

unsigned long hook_handler(struct pt_regs *regs) {
    unsigned long nr = regs->orig_ax;

    if (pre_hook[nr]) {
        pre_hook[nr](regs);
    }

    unsigned long ret = orgi_handler[regs->orig_ax](regs);

    if (pos_hook[nr]) {
        pos_hook[nr](regs, &ret);
    }
    return ret;
}

void syscall_hook_init(void) {
    LOG_I("Init syscall hook.");
    int i         = 0;
    syscall_table = (void **)kallsyms_lookup_name("sys_call_table");

    if (syscall_table == NULL) {
        LOG_E("Symbol `sys_call_table` not found.");
        return;
    }

    LOG_I("Find symbol `sys_call_table`: 0x%lx.", (long)syscall_table);

    make_rw(syscall_table);

    for (i = 0; i < NR_syscalls; i++) {
        orgi_handler[i]  = syscall_table[i];
        pre_hook[i]      = NULL;
        pos_hook[i]      = NULL;
        syscall_table[i] = &hook_handler;
    }

    make_ro(syscall_table);
    LOG_I("Init syscall hook finished.");
}

int hook_syscall(int nr, pre_hook_ptr_t pre_handler, pos_hook_ptr_t pos_handler) {
    pre_hook[nr] = pre_handler;
    pos_hook[nr] = pos_handler;
    return 0;
}
