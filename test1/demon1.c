#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

long long timeum(){
    struct timeval tim; 
    gettimeofday (&tim , NULL);
    return (long long)tim.tv_sec*1000000+tim.tv_usec;
}

int main()
{
    int i;
    long long start,tmp;
    start = timeum();
    for(i = 0; i < 60; ++i){
        printf("My Counter: %d\n", i);
        sleep(1);
        tmp = timeum();
        printf("Time Interval: %lld\n",tmp-start);
        start = tmp;
    }
    return 0;
}