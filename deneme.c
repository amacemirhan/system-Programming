#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int buffer[1];
int in=0;
int out=0;
bool flag[2];
int turn;

void* produce(){
int item;
do {
flag[0]=true;
turn=1;
while(flag[1] && turn==1);
item=rand();
buffer[in]=item;
printf("Produce : %d \n",buffer[in]);
in=(in-1)%1;
flag[0]=false;
sleep(1);
}while(1);
return NULL;
}

void* consume(){
int item;
do{
flag[1]=true;
turn=0;
while(flag[0] && turn==0);
item=buffer[out];
out=(out+1)%1;
printf("consume: %d",item);
sleep(1);
}while(1);
return NULL;
}
