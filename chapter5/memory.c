/*************************************************************************
	> File Name: memory.c
	> Author: Liu Shengxi 
	> Mail: 13689209566@163.com
	> Created Time: 2018年06月21日 星期四 16时53分40秒
 ************************************************************************/

#include<stdio.h>
typedef struct ELE {
	struct ELE *next ;
	long data ;
}list_ele,*list_ptr ;

long list_len(list_ptr ls){ 
	long len = 0 ;
	while(ls){
		len++;
		ls = ls ->next ;
	}
	return len ;
}
/* 加载与存储 */
void write_read(long *src,long *dst, long n){
	long cnt = n;
	long val = 0;
	while(cnt){
		*dst = val ;
		val = (*src) + 1; 
		cnt--;
	}
}
int main(int argc, char const *argv[])
{

	
	return 0;
}
