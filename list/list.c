// GOAL:: make a execv command using child -. would print results to stdout. WIll use 'dupt' to paste the contents of stdout to a file instead
#include <stdlib.h>                                                 // system() to clear screen
#include <stdio.h>                                                  // rename file using rename()
#include <unistd.h>                                                 // sleep(), F_OK
#include <stdbool.h>                                                // bool, true, false
#include <errno.h>                                                  // errno
#include <sys/types.h>                                              // for pid_child, getpid(), etc
#include <sys/wait.h>                                               // wait()
#include <fcntl.h>                                                  // read/write permission:  O_RDWR | O_CREAT
#include <sys/stat.h>                                               // access perm: S_IRUSR | S_IWUSR
#include <string.h>                                                 // strerror

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


void execv_with_fork(char *old_name)
{
    pid_t pid_child, pid_child2, pid;
    char *args[] = {"ls", "-l", NULL};
    pid_child = fork();                                             // 1) FORK 1  (Parent and Child Processes now)                               
    
    if (pid_child == 0){                                            // 2) CHILD: 
        int fd = open(old_name, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);   
        dup2(fd, 1);                                                    // dup2: Make stdout go to file
        close(fd);                                                      // fd no longer needed - the dup'ed handles are sufficient

        execvp("ls", args);                                             // 3) Executing the 'ls -l' command on child and letting it end
        exit(0);
    }
    else{                                                               // COPY OF MAIN PARENT: can now continue with code after execv
        wait(NULL);
    }
}

int print_file(char *old_name)
{
	int returnval;
    int fd;                                                             // file descriptor
    char buffer[fd];                                                    // char buffer for read

    errno = 0;
    fd = open(old_name, O_RDWR|O_CREAT);                                //opening the file, if it dont exit, will create it
    
    if(fd < 0){                                                         // if file dont exist, let me know
        printf("\n Failed to open file with error [%s]\n",strerror(errno));
        return (1);
    }

    // Opened the file can now read and write here
    size_t lengthOfFile = read(fd, buffer, sizeof(buffer)) ;            // READ THE FILE. FUNCTION RETURNS LENGTH OF WHAT IT READS. passed in the file opened id, the char buffer, and the size of the buffer (last index)
    write(1, buffer, lengthOfFile);                                     // PRINT THE CONTENTS OF THE BUFFER
    close(fd);   
}

void list(){
    char old_name[] = "t1.txt";                                     // old file name  
    char new_name[] = "tree.txt";                                   // new file name

    // 1) Clear screen:
    system("clear");                                                // clear screen
               
    // 2) Running command: ls -l (print what it would print in stdout to file)
    execv_with_fork(old_name);

    // 3) print the results of the file to stdout
    print_file(old_name);

    // 3) Change file name:
    change_fileName(old_name, new_name);
}

int main()
{
    list();
    return 0; 
}