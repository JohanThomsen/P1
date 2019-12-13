#include <stdio.h>
#include <stdlib.h>
#include "Utility.h"
#include "Get_Data.h"
#include "User_Dialogue.h"
#include "Analyze_Data.h"

#define SENTINEL -1

void initialize(double *data_array, profile *profile_array, renewable *renewable_array, FILE *fp_day_hour, time_of_day *current_time, time_of_day *saved_time);
void clean_exit(double *data_array, profile *profile_array, renewable *renewable_array);

int main(void) {
  int         sentinel       = 0;
  FILE        *fp_day_hour   = NULL;
  time_of_day current_time,
              saved_time;
  double *data_array         = calloc(HOURS_IN_TWO_DAYS, sizeof(double));
  profile *profile_array     = calloc(MAX_USERS, sizeof(profile));
  renewable *renewable_array = calloc(RENEW_ARRAY_SIZE, sizeof(renewable));

  initialize(data_array, profile_array, renewable_array, fp_day_hour, &current_time, &saved_time);
  validate_allocation(data_array, __LINE__, __FILE__);
  
  intro_frontend(profile_array);
  print_current_price(data_array, current_time.hour, renewable_array);
  do {
    sentinel = menu_interface(profile_array, data_array, renewable_array);
  } while (sentinel != SENTINEL);

  clean_exit(data_array, profile_array, renewable_array);
  return 0;
}

void initialize(double *data_array, profile *profile_array, renewable *renewable_array, FILE *fp_day_hour, time_of_day *current_time, time_of_day *saved_time){
  validate_allocation(data_array, __LINE__, __FILE__);
  validate_allocation(profile_array, __LINE__, __FILE__);
  validate_allocation(renewable_array, __LINE__, __FILE__);
  
  read_file(renewable_array);

  init_profile();
  read_profile_data(profile_array);
  
  get_current_time(current_time);
  find_saved_day_and_hour(fp_day_hour, saved_time, current_time);
  check_time_and_generate_data (current_time, saved_time, data_array, fp_day_hour);
}

void clean_exit(double *data_array, profile *profile_array, renewable *renewable_array){
  free(renewable_array);
  free(profile_array);
  free(data_array);
  exit(EXIT_SUCCESS);
}

