#include <stdlib.h>
#include <stdio.h>

#include <pthread.h>
#include <unistd.h>

/*
guokd
#include <limit.h>
kdjfk
*/

#if 0
#include <limit.h>
#endif

void* business_thread(void * arg)
{
    while(1){
    	malloc(rand()%10);
    	printf("malloc \n");
    	sleep(1);
    }
}

int main()
{
    pthread_t thread = 0;
    int ch = 0;
    
    pthread_create(&thread, NULL, business_thread, NULL);
    
    while(1){
    	ch = getchar();
    	if (EOF == ch)
    		exit(0);
    	else
    		testShowMallocCount();
    }

    return 0;
}

