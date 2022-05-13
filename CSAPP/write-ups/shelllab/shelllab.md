# CSAPP ShellLab 详解

## 书中一些函数的功能

```c
#include<unistd.h>
#include<signal.h>
#include<sys/types.h>
pid_t getpgrp(void);										// 返回当前进程的进程组id
int setpgid(pid_t pid,pid_t pgid)							// 改变自己或其他进程的进程组，成功返回0失败返回1
int kill(pid_t pid,int sig)									// 进程通过调用kill函数发送信号给其他进程(包括自己)，成															// 功返回0失败返回1
typedef void (*sighandler_t) (int);
sighandler_t signal(int signum, sighandler_t handler);		// 若成功则返回指向前次处理程序的指针，否则返回SIG_ERR
int sigprocmask(int how,const sigset_t *set, sigset_t *oldset);
int sigemptyset(sigset_t *set);
int sigfillset(sigset_t *set);
int sigaddset(sigset_t *set,int signum);
int sigdelset(sigset_t *set,int signum);
/* sigprocmask 函数改变当前阻塞的信号集合，具体行为依赖how的值
   SIG_BLOCK   把set中的信号添加到blocked向量
   SIG_UNBLOCK 从blocked中删除set的信号
   SIG_SETMASK block=set
   如果oldset非空，那么blocked位向量的值保存在oldset中
   sigemptyset 初始化set为空集合
   sigfillset  把每个信号都添加到set中
   sigaddset   把signum添加到set
   sigdelset   从set中删除signum
   如果signum是set的成员，那么sigismember返回1，否则返回0 */
int sigismember(const sigset_t *set,int signum);
```



## eval函数

实现代码如下：

```
```

## builtin_cmd函数

依照书中方法实现即可：

```c
int builtin_cmd(char **argv) 
{
    if(!strcmp(argv[0], "quit"))
        exit(0);
    if(!strcmp(argv[0], "bg") || !strcmp(argv[0], "fg") ){
        do_bgfg(argv);
        return 1;
    }
    if(!strcmp(argv[0], "jobs")){
        listjobs(jobs);
        return 1;
    }
    if(!strcmp(argv[0], "&")){
        return 1;
    }
    return 0;     /* not a builtin command */
}
```

## 三个signal_handler实现

```c
/* 
 * sigchld_handler - The kernel sends a SIGCHLD to the shell whenever
 *     a child job terminates (becomes a zombie), or stops because it
 *     received a SIGSTOP or SIGTSTP signal. The handler reaps all
 *     available zombie children, but doesn't wait for any other
 *     currently running children to terminate.  
 */
void sigchld_handler(int sig) 
{
    
}

/* 
 * sigint_handler - The kernel sends a SIGINT to the shell whenver the
 *    user types ctrl-c at the keyboard.  Catch it and send it along
 *    to the foreground job.  
 */
void sigint_handler(int sig) 
{
    pid_t pid = fgpid(jobs);
    if(pid == 0)
    {
        return;
    }
    kill(-pid,sig);
}

/*
 * sigtstp_handler - The kernel sends a SIGTSTP to the shell whenever
 *     the user types ctrl-z at the keyboard. Catch it and suspend the
 *     foreground job by sending it a SIGTSTP.  
 */
void sigtstp_handler(int sig) 
{
    pid_t pid = fgpid(jobs);
    if(pid == 0)
    {
        return;
    }
    kill(-pid,sig);
}

```

