#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#define yatak 20

sem_t ameliyat;
sem_t dinlenme;
//sem_t hastaGelme;
sem_t hastaHazir;
sem_t yataklar;
/*int hastaSayisi=0;
int doluYatak=3;*/
int value,value2;
void *hastaGelme(){
	while(1){
	printf("Yeni hasta yolda..\n");
	sleep(10);
	sem_post(&hastaHazir);
	printf("Yeni Hasta Geldi.\n");
	}
}
void *hasta(){
	while(1){
	sem_wait(&hastaHazir);
	sem_wait(&yataklar);
	printf("Hasta Yatirildi.");
	}
}
void *doktor(){
	while(1){
	sem_wait(&hastaHazir);
	sem_post(&dinlenme);
	printf("Doktor uyandirildi.\n");
	sem_wait(&ameliyat);
	printf("Doktor hastayi ameliyat ediyor.\n");
	sleep(2);
	sem_post(&ameliyat);
        }
	

}
void *doktor2(){
	while(1){
	sem_getvalue(&yataklar,&value);
	sem_getvalue(&dinlenme,&value2);
	printf("yataklar: %d , dinlenme: %d \n",value,value2);
	if(value<20){
	if(value2==0){
	sem_post(&dinlenme);}
	sem_wait(&ameliyat);
	printf("Doktor yatan hastayı ameliyat ediyor\n");
	sleep(2);
	sem_post(&yataklar);
	sem_post(&ameliyat);
	}else{
	sem_wait(&dinlenme);
	printf("Doktor dinlenmeye gitti.\n");
	}
	}
}
int main(){
	pthread_t thread1;
	pthread_t thread2;
	pthread_t thread3;
	pthread_t thread4;
	sem_init(&ameliyat,0,1);
	sem_init(&dinlenme,0,0);//doktor dinleniyor baslangicta
	//sem_init(&hastaGelme,0,1);
	sem_init(&hastaHazir,0,1);
	sem_init(&yataklar,0,yatak);
	pthread_create(&thread1,NULL,hasta,NULL); 
	pthread_create(&thread2,NULL,doktor,NULL); 
	pthread_create(&thread3,NULL,hastaGelme,NULL); 
	pthread_create(&thread4,NULL,doktor2,NULL); 
	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);
}
