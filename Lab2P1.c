//bmgbbr

#include <pthread.h>
#include <stdio.h>

//initialize the size of array parameters
	int colSize1, rowSize1;
	int colSize2, rowSize2;


int main(void)
{
	//open the desired file
    	FILE *myFile;
    	myFile = fopen("2x10.txt", "r");
	//myFile = fopen("20x10.txt", "r");

						//Number Array
	//get colSize1
	fscanf(myFile, "%d", &colSize1);
	//get rowSize1
	fscanf(myFile, "%d", &rowSize1);
	//initialize 2D array based on Column and Row sizes from file
	int numberArray[colSize1][rowSize1];

    	int i,j;

	//read file into array
   	for (i=0; i<colSize1; i++) {
		for(j=0; j<rowSize1; j++) {
        		fscanf(myFile, "%d", &numberArray[i][j]);
   		}
	}
	//print array (for testing)
    	for (i=0; i<colSize1; i++) {
		for (j=0;j<rowSize1; j++) {
        		printf("Number is: %d\n", numberArray[i][j]);
		}
    	}
						//Filter
	//get colSize2
	fscanf(myFile, "%d", &colSize2);
	//get rowSize2
	fscanf(myFile, "%d", &rowSize2);
	//initialize 2D array based on Column and Row sizes from file
	int filterArray[colSize2][rowSize2];

	//read files into filter array
	for(i=0;i<colSize2;i++) {
		for(j=0;j<rowSize2;j++) {
			fscanf(myFile, "%d", &filterArray[i][j]);
		}
	}

	//print filter array (for debug)
	for(i=0;i<colSize2;i++) {
		for(j=0;j<rowSize2;j++) {
			printf("Filter Number is: %d\n", filterArray[i][j]);
		}
	}
	//close the file
	fclose(myFile);



	return 0;
}


