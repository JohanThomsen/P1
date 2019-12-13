#define MAX_USERS        10
#define MAX_NAME_LENGTH  20
#define MAX_LABEL_LENGTH  5

typedef struct {
  char profile_name[MAX_NAME_LENGTH];
  char energy_label_wash[MAX_LABEL_LENGTH];
  char energy_label_dish[MAX_LABEL_LENGTH];
} profile;

void error_handler       (int error_code, int line_number, char *file);
void* validate_allocation(void* input_pointer, int line_number, char *file);
void init_profile        (profile *profile_input);
void check_fp(FILE *file_pointer, int line_number, char *file);

#define RENEW_ARRAY_SIZE 144

typedef struct {
  double total_load;
  double hydro_power;
  double other_renewable;
  double solar_power;
  double onshore_windpower;
  double offshore_windpower;
} renewable;

void read_file           (renewable *renewable_array);
