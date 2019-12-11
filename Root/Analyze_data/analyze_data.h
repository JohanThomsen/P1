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

double renewable_average (renewable *renewable_array);

double saving_average (double price_interval_array[], int start_interval2, int end_interval2, double *temp_low, double *temp_high);
