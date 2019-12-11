#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct
{
  double total_load;
  double hydro_power;
  double other_renewable;
  double solar_power;
  double onshore_windpower;
  double offshore_windpower;
} renewable;

void read_file(FILE *ifp, char *current_string, renewable *renewable_array);

int cmpfunc (const void * a, const void * b);

void sort_price (double price_interval_array[], int size_price);

double renewable_average (renewable *renewable_array);

double saving_average (double price_interval_array[], int size_price);

double max_price (double price_interval_array[]);

double min_price (double price_interval_array[], int size_price);

/* Besparelse ved forskellen mellem dagens gennemsnitspris, min og og max.
   Dette kan gøres ved at finde gennemsnittet af vores simulerede priser. */ 

int main(void)
{
    FILE *ifp = fopen("green_energy_48.txt", "r");
    char *current_string = (char*)calloc(100, sizeof(char));
    renewable renewable_array[144];

    read_file(ifp, current_string, renewable_array);
    
  double price_interval_array[] =
    {
     2.890, 2.910, 2.890, 2.920, 2.950, 3.040, 3.860, 4.520, 5.140, 4.920, 4.550, 4.530, 4.410, 4.410, 4.460, 4.530, 4.720, 5.300, 4.740, 4.170, 3.630,
     3.250, 2.990, 2.880, 2.890, 2.910, 2.890, 2.920, 2.950, 3.040, 3.860, 4.520, 5.140, 4.920, 4.550, 4.530, 4.410, 4.410, 4.460, 4.530, 4.720, 5.300,
     4.740, 4.170, 3.630, 3.250, 2.990, 2.880
    };

  int size_price = *(&price_interval_array + 1) - price_interval_array;
    
  sort_price(price_interval_array, size_price);
  
  printf("Average renewable energy in time interval: %.2f percent\n",renewable_average(renewable_array));
  printf("Average price in time interval: %.2f DKK/kWh\n",saving_average(price_interval_array, size_price));
  printf("Max price in time interval: %.2f DKK/kWh\n",max_price(price_interval_array));
  printf("Min price in time interval: %.2f DKK/kWh\n",min_price(price_interval_array, size_price));

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

int cmpfunc (const void * a, const void * b)
{
  return ( *(double*)b - *(double*)a );
}

void sort_price (double price_interval_array[], int size_price)
{
  qsort(price_interval_array, size_price, sizeof(double), cmpfunc);
}

double renewable_average (renewable *renewable_array)
{
  double renewable_sum=0;
  int i, start_interval, end_interval;
  
  printf("Specify your interval: ");
  scanf(" %d %d",&start_interval, &end_interval);
  
  for (i=start_interval;i < end_interval; i++)
    {
      printf("\n%lf",renewable_array[i].total_load);
      renewable_sum += (renewable_array[i].hydro_power + renewable_array[i].other_renewable + renewable_array[i].solar_power
	            + renewable_array[i].onshore_windpower + renewable_array[i].offshore_windpower) / renewable_array[i].total_load;
    }
  
  double print_renew = (renewable_sum/(end_interval-start_interval))*100;
  return print_renew;
}

double saving_average (double price_interval_array[], int size_price)
{
  double sum=0;
  int i, start_interval2, end_interval2, interval2;

  printf("Specify your interval: ");
  scanf(" %d %d",&start_interval2,&end_interval2);
  
  for (i = start_interval2; i < end_interval2; i++)
    {
      printf("\n%f",price_interval_array[i]);
      sum += price_interval_array[i];
    }
  
  interval2 = end_interval2 - start_interval2;
    
  printf("interval %d",interval2);
  sum /= interval2;
  return sum/10;
}

double max_price (double price_interval_array[])
{
  return (price_interval_array[0])/10;
}

double min_price (double price_interval_array[], int size_price)
{
  return (price_interval_array[size_price - 1])/10;
}
  
/*price_interval_array[0]-current_price=difference_to_max;*/
