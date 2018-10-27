#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
 
void* thrd_start_routine(void* v)
{
    sleep(10);
        printf("created thread\n");
}
 
int main()
{
        pthread_t thrdid;
                
        pthread_create(&thrdid, NULL, &thrd_start_routine, NULL);
        
        sleep(5);
        printf("main thread\n");
        pthread_exit(NULL);  
        printf("main exit\n");      
        return  0;
}

