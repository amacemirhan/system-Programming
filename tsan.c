#include <pthread.h>
#include <stdio.h>
int global;

void *Thread1(void *x){
global++;
return NULL;
}

int main() {
pthread_t t[2];
pthread_create(&t[0], NULL, Thread1,NULL);
global = 100;
pthread_join (t[0],NULL);
return 0;
}
