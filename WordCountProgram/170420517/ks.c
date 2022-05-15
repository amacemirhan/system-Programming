#include <stdio.h>
#include <string.h>
#include <unistd.h>
//Mehmed Emirhan Amac - 170420517
int Topbytes=0; //birden fazla dosya icin toplam degerler
int Topwords=0;
int TopnewLine=0;
int dosya=0;// okunan dosya sayisi
enum states { WHITESPACE, WORD };
int state = WHITESPACE;
int specComm[]={0,0,0}; // -l , -w , -c Special commands array
int isSpec=0; // eger herhangi bir ozel komut yoksa 0 kalir
int isStdin=0;// eger stdin den okunmussa 1 olur
char stdinChar[30];

void yazdir(int newLine,int words,int bytes,char *thefile);
int ks(char fName[]);

int main(int argc, char** argv)
{
    int opt;
    while((opt = getopt(argc, argv, "lwc")) != -1) //parametre kontrolu
    { 
        isSpec=1;
        switch(opt) 
        { 
            case 'l':
            specComm[0]=1;
            break;

            case 'w':
            specComm[1]=1;
            break;

            case 'c': 
            specComm[2]=1;
            break;

            case '?': 
                fprintf(stderr,"Unknown arguments: %d\n",opt);
                break; 
        } 
    } 
    
    for(; optind < argc; optind++){   
        
            if(ks(argv[optind])){
            
            }else if(argv[optind][0]=='+'){
                isStdin=1;
                fscanf(stdin,"%s",stdinChar);
                ks(stdinChar);
            }
            else{
                fprintf(stderr,"ERROR: Unknown arguments: %s\n",argv[optind]);
            } 
    }
    if(dosya>1)
    yazdir(TopnewLine,Topwords,Topbytes,"TOPLAM");
    else if(dosya==0){
        fscanf(stdin,"%s",stdinChar);
        isStdin=1;
        ks(stdinChar);
    }
    
}

void yazdir(int newLine,int words,int bytes,char *thefile){
    if(isSpec==0)
    printf("%d %d %d %s\n",newLine,words,bytes,thefile);
    else{
        if(specComm[0])
        printf("%d ",newLine);
        if(specComm[1])
        printf("%d ",words);
        if(specComm[2])
        printf("%d ",bytes);
        if(isStdin){
            printf("-stdin-\n");
            isStdin=0;
        }
        else
        printf("%s\n",thefile);
    }
    
}

int ks(char fName[]) {
    FILE *file = fopen( fName, "r");
    int bytes = 0;
    int words = 0;
    int newLine = 0;
    char buffer[1];
   if(file == 0){
       if(fName[0]!='+')
      fprintf(stderr,"ERROR(HATA): '%s' dosyasi acilamiyor\n",fName);
      return 0;
   }
   else{
       dosya++;
            char *thefile = fName;
      char last = ' ';
      while(1)
      {
          buffer[0]=fgetc(file);// 1 bayt okuyup buffera aliyoruz
          if(buffer[0]==EOF)
          break;
         bytes++;
         if ( buffer[0]== ' ' || buffer[0] == '\t'  )//eger bosluk veya tab karakteriyse
         {
            state = WHITESPACE;//son durum bos alan olarak guncelle
         }
         else if (buffer[0]=='\n')
         {
            newLine++;
            state = WHITESPACE;
         }
         else 
         {
            if ( state == WHITESPACE )// eger son durum bos alansa ve bosluktan baska karakter varsa kelime say
            {
               words++;
            }
            state = WORD;
         }
         last = buffer[0];
      }

      yazdir(newLine,words,bytes,thefile);
      
      Topbytes+=bytes;
      TopnewLine+=newLine;
      Topwords+=words;
      return 1;      
   }
}