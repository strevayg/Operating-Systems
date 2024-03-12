/* (c) Gabby Strevay 2023
 * Interprocess communication via shared memory program
*/
#include <stdio.h>
#include <unistd.h> //header thaat includes fork() and sleep()
#include <sys/shm.h> //for shmat and all the other shm service calls
#include <stdlib.h> //for malloc
#include <string.h> //for sterror
#include<sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
int main()
{
    int errorcode;
    int* shared;
    pid_t pid; 
    key_t key;
    int shm_ID;
    //0666 sets the access permissions of the memory segment 
    //IPC_CREAT tells the system to create a new memory segment for the shared memory
    shm_ID = shmget(key, 4,IPC_CREAT | 0666);
    if(shm_ID == -1)//error occurred
        printf("Damn: %s", strerror(shm_ID) );
    
    printf("Parent: Successfully created shared memory segment with shared memory ID #%d (not segment #)\n", shm_ID);
    printf("This shared memory doesn't get a true segment number until this process adds it to its segment table by attaching to it.\n");
    printf("\n");
    printf("Parent: My pid is %d; now spawning a child after setting the shared integer to 0\n", getpid());
    
    shared = shmat(shm_ID, NULL, 0);
    if( (int*)shared == (void *)-1) //have to cast of get an error
        printf("Damn: %s", strerror(*shared) );

    *shared = 0; //set it to zero

    //NOW FORK A CHILD AND SHARE SOME MEMORY 
    pid = fork();
    if(pid < 0)  //failed
    {
        printf("FAILED FORK! NO CHILD CREATED!\n");
    }
    else if (pid > 0) //parent execution
    {
        printf("Parent: My pid is %d, spawned a child with pid of %d; please enter an integer to be stored in shared memory:\n", getpid(), pid);
        scanf("%d", shared);
        //printf("parent: shared int set to %d\n", *shared);
        while(*shared != 0) ; //spin loop
        printf("Parent: the child has re-zeroed our shared integer\n");
        printf("Parent: Child terminated; parent successfully removed segment whose ID # was %d\n", shm_ID);
    }
    else // pid == 0 child execution
    {
        printf("Child: My pid is %d, my parent's pid is %d; the shared integer value is currently 0; I'll spin until it's NOT 0\n", getpid(), getppid());
        while(*shared == 0) ; //spin loop
        printf("Child: The value in the shared integer is now %d; I'll set it back to 0\n", *shared);
        *shared = 0; //set back to zero
        printf("Child process terminating\n");
    }

    errorcode= shmctl(shm_ID, IPC_RMID, NULL); //2nd argument marks segment to be destroyed
    if(errorcode == -1)//error occurred
        printf("Damn: %s", strerror(errorcode) );
        
    errorcode = shmdt(shared); //detatched from shared mem
    if(errorcode == -1)//error occurred
        printf("Damn: %s", strerror(errorcode) );
    
    return 0;
}
