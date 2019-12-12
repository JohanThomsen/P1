#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "Get_Data.h"


 /* Input : time_of_day pointer Current_time, time_of_day pointer saved_time, Double data_array, FILE pointer fp_day_hour
  * Output: Either and updated data_array, if it is a new new day and past 12 o'clock. if this happens it also updates the saved time with current_time. Else it does nothing. */
void check_time_and_generate_data (time_of_day *current_time, time_of_day *saved_time, double *data_array, FILE *fp_day_hour){
  FILE *fp_saved_prices = NULL;
  if (((saved_time->day != current_time->day) || (saved_time->month != current_time->month) || (saved_time->year != current_time->year)) && (current_time->hour >= 12)){
    read_from_seed_data(data_array);
    data_gen(data_array, fp_saved_prices);
    put_day_and_hour_into_txt(fp_day_hour, current_time);
  } else {
    read_from_saved_prices(data_array, fp_saved_prices);
  }
}

/* Input : double data_array.
 * Output: data_array filled with 48 hours of prices, from saved saved_prices file 
 * Method: Creates a file pointer to the file "saved_prices.txt" and checks if it is there. If it isnt it exits the program as nothing would work if it does not exist
 * If it finds the file it puts the prices into the data array via a for loop and fscanf */
void read_from_saved_prices(double *data_array, FILE *fp_saved_prices){
  int i;

  fp_saved_prices = fopen("saved_prices.txt","r");

  if (fp_saved_prices == NULL){
    printf("Couldnt find data. Now terminating\n");
    exit(EXIT_FAILURE);
  }

  for ( i = 0; i < HOURS_IN_TWO_DAYS; i++){
    fscanf(fp_saved_prices, "%lf, ", &data_array[i]);
  }
  fclose(fp_saved_prices);
}

/* Input : double data_array.
 * Output: data_array filled with 48 hours of prices, from saved seed_data file 
 * Method: Creates a file pointer to the file "seed_data.txt" and checks if it is there. If it isnt it exits the program as nothing would work if it does not exist
 * If it finds the file it puts the prices into the data array via a for loop and fscanf */
void read_from_seed_data (double *data_array){
  int i;
  FILE *fp_seed_data = fopen("Seed_Data.txt", "r");

  if (fp_seed_data == NULL){
    printf("Couldnt find data. Now terminating\n");
    exit(EXIT_FAILURE);
  }

  for ( i = 0; i < HOURS_IN_TWO_DAYS; i++){
    fscanf(fp_seed_data, "%lf, ", &data_array[i]);
  }
  fclose(fp_seed_data);
}


/* Input : FILE pointer to fp_day_hour, time_of_day struct pointer saved_time
 * Output: Saved time from "day_hour_reset.txt" inputted into the saved_time struct */
void find_saved_day_and_hour(FILE *fp_day_hour, time_of_day *saved_time, time_of_day *current_time){
  fp_day_hour = fopen("day_hour_reset.txt", "r");

  if (fp_day_hour == NULL){
    printf("Couldnt find text file. Generating a new set of prices\n");
    put_day_and_hour_into_txt(fp_day_hour, current_time);
  } else {
    fscanf(fp_day_hour, "%d,%d,%d,%d", &saved_time->day, &saved_time->hour, &saved_time->month, &saved_time->year);
  }
  fclose(fp_day_hour);
}

/* Input : Double data_array, int current_hour, int interval
 * No Output:
 * Method: Prints data_array of prices from current time, and inputted interval amount of hours forward */
void print_data_array(double *data_array, int current_hour, int interval){
  int i;
  interval += current_hour;

  for (i = current_hour; i < interval; ++i){
    printf("%2d:00 = %2.2f DKK/KWh\n", (i % 24), data_array[i]);
  }
}

double get_current_price(double *data_array, int current_hour){
  return data_array[current_hour];
}

/* Input : File Pointer fp_day_hour, time_of_day struct pointer current_time
 * Output: An updated "day_hour_reset.txt"
 * Method: Opens "day_hour_reset.txt" and checks if it exists, if it doesnt it creates a new. If this creation was unsuccesful it exits the program
 * if it is not it inputs the values of the current_time struct into "day_hour_reset.txt", with commas separating the numbers. */
void put_day_and_hour_into_txt(FILE *fp_day_hour, time_of_day *current_time){

  fp_day_hour = fopen("day_hour_reset.txt", "w");

  if (fp_day_hour == NULL){
    printf("Couldnt create text file. Now terminating\n");
    exit(EXIT_FAILURE);
  }

  fprintf(fp_day_hour, "%d,%d,%d,%d", current_time->day, current_time->hour, current_time->month, current_time->year);

  fclose(fp_day_hour);
}

/* Input : Double data_array
 * Output: an updated data_array ran through a randomised noise generator.
 * Method: Runs through all numbers in the array, via a for loop, and multiplies it by a random number between 0.9 and 1.1, then divided by 100 as the price in seed_data in is Mwh
 * This random number is seeded by the previous random number each iteration so it remains random from number to number */
void data_gen(double *data_array, FILE *fp_saved_prices){
  int i,
      multiplier,
      random_number;
  fp_saved_prices = fopen("saved_prices.txt","w");

  for (i = 0; i < HOURS_IN_TWO_DAYS; ++i){
    srand(clock());
    random_number = rand();
    multiplier    = (random_number % 20) + 90;
    data_array[i] = ((data_array[i] / 1000) * (multiplier));
    fprintf(fp_saved_prices,"%2lf,", data_array[i]);
  }
  fclose(fp_saved_prices);
}

/* Input : time_of_day pointer current_time
 * Output: An updated current_time filled with the current system time in the compute the program is run on
 * Method: Uses the time.h library to extract the system time from the pc, and the makes the needed alterations to the months and year to make it correct. */
void get_current_time(time_of_day *current_time){
  time_t now;
  struct tm *now_tm;

  now = time(NULL);
  now_tm = localtime(&now);
  current_time->hour = now_tm->tm_hour;
  current_time->day  = now_tm->tm_mday;
  current_time->month  = now_tm->tm_mon + 1;
  current_time->year = now_tm->tm_year + 1900;
}

int get_current_hour(void){
  time_t now;
  struct tm *now_tm;
  now = time(NULL);

  now_tm = localtime(&now);
  return now_tm->tm_hour;
}
