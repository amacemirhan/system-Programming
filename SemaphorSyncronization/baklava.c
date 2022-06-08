#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
//Mehmed Emirhan Amac - 170420517

sem_t S;//Sut
sem_t U;//Un
sem_t G;//Seker
sem_t F;//Fistik
sem_t B;//Baklava
sem_t Ge;//Genel usta durduran
sem_t Tp;//Toptanci mesgul
pthread_t Us[6],Topt;
int bitti=0;
int ust[]={0,0,0,0,0,0};

void *usta(void *nv);

void *toptanci();

int main(){
	int i, n[6];
	

	
	sem_init(&S,0,0);//Sut
	sem_init(&U,0,0);//Un
	sem_init(&G,0,0);//Seker
	sem_init(&F,0,0);//Fistik
	sem_init(&B,0,0);//Baklava

	sem_init(&Ge,0,0);//Genel
	sem_init(&Tp,0,1);
	for(i=0;i<6;i++){
	n[i]=i+1;
	pthread_create(&Us[i],NULL,*usta,(void *)&n[i]);
	}
	pthread_create(&Topt,NULL,*toptanci,NULL);
	pthread_join(Topt,NULL);
}

void *usta(void *nv){
	int n=*(int *)nv;
	int value;
	while(bitti==0){
		sem_wait(&Ge);
		
		if(bitti==1)
		break;
	if(n==1 && ust[n-1]==1){
		printf("Usta %d Fistik ve Seker bekliyor.\n",(int)n);
		sem_wait(&F);
		sem_wait(&G);
		ust[n-1]=0;
	}else if(n==2 && ust[n-1]==1){
		printf("Usta %d Un ve Fistik bekliyor.\n",(int)n);
		sem_wait(&F);
		sem_wait(&U);
		ust[n-1]=0;
	}else if(n==3 && ust[n-1]==1){
		printf("Usta %d Un ve Seker bekliyor.\n",(int)n);
		sem_wait(&G);
		sem_wait(&U);
		ust[n-1]=0;
	}
	else if(n==4 && ust[n-1]==1){
		printf("Usta %d Sut ve Fistik bekliyor.\n",(int)n);
		sem_wait(&F);
		sem_wait(&S);
		ust[n-1]=0;
	}
	else if(n==5 && ust[n-1]==1){
		printf("Usta %d Sut ve Seker bekliyor.\n",(int)n);
		sem_wait(&S);
		sem_wait(&G);
		ust[n-1]=0;
	}
	else if(n==6 && ust[n-1]==1){
		printf("Usta %d Sut ve Un bekliyor.\n",(int)n);
		sem_wait(&S);
		sem_wait(&U);
		ust[n-1]=0;
	}else{
		sem_post(&Ge);
		continue;
	}
	printf("Usta %d baklava hazirladi.\n",(int)n);
	sem_post(&B);
	sleep(1);
	}
	printf("Usta %d ayrildi.\n",(int)n);
}

void *toptanci(){
	char str[5];
	FILE *fp=fopen("malzemeler.txt","r");
	if(fp==NULL){
		fprintf(stderr,"Error: file was not found.\n");
		exit(1);
	}
	while(fgets(str,3,fp)!=NULL){
	sem_wait(&Tp);
	if(strcmp(str,"FG")==0||strcmp(str,"GF")==0){
	sem_post(&F);
	sem_post(&G);
	printf("Toptanci Fistik Ve Seker Dagitti\n");
	ust[0]=1;
	}
	else if(strcmp(str,"UF")==0||strcmp(str,"FU")==0){
	sem_post(&U);
	sem_post(&F);
	printf("Toptanci Un Ve Fistik Dagitti\n");
	ust[1]=1;
	}
	else if(strcmp(str,"UG")==0||strcmp(str,"GU")==0){
	sem_post(&U);
	sem_post(&G);
	printf("Toptanci Un Ve Seker Dagitti\n");
	ust[2]=1;
	}//
	else if(strcmp(str,"SF")==0||strcmp(str,"FS")==0){
	sem_post(&S);
	sem_post(&F);
	printf("Toptanci Sut Ve Fistik Dagitti\n");
	ust[3]=1;
	}
	else if(strcmp(str,"SG")==0||strcmp(str,"GS")==0){
	sem_post(&S);
	sem_post(&G);
	printf("Toptanci Sut Ve Seker Dagitti\n");
	ust[4]=1;
	}
	else if(strcmp(str,"SU")==0||strcmp(str,"US")==0){
	sem_post(&U);
	sem_post(&S);
	printf("Toptanci Sut Ve Un Dagitti\n");
	ust[5]=1;
	}
	else{
	printf("Toptanci islevsiz.\n");
	sem_post(&Tp);
	continue;
	}
	sem_post(&Tp);
	sleep(1);
	sem_post(&Ge);
	printf("Toptanci baklavanin cikmasini bekliyor.\n");
	sem_wait(&B);
	printf("Toptanci baklavayi satti.\n");
	
	}
	printf("Toptancinin malzemeleri bitti.\n");
	bitti=1;
	for(int i=0;i<5;i++)
	sem_post(&Ge);
	for (int i=0;i<6;i++){
	pthread_join(Us[i],NULL);
	}
	
	fclose(fp);

}