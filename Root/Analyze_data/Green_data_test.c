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

double renewable_average (double renewable_interval_array[], int size_renewable);

double saving_average (double price_interval_array[], int size_price);

double max_price (double price_interval_array[]);

double min_price (double price_interval_array[], int size_price);

/* Besparelse ved forskellen mellem dagens gennemsnitspris, min og og max.
   Dette kan g�res ved at finde gennemsnittet af vores simulerede priser. */ 

int main(void)
{
    FILE *ifp = fopen("data.txt", "r");
    char *current_string = (char*)calloc(100, sizeof(char));
    renewable renewable_array[144];

    read_file(ifp, current_string, renewable_array);
    
    double renewable_interval_array[] =
    {
      3069.51, 2.2, 4, 2.1, 527.3, 542.6,
      3092.53, 2.2, 3.7, 0.1, 596.1, 584.5,
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
    
  int size_renewable = *(&renewable_interval_array + 1) - renewable_interval_array;
    
  double price_interval_array[] =
    {
      287.32, 280.90, 276.86, 281.49, 286.87, 298.61, 340.68, 433.26, 436.40, 440.36, 442.08,
      441.71, 420.56, 434.08, 428.33, 426.24, 438.64, 473.61, 396.87, 371.99, 325.43, 300.32,
      292.70, 277.23
    };

  int size_price = *(&price_interval_array + 1) - price_interval_array;

  int i;
      for (i=0; i < 144; i+=6)
      {
        printf("%f",renewable_array[i].total_load);
      }    
    
  sort_price(price_interval_array, size_price);
  printf("Average renewable energy in time interval: %.2f percent\n",renewable_average(renewable_interval_array, size_renewable));
  printf("Average price in time interval: %.2f DKK/MWh\n",saving_average(price_interval_array, size_price));
  printf("Max price in time interval: %.2f DKK/MWh\n",max_price(price_interval_array));
  printf("Min price in time interval: %.2f DKK/MWh\n",min_price(price_interval_array, size_price));

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
      " %*[^DK1,]"
      " %lf" 
      " %lf"
      " %lf"
      " %lf"
      " %lf",
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

double renewable_average (double renewable_interval_array[], int size_renewable)
{
  double percentage_renewable_energy=0;
  int i;
  
  for (i=0; i<size_renewable; i+=5)
    {
      percentage_renewable_energy += (renewable_interval_array[i]-renewable_interval_array[i+1]-renewable_interval_array[i+2]-renewable_interval_array[i+3]-renewable_interval_array[i+4])/
      renewable_interval_array[i];          
    }
  double print_renew = (percentage_renewable_energy/24)*100;
  return print_renew;
}

double saving_average (double price_interval_array[], int size_price)
{
  double sum=0;
  int i;
  
  for (i = 0; i < size_price; i++)
    {
      sum += price_interval_array[i];
    }
  sum /= size_price;
  return sum;
}

double max_price (double price_interval_array[])
{
  return price_interval_array[0];
}

double min_price (double price_interval_array[], int size_price)
{
  return price_interval_array[size_price - 1];
}
  
/*price_interval_array[0]-current_price=difference_to_max;*/
