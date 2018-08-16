/*************************************************************************
	> File Name: public.h
	> Author: Liu Shengxi 
	> Mail: 13689209566@163.com
	> Created Time: 2018年08月16日 星期四 10时15分39秒
 ************************************************************************/

#ifndef _PUBLIC_H
#define _PUBLIC_H
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>
#include <sys/select.h>
#include <strings.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/mman.h>

void err_sys(const char *err_string)
{
	perror(err_string);
	exit(-1);
}
int Open(const char *pathname, int oflags, mode_t mode)
{
	int fd;
	if ((fd = open(pathname, oflags, mode)) < 0)
		err_sys("open error ");
	return fd;
}
void Close(int fd)
{
	if (close(fd) == -1)
		err_sys("close error");
}
void Write(int fd, void *ptr, size_t nbytes)
{
	if (write(fd, ptr, nbytes) != nbytes)
		err_sys("write error");
}

#endif
