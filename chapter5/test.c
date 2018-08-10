/*************************************************************************
	> File Name: test.cpp
	> Author: Liu Shengxi 
	> Mail: 13689209566@163.com
	> Created Time: 2018年06月10日 星期日 21时25分51秒
 ************************************************************************/

#include<stdio.h>
void swap(int *xp,int *yp){
    *xp = *xp + *yp ;
    *yp = *xp - *yp ;
    *xp = *xp - *yp ;
}
int main(void) {
    /*P343.1
    int x= 100555 ;
    int y=3000;
    int tmp=0;
    int *q,*p;
    p=q=NULL;
    //p=q=&tmp;
    *q=y;
    *p=x;
    int t1 = *q; 
    printf("t1 == %d \n",t1);*/
    int x=12 ,y=15;
    swap(&x,&x);
    printf("x== %d  y== %d\n",x,y);

    return 0;

}

