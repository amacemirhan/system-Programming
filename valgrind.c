#include <stdlib.h>

void dummy_function(){

int * x = malloc (10 * sizeof (int));

x[10] = 0;
free(x);
}
int main(void) {

dummy_function();

return 0;
}
