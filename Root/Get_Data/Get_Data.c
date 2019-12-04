#include <stdio.h>
#include <stdlib.h> 
#include <math.h>
#include <time.h>

#define HOURS_IN_TWO_DAYS 48

void find_saved_day_and_hour(FILE *fp_day_hour, int *saved_day, int *saved_hour, int *saved_month, int *saved_year);
void print_data_array(double *data_array, int currenthour, int interval);
void put_day_and_hour_into_txt(FILE *fp_day_hour, int current_day, int current_hour, int current_month, int current_year);
void Data_Gen(double *data_array);
void get_lowest_price(double *data_array, double *low_price, int *low_price_time, int current_hour);
void Get_Current_Time(int *hour, int *day, int *month, int *year);

int main(void){
    double data_array[HOURS_IN_TWO_DAYS] = {2.890, 2.910, 2.890, 2.920, 2.950, 3.040, 3.860, 4.520, 5.140, 4.920, 4.550, 4.530, 4.410, 4.410, 4.460, 4.530, 4.720, 5.300, 4.740, 4.170, 3.630, 3.250, 2.990, 2.880,2.890, 2.910, 2.890, 2.920, 2.950, 3.040, 3.860, 4.520, 5.140, 4.920, 4.550, 4.530, 4.410, 4.410, 4.460, 4.530, 4.720, 5.300, 4.740, 4.170, 3.630, 3.250, 2.990, 2.880};
    double low_price                = 1024;
    int    low_price_time           = 0,
           current_hour             = 0,
           current_day              = 0,
           current_month            = 0,
           current_year             = 0,
           saved_day                = 0,
           saved_hour               = 0,
           saved_month              = 0,
           saved_year               = 0;
    FILE *fp_day_hour = NULL;       


    Get_Current_Time(&current_hour, &current_day, &current_month, &current_year);

    find_saved_day_and_hour(fp_day_hour, &saved_day, &saved_hour, &saved_month, &saved_year);
     

    if (((saved_day != current_day) || (saved_month != current_month) || (saved_year != current_year)) && (current_hour >= 12))
    {
       Data_Gen(data_array);
       put_day_and_hour_into_txt(fp_day_hour, current_day, current_hour, current_month, current_year);
    }

    print_data_array(data_array, current_hour, 6);
    
    /*get_lowest_price(data_array, &low_price, &low_price_time, current_hour);

    printf("The lowest price is at %d o'clock, and it is %0.2f DKK per MWH\n", low_price_time, low_price);

    printf("Price right now is : %0.2f, and the price diff is : %0.2f\n", data_array[current_hour], data_array[current_hour] - low_price);

    printf("%d\n", current_day);*/

    

  return 0;
}

void find_saved_day_and_hour(FILE *fp_day_hour, int *saved_day, int *saved_hour, int *saved_month, int *saved_year){
    fp_day_hour = fopen("day_hour_reset.txt", "r");

    if (fp_day_hour == NULL)
    {
        printf("Couldnt find text file. Generating a new set of prices\n");
    } else {
        fscanf(fp_day_hour, "%d,%d,%d,%d", saved_day, saved_hour, saved_month, saved_year);
    }
    
}

void print_data_array(double *data_array, int currenthour, int interval){
    int i;
    interval += currenthour;

    for (i = currenthour; i < interval; ++i){
        printf("%2d:00 = %2.2f DKK/KWh\n", (i % 24), data_array[i]);
    }
}

void put_day_and_hour_into_txt(FILE *fp_day_hour, int current_day, int current_hour, int current_month, int current_year){

    fp_day_hour = fopen("day_hour_reset.txt", "w");

    if (fp_day_hour == NULL)
    {
        printf("Couldnt find text file. Generating a new set of prices\n");
    }

    fprintf(fp_day_hour, "%d,%d,%d,%d", current_day, current_hour, current_month, current_year);

    fclose(fp_day_hour);

}

void Data_Gen(double *data_array){
    int i;
    int multiplier;
    int random_number;

    for (i = 0; i < HOURS_IN_TWO_DAYS; ++i){
        srand(random_number);
        random_number = rand();
        multiplier    = (random_number % 20) + 90;
        data_array[i] = ((data_array[i] / 100) * multiplier);
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

void Get_Current_Time(int *hour, int *day, int *month, int *year){
    time_t now;
    struct tm *now_tm;

    now = time(NULL);
    now_tm = localtime(&now);
    *hour = now_tm->tm_hour;
    *day  = now_tm->tm_mday;
    *month  = now_tm->tm_mon + 1;
    *year = now_tm->tm_year + 1900;
}
