#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#define true 1
#define false 0
i=0;
int lock=0;
void *f(){
printf("thread girdi\n");
while (test_and_set(&lock)); /* do nothing */
i++;
printf("%d\n",i);
i--;
lock = false;
printf("thread cıkti\n");

}

int test_and_set(int *target)
{
int rv = *target;
*target = true;
return rv;
}

int main(){
	pthread_t pro[2];
	for(int i = 0; i < 2; i++) {
        pthread_create(&pro[i], NULL, (void *)f, NULL);
    }
    for(int i = 0; i < 2; i++) {
        pthread_join(pro[i], NULL);
    }
    return 0;
}
