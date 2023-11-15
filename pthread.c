#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *A(void *argumentPointer) {
	pthread_t id = pthread_self(); 
	while(1) {
		printf("thread ID (TID) :: %lu\n", id);
		sleep(1);
	}
	return NULL;
}

void *B(void *argumentPointer) {
	pthread_t id = pthread_self();
	while(1) {
		printf("thread ID (TID) :: %lu\n", id);
		sleep(1);
	}
	return NULL;
}

int main() {
		pthread_t threadID1;
		pthread_t threadID2;
		
		printf("Create Thread\n");
		pthread_create(&threadID1, NULL, A, NULL);
		pthread_create(&threadID2, NULL, B, NULL);
		
		printf("Main Thread is now waiting for Child Thread\n");
		
		pthread_join(threadID1, NULL);
		pthread_join(threadID2, NULL);
		
		printf("Main Thread finish waiting Child Thread\n");
		return 0;
}
