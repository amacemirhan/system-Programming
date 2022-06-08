#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

int main(){
FILE *fp=fopen("malzemeler.txt","w");
srand(time(NULL));
char strs[12][2]={"SU","SG","SF","UG","UF","GF","US","GS","FS","GU","FU","FG"};
char curr[2];
for(int i=0;i<400;i++){
strncpy(curr,strs[rand()%12],2);
fprintf(fp,curr,"%s");
printf("%s",curr);
}
fclose(fp);
	
}