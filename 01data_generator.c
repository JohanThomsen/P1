#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


int main(void){
  double  *data_array = NULL;
  int     i;

  srand(time(NULL));

  data_array = calloc(24, sizeof(char));

  for(i = 0; i < 24; i++){
    if(i%2 == 0){
      data_array[i] = (rand() * 0.22*0.90);
      printf("data_array[%d] = %0.2f\n", i, data_array[i]);
    }
  }



  return 0;
}