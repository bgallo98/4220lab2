//bmgbbr

#include <pthread.h>
#include <stdio.h>

//initialize the size of array parameters
	int colSize1, rowSize1;
	int colSize2, rowSize2;

//function should perform convolution for each pthread and return the target array value
//to perform convolution
//int *Convolution(void *



int main(void)
{
	//open the desired file
    	FILE *myFile;
    	myFile = fopen("2x10.txt", "r");
	//myFile = fopen("20x10.txt", "r");

						//Number Array
	//get colSize1
	fscanf(myFile, "%d", &rowSize1);
	//get rowSize1
	fscanf(myFile, "%d", &colSize1);
	//initialize 2D array based on Column and Row sizes from file
	int numberArray[rowSize1][colSize1];

    	int i,j;

	//read file into array
   	for (i=0; i<rowSize1; i++) {
		for(j=0; j<colSize1; j++) {
        		fscanf(myFile, "%d", &numberArray[i][j]);
   		}
	}
	//print array (for testing)
    	for (i=0; i<rowSize1; i++) {
		for (j=0;j<colSize1; j++) {
        		printf("Number is: %d\n", numberArray[i][j]);
		}
    	}
						//Filter
	//get colSize2
	fscanf(myFile, "%d", &rowSize2);
	//get rowSize2
	fscanf(myFile, "%d", &colSize2);
	//initialize 2D array based on Column and Row sizes from file
	int filterArray[rowSize2][colSize2];

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

	/*pthread_t thread0; // 

	void 

	int targetArray[colSize1*rowSize1];//create 1D array with the same # of elements as the first array

	for (i=0;i<colsize*/
	
	int a = 0;
	int b = 0;
	int sum = 0;
	
	//printf("%d , %d , %d , %d", rowSize1, colSize1, rowSize2, colSize2);

	for(a=0;a<rowSize1;a++)
	{
		for(b=0;b<colSize1;b++)
		{
			int target1;								             //  v--- doesnt change
			printf("\n%d\n", target1 = numberArray[a][b-1]*filterArray[0][0]); //starting 0,-1 -- 0,[0]
			int target2;
			printf("\n%d\n", target2 = numberArray[a][b]*filterArray[0][1]);  //starting 0, 0 --  0,[1]
			int target3;
			printf("\n%d\n", target3 = numberArray[a][b+1]*filterArray[0][2]);  //starting 0,1 -- 0,[2]
		
			if (b==0)
			{
				sum = target2+target3;
				printf("\n target is %d\n", sum);
			}
			else if (b == 9)
			{
				sum = target1+target2;
				printf("\n target is %d\n", sum);
			}
			else
			{
				sum = target1+target2+target3;
				printf("\n target is %d\n", sum);
			}
		}
	}	
		
	return 0;
}








