#include <stdio.h>
#include <assert.h>

int fonk(int id1, int id2){
return id1 * id2;}

int main( void ){
int id1=21, id2=0;
//assert ((id1!=0) && (id2!=0)); /* Her iki değişken değeri 0'dan farklı olmalıdır.*/
printf ("Sayıların çarpımı: %d", fonk (id1,id2));
return 0;
}
