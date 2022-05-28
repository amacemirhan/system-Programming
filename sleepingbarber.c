#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#define MAX_MUSTERI 20

//Mehmed Emirhan Amac - 170420517

sem_t musteriBekle;
sem_t berberUyuma;
sem_t koltukDurum;
sem_t koltukBekleme;

int comp=0;
int koltuk;
int musteriSay;

void *musteri(void *num);
void *berber(void *);

int main(){
pthread_t berberThread;
pthread_t musteriThread[MAX_MUSTERI];
int Sayi[MAX_MUSTERI];
int i;
printf("Koltuk sayisi giriniz:");
scanf("%d",&koltuk);
do{
printf("(max %d olacak) Musteri sayisini giriniz:",MAX_MUSTERI);
scanf("%d",&musteriSay);
}while(musteriSay>MAX_MUSTERI);

sem_init(&koltukDurum,0,1);
sem_init(&koltukBekleme,0,koltuk);
sem_init(&musteriBekle,0,0);
sem_init(&berberUyuma,0,0);

pthread_create(&berberThread, NULL, berber, NULL);

for(i=0; i<musteriSay;i++){
Sayi[i]=i;
pthread_create(&musteriThread[i],NULL, musteri, (void *)&Sayi[i]);
}

for(i=0; i<musteriSay; i++)
pthread_join(musteriThread[i],NULL);

comp=1;
sem_post(&berberUyuma);
pthread_join(berberThread,NULL);
return 0;

}

void *musteri(void *sayi)/*musteri Process*/
{
int numara=*(int *)sayi;

printf("Musteri %d dükkana girdi\n",numara);
sem_wait(&koltukBekleme);
printf("Musteri %d bekleme koltuguna gecti\n",numara);
sem_wait(&koltukDurum);
sem_post(&koltukBekleme);
printf("Musteri %d berberi uyandirdi\n",numara);
sem_post(&berberUyuma);
sem_wait(&musteriBekle);
sem_post(&koltukDurum);
printf("Musteri %d dukkandan ayrildi\n",numara);

}

void *berber(void *sacKesimi){/*berber Process*/
while(!comp){
printf("Berber uyuyor..\n");
sem_wait(&berberUyuma);
	if(!comp){
	printf("Berber sac kesiyor\n");
	sleep(3);
	printf("Sac kesimi bitti\n");
	sem_post(&musteriBekle);
	}
	else{
	printf("Dukkan kapandi\n");}
}
}
