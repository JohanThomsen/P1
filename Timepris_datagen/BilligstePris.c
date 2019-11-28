#include <stdio.h>
#include <stdlib.h> 
#include <math.h>
#include <time.h>

#define HOURS_IN_DAY 24

void Data_Gen        (double *data_array);
int Get_Hour         (void);
char* Get_Full_Time  (void);
void get_lowest_price(double *data_array, double *low_price, int *low_price_time, int current_hour);
int Get_Day          (void);
void put_day_and_hour_into_txt(FILE *fp_day_hour, int current_day, int current_hour);
void find_saved_day_and_hour(FILE *fp_day_hour, int *saved_day, int *saved_hour);
void print_data_array(double *data_array);

int main(void){
    double data_array[HOURS_IN_DAY] = {2.890, 2.910, 2.890, 2.920, 2.950, 3.040, 3.860, 4.520, 5.140, 4.920, 4.550, 4.530, 4.410, 4.410, 4.460, 4.530, 4.720, 5.300, 4.740, 4.170, 3.630, 3.250, 2.990, 2.880};
    double low_price                = 1024;
    int    low_price_time           = 0,
           current_hour             = Get_Hour(),
           current_day              = Get_Day(),
           saved_day                = 0,
           saved_hour               = 0;
    FILE *fp_day_hour = NULL;       


    find_saved_day_and_hour(fp_day_hour, &saved_day, &saved_hour);

    if (saved_day != current_day && current_hour >= 12)
    {
        srand(time(NULL));
        Data_Gen(data_array);
        put_day_and_hour_into_txt(fp_day_hour, current_day, current_hour);
    }

    print_data_array(data_array);
    
    get_lowest_price(data_array, &low_price, &low_price_time, current_hour);

    printf("The lowest price is at %d o'clock, and it is %0.2f DKK per MWH\n", low_price_time, low_price);

    printf("Price right now is : %0.2f, and the price diff is : %0.2f\n", data_array[current_hour], data_array[current_hour] - low_price);

    printf("%d\n", current_day);

    

  return 0;
}

void find_saved_day_and_hour(FILE *fp_day_hour, int *saved_day, int *saved_hour){
    fp_day_hour = fopen("day_hour_reset.txt", "r");

    if (fp_day_hour == NULL)
    {
        printf("Couldnt find text file. Generating a new set of prices\n");
    } else {
        fscanf(fp_day_hour, "%d,%d", saved_day, saved_hour);
    }
    
}

void print_data_array(double *data_array){
    int i;

    for (i = 0; i < HOURS_IN_DAY; ++i){
        printf("%2d:00 = %2.2f DKK/KWh\n", i, data_array[i]);
    }
}

void put_day_and_hour_into_txt(FILE *fp_day_hour, int current_day, int current_hour){

    fp_day_hour = fopen("day_hour_reset.txt", "w");

    if (fp_day_hour == NULL)
    {
        printf("Couldnt find text file. Generating a new set of prices\n");
    }

    fprintf(fp_day_hour, "%d,%d", current_day, current_hour);

    fclose(fp_day_hour);

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

void get_lowest_price(double *data_array, double *low_price, int *low_price_time, int current_hour){
    int i;
    for (i = current_hour; i < current_hour + 24; ++i){
        if (data_array[i - current_hour] < *low_price){
            *low_price = data_array[i - current_hour];
            *low_price_time = i - current_hour;
        }
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

int Get_Day(void){
    time_t now;
    struct tm *now_tm;
    int day;

    now = time(NULL);
    now_tm = localtime(&now);
    day = now_tm->tm_mday;

    return day;
}