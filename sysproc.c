#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
extern int v_toggle;
extern int ps(void);
extern int set_priority(int,int);
extern int get_priority(int);


int
sys_add(void)
{
  int a,b;
  if(argint(0,&a)<0 || argint(1,&b)<0)
    return -1;
  return a+b;
}
int
sys_setpriority(void)
{
  int a,b;
  if(argint(0,&a)<0 || argint(1,&b)<0)
    return -1;
  return set_priority(a,b);
}
int
sys_getpriority(void)
{
  int a;
  if(argint(0,&a)<0)
    return -1;
  return get_priority(a);
}
int
sys_toggle(void)
{
  v_toggle = 1 - v_toggle;
  return 0;
}
int
sys_ps(void)
{
  return ps();
}

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
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
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
