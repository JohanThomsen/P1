#include <stdio.h>
#include <stdlib.h> 
#include <math.h>
#include <time.h>

#define HOURS_IN_DAY 24

void Data_Gen(double *data_array);
int Get_Hour(void);
char* Get_Full_Time(void);

int main(void){
 double data_array[HOURS_IN_DAY] = {2.890, 2.910, 2.890, 2.920, 2.950, 3.040, 3.860, 4.520, 5.140, 4.920, 4.550, 4.530, 4.410, 4.410, 4.460, 4.530, 4.720, 5.300, 4.740, 4.170, 3.630, 3.250, 2.990, 2.880};
    int i;
    double temp_low = 1000;
    int temp_low_time = 0,
    current_hour = Get_Hour();

    srand(time(NULL));
    Data_Gen(data_array);


    
    for (i = current_hour; i < current_hour + 24; ++i){
        if (data_array[i - current_hour] < temp_low){
            temp_low = data_array[i - current_hour];
            temp_low_time = i - current_hour;
        }
    }

    printf("The lowest price is at %d o'clock, and it is %0.2f DKK per MWH\n", temp_low_time, temp_low);

    printf("Price right now is : %f, and the price diff is : %f\n", data_array[current_hour], data_array[current_hour] - temp_low);
  return 0;
}

void Data_Gen(double *data_array){
    int i;
    int multiplier;

    for (i = 0; i < HOURS_IN_DAY; ++i){
        multiplier = (rand() % 20) + 90;
        data_array[i] = ((data_array[i] / 100) * multiplier);
        printf("%2d:00 = %2.2f DKK/KWh\n", i, data_array[i]);
    }
}

char* Get_Full_Time(void){
    time_t rawtime;
    struct tm * timeinfo;

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    return asctime (timeinfo);
}

int Get_Hour(void){
    time_t now;
    struct tm *now_tm;
    int hour;

    now = time(NULL);
    now_tm = localtime(&now);
    hour = now_tm->tm_hour;

    return hour;
}