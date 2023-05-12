#include "proc.h"
#include "printk.h"
#include "syscall.h"

void syscall(struct pt_regs* regs) {
    if (regs->a7 == SYS_WRITE) {
        if (regs->a0 == 1) {
            char buf[1000] = {0};
                memcpy(buf, (void *)regs->a1, regs->a2);
                regs->a0 = printk(buf);
        }
    }
    else if (regs->a7 == SYS_GETPID) {
        regs->a0 = current->pid;
    }
    else {}
}