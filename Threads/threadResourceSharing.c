/* (c) Gabby Strevay 2023
 * Program that demonstrates thread creation and the sharing of a global resource between threads 
*/
#include <stdio.h> 
#include <pthread.h> //for pthread, etc 
#include <unistd.h> //for pid_t (to get process IDs)
#include <string.h>

int number=0; //global variable 

//thread function
void *threadfunct()
{
    printf("\tSecond thread: My TID is %lu but still in process #%d\n", pthread_self(), getpid());
    printf("I'm about to spin until main enters a non-zero value into the shared variable\n");
    while(number == 0) ; //spin loop

    printf("\tSecond thread: main set the shared variable to %d; I'll set it back to zero and then I'm done.\n", number);
    number = 0;
}

int main()
{
    pid_t pid;
    pthread_t tid; //thread identifier
    int threadreturn; 
    printf("Main: PID is %d\n", getpid());
    
    threadreturn= pthread_create(&tid, NULL, threadfunct, NULL);
    if (threadreturn == 0) //returns 0 if successful 
    {
        printf("Main: Successfully created a thread with TID of %lu\n", tid);
    }
    else //it returns an error number
        printf("Damn: %s", strerror(threadreturn) );
    printf("Main: Enter a non-zero integer so that the other thread can get out of its spin loop:\n");
    scanf("%d", &number);

    while( number != 0) ; //spin loop
    printf("Main: second thread has re-zeroed the shared variable, so I'm done.\n");
    return 0;
}
