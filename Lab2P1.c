//bmgbbr

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//initialize the size of array parameters
	struct arrayInfo {
		int colSize1;
		int rowSize1;
		int targetArray[20][20];
};
//create an instance of arrayInfo globally
struct arrayInfo info;
//initialize the filterArray parameters
int colSize2, rowSize2;

//initialize 2D array based on Column and Row sizes from file
int numberArray[20][20];
//initialize 2D array based on Column and Row sizes from file
int filterArray[1][3];

//function should perform convolution for each pthread and return the target array value
//to perform convolution
void *Convolution(void *t)
{	//pseudo code for this function is my previous attempt. I kept it as a reference to what is going on
	int sum;	
	int a,b;	
	int counter=0;
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
			else if (b==(info.colSize1-1))
			{
				info.targetArray[a][b] = (numberArray[a][b-1]*filterArray[0][0]) + (numberArray[a][b]*filterArray[0][1]);
				//sum = target1+target2;
				//info.targetArray[a][b] = sum;
			}
			else
			{
				info.targetArray[a][b] = (numberArray[a][b-1]*filterArray[0][0]) + (numberArray[a][b]*filterArray[0][1]) + (numberArray[a][b+1]*filterArray[0][2]);
				//sum = target1+target2+target3;
				//info.targetArray[a][b] = sum;
			}
			counter++;
		}
	}

	pthread_exit((void*) counter);	
}


int main(void)
{
	clock_t start[3], end[3];
	double total_time[3];	
	
	pthread_t thread_id;

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
////////////////////////////////////////////////////
//now have the desired arrays to begin convolution//
////////////////////////////////////////////////////
//1 thread
	int rc;
	int *numConvolutions;

	start[1]=clock();

	pthread_t thread1;
	//create a thread
	rc = pthread_create(&thread1, NULL, Convolution, (void *) &info);
	if (rc){
          printf("ERROR; return code from pthread_create() is %d\n", rc);
          exit(-1);
	}
	//join the thread
	rc = pthread_join(thread1, (void**)&numConvolutions);
		
       		if (rc) 
		{
			printf("ERROR; return code from pthread_join() is %d\n", rc);
          		exit(-1);
        	}
	printf("The number of convolutions with 1 thread: %d\n", numConvolutions);

	end[1]=clock();
	total_time[1] = ((double) end[1]-start[1]);
	printf("total time with 1 thread: %lf\n\n", total_time[1]);
////////////////////////////////
//a thread per row (2 threads)

	start[2]=clock();	

	pthread_t thread2[2];
	//create 2 threads		
	for(i=0;i<info.rowSize1;i++)
	{
		rc = pthread_create(&thread2[i], NULL, Convolution, (void *) &info);
		if (rc)
		{
          		printf("ERROR; return code from pthread_create() is %d\n", rc);
          		exit(-1);
		}
	}
	//join 2 threads
	for(i=0;i<info.rowSize1;i++)
	{
		rc = pthread_join(thread2[i], (void**)&numConvolutions);
		
       		if (rc) 
		{
			printf("ERROR; return code from pthread_join() is %d\n", rc);
          		exit(-1);
        	}
	}
	printf("The number of convolutions with a thread for each row: %d\n", numConvolutions);		
	
	end[2]=clock();
	total_time[2] = ((double) end[2]-start[2]);
	printf("total time with a thread for each row: %lf\n\n", total_time[2]);
/////////////////////////////////
//a thread for every element (20 threads)

	start[3]=clock();	

	pthread_t thread3[20];
	//create 20 threads		
	for(i=0;i<info.rowSize1*info.colSize1;i++) 
	{
		rc = pthread_create(&thread3[i], NULL, Convolution, (void *) &info);
		if (rc)
		{
          		printf("ERROR; return code from pthread_create() is %d\n", rc);
          		exit(-1);
		}

	}
	//join 20 threads
	for(i=0;i<info.rowSize1*info.colSize1;i++)
	{
		rc = pthread_join(thread3[i], (void**)&numConvolutions);
       		if (rc) 
		{
			printf("ERROR; return code from pthread_join() is %d\n", rc);
        	  	exit(-1);
        	}
	}
	printf("The number of convolutions with a thread for each element: %d\n", numConvolutions);

	end[3]=clock();
	total_time[3] = ((double) end[3]-start[3]);
	printf("total time with a thread for each element: %lf\n\n", total_time[3]);
//////////////////////////////////

	//iterate through targetArray
	for (i=0; i<info.rowSize1; i++) {
		for(j=0; j<info.colSize1; j++) {
			printf(" target array value: %d\n", info.targetArray[i][j]);
		}
	}
	pthread_exit(NULL); 
	fclose(myFile); //close the file
			
	return 0;
}








