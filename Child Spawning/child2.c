#include <stdio.h>
#include <unistd.h>

int main()
{
     printf("Process #%d, now running program ""child2.exe"" My parent's pid is %d\n", getpid(), getppid());
     return 0;
}
