#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define HOURS_IN_DAY 24

double saving_average (double price_interval_array[]);

int cmpfunc (const void * a, const void * b);

void sort_price (double price_interval_array[]);

double max_price (double price_interval_array[]);

double min_price (double price_interval_array[]);


/* Besparelse ved forskellen mellem dagens gennemsnitspris, min og og max.
   Dette kan gøres ved at finde gennemsnittet af vores simulerede priser. */ 

int main(void)
{
  double price_interval_array[] =
    {
      3069.51,521.74,604.92,19.35,119.57,
      3092.53,521.48,609.07,16.17,116.93,
      3006.23,436.74,540.47,14.68,114.51,
      2574.83,334.25,279.32,12.03,115.91,
      2136.74,272.44,338.81,11.6,115.8,
      1956.9,225.02,294.51,11.63,116.58,
      1902.49,225.26,298.9,12.37,118.14,
      1885.83,228.05,296.39,10.84,117.55,
      1908.92,228.66,216.36,10.73,116.83,
      1940.92,256.96,107.72,11.71,117.5,
      2027.06,382.5,136.68,17.95,119.31,
      2138.62,413.85,154.19,21.5,119.29,
      2309.3,388.34,109.9,12.82,113.85,
      2412.11,407.64,136.83,17.69,115.72,
      2545.49,413.88,131.21,16.44,115.74,
      2742.61,412.53,130.02,16.25,115.7,
      2862.62,400.84,112.32,12.78,113.87,
      2642.54,398.28,112.97,12.88,113.37,
      2507.59,379.43,103.18,10.91,112.5,
      2475.55,366.52,99.56,10.2,111.82,
      2468.25,370.03,97.69,10.01,112.98,
      2504.54,398.57,142.53,19.18,115.65,
      2547.7,329.96,145.11,19.72,109.04,
      2564.09,272.71,148.47,20.1,105.9
    };
  int i;
  
  for (i=0; i<120; i+=5)
    {
      double percentage_renewable_energy = (price_interval_array[i]-price_interval_array[i+1]-price_interval_array[i+2]-price_interval_array[i+3]-price_interval_array[i+4])/
      price_interval_array[i];
      printf("\n%f percentage green energy", percentage_renewable_energy);
          
    }
  
  sort_price(price_interval_array);
  printf("Average price in time interval: %.2f DKK/MWh\n",saving_average(price_interval_array));
  printf("Max price in time interval: %.2f DKK/MWh\n",max_price(price_interval_array));
  printf("Min price in time interval: %.2f DKK/MWh\n",min_price(price_interval_array));
  
  return 0;
}

double saving_average (double price_interval_array[])
{
  double sum=0;
  int i;
  
  for (i = 0; i < HOURS_IN_DAY; i++)
    {
      sum += price_interval_array[i];
    }
  sum /= HOURS_IN_DAY;
  return sum;
}

int cmpfunc (const void * a, const void * b)
{
  return ( *(double*)b - *(double*)a );
}

void sort_price (double price_interval_array[])
{
  qsort(price_interval_array, HOURS_IN_DAY, sizeof(double), cmpfunc);
}

double max_price (double price_interval_array[])
{
  return price_interval_array[0];
}

double min_price (double price_interval_array[])
{
  return price_interval_array[HOURS_IN_DAY - 1];
}
  
/*price_interval_array[0]-current_price=difference_to_max;*/
