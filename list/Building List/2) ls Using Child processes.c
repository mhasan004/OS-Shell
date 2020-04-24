// Takeaway 2: Using child processes to execute a command and continue with rest of code in parent process



#include <stdio.h>                                              // IO
#include <stdlib.h>                                             // for exist(1)
#include <unistd.h>                                             // for pid_child, getpid(), etc
#include <sys/types.h>                                          // for pid_child, getpid(), etc
#include <string.h>                                             // for strlen (length of char array)
#include <sys/wait.h>                                           // wait()
#include <fcntl.h>		                                        // F_DUPFD

/* ***FINALLY UNDERSTAND WHY WE USE CHILD PROCESSES!***
    WHAT IS EXEC? WHAT ARE ALL THE DIFFERENT TYPES OF IT?
    exec---   ex: execL, execV, execP
    exec---("command", __arguments__ )
    * With L: comma seperated arguments
    * With V: Vector (arry of string arguments)
    * With P: Path (include the search path for executable), can run 'ls' if u specify the bin file
    
    * execv() - wipes out all variables and anything below it wont run!
    * SOLUTION: NEED TO RUN EXECV IN A CHILD PROCESS. LET IT END, AND CONTINUE CODE 
*/
// fd[0] = read end of pipe
// fd[1] = writ enf of pipe
// fd[3] = both
// int pipe( int fd[0 or 1 or 3)            


void execv_with_fork(){
    pid_t pid_child, pid_child2, pid;
    char *args[] = {"ls", "-l", NULL};

    pid_child = fork();                                            // 1) FORK 1  (Parent and Child Processes now)                               

    if (pid_child == 0){                                           // 2) CHILD: 
        execvp("ls", args);                                        // 3) Executing the 'ls -l' command on child and letting it end
        exit(0);
    }

    else{                                                          // COPY OF MAIN PARENT: can now continue with code after execv
        wait(NULL);
    }
}

int main(char *argv[]){
    printf("\n****************************** 1\n");
    execv_with_fork();
    printf("\n****************************** 2\n");
    return 0;                                                      // kills the whole proces linux had open
}