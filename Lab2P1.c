//bmgbbr

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//initialize the size of array parameters
	struct arrayInfo {
		int colSize1;
		int rowSize1;
		int targetArray[20][10];
};
//create an instance of arrayInfo globally
struct arrayInfo info;
//initialize the filterArray
int colSize2, rowSize2;

//initialize 2D array based on Column and Row sizes from file
int numberArray[20][10];
//initialize 2D array based on Column and Row sizes from file
int filterArray[1][3];




//function should perform convolution for each pthread and return the target array value
//to perform convolution
void *Convolution(void *args_thread)
{		
	//int sum;
	int a,b;	

	for(a=0;a<info.rowSize1;a++)
	{
		for(b=0;b<info.colSize1;b++)
		{
			/*int target1;								          
			target1 = numberArray[a][b-1]*filterArray[0][0]; //starting 0,-1 -- 0,[0]
			int target2;
			target2 = numberArray[a][b]*filterArray[0][1];  //starting 0, 0 --  0,[1]
			int target3;
			target3 = numberArray[a][b+1]*filterArray[0][2];  //starting 0,1 -- 0,[2]
			*/
			if (b==0)
			{
				info.targetArray[a][b] = (numberArray[a][b]*filterArray[0][1]) + (numberArray[a][b+1]*filterArray[0][2]);
				//sum = target2+target3;
				//info.targetArray[a][b] = sum;
			}
			else if (b==9)
			{
				info.targetArray[a][b] = (numberArray[a][b-1]*filterArray[0][0]) + (numberArray[a][b]*filterArray[0][1]);
				//sum = target1+target2;
				//info.targetArray[a][b] = sum;
			}
			else
			{
				info.targetArray[a][b] = (numberArray[a][b-1]*filterArray[0][0]) + (numberArray[a][b]*filterArray[0][1]) +(numberArray[a][b+1]*filterArray[0][2]);
				//sum = target1+target2+target3;
				//info.targetArray[a][b] = sum;
			}
		}
	}

	pthread_exit(NULL);	
}


int main(void)
{
	//open the desired file
    	FILE *myFile;
    	myFile = fopen("2x10.txt", "r");
	//myFile = fopen("20X10.txt", "r");

						//Number Array
	//get colSize1
	fscanf(myFile, "%d", &info.rowSize1);
	//get rowSize1
	fscanf(myFile, "%d", &info.colSize1);
	
    	int i,j;

	//read file into array
   	for (i=0; i<info.rowSize1; i++) {
		for(j=0; j<info.colSize1; j++) {
        		fscanf(myFile, "%d", &numberArray[i][j]);
   		}
	}
	//print array (for testing)
    	for (i=0; i<info.rowSize1; i++) {
		for (j=0;j<info.colSize1; j++) {
        		printf("Number is: %d\n", numberArray[i][j]);
		}
    	}
						//Filter
	//get colSize2
	fscanf(myFile, "%d", &rowSize2);
	//get rowSize2
	fscanf(myFile, "%d", &colSize2);
	
	//read files into filter array
	for(i=0;i<rowSize2;i++) {
		for(j=0;j<colSize2;j++) {
			fscanf(myFile, "%d", &filterArray[i][j]);
		}
	}
	//print filter array (for debug)
	for(i=0;i<rowSize2;i++) {
		for(j=0;j<colSize2;j++) {
			printf("Filter Number is: %d\n", filterArray[i][j]);
		}
	}
	//close the file
	fclose(myFile);
//////////////////////////////////now have the desired arrays to begin convolution

	pthread_t thread_id;

	int rc;
	rc = pthread_create(&thread_id,NULL,Convolution,(void*)&info);
	if (rc){
          printf("ERROR; return code from pthread_create() is %d\n", rc);
          exit(-1);
	}
	int a,b;
	//iterate through targetArray
	for (a=0; a<info.rowSize1; a++) {
		for(b=0; b<info.colSize1; b++) {
			printf(" target array value: %d\n", info.targetArray[a][b]);
		}
	}
	pthread_exit(NULL); 
			
	
		

		
	return 0;
}








