#include <stdio.h>
#include <stdlib.h>
#include <time.h>



int main(void){
  int x;

  double rand_var;
  
  srand(time(NULL));

  for(x = 0; x < 10; ++x){
    rand_var = ((double)rand()/RAND_MAX)*0.9;
    printf("randomly generated value %d = %f\n", x, rand_var);
  }

  return 0;
}