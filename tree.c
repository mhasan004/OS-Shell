#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

void tree() {

	int dir0;
	dir0 = mkdir("Dir0", 0777);	// create the directory dir0
	if (dir0 == 0) { // if dir0 exist

		printf("Creating Dir0 successful!\n"); 
		
		FILE *fp = fopen("Dir0//t1.txt", "a");  // open/create t1.txt inside dir0
		if (fp!=NULL) {
			fclose(fp);
			printf("Creating t1.txt successful!\n");
		}
		else { 
			printf("Creating t1.txt failed!\n");
		}		
		
		FILE *fp1 = fopen("Dir0//t2.txt", "a"); // open/create t2.txt inside dir0
		if (fp1!=NULL) {
			fclose(fp1);
			printf("Creating t2.txt successful!\n");
		}
		else { 
			printf("Creating t2.txt failed!\n");
		}	
	
		FILE *fp2 = fopen("Dir0//t3.txt", "a"); // open/create t3.txt inside dir0
		if (fp2!=NULL) {
			fclose(fp2);
			printf("Creating t3.txt successful!\n");
		}
		else { 
			printf("Creating t3.txt failed!\n");
		}

		int dir1;
 		dir1 = mkdir("Dir0/Dir1", 0777);  // create the directory dir1 inside dir0	
		if (dir1 == 0) {
			printf("Creating Dir1 sucessfuly!\n");
				}
		 else {
			printf("Creating Dir1 failed!\n");		
		}
	} else { 
		printf("Creating Dir0 failed!\n");
	}		

}

int main(int agrc, char *argv[]) {

	tree();
			
	return 0;
}
