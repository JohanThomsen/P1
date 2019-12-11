#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "analyze_data.h"

int main(void)
{
    FILE *ifp = fopen("green_energy_48.txt", "r");
    char *current_string = (char*)calloc(100, sizeof(char));
    renewable renewable_array[144];
    int start_interval2, end_interval2;
    double low_price, high_price;

    read_file(ifp, current_string, renewable_array);
    
  double price_interval_array[] =
    {
     2.890, 2.910, 2.890, 2.920, 2.950, 3.040, 3.860, 4.520, 5.140, 4.920, 4.550, 4.530, 4.410, 4.410, 4.460, 4.530, 4.720, 5.300, 4.740, 4.170, 3.630,
     3.250, 2.990, 2.880, 2.890, 2.910, 2.890, 2.920, 2.950, 3.040, 3.860, 4.520, 5.140, 4.920, 4.550, 4.530, 4.410, 4.410, 4.460, 4.530, 4.720, 5.300,
     4.740, 4.170, 3.630, 3.250, 2.990, 2.880
    };
  
  printf("Average renewable energy in time interval: %.2f percent\n",renewable_average(renewable_array));
  printf("Average price in time interval: %.2f DKK/kWh\n",saving_average(price_interval_array, start_interval2, end_interval2, &low_price, &high_price));

  printf("Max price in time interval: %.2f DKK/kWh\n",high_price/10);
  printf("Min price in time interval: %.2f DKK/kWh\n",low_price/10);

  free(current_string);
  fclose(ifp);
  
  return 0;
}

void read_file(FILE *ifp, char *current_string, renewable *renewable_array)
{
  int i=0, j=0;

  if (ifp != NULL)
  {
    current_string = fgets(current_string,100,ifp);
    
    while (current_string != NULL)
    {
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

double renewable_average (renewable *renewable_array)
{
  double renewable_sum=0;
  int i, start_interval, end_interval;
  
  printf("Specify your hour interval for green energy: ");
  scanf(" %d %d",&start_interval, &end_interval);
  
  for (i=start_interval;i < end_interval; i++)
    {
      renewable_sum += (renewable_array[i].hydro_power + renewable_array[i].other_renewable + renewable_array[i].solar_power
	            + renewable_array[i].onshore_windpower + renewable_array[i].offshore_windpower) / renewable_array[i].total_load;
    }
  
  double print_renew = (renewable_sum/(end_interval-start_interval))*100;
  return print_renew;
}

double saving_average (double price_interval_array[], int start_interval2, int end_interval2, double *temp_low, double *temp_high)
{
  double sum=0;
  int i, interval2;
  *temp_low = 1000;
  *temp_high = 0;

  printf("Specify your hour interval for price: ");
  scanf(" %d %d",&start_interval2,&end_interval2);
  
  for (i = start_interval2; i < end_interval2; i++)
    {
      sum += price_interval_array[i];
      
      if (price_interval_array[i] < *temp_low)
      {
        *temp_low = price_interval_array[i];
      }

      if (price_interval_array[i] > *temp_high)
      {
        *temp_high = price_interval_array[i];
      }      
    }
  
  interval2 = end_interval2 - start_interval2;
    
  sum /= interval2;
  return sum/10;
}

