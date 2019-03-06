#include <iostream>
#include <pthread.h>
 
void* ThreadFun1(void* arg)
{
    int *value=static_cast<int*> (arg);
    int n=10000000;
    while(n--)
    {
        std::cout<<"This is thread    "<<*value<<std::endl;
    }
    pthread_exit(0);
}

void* ThreadFun2(void* arg)
{
    int *value=static_cast<int*> (arg);
    int n=10000000;
    srand((int)time(0)); 
    while(n--)
    {
        *value = rand()%100;
    }
    pthread_exit(0);
}
 
int main()
{
    int  ret=0;
    pthread_t thread_id1,thread_id2;
    int v1 = 666 ;
    ret = pthread_create(&thread_id1, NULL, ThreadFun1, static_cast<void*>(&v1)); 
    if (ret)
    {
        std::cout<<"Create pthread error!"<<std::endl;
        return 1;
    }
 
    ret = pthread_create(&thread_id2, NULL, ThreadFun2, static_cast<void*>(&v1));
    if (ret)
    {
        std::cout<<"Create pthread error!"<<std::endl;
        return 1;
    }
 
    pthread_join(thread_id1, NULL);
    pthread_join(thread_id2, NULL);
 
    return 0;
}
