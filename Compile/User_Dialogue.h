#define EMPTY 0
void init_profile        (void);
int  intro_frontend      (profile *profile_array, double *data_array, time_of_day current_time, renewable *renewable_array);
int  menu_interface      (profile *profiles, double *data_array, renewable *renew_array);
int  read_profile_data   (profile *profiles);
void print_current_price (double *data_array, int current_hour, renewable *renew_array);


