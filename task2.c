#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    int pipefd[2];
    //pid_t cpid;
    char buf;
    pipe(pipefd);   //pipe is a way of communication between a child process and parent; pipefd[0] reading; pipefd[1] writing

    if(fork()==0){
        close(pipefd[0]);
        printf("[son] pid %d from [parent] pid %d \n",getpid(),getppid()); 
        printf("[son] sleeping for 5 seconds \n");
        sleep(5);
        printf("[son] waking up\n");
        write(pipefd[1],"BYE",sizeof("BYE"));
        close(pipefd[1]);
        exit(EXIT_SUCCESS);

    }
    close(pipefd[1]);
    printf("[parent] %d waiting \n",getpid());
    while (read(pipefd[0], &buf, 1) > 0);
    printf("[parent] %d received message from child \n",getpid());
    close(pipefd[0]);
    return 0;
}
