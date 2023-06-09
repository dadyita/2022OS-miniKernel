#include "printk.h"
#include "clock.h"
#include "proc.h"
#include "syscall.h"

void trap_handler(unsigned long scause, unsigned long sepc, struct pt_regs *regs)
{
    // 通过 `scause` 判断trap类型
    // 如果是interrupt 判断是否是timer interrupt
    // 如果是timer interrupt 则打印输出相关信息, 并通过 `clock_set_next_event()` 设置下一次时钟中断
    // `clock_set_next_event()` 见 4.5 节
    // 其他interrupt / exception 可以直接忽略

    // printk("scause: 0x%lx, sepc: %lx\n", scause, sepc);

    if (scause & (1LL << 63))
    {
        if (scause ^ (1LL << 63) == 5)
        {
            // printk("kernel is running!\n");
            // printk("[S] Supervisor Mode Timer Interrupt\n");
            clock_set_next_event();
            do_timer();
        }
        else
        {
        }
    }
    else
    {
        if (scause == 8)
        {
            syscall(regs);
        }
    }
}