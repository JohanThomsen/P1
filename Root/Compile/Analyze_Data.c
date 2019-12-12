#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "Analyze_Data.h"

#define INIT_VALUE_LOW 1000
#define INIT_VALUE_HIGH 0
/*
int main(void)
{
    FILE *ifp = fopen("green_energy.txt", "r");
    char *current_string = (char*)calloc(100, sizeof(char));
    renewable renewable_array[144];
    int start_interval2, end_interval2;

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
void read_file(FILE *ifp, char *current_string, renewable *renewable_array)
{
  int i=0, j=0;

  if (ifp != NULL){
    current_string = fgets(current_string,100,ifp);
    
    while (current_string != NULL){
      sscanf(current_string,
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
      &renewable_array[i].offshore_windpower
      );

      current_string = fgets(current_string, 100, ifp);
      i++;
    }
  }
}

/* Adding up renewable production in specified interval, diving to find average */ 
double renewable_average (renewable *renewable_array)
{
  double renewable_sum=0;
  int i, start_interval, end_interval;
  
  printf("Specify your hour interval for green energy: ");
  scanf(" %d %d",&start_interval, &end_interval);
  
  for (i=start_interval;i < end_interval; i++){
      printf("\n%f",renewable_array[i].other_renewable );
      renewable_sum += (renewable_array[i].hydro_power + renewable_array[i].other_renewable + renewable_array[i].solar_power
	            + renewable_array[i].onshore_windpower + renewable_array[i].offshore_windpower) / renewable_array[i].total_load;
    }
  
  double print_renew = (renewable_sum/(end_interval-start_interval))*100;
  return print_renew;
}

/* Adding up prices in specified interval, dividing to find average and finding highest and lowest price  */
double saving_average (double *price_interval_array, int start_interval2, int end_interval2)
{
  double sum=0;
  int i, interval2;

  printf("Specify your hour interval for price: ");
  scanf(" %d %d",&start_interval2,&end_interval2);
  
  for (i = start_interval2; i < end_interval2; i++){
      sum += price_interval_array[i];        
    }
  
  interval2 = end_interval2 - start_interval2;
    
  sum /= interval2;
  return sum/10;
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
  
  return temp_high/10;
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
  
  return temp_low/10;
}
