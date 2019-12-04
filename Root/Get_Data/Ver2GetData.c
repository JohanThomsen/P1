#include <stdio.h>
#include <stdlib.h> 
#include <math.h>
#include <time.h>
#include <string.h>

#define HOURS_IN_TWO_DAYS 48
#define ENOUGH 1000
typedef struct
{
    int hour,
        day,
        month,
        year;
}current_time_struct;

typedef struct 
{
    int hour,
        day,
        month,
        year;
}saved_time_struct;



void check_time_and_generate_data ( current_time_struct *current_time, saved_time_struct *saved_time, double data_array[], FILE *fp_day_hour);
void read_from_seed_data (double data_array[]);
double* double_Array_Memory_Allocation(double *array, double sizeof_array);
void find_saved_day_and_hour(FILE *fp_day_hour, saved_time_struct *saved_time);
void print_data_array(double *data_array, int currenthour, int interval);
void put_day_and_hour_into_txt(FILE *fp_day_hour, current_time_struct *current_time);
void Data_Gen(double *data_array);
void get_lowest_price(double *data_array, double *low_price, int *low_price_time, int current_hour);
void Get_Current_Time(current_time_struct *current_time);

int main(void){
    double* data_array = NULL;
    FILE *fp_day_hour = NULL;
    current_time_struct current_time;
    saved_time_struct   saved_time;

    data_array = double_Array_Memory_Allocation(data_array, HOURS_IN_TWO_DAYS);

    read_from_seed_data(data_array);

    Get_Current_Time(&current_time);

    find_saved_day_and_hour(fp_day_hour, &saved_time);

    check_time_and_generate_data (&current_time, &saved_time, data_array, fp_day_hour);

    print_data_array(data_array, current_time.hour, 24); /* Interval input wanted here */

  return 0;
}

void check_time_and_generate_data ( current_time_struct *current_time, saved_time_struct *saved_time, double data_array[], FILE *fp_day_hour){
    if (((saved_time->day != current_time->day) || (saved_time->month != current_time->month) || (saved_time->year != current_time->year)) && (current_time->hour >= 12))
    {
       Data_Gen(data_array);
       put_day_and_hour_into_txt(fp_day_hour, current_time);
    }
}

void read_from_seed_data (double data_array[]){
    int i;
    FILE *fp_seed_data = fopen("Seed_Data.txt", "r"); 
    
    for ( i = 0; i < HOURS_IN_TWO_DAYS; i++)
    {
        fscanf(fp_seed_data, "%lf, ", &data_array[i]);
    }

    fclose(fp_seed_data);
}

double* double_Array_Memory_Allocation(double *array, double sizeof_array){
    array = (double *) calloc (sizeof_array, (sizeof(double)));
    if (array == NULL)
    {
        printf("Didn't get the memory we wanted. Now terminating");
        exit(EXIT_FAILURE);
    }

    return array;
}

void find_saved_day_and_hour(FILE *fp_day_hour, saved_time_struct *saved_time){
    fp_day_hour = fopen("day_hour_reset.txt", "r");

    if (fp_day_hour == NULL)
    {
        printf("Couldnt find text file. Generating a new set of prices\n");
    } else {
        fscanf(fp_day_hour, "%d,%d,%d,%d", &saved_time->day, &saved_time->hour, &saved_time->month, &saved_time->year);
    }
    
}

void print_data_array(double *data_array, int currenthour, int interval){
    int i;
    interval += currenthour;

    for (i = currenthour; i < interval; ++i){
        printf("%2d:00 = %2.2f DKK/KWh\n", (i % 24), data_array[i]);
    }
}

void put_day_and_hour_into_txt(FILE *fp_day_hour, current_time_struct *current_time){

    fp_day_hour = fopen("day_hour_reset.txt", "w");

    if (fp_day_hour == NULL)
    {
        printf("Couldnt find text file. Generating a new set of prices\n");
    }

    fprintf(fp_day_hour, "%d,%d,%d,%d", current_time->day, current_time->hour, current_time->month, current_time->year);

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

void Get_Current_Time(current_time_struct *current_time){
    time_t now;
    struct tm *now_tm;

    now = time(NULL);
    now_tm = localtime(&now);
    current_time->hour = now_tm->tm_hour;
    current_time->day  = now_tm->tm_mday;
    current_time->month  = now_tm->tm_mon + 1;
    current_time->year = now_tm->tm_year + 1900;
}
