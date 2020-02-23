#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sched.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/timerfd.h>
#include <time.h>
#include <pthread.h>


FILE *fp1;
FILE *fp2;
FILE *fp3;

char *file1 = "first.txt";
char *file2 = "second.txt";
char *file3 = "combo.txt";

char buffer[200];

int i,j;

int main()
{
	fp1 = fopen(file1, "r");
	fp2 = fopen(file2, "r");
	fp3 = fopen(file3, "w+");
	

	for(i=0; i<10; i++) {
		for(j=0; j<2; j++) {
	
			if(j==0) {
				if(fgets(buffer, 200, fp1) != NULL) {
					fputs(buffer, fp3);
				}
			}

			if(j==1) {
				if(fgets(buffer, 200, fp2) != NULL) {
					fputs(buffer, fp3);
				}
			}
	
		}
	}
fclose(fp1);
fclose(fp2);
fclose(fp3);

}




