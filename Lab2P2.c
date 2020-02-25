#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sched.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/timerfd.h>
#include <time.h>
#include <pthread.h>

#define MY_PRIORITY 51 //kernel is priority 50

struct itimerspec itval;
struct sched_param param;
struct timespec val;

FILE *fp1;
FILE *fp2;
FILE *fp3;


char *file1 = "first.txt";
char *file2 = "second.txt";
char *file3 = "combo.txt";


char buffer[200];
//char newArray[20][200]; // this is the array that the buffer will load into

void *Read1()
{

//create timer 
	int tfd, InitTime_seconds=0,InitTime_nseconds=0,errno, result, check;
	int Period_seconds=0, Period_nseconds=80000000;

	//itval.it_value.tv_nsec = InitTime_nseconds;

	clock_gettime(CLOCK_MONOTONIC, &val);
	
	val.tv_nsec += InitTime_nseconds;

	clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &val, NULL);
	
	/*tfd = timerfd_create(CLOCK_MONOTONIC, 0);

	clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &val, NULL);
	if(tfd == -1)
	{
		printf("timerfd_create() failed: errno=%d\n",errno);
	}
	printf("created timerfd %d\n", tfd);

	check = timerfd_settime(tfd, 0, &itval, NULL);
	if(check == -1)
	{
		printf("timerfd_settime() failed: check==%d\n", check);
	}
*/
//set scheduler
	param.sched_priority = MY_PRIORITY;
	int ret_sched;
	
	ret_sched = sched_setscheduler(0, SCHED_FIFO, &param);

	if(ret_sched!=0)
	{
		printf("ERROR!! sched_setscheduler() not successful\n");
	}
//////while loop
	while(!feof(fp1))
	{
		result = clock_gettime(CLOCK_MONOTONIC, &val);
		
		val.tv_nsec += 80000000;
	//read one line
		if(fp1 == NULL)
		{
			printf("Error! couldn't open file \n");
		}
		fgets(buffer, 200, fp1);
		printf("%s\n", buffer);

	//clock_nanosleep
		clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &val, NULL);
	}
	pthread_exit(NULL); 
}
//==================================================//
void *Read2()
{
	
//create timer
	int tfd, InitTime_seconds=0,InitTime_nseconds=40000000,errno, result, check;
	int Period_seconds=0, Period_nseconds=80000000;

	clock_gettime(CLOCK_MONOTONIC, &val);
	
	val.tv_nsec += InitTime_nseconds;
	
	clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &val, NULL);

	//itval.it_value.tv_nsec = InitTime_nseconds;
	
	/*tfd = timerfd_create(CLOCK_MONOTONIC, 0);
	if(tfd == -1)
	{
		printf("timerfd_create() failed: errno=%d\n",errno);
	}
	printf("created timerfd %d\n", tfd);

	check = timerfd_settime(tfd, 0, &itval, NULL);
	if(check == -1)
	{
		printf("timerfd_settime() failed: check==%d\n", check);
	}
	*/
//set scheduler
	param.sched_priority = MY_PRIORITY;
	int ret_sched;
	
	ret_sched = sched_setscheduler(0, SCHED_FIFO, &param);

	if(ret_sched!=0)
	{
		printf("ERROR!! sched_setscheduler() not successful\n");
	}
//////while loop
	while(!feof(fp2))
	{
		result = clock_gettime(CLOCK_MONOTONIC, &val);
		
		val.tv_nsec += 80000000;
	//read one line
		if(fp2 == NULL)
		{
			printf("Error! couldn't open file \n");
		}
		fgets(buffer, 200, fp2);
		printf("%s\n", buffer);

	//clock_nanosleep
		clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &val, NULL);
	}
	pthread_exit(NULL);
}
//================================================================//
void *Write()
{

	int tfd,InitTime_nseconds=20000000, errno, result, check, counter;
	int Period_seconds=0, Period_nseconds=40000000;

	clock_gettime(CLOCK_MONOTONIC, &val);
	
	val.tv_nsec += InitTime_nseconds;
	
	clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &val, NULL);

	//itval.it_value.tv_nsec = InitTime_nseconds;

	/*tfd = timerfd_create(CLOCK_MONOTONIC, 0);
	if(tfd == -1)
	{
		printf("timerfd_create() failed: errno=%d\n",errno);
	}
	printf("created timerfd %d\n", tfd);

	check = timerfd_settime(tfd, 0, &itval, NULL);
	if(check == -1)
	{
		printf("timerfd_settime() failed: check==%d\n", check);
	}
	*/
//set scheduler
	param.sched_priority = MY_PRIORITY;
	int ret_sched;
	
	ret_sched = sched_setscheduler(0, SCHED_FIFO, &param);

	if(ret_sched!=0)
	{
		printf("ERROR!! sched_setscheduler() not successful\n");
	}

//////while loop
	while(counter<16)
	{
		result = clock_gettime(CLOCK_MONOTONIC, &val);
		
		val.tv_nsec += 40000000;
//read one line
		if(fp3 == NULL)
		{
			printf("Error! couldn't open file \n");
		}
		fputs(buffer, fp3);
		printf("%s\n", fp3);
		counter++;

//clock_nanosleep
		clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &val, NULL);
	}
	pthread_exit(NULL);
}


int main()
{
	int rc1, rc2, rc3;
	
	fp1 = fopen(file1, "r");
	fp2 = fopen(file2, "r");
	fp3 = fopen(file3, "w");

	pthread_t thread[3];

	rc1 = pthread_create(&thread[0], NULL, Read1, NULL);
	if (rc1){
          printf("ERROR; return code from pthread_create() is %d\n", rc1);
          exit(-1);
	}
	
	pthread_t thread2;

	rc2 = pthread_create(&thread[1], NULL, Read2, NULL);
	if (rc2){
          printf("ERROR; return code from pthread_create() is %d\n", rc2);
          exit(-1);
	}
	
	pthread_t thread3;

	rc3 = pthread_create(&thread[2], NULL, Write, NULL);
	if (rc3){
          printf("ERROR; return code from pthread_create() is %d\n", rc3);
          exit(-1);
	}
	pthread_join(thread[0], NULL);
	pthread_join(thread[1], NULL);
	pthread_join(thread[2], NULL);

	fclose(fp1);
	fclose(fp2);
	fclose(fp3);

}

/*
int i,j;
	for(i=0; i<10; i++) {
		for(j=0; j<2; j++) {
	
			if(j==0) {
				if(fgets(buffer, 200, fp1) != NULL) {
					printf("%s\n", buffer[i]);
				}
			}

			if(j==1) {
				if(fgets(buffer, 200, fp2) != NULL) {
					printf("%s\n", buffer[i]);
				}
			}
	
		}
	}

*/
//this is the algorithm for putting the two files together into the output combo file
