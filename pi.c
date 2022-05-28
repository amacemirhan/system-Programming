#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
//Mehmed Emirhan Amac - 170420517
int n,s=0;
float top=0.0;
void *myThread(void *vargp)
{
    for(int i=1;i<n;i=i+2){
    if(s){
        top=top-1.0/i;
        s=0;
    }else{
        top=top+1.0/i;
        s=1;
    }
}
printf("%f\n",4*top);
    return NULL;
}

void main(){

printf("n:");
scanf("%d",&n);

pthread_t thread_id;
    pthread_create(&thread_id, NULL, myThread, NULL);
    pthread_join(thread_id, NULL);
    exit(0);
}