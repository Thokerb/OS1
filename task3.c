#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

//handler functions
void child_sigurs1(){
  printf("[child] received sigurs1\n");
}

void child_sigurs2(){
  printf("[child] received sigurs2, can stop\n");
  exit(0);
}

void childHandler(){
  printf("[parent] child finished, can stop\n");
  exit(0);
}

void alarmHandler(){
  printf("[parent] 3 seconds passed\n");
}


 int main()
 {
    
    pid_t childPid = 0;
     if((childPid=fork())==0){
        //child process
        //handler of child process
        struct sigaction saSig1;
        saSig1.sa_handler = child_sigurs1;
        saSig1.sa_flags=SA_RESTART;
        struct sigaction saSig2;
        saSig2.sa_handler = child_sigurs2;
        saSig2.sa_flags=SA_RESTART;
        sigaction(SIGUSR2, &saSig2, NULL);
        sigaction(SIGUSR1, &saSig1, NULL);

        sigset_t mask;
        sigemptyset (&mask); //create an empty set
	      sigaddset (&mask, SIGUSR2); //add the signal, which we want to block
        printf("[child] block SIGURS2 \n");
        sigprocmask(SIG_BLOCK,&mask,NULL);

        //sleep for 13 seconds
        int i = sleep(13);
        while (i > 0)
        {
          i = sleep(i);
        }
        printf("[child] unblock SIGURS2 \n");
        sigprocmask(SIG_UNBLOCK,&mask,NULL);
        while (1)
        {
          //wait
        }
        
     }
     else{
    //parent process

    //handler for child and alarm
    struct sigaction handler;
    handler.sa_handler = childHandler;
    handler.sa_flags = SA_RESTART;
    sigaction(SIGCHLD,&handler,NULL);

    struct sigaction handler2;
    handler2.sa_handler = alarmHandler;
    handler2.sa_flags = SA_RESTART;
    sigaction(SIGALRM,&handler2,NULL);

    //wait 3 seconds
    alarm(3);
    pause();

    printf("[parent] sending SIGURS2\n");
    kill(childPid,SIGUSR2);
    printf("[parent] sending SIGURS1\n");
    kill(childPid,SIGUSR1);
    while(1){
      alarm(3);
      pause();
      printf("[parent] sending SIGURS1\n");
      kill(childPid,SIGUSR1);

    }
 }
       
 }
 