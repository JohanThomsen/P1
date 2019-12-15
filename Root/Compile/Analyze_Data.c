#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "Utility.h"
#include "Analyze_Data.h"

#define INIT_VALUE_LOW 1000
#define INIT_VALUE_HIGH 0

/* Input : renewable *renewable_array,
 * Output: different values in the struct renewable,
 * Method: Read file data and adds the values to the corrosponding elements in the struct renewable */
void read_file(renewable *renewable_array){
  
  int i = 0;
  FILE *ifp = fopen("green_energy.txt", "r");
  char *current_str = calloc(100, sizeof(char));
  
  validate_allocation(current_str, __LINE__, __FILE__);
  check_fp(ifp, __LINE__, __FILE__);

  while (fgets(current_str, 100, ifp) != NULL){
    sscanf(current_str,
          " %lf,"
          " %lf," 
          " %lf,"
          " %lf,"
          " %lf,"
          " %lf,",
          &renewable_array[i].total_load,
          &renewable_array[i].hydro_power,
          &renewable_array[i].other_renewable,
          &renewable_array[i].solar_power,
          &renewable_array[i].onshore_windpower,
          &renewable_array[i].offshore_windpower);
    i++;
  }
}

/* Input : renewable *renewable_array, int interval, int current_hour.
 * Output: The average renewable energi produced in specified interval.
 * Method: Sums electricity produced by all renewable eletricity categories and devides it by the total load. 
 * The percentage is then divided by the interval and timed 100 to get the percentage of renewable electricity in the interval. */
double renewable_average (renewable *renewable_array, int interval, int current_hour){
  double renewable_sum,
         renew_result = 0;
  int i,
      hour_interval = current_hour + interval;
  
  for (i = current_hour, renewable_sum = 0; i < hour_interval; i++){

    renewable_sum += (renewable_array[i].hydro_power + renewable_array[i].other_renewable + renewable_array[i].solar_power
	                + renewable_array[i].onshore_windpower + renewable_array[i].offshore_windpower) / renewable_array[i].total_load;
  }
  
  renew_result = renewable_sum / interval * 100;
  return renew_result;
}

/* Input : renewable *renewable_array, int interval, int current_hour.
 * Output: The interval with the lowest percentage of renewable energy.
 * Method: Sums electricity produced by all renewable eletricity categories and devides it by the total load times 100 to get the percentage.
 *         If the current interval percentage is lower then the privious interval temp_high is said to be the value of the current interval percentage */
double lowest_percent_renewable_in_interval(renewable *renewable_array, int interval, int current_hour){
  int i,
      hour_interval = interval + current_hour;
  double temp_low = INIT_VALUE_LOW,
         renewable_hour = 0;

  for (i = current_hour; i < hour_interval; i++)
  {
    renewable_hour = (renewable_array[i].hydro_power + renewable_array[i].other_renewable + renewable_array[i].solar_power
                      + renewable_array[i].onshore_windpower + renewable_array[i].offshore_windpower) / renewable_array[i].total_load;

    if (renewable_hour < temp_low)
      {
        temp_low = renewable_hour;
      }
  }
  return temp_low * 100;
}

/* Input : renewable *renewable_array, int interval, int current_hour.
 * Output: The interval with the highest percentage of renewable energy.
 * Method: Sums electricity produced by all renewable eletricity categories and devides it by the total load times 100 to get the percentage.
 *         If the current interval percentage is higher then the privious interval temp_high is said to be the value of the current interval percentage */
double highest_percent_renewable_in_interval(renewable *renewable_array, int interval, int current_hour){
  int i,
      hour_interval = interval + current_hour;
  double temp_high = INIT_VALUE_HIGH,
         renewable_hour = 0;

  for (i = current_hour; i < hour_interval; i++)
  {
    renewable_hour = (renewable_array[i].hydro_power + renewable_array[i].other_renewable + renewable_array[i].solar_power
                      + renewable_array[i].onshore_windpower + renewable_array[i].offshore_windpower) / renewable_array[i].total_load;

    if (renewable_hour > temp_high)
      {
        temp_high = renewable_hour;
      }
  }
  return temp_high * 100;
}

/* Input : double *price_interval_array, int interval, int current_hour.
 * Output: The average price of interval.
 * Method: Sums prices in specified interval and devied said sum with the interval to find the average */
double saving_average (double *price_interval_array, int interval, int current_hour){
  double sum;
  int      i,
           hour_interval = interval + current_hour;
 
  for (i = current_hour, sum = 0; i < hour_interval; i++){
      sum += price_interval_array[i];        
  }  
  sum /= interval;
  
  return sum;
}

/* Input : double *price_interval_array, int interval, int current_hour.
 * Output: The highest price of interval.
 * Method: Loops through the entire price_interval_array, and replaces temp_high with the value of index in price_interval_array if its higher the the current value of temp_high */
double highest_price_in_interval(double *price_interval_array, int interval, int current_hour){
  int i,
      hour_interval = interval + current_hour;
  double temp_high = INIT_VALUE_HIGH;

  for ( i = current_hour; i < hour_interval; i++){
    if (price_interval_array[i] > temp_high){
        temp_high = price_interval_array[i];
      }  
  }
  
  return temp_high;
}

/* Input : double *price_interval_array, int interval, int current_hour, int *time
 * Output: The lowest price of interval.
 * Method: Loops through the entire price_interval_array, and replaces temp_low with the value of index in price_interval_array if its lower the the current value of temp_low */
double lowest_price_in_interval(double *price_interval_array, int interval, int current_hour, int *time){
  int i,
      hour_interval = interval + current_hour;
  double temp_low = INIT_VALUE_LOW;
  for ( i = current_hour; i < hour_interval; i++){
    if (price_interval_array[i] < temp_low){
        temp_low = price_interval_array[i];
        *time = i;
      }  
  }
  return temp_low;
}

/* NOTE: What is the point of this one? */
double get_current_price(double *data_array, int current_hour){
  return data_array[current_hour];
}

/* Input : renewable *renewable_array, int current_hour.
 * Output: The percentage of the total_load which comes from renewable energy.
 * Method: Sums electricity produced by all renewable eletricity categories and devides it by the total load times 100 to get the percentage */
double get_current_renewable_share(renewable *renewable_array, int current_hour){
  return  (renewable_array[current_hour].hydro_power + renewable_array[current_hour].other_renewable + renewable_array[current_hour].solar_power + 
           renewable_array[current_hour].onshore_windpower + renewable_array[current_hour].offshore_windpower) / renewable_array[current_hour].total_load * 100;
}