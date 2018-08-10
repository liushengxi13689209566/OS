#include<stdio.h>
int main(void){
    char buf[10] = "123456789";
    printf("sizeof(buf) == %d \n",sizeof(buf));
    printf("buf ==%s||\n",buf);
    return 0;
}