

/* create a zombie process*/
#include <sys/types.h>
//#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
int main(void)
{
    if( fork() == 0 )
    { //create child proce
        if ( fork()！=0  )
        { //子进程部分
            while (1)
            {
                sleep(5);
                //    break;
            }
        }
        /*子子进程部分 */
    }
    /*父进程部分*/
    return 0;
}
