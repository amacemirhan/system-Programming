#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

sem_t doktorlar;
sem_t musteriler;
sem_t mutex;

#define Musteri_Siniri 100

void ip_doktor(void* sayi);
void ip_musteri(void* sayi);
void bekle();

int koltukSayisi = 0;
int musteriSayisi = 0;
int sandalyeSayisi = 0;
int bosSandalyeSayisi = 0;
int hizmetEdilecekMusteri = 0;
int oturulacakSandalye = 0;
int koltuk;

int main(int argc, char** args)
{
    //girdi kontrolu
    if(argc != 4)
    {printf("\n Kullanim Hatası");
     printf("musteri sayisi ve sandalye sayisini da giriniz.");
    return EXIT_FAILURE;}


    //Atama islemleri
    musteriSayisi=atoi(args[1]);
    sandalyeSayisi=atoi(args[2]);
    koltukSayisi=atoi(args[3]);
    bosSandalyeSayisi=sandalyeSayisi;
    koltuk = (int) malloc(sizeof(int) * sandalyeSayisi);

    if (musteriSayisi > Musteri_Siniri)
    {     printf("\nMusteri siniri: %d\n",Musteri_Siniri);
    return EXIT_FAILURE;    }

    //Musteri, sandalye ve Koltuk sayilari.
    printf("\nMusteri Sayisi:\t%d",musteriSayisi);
    printf("\nSandalye Sayisi:%d",sandalyeSayisi);
    printf("\nKoltuk Sayisi:\t%d\n",koltukSayisi);

    pthread_t doktor[koltukSayisi], musteri[musteriSayisi];

    //semaphorelarin baslatilmasi
    sem_init(&doktorlar,0,0);
    sem_init(&musteriler,0,0);
    sem_init(&mutex,0,1);

    printf("Ameliyathane Acildi!\n");
    int i = 0;

    //doktor threadleri
    for(i=0;i<koltukSayisi;i++){
    pthread_create(&doktor[i], NULL, (void)ip_doktor,(void)&i);
    sleep(1);    }

     //Musteri threadleri
    for(i=0;i<musteriSayisi;i++){
    pthread_create(&musteri[i], NULL, (void)ip_musteri,(void)&i);
    bekle();    }

    //Musterilerle ilgilen
    for(i=0;i<musteriSayisi;i++){
    pthread_join(musteri[i], NULL);    }

    printf("Tum Hastalar ameliyat edildi.");
    return EXIT_SUCCESS;
}

void ip_doktor(void* sayi)
{
    int s= (int)sayi+1;
    int sonrakiMusteri, musteriKimligi;

    printf("doktor %d ameliyathaneye geldi.\n",s);
    while(1){
        if (!musteriKimligi){
        printf("doktor %d uyuyor.\n",s);    }


    sem_wait(&doktorlar); //uyuyan doktorlar kuyruguna katil
    sem_wait(&mutex); //Koltuklara erisimi kilitle

    hizmetEdilecekMusteri = (++hizmetEdilecekMusteri) % sandalyeSayisi;
    sonrakiMusteri=hizmetEdilecekMusteri;
    musteriKimligi=koltuk[sonrakiMusteri];
    koltuk[sonrakiMusteri] = pthread_self();

    sem_post(&mutex); //Koltuklara erisimi ac
    sem_post(&musteriler); //Secilen musteriyle ilgilem

    printf("%d. doktor, %d. hastayı ameliyat ediyor.\n",s,musteriKimligi);
    sleep(2);
    printf("%d. doktor, %d. hasta taburcu oldu.\n",s,musteriKimligi);
    }
}

void ip_musteri(void* sayi)
{
    int s = (int)sayi +1;
    int oturulanSandalye, doktorID;

    sem_wait(&mutex); //Koltuga erisimi kilitle
    printf("Hasta %d hastaneye geldi.\n",s);

    if(bosSandalyeSayisi>0){
        bosSandalyeSayisi--;
        printf("Hasta %d ameliyat olmak icin bekliyor.",s);

        oturulacakSandalye=(++oturulacakSandalye)%sandalyeSayisi;
        oturulanSandalye=oturulacakSandalye;
        koltuk[oturulanSandalye]=s;

        sem_post(&mutex);    //Koltuga erisimi ac
        sem_post(&doktorlar);    //doktoru uyandir

        sem_wait(&musteriler); //Bekleyen Musteriler kuyruguna gir
        sem_wait(&mutex);    //Koltuklara erisimi kilitle

        doktorID = koltuk[oturulanSandalye];
        bosSandalyeSayisi++;

        sem_post(&mutex);    //Koltuga erisimi ac
    }
    else{
        sem_post(&mutex);    //Koltuga erisimi ac
        printf(",Hasta %d yer bulamadi. Hastaneden gidiyor\n",s);    }
    pthread_exit(0);
}

void bekle()
{
    srand((unsigned int)time(NULL));
    usleep(rand()%(300000)+ 50000); //50ms-350ms
}
