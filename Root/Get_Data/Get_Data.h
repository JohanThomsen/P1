#define HOURS_IN_TWO_DAYS 48

typedef struct
{
  int hour,
      day,
      month,
      year;
}time_of_day;
double* double_Array_Memory_Allocation(double *array, int sizeof_array);
double  get_current_price             (double *data_array, int current_hour);
void    check_time_and_generate_data  (time_of_day *current_time, time_of_day *saved_time, double *data_array, FILE *fp_day_hour);
void    read_from_saved_prices        (double *data_array, FILE *fp_saved_prices);
void    read_from_seed_data           (double *data_array);
void    find_saved_day_and_hour       (FILE *fp_day_hour, time_of_day *saved_time, time_of_day *current_time);
void    print_data_array              (double *data_array, int current_hour, int interval);
void    put_day_and_hour_into_txt     (FILE *fp_day_hour, time_of_day *current_time);
void    data_gen                      (double *data_array, FILE *fp_saved_prices);
void    get_current_time              (time_of_day *current_time);