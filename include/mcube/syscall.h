/**
 * @file include/mcube/syscall.h
 *
 * @author Hiroyuki Chishiro
 */
#ifndef __MCUBE_MCUBE_SYSCALLS_H__
#define __MCUBE_MCUBE_SYSCALLS_H__


#if !CONFIG_ARCH_SIM

#define SYS_sched 0
#define SYS_end_job 1
#define SYS_get_exec_time 2
#define SYS_write 3
#define SYS_get_cpu_id 4
#define SYS_get_mode_level 5
#define SYS_move_to_kernel_level 6
#define NR_syscalls 7

#endif /* !CONFIG_ARCH_SIM */

#ifndef __ASSEMBLY__


/* user-level APIs */
int call_sys_sched(void);
int call_sys_end_job(void);
unsigned long call_sys_get_exec_time(void);
int call_sys_write(char *buf);
unsigned long call_sys_get_cpu_id(void);
int call_sys_get_mode_level(void);
int call_sys_move_to_kernel_level(void);

/* kernel-level APIs */
asmlinkage int sys_sched(void);
asmlinkage int sys_end_job(unsigned long *id_ptr);
asmlinkage int sys_get_exec_time(unsigned long *id_ptr,
                                 unsigned long *cputime_ptr);
asmlinkage int sys_mcube_write(char *buf);
asmlinkage int sys_get_cpu_id(void);
asmlinkage int sys_get_mode_level(void);
asmlinkage int sys_move_to_kernel_level(void);
asmlinkage int sys_bad_syscall(int number);



asmlinkage int syscall0(int number);
asmlinkage int syscall1(int number, unsigned long arg1);
asmlinkage int syscall2(int number, unsigned long arg1, unsigned long arg2);


#endif /* !__ASSEMBLY__ */


#endif /* __MCUBE_MCUBE_SYSCALLS_H__ */
