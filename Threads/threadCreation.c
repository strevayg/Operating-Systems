/* (c) Gabby Strevay 2023
 *  Small program to portray thread creation and sharing of a resource (a character)
*/
#include <stdio.h>
#include <pthread.h>  //for pthread, etc
#include <unistd.h> //for pid_t (to get process IDs)
#include <string.h>

//thread function
void *threadfunct(void *letter)
{
    printf("second thread here, my tid is %lu but I'm still in process %d", pthread_self(), getpid());
    printf(", I received a '%s' when I was created\n", letter);
    pthread_exit(0); //thread will terminate 
}

int main()
{
    char letter= 'B'; //passing in argument for version 3
    pid_t pid;
    pthread_t tid; //thread identifier
    int threadreturn; 
    printf("main thread here; pid is %d, tid is %lu\n", getpid(), pthread_self() );
    
    threadreturn= pthread_create(&tid, NULL, threadfunct, &letter);
    if (threadreturn == 0) //returns 0 if successful 
        printf("main: successfully created a new thread with TID of %lu\n", tid);
    else //it returns an error number
        printf("Damn: %s", strerror(threadreturn) );
   
    threadreturn=pthread_join(tid,NULL); //wait for thread to exit
    if (threadreturn != 0) //returns 0 if successful 
        printf("Damn: %s", strerror(threadreturn) );
    //else it was successful 
    printf("main: second thread has terminated, main will now exit\n");
    return 0;
}
