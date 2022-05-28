#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
void *thread_routine(){
	//sleep(30);
	fork();
	printf("yeni uretilen thread calisti.\n");
}

int main(){
	pthread_t yeni;
	pthread_create(&yeni,NULL,thread_routine,NULL);
	printf("Ana thread calisiyor.\n");
	sleep(3);
	//pthread_cancel(yeni);
	return 0;

}
