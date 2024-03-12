Contained are programs involving thread creation and usage 

hw2.c 
  - Program portraying thread creation and the passing of data (a letter in this case) when creating a thread
    
hw3.c
  - Program portraying thread creation and the sharing of a global variable between the two threads

hw6.c 
  - Program portraying inter-process communication via shared memory
  - Parent process will fork a child and use system service calls shmget, assigns a block of memory (enough for an integer here), and shmat, attaches the shared memory to the process, to share memory between the parent process and child process
