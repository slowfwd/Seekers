#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include "init.h"


void *objectDetect(void *arg)
{
	
	startDetect();
	//return;
}


void *objectSearch(void *arg)
{
    	startSearch();
	//return ;
}

void errorDisp(int x)
{
	if (x)
	{
        	 printf("ERROR; return code from pthread_create() is %d\n", x);
     	}
	//return;
}

int main()
{
	pthread_t threads[2];
	int retVal[2];
	retVal[0] = pthread_create(&threads[0], NULL, objectDetect, NULL);
	errorDisp(retVal[0]);
	retVal[1] = pthread_create(&threads[1], NULL, objectSearch, NULL);
	errorDisp(retVal[1]);
	
	pthread_exit(NULL);
	return 0;
}
