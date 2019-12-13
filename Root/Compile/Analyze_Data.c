#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "Utility.h"
#include "Analyze_Data.h"

#define INIT_VALUE_LOW 1000
#define INIT_VALUE_HIGH 0
/*
int main(void)
{
    

    read_file(ifp, current_string, renewable_array);
    
  double price_interval_array[] =
    {
     2.890, 2.910, 2.890, 2.920, 2.950, 3.040, 3.860, 4.520, 5.140, 4.920, 4.550, 4.530, 4.410, 4.410, 4.460, 4.530, 4.720, 5.300, 4.740, 4.170, 3.630,
     3.250, 2.990, 2.880, 2.890, 2.910, 2.890, 2.920, 2.950, 3.040, 3.860, 4.520, 5.140, 4.920, 4.550, 4.530, 4.410, 4.410, 4.460, 4.530, 4.720, 5.300,
     4.740, 4.170, 3.630, 3.250, 2.990, 2.880
    };
  
  printf("Average renewable energy in time interval: %f percent\n",renewable_average(renewable_array));
  printf("\nAverage price in time interval: %.2f DKK/kWh\n",saving_average(price_interval_array, start_interval2, end_interval2));

  printf("Max price in time interval: %.2f DKK/kWh\n",highest_price_in_interval(price_interval_array, 10, 10));
  printf("Min price in time interval: %.2f DKK/kWh\n",lowest_price_in_interval(price_interval_array, 10, 10));
  
  free(current_string);
  fclose(ifp);
  
  return 0;
}
*/

/* Reading green_energy and assigning values to the renewable struct, which the renewable_array is created from */
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

/* Adding up renewable production in specified interval, dividing to find average */ 
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
  return temp_low;
}

double highest_percent_renewable_in_interval(renewable *renewable_array, int interval, int current_hour){
  int i,
      hour_interval = interval + current_hour;
  double temp_high = INIT_VALUE_HIGH,
         renewable_hour = 0;

  for (i = current_hour; i < hour_interval; i++)
  {
    renewable_hour = (renewable_array[i].hydro_power + renewable_array[i].other_renewable + renewable_array[i].solar_power
                      + renewable_array[i].onshore_windpower + renewable_array[i].offshore_windpower) / renewable_array[i].total_load;

    if (renewable_hour < temp_high)
      {
        temp_high = renewable_hour;
      }
  }
  return temp_high;
}

/* Adding up prices in specified interval, dividing to find average and finding highest and lowest price  */
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

double lowest_price_in_interval(double *price_interval_array, int interval, int current_hour){
  int i,
      hour_interval = interval + current_hour;
  double temp_low = INIT_VALUE_LOW;

  for ( i = current_hour; i < hour_interval; i++){
    if (price_interval_array[i] < temp_low){
        temp_low = price_interval_array[i];
      }  
  }
  
  return temp_low;
}

double get_current_price(double *data_array, int current_hour){
  return data_array[current_hour];
}

double get_current_renewable_share(renewable *renewable_array, int current_hour){
  return  (renewable_array[current_hour].hydro_power + renewable_array[current_hour].other_renewable + renewable_array[current_hour].solar_power + 
           renewable_array[current_hour].onshore_windpower + renewable_array[current_hour].offshore_windpower) / renewable_array[current_hour].total_load * 100;
}