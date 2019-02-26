/*************************************************************************
	> File Name: change.c
	> Author: Liu Shengxi 
	> Mail: 13689209566@163.com
	> Created Time: 2019年02月05日 星期二 13时51分26秒
 ************************************************************************/

#include <stdio.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/reg.h>

int main(int argc,char *argv[]) // a.out   pid  n的地址
{
	pid_t pid =  atoi(argv[1]);
	ptrace(PTRACE_ATTACH, pid,NULL, NULL);
    wait(NULL);
	int temp =  0 ;
	ptrace(PTRACE_POKEDATA,pid,argv[2],&temp);
	ptrace(PTRACE_DETACH, traced_process, 
           NULL, NULL);
	return 0;
}
