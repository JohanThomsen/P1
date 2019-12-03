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
   Dette kan g�res ved at finde gennemsnittet af vores simulerede priser. */ 

int main(void)
{
  double price_interval_array[] =
    {
      287.32, 280.90, 276.86, 281.49, 286.87, 298.61, 340.68, 433.26, 436.40, 440.36, 442.08,
      441.71, 420.56, 434.08, 428.33, 426.24, 438.64, 473.61, 396.87, 371.99, 325.43, 300.32,
      292.70, 277.23
    };
  
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

/*This is a test*/
