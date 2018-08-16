/*************************************************************************
	> File Name: mmapcopy.c
	> Author: Liu Shengxi 
	> Mail: 13689209566@163.com
	> Created Time: 2018年08月16日 星期四 10时11分52秒
 ************************************************************************/
/*#include <sys/mman.h>

void *mmap(void *addr, size_t length, int prot, int flags, 
			int fd, off_t offset);
int munmap(void *addr, size_t length);
参数说明：
1.从addr开始进行相应的内存映射
2.映射长度
3.新映射的虚拟内存区域的访问权限vm_prot
4.被映射对象的类型，如果是MAP_ANON，就是一个匿名对象，相应虚拟页面以0填充，
如果是MAP_PRIVATE私有的，写时复制的对象，MAP_SHARED 共享对象
5.被映射对象的起始地址
*/
#include "public.h"
void realmmap(int fd, size_t length)
{
	char *bufp = mmap(NULL, length, PROT_READ, MAP_PRIVATE | MAP_ANON, fd, 0);
	Write(1, bufp, length);
	return;
}
int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("输入参数错误 \n");
		return -1;
	}
	int fd = Open(argv[1], O_RDONLY, 0);
	struct stat filestat;
	stat(argv[1], &filestat);
	
	realmmap(fd, filestat.st_size);

	Close(fd);
	exit(0);
}
