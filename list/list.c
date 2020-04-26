#include <stdlib.h>                                                 // system() to clear screen
#include <stdio.h>                                                  // rename file using rename()
#include <unistd.h>                                                 // sleep(), F_OK
#include <stdbool.h>                                                // bool, true, false
#include <errno.h>                                                  // errno
#include <sys/types.h>                                              // for pid_child, getpid(), etc
#include <sys/wait.h>                                               // wait()

bool check_file_exists(const char file[] )
{
    int return_val = access (file, F_OK);                           // -1 = file not found, error. 0 = no error, found file
    if (return_val == 0)
	{
        return true;
    }
    else{
        if (errno == ENOENT)
            printf ("\nFile %s does not exist\n", file);
        if (errno == EACCES)
            printf ("\nFile %s is not accessible\n", file);
        return false;
    } 
    return false;
}

void change_fileName(const char *old_name, const char *new_name)
{
    if (check_file_exists(old_name) == 1){                          // if the file exists, can chnage it
        int error_check = rename(old_name, new_name);               // if error_check == 0 -> no error 
    
        if(error_check == 0){ 
            printf("%s %s %s %s %s", "\nFile name changed from", old_name, "to", new_name, "\n"); 
        } 
        else{ 
            perror("\nError changing file name!\n"); 
        } 
    }

}


void execv_with_fork()
{
    pid_t pid_child, pid_child2, pid;
    char *args[] = {"ls", "-l", NULL};
    pid_child = fork();                                             // 1) FORK 1  (Parent and Child Processes now)                               

    if (pid_child == 0){                                            // 2) CHILD: 
        execvp("ls", args);                                         // 3) Executing the 'ls -l' command on child and letting it end
        exit(0);
    }
    else{                                                           // COPY OF MAIN PARENT: can now continue with code after execv
        wait(NULL);
    }
}

void list(){
    // 1) Clear screen:
    system("clear");                                                // clear screen
               
    // 2) Running command: ls -l
    execv_with_fork();

    // 3) Change file name:
    char old_name[] = "t1.txt";                                     // old file name  
    char new_name[] = "tree.txt";                                   // new file name
    change_fileName(old_name, new_name);
}

int main()
{
    list();
    return 0; 
}