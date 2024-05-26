#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"

uint64
sys_exit(void)
{
  uint64 msg_ptr;
  argaddr(1, &msg_ptr);
  char msg[32];
  if (!msg_ptr || fetchstr(msg_ptr, msg, 32) <= 0)
    strncpy(msg, "No exit message", 16);
  int n;
  argint(0, &n);
  exit(n, msg);
  return 0;
}

uint64
sys_set_affinity_mask(void)
{
  int mask;
  argint(0, &mask);
  set_affinity_mask(mask);
  return 0;
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  uint64 exit_msg_ptr;
  argaddr(0, &p);
  argaddr(1, &exit_msg_ptr); // Get the second argument
  return wait(p, exit_msg_ptr);
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int n;

  argint(0, &n);
  addr = myproc()->sz;
  if (growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;

  argint(0, &n);
  acquire(&tickslock);
  ticks0 = ticks;
  while (ticks - ticks0 < n)
  {
    if (killed(myproc()))
    {
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  argint(0, &pid);
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

// return the size of the current process's memory in bytes:
uint64
sys_memsize(void) { return myproc()->sz; }