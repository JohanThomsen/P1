#include <stdio.h>
#include <stdlib.h> 
#include <math.h>
#include <time.h>

int main(void){
    double data[] = {2.89, 2.91, 2.89, 2.92, 2.95, 3.04, 3.86, 4.52, 5.14, 4.92, 4.55, 4.53, 4.41, 4.41, 4.46, 4.53, 4.72, 5.30, 4.74, 4.17, 3.63, 3.25, 2.99, 2.88};
    int array_length;
    int i;
    double multiplier;
    array_length = sizeof(data) / sizeof(int);
    double max =  1.0,
           min = -1.0;

    srand(time(NULL));

    double range = (max - min);
    double div   = RAND_MAX / range;

    for (i = 0; i < array_length; ++i){
      multiplier = ((double)rand() / div);
      data[i] = multiplier;
      printf("data[%2d] = %2d\n", i, data[i]);
    }
    return 0;
}
