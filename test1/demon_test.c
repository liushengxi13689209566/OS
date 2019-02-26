#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <stdio.h>
#include <string.h>

const int long_size = sizeof(long); //8 

// getdata(traced_process, regs.rip, backup, len);//将指令复制到 backup
void getdata(pid_t child, long addr, char *str, int len)
{
    char *laddr;
    int i, j;
    union u {
        long val;
        char chars[long_size]; //chars[8]
    } data;

    i = 0;
    j = len / long_size;
    laddr = str;
    while (i < j)
    {
        data.val = ptrace(PTRACE_PEEKDATA, child, addr + i * 8, NULL); //读取一个字的数据
        memcpy(laddr, data.chars, long_size);
        ++i;
        laddr += long_size;
    }
    j = len % long_size;
    if (j != 0)
    {
        data.val = ptrace(PTRACE_PEEKDATA, child, addr + i * 8, NULL);
        memcpy(laddr, data.chars, j);
    }
    str[len] = ' ';
}
// putdata(traced_process, regs.rip, code, len);
void putdata(pid_t child, long addr, char *str, int len)
{
    char *laddr;
    int i, j;
    union u {
        long val;
        char chars[long_size];
    } data;

    long rst;

    i = 0;
    j = len / long_size;
    laddr = str;
    while (i < j)
    {
        memcpy(data.chars, laddr, long_size);
        rst = ptrace(PTRACE_POKEDATA, child, addr + i * 8, data.val);
        if (rst < 0)
        {
            printf("Putdata Failed! \n");
            return;
        }
        ++i;
        laddr += long_size;
    }
    j = len % long_size;
    if (j != 0)
    {
        memcpy(data.chars, laddr, j);
        rst = ptrace(PTRACE_POKEDATA, child, addr + i * 8, data.val);
        if (rst < 0)
        {
            printf("Putdata Failed! \n");
            return;
        }
    }
}

int main(int argc, char *argv[])
{
    pid_t traced_process;
    struct user_regs_struct regs;
    int len = 39;

    /* hello world */
    char code[] =
        "\xeb\x13\x5e\xb8\x01\x00\x00\x00"
        "\xbf\x01\x00\x00\x00\xba\x0d\x00"
        "\x00\x00\x0f\x05\xcc\xe8\xe8\xff"
        "\xff\xff\x48\x65\x6c\x6c\x6f\x20"
        "\x77\x6f\x72\x6c\x64\x21\x0a";

    char backup[len + 1];

    if (argc != 2)
    {
        printf("PID?\n");
        return 1;
    }
    traced_process = atoi(argv[1]);
    ptrace(PTRACE_ATTACH, traced_process, NULL, NULL); //附着 
    int pid = wait(NULL);
    printf("Attach Pid: %d\n", pid);

    ptrace(PTRACE_GETREGS, traced_process, NULL, &regs); //取得所有的 regs 
    /* Copy instructions into a backup variable */
    getdata(traced_process, regs.rip, backup, len);//将指令复制到 backup
    
    /* Put the shellcode & int3 */
    putdata(traced_process, regs.rip, code, len);
    /* Let the process continue and execute the int3 instruction */
    ptrace(PTRACE_CONT, traced_process, NULL, NULL);
    wait(NULL);
    putdata(traced_process, regs.rip, backup, len);
    /* Setting the rip back to the original instruction to let the process continue */
    ptrace(PTRACE_SETREGS, traced_process, NULL, &regs);
    ptrace(PTRACE_DETACH, traced_process, NULL, NULL);
    return 0;
}