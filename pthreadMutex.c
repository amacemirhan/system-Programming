#include <stdio.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t mutex;//PTHREAD_MUTEX_INITIALIZER;
int shared_data=1;
int buffer[5];
int index=0;
int out=0;
void *consumer(){
	int item;
        while(1){
		while(out==index);
                pthread_mutex_lock(&mutex);
                item=buffer[out];
                printf("Consumer consume %d in buffer location %d \n",item,out);
                out=(out+1)%5;
                pthread_mutex_unlock(&mutex);
		sleep(1);
                }
}

void *producer(){
int item;
        while(1){
		while(index==out-1);
		item=rand();
       		pthread_mutex_lock(&mutex);
        	buffer[index]=item;
        	printf("Producer produce %d at buffer location %d \n",item,index);
		index=(index+1)%5;
        	pthread_mutex_unlock(&mutex);
		sleep(1);
		}
}


int main(){
	pthread_t thread1;
	pthread_t thread2;
	pthread_mutex_init(&mutex,NULL);
	pthread_create(&thread2,NULL,producer,NULL);
	pthread_create(&thread1,NULL,consumer,NULL);
	void *thread_result;
	pthread_join(thread1,&thread_result);
	pthread_join(thread2,&thread_result);
	return 0;
}
