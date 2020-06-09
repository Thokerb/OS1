#include <stdlib.h>
#include <stdio.h> 
#include <unistd.h>
#include <sys/wait.h>


unsigned fib(unsigned n) {
  if(n <= 1) return n;
  return fib(n - 1) + fib(n - 2);
}

/*
Fork:
Negative Value: creation of a child process was unsuccessful.
Zero: Returned to the newly created child process.
Positive value: Returned to parent or caller. The value contains process ID of newly created child process.
*/
int main(int argc, char const *argv[])
{
    if(argc != 2){
        return EXIT_FAILURE;
    }
    int n = atoi(argv[1]);
    printf("n: %d \n",n);
    for(int i = 0; i < n; i++)
    {
        if(fork() == 0) 
        { 
            unsigned int res = fib(40);
            printf("[child] %d [son] pid %d from [parent] pid %d fib: %d \n",i,getpid(),getppid(),res); 
            return EXIT_SUCCESS; 
        } 
    }
    //waits for all child process to die before continuing
    while(wait(0)>0);
    return EXIT_SUCCESS;
}
