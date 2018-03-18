#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  cprintf("%s ",__FUNCTION__);
  return fork();
}

int
sys_exit(void)
{
  cprintf("%s ",__FUNCTION__);
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  cprintf("%s ",__FUNCTION__);
  return wait();
}

int
sys_kill(void)
{
  cprintf("%s ",__FUNCTION__);
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  cprintf("%s ",__FUNCTION__);
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  cprintf("%s ",__FUNCTION__);
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  cprintf("%s ",__FUNCTION__);
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  cprintf("%s ",__FUNCTION__);
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
