#define MAX_USERS        10
#define MAX_NAME_LENGTH  20
#define MAX_LABEL_LENGTH  5


typedef struct {
  char profile_name[MAX_NAME_LENGTH];
  char energy_label_wash[MAX_LABEL_LENGTH];
  char energy_label_dish[MAX_LABEL_LENGTH];
} profile;

void init_profile(profile *profile_input);


