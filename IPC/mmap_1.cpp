/*************************************************************************
	> File Name: mmap.cpp
	> Author: Liu Shengxi 
	> Mail: 13689209566@163.com
	> Created Time: 2019年03月24日 星期日 21时32分48秒
 ************************************************************************/

#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
using namespace std;

void print_err(const char *str)
{
    perror(str);
    exit(EXIT_FAILURE);
}
int main(void)
{
    // 1.打开映射文件
    int fd = open("test.shm", O_RDWR | O_CREAT, 0666);

    // 2. 让其在磁盘上存在实际的页面
    ftruncate(fd, sizeof(int));

    //3.将文件映射到自己的虚拟地址空间中
    int *p = (int *)mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (p == MAP_FAILED)
        print_err("mmapp函数");
    //4.关闭映射文件，不影响
    close(fd);

    // 5.产生随机数并存入共享内存中，使用sleep为了便于观察
    for (srand(7777);; sleep(1))
    {
        int v = rand();
        *p = v;
        printf("produce: %d\n", v);
    }
    //6.解除内存映射
    munmap(p, sizeof(int));

    return 0;
}
