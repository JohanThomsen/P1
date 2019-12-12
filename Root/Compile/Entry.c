#include<stdio.h>
#include<stdlib.h>
#include "Utility.h"
#include "Get_Data.h"
#include "User_Dialogue.h"


int main(void) {
  double* data_array = calloc(HOURS_IN_TWO_DAYS, sizeof(double));
  FILE *fp_day_hour = NULL;
  time_of_day current_time,
               saved_time;
  profile *profile_array = calloc(MAX_USERS, sizeof(profile));



  validate_allocation(data_array);
  validate_allocation(profile_array);

  init_profile(profile_array);
  read_profile_data(profile_array);
  
  get_current_time(&current_time);
  find_saved_day_and_hour(fp_day_hour, &saved_time, &current_time);
  check_time_and_generate_data (&current_time, &saved_time, data_array, fp_day_hour);
  
  intro_frontend(profile_array);
  menu_interface(profile_array, data_array);


  free(profile_array);
  free(data_array);
  return 0;
}



