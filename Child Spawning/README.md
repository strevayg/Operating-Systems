Child spawning is contained in this subdirectory 

hw1.c
  - Program that spawns three children and the second one 
  - Renamed the executable file for the 2nd child "child2.c" with the linux command
  - gcc child2.c -o child2.exe

hw6.c 
  - Program portraying inter-process communication via shared memory
  - Parent process will fork a child and use system service calls shmget, assigns a block of memory (enough for an integer here), and shmat, attaches the shared memory to the process, to share memory between the parent process and child process
