#include "types.h"
#include <string.h>

#define NR_TASKS  (1 + 4) // 只需要创建 4 个用户态进程

#define TASK_RUNNING    0 // 为了简化实验，所有的线程都只有一种状态

#define PRIORITY_MIN 1
#define PRIORITY_MAX 10

#define COUNTER_MIN 1
#define COUNTER_MAX 10

#define OFFSET(TYPE , MEMBER) ((unsigned long)(&(((TYPE *)0)->MEMBER)))

extern struct task_struct* current;

typedef unsigned long* pagetable_t;

/* 用于记录 `线程` 的 `内核栈与用户栈指针` */
struct thread_info {
    unsigned long kernel_sp;
    unsigned long user_sp;
};

/* 线程状态段数据结构 */
struct thread_struct {
    unsigned long ra;
    unsigned long sp;
    unsigned long s[12];

    unsigned long sepc, sstatus, sscratch;
};

/* 线程数据结构 */
struct task_struct {
    struct thread_info* thread_info;
    unsigned long state;    // 线程状态
    unsigned long counter;  // 运行剩余时间
    unsigned long priority; // 运行优先级 1最低 10最高
    unsigned long pid;      // 线程id

    struct thread_struct thread;

    unsigned long pgd;
};

/* 线程初始化 创建 NR_TASKS 个线程 */
void task_init();

/* 在时钟中断处理中被调用 用于判断是否需要进行调度 */
void do_timer();

/* 调度程序 选择出下一个运行的线程 */
void schedule();

/* 线程切换入口函数*/
void switch_to(struct task_struct* next);

/* dummy funciton: 一个循环程序，循环输出自己的 pid 以及一个自增的局部变量*/
void dummy();

void SJF_schedule();

void Priority_schedule();