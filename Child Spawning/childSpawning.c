/*  (c) Gabby Strevay 2023
 *  C program that spawns (forks) three children without having the parent wait for child
 *  compltion before the parent continues to maximize concurrency.
 *  Additionally, child #2 uses an execv system service call to replace the program in its 
 *  text section with a seperate program
 *
*/

#include <stdio.h>
#include <unistd.h> //header that includes fork()

int main()
{
    pid_t  pid;  
    int num = 1; //using to increment for the 3 childs
    for (num=1; num <4; num++) {
        pid= fork();
        if (pid < 0)
            printf("FAILED FORK! NO CHILD CREATED!\n");
        else if (pid > 0) //parent execution 
            printf("Parent, my pid is %d: Spawned child #%d whose pid is %d\n", getpid(),num, pid);
        //  pid == 0 child execution
        else {
            printf("I am child #%d, my pid is %d; my parent's pid is %d\n", num, getpid(), getppid());
            if (num==2) 
                execv("child2.exe", NULL);
            break;
        }
    }
return 0;
}
