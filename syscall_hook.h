#pragma once

#include <asm/ptrace.h>
#include <linux/types.h>

typedef void (*pre_hook_ptr_t)(struct pt_regs *);
typedef void (*pos_hook_ptr_t)(struct pt_regs *, unsigned long *);

void syscall_hook_init(void);
int  hook_syscall(int nr, pre_hook_ptr_t pre_handler, pos_hook_ptr_t pos_handler);
