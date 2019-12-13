

double renewable_average (renewable *renewable_array, int interval, int current_hour);
double saving_average              (double *price_interval_array, int interval, int current_hour);
double highest_price_in_interval   (double *price_interval_array, int interval, int current_hour);
double lowest_price_in_interval    (double *price_interval_array, int interval, int current_hour);
double get_current_price           (double *data_array, int current_hour);
double get_current_renewable_share (renewable *renew_array, int current_hour);

