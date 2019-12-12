
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Get_Data.h"
#include "White_goods.h"
#include "Analyze_Data.h"
#include "Utility.h"
#include "User_Dialogue.h"

int intro_frontend(profile *profile_array);
int menu_interface(profile *profiles, double *data_array);
int interface_handler(int user_response, profile *profile_array, double *data_array);
double price_kwh(double *data_array);
int price_prompt(double *data_array);
double user_input_price(void);
int interval_prompt(void);
int prompt_menu(int input);
int user_input(int input);
int overview_message(void);
int answer_handling(char input, profile *profile_array);
int user_handler(profile *profile_array);
int read_profile_data(profile *profiles);
int profile_prompt(profile *profile_array);
void init_profile(profile *profile_input);
void create_profile(profile *profile_input);
void check_fp(FILE *file_pointer);
int compare_labels(char* user_label, char **energy_label_input);
void user_name(char* name);
void energy_label_function(char* energy_label);

int intro_frontend(profile *profile_array) {
  
  printf("Welcome to A404s price evaluator\n");
  user_handler(profile_array);

  return 0;
}

int menu_interface(profile *profiles, double *data_array) {
  int user_response = 0;
  
  printf("Current price: %lf DKK/kWh - %lf%% green energy\n\n", get_current_price(data_array, get_current_hour())); /* Can fetch current price, but not green energy */
  user_response = prompt_menu(user_response);
  
  interface_handler(user_response, profiles, data_array);

  return 0;
}

int interface_handler(int user_response, profile *profile_array, double *data_array) {
  int index = -1;

  switch (user_response) {
    /*case 1:
      electricity_overview(interval_prompt());                                Analyze data - NOT INCLUDED YET 
      break;
    */
    case 2:                                                                  /* DONE DONE */
      index = read_profile_data(profile_array);
      simulate_electricity_usage(profile_array[index].energy_label_wash, profile_array[index].energy_label_dish, price_kwh(data_array));
      break;
    /*
      case 3:
      subscription_compare();                                   MISSING 
      break;  
    case -1:
      exit_function();                                          MISSING
      break;
    */
  }
  return 0;
}

double price_kwh(double *data_array){
  return price_prompt(data_array);
}

int price_prompt(double *data_array){
  char answer = 'n';
  int scanres = 0;
  double result = 0;

  printf("To calculate price of electricity usage the price of electricity in DKK/kWh is needed.\nDo you want to use the cheapest price within the next 24 hours, or manually input price?\n'C' for Cheapeast price, 'M' for Manual price: ");
  scanres = scanf(" %c", &answer);
 
  if (scanres == 1){ 
    if (answer == 'C' || answer == 'c') {
      result = lowest_price_in_interval(data_array, interval_prompt(), get_current_hour()); /* get_cheapest_price() er en del af Analyze_data modulet */
    } else if (answer == 'M' || answer == 'm') {
      result = user_input_price();
    } else {
      error_handler(1, __LINE__, __FILE__); /* Invalid input error */
    }
  } else {
    error_handler(3, __LINE__, __FILE__);
  }

  return result;
}

double user_input_price(void){
  double price  = 0,
         input  = 0;
  int scanres = 0;

  printf("Input price of electricity in DKK/kWh - BEFORE taxes (in DK usually between 0.20 and 0.60 DKK): ");
  scanres = scanf(" %lf", &input);
  
  if (scanres != 1) {
    error_handler(3, __LINE__, __FILE__); /* Too many scanf conversions */
  } else {
    price = input;
  }

  return price;
}

  
int interval_prompt(void) {
  int interval = 0,
      scanres = 0;
  printf("Input interval for which the prices should be shown (1-24): \n");
  scanres = scanf(" %d", &interval);

  if(scanres != 1) {
    error_handler(3, __LINE__, __FILE__); /* Too many scanf conversions */
  }
  if(scanres == 1 && (interval < 0 || interval > 24)) {
    error_handler(5, __LINE__, __FILE__); /* Interval out of bounds - should be between 1 and 24 */
  }

  return interval;
}

int prompt_menu(int input) {

  overview_message();
  input = user_input(input);

  return input;
}

int user_input(int input) {
  scanf(" %d", &input);
  return input;
}


int overview_message(void) {
  printf("See the list below and enter the corresponding number for each usecase: \n");
  printf("-----------------------------------------------------------------------------------\n");
  printf(" '1'  to see overview of electricity and its composition in a userdefined interval\n");
  printf(" '2'  to simulate electricity-usage based on profile information\n");
  printf(" '3'  to see price difference between set-price and variable-price subscriptions\n");
  printf(" '-1' to exit\n");
  printf("-----------------------------------------------------------------------------------\n");
  printf("\nInput: ");
  putchar('\n');
  return 0;
}

int user_handler(profile *profile_array) {
  char answer = '\0';
  printf("\nDo you have a profile? [Y/n] "); 
  scanf(" %c", &answer);
  
  answer_handling(answer, profile_array);

  return 0;
}

int answer_handling(char input, profile *profile_array) {
  char answer = input;

  if (answer == 'Y' || answer == 'y') {
    read_profile_data(profile_array); /* Stub function */
  } else if (answer == 'N' || answer == 'n') {
    profile_prompt(profile_array);
    
  } else {
    error_handler(1, __LINE__, __FILE__); /* Invalid input error handling */
  }

  return 0;
}

int read_profile_data(profile *profiles) { /* Stub function */
  int local_max_array_lgt = 100, 
      i,
      local_max_entries,
      index = 0;
  FILE *fp_profile = fopen("profile_data.txt", "r");
  char *current_str = calloc(local_max_array_lgt, sizeof(char));
  check_fp(fp_profile);
  validate_allocation(current_str);
  

  printf("Due to development deadline and project constraints, the user profile will be assumed to be the first entry in the profile_data.txt\n");
  for (i = 0, local_max_entries = 10; i < local_max_entries; ++i) { 
    if (fgets(current_str, local_max_array_lgt, fp_profile) != NULL){
      sscanf(current_str, "Username: %s, Energy label washing machine: %s, Energy label dishwasher: %s", 
                           profiles[i].profile_name, 
                           profiles[i].energy_label_wash, 
                           profiles[i].energy_label_dish);
    }
  }

  fclose(fp_profile);
  free(current_str);
  return index;
}


int profile_prompt(profile *profile_array) {
  char answer = '\0';
  printf("\nDo you want to create a profile? [Y/n] ");
  scanf(" %s", &answer);
  if (answer == 'Y' || answer == 'y') {
    create_profile(profile_array);
  } else if (answer == 'N' || answer == 'n') {
    return 0;
  } else {
    error_handler(1, __LINE__, __FILE__); /* Invalid input error handling */
  }

  return 0;
}


void init_profile(profile *profile_input) {
  FILE *fp = fopen("profile_data.txt", "a+");
  
  check_fp(fp);

  fprintf(fp, "Username: %s, Energy label washing machine: %s, Energy label dishwasher: %s\n",
                                                               "Placeholder_Username",
                                                               "A++",
                                                               "A+++");


  fclose(fp);
}

void check_fp(FILE *file_pointer) { /* Utility function */
  if (file_pointer == NULL) {
    error_handler(2, __LINE__, __FILE__); /* Could not open or access the desired file */
  }
}


void create_profile(profile *profile_input) {  /* Nominated for header */
    FILE *fp = fopen("profile_data.txt", "a+");
    char *energy_label[MAX_LABEL_LENGTH] = {"A+++", "A++", "A+", "A"};
  
    validate_allocation(profile_input);
    check_fp(fp);

    user_name(profile_input->profile_name);
    energy_label_function(profile_input->energy_label_wash);
    energy_label_function(profile_input->energy_label_dish);
   
    if((compare_labels(profile_input->energy_label_wash, energy_label) == 1) && (compare_labels(profile_input->energy_label_dish, energy_label) == 1)) {
      
      fprintf(fp, "Username: %s, Energy label washing machine: %s, Energy label dishwasher: %s\n",
                                                                   profile_input->profile_name,
                                                                   profile_input->energy_label_wash,
                                                                   profile_input->energy_label_dish);

      printf("You succesfully entered energy_label_wash\n\n" );
    }
    if (compare_labels(profile_input->energy_label_wash, energy_label) != 1) {
      printf("Failed to input wash label..\n");
    }
    if (compare_labels(profile_input->energy_label_dish, energy_label) != 1) {
      printf("Failed to input dish label..\n");
    }   

  fclose(fp);
}

int compare_labels(char* user_label, char** energy_label_input) {
  int result,
      i;
  for (i = 0, result = 0; i < 4 && result != 1; i++) {  
    if (strcmp(user_label, energy_label_input[i]) == 0) {
       result = 1;
    } else if ((strcmp(user_label, energy_label_input[i]) != 0) && result != 1) {
       result = -1;
    }
  }

  return result;
}


void user_name(char* name) {
  int scanres = 0;
  printf("\nEnter username (max 20 characters): \n");
  scanres = scanf(" %s", name);

  if(scanres != 1) {
    error_handler(3, __LINE__, __FILE__); /* Too many scanf conversions */
  }
  if(scanres == 1 && strlen(name) > MAX_NAME_LENGTH) {
    error_handler(4, __LINE__, __FILE__); /* Too long user name - MAX 20 characters */
  }
}

void energy_label_function(char* energy_label) {
  int scanres = 0;
  printf("\nEnter energy label (A, A+, A++, A+++): ");
  scanres = scanf(" %s", energy_label);

  if(scanres != 1) {
    error_handler(3, __LINE__, __FILE__); /* Too many scanf conversions */
  }
}
