#include<stdio.h>
#include<stdlib.h>
#include "Utility.h"
#include "Get_Data\Get_Data.h"



int main(void) {
  double* data_array = NULL;
  FILE *fp_day_hour = NULL;
  time_of_day current_time,
               saved_time;
  
  data_array = validate_allocation(data_array); /* include utility */

  get_current_time(&current_time); /* include utility or get_data*/ 
  find_saved_day_and_hour(fp_day_hour, &saved_time, &current_time);
  check_time_and_generate_data (&current_time, &saved_time, data_array, fp_day_hour);
  
  intro_frontend(); /* include userdialogue*/ 
  menu_interface(data_array, current_time.hour); /* userdialogue og get_data*/  

  free(data_array);
  return 0;
}



