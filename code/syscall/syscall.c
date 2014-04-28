#include<linux/kernel.h>
//#include<linux/module.h>
#include<linux/modversions.h>
#include<linux/sched.h>
#include<asm/uaccess.h>
#define_NR_testsyscall 191
extern viod *sys_call+table[];
asmlinkage int testsyscall()
{

console_print("hello world/n");
return 0;
}
int init_module()
{

sys_call_table[_NR_tsetsyscall]=testsyscall;
printk("system call testsyscall() loaded success/n");
return 0;
}
void cleanup_module()
{
printk("system call testsyscall() unloaded success/n"); 
}
