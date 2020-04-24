// TAKEAWAY 1: After running a command in execv, code after it dont run, so need to use child processes. See 2)


#include <stdio.h>                                              // IO
#include <stdlib.h>                                             // for exist(1)
#include <unistd.h>                                             // for pid_child, getpid(), etc
#include <sys/types.h>                                          // for pid_child, getpid(), etc
#include <string.h>                                             // for strlen (length of char array)
#include <sys/wait.h>                                           // wait()
#include <fcntl.h>		                                        // F_DUPFD

/* WHAT IS EXEC? WHAT ARE ALL THE DIFFERENT TYPES OF IT?
    exec---   ex: execL, execV, execP
    exec---("command", __arguments__ )
    * With L: comma seperated arguments
    * With V: Vector (arry of string arguments)
    * With P: Path (include the search path for executable), can run 'ls' if u specify the bin file
    
    * execv() - wipes out all variables and anything below it wont run!
*/
// fd[0] = read end of pipe
// fd[1] = writ enf of pipe
// fd[3] = both
// int pipe( int fd[0 or 1 or 3)

#define STDIN_FILE 0
#define STDOUT_FILE 1
#define READ 0                
#define WRITE 1                


// 1) ls -l (execvp end after it executes, it replaces everything in the current memory space (vars, etc) to the command im trying to run)
void execute_lsl_execvp(){
    char *args[] = {"ls","-l", NULL};
    execvp(args[0], args);               // runing the first command (args[0]), and all the other params of it
}

// 2) ls -l
void execute_lsl_execl(){
    execl("ls", "-l", NULL);              // runing the first command (args[0]), and all the other params of it
}

// 3) ls -l
int execute_lsl_execl2(){
    execl("/bin/ls", "ls","-l", NULL);
}

int main(char *argv[]){
    printf("\n****************************** 1\n");
    
    // execute_lsl_execvp();
    execute_lsl_execl2();
    
    printf("\n****************************** 2\n");

    return 0;                             // kills the whole proces linux had open
}