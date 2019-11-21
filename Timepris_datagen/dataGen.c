#include <stdio.h>
#include <stdlib.h> 
#include <math.h>
#include <time.h>

int main(void){
    int data[] = {2890, 2910, 2890, 2920, 2950, 3040, 3860, 4520, 5140, 4920, 4550, 4530, 4410, 4410, 4460, 4530, 4720, 5300, 4740, 4170, 3630, 3250, 2990, 2880};
    int array_length;
    int i;
    int multiplier;
    array_length = sizeof(data) / sizeof(int);

    srand(time(NULL));

    for (i = 0; i < array_length; ++i){
        multiplier = (rand() % 20) + 90;
        data[i] = ((data[i] / 1000) * multiplier);
        printf("data[%2d] = %2d\n", i, data[i]);
    }
    return 0;
}