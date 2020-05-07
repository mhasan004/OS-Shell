//READ.me
//	1) Save the file as 'shell.c'. Then compile: gcc shell.c -o shell.
//	2) Save path, list, tree, and exit and compile: gcc path.c -o path, etc...
//	3) run the shell as ./shell
// 	4) now that the shell is running to run the other commands just run the executbale file ex: ./list, ./path, etc...
//  5) Exit is also now implemented within the Shell

#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main() 
{ 
	pid_t pid;
	char buf[20];
	char quit[]="./exit";
	int max=20;

// Opens a file called history.txt which stores last 4 commands used
	FILE *fp;
	fp = fopen("./history.txt", "a+");
	


	printf("+"); 
	while(fgets(buf,max, stdin)){
		printf("+");

// getting rid of the last \n
		if (buf[strlen (buf) - 1] == '\n')
       			 buf[strlen (buf) - 1] = '\0';
// comparing the input to exit.	
		
		char * args[max];
		args[0] = strtok(buf," ");

		int i = 0;
		while(args[i]!=NULL){
			//printf("args[%d]:%s\n",i,args[i]);
			args[++i] = strtok(NULL," ");
		}
		
		pid= fork();
		
		if (pid==0){ 
			execvp(args[0],args);
			return 1;
		}
		fputs(buf, fp);
		fputs("\n", fp);

		waitpid(pid, NULL,0);
		if(strcmp (buf,quit) == 0){
			// Here we close the file pointer. But the only disadvantage is the fact that it depends on the location of the history file
			fclose(fp);
			system("tail -4 /home/faheem/Downloads/OS_Shell-master/history.txt");
			system("ls -l"); //List all contents of the directory
			printf("thank you, come again\n"); //Print final message 
			exit(1);
		}
							
	//	fflush(stdout);
		
	}

    return 0; 
} 
