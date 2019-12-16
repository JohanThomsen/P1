#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Utility.h"
#include "Get_Data.h"
#include "White_Goods.h"
#include "Analyze_Data.h"
#include "User_Dialogue.h"



int    user_handler          (profile *profile_array);
int    answer_handling       (char input, profile *profile_array);
int    profile_prompt        (profile *profile_array);
void   create_profile        (profile *profile_input);
void   user_name             (char* name);
void   energy_label_function (char* energy_label);
int    compare_labels        (char* user_label, char **energy_label_input);
int    prompt_menu           (int input);
int    user_input            (int input);
int    overview_message      (void);
int    interface_handler     (int user_response, profile *profile_array, double *data_array, renewable *renew_array);
void   electricity_overview  (double *data_array, renewable *renew_array, int interval);
void   print_data_array      (double *data_array, renewable *renew_array, int interval, int current_hour);
double price_prompt          (double *data_array, renewable *renew_array, int *time);
double user_input_price      (void);
int    interval_prompt       (void);



int intro_frontend(profile *profile_array, double *data_array, time_of_day current_time, renewable *renewable_array) {
  printf("------------------------------------------------------------------------------------------------------------------\n");
  printf("                                       Welcome to A404s P1 Project solution                                       \n");
  print_current_price(data_array, current_time.hour, renewable_array);
  printf("------------------------------------------------------------------------------------------------------------------\n");
  return user_handler(profile_array);
}

int user_handler(profile *profile_array) {
  char answer = '\0';
  printf("\nDo you have a profile? [Y/n] "); 
  scanf(" %c", &answer);
  
  return answer_handling(answer, profile_array);
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

int read_profile_data(profile *profiles) {
  int local_max_array_lgt = 100, 
      i,
      local_max_entries,
      index = 0;
  FILE *fp_profile = fopen("profile_data.txt", "r");
  char *current_str = calloc(local_max_array_lgt, sizeof(char));
  check_fp(fp_profile, __LINE__, __FILE__);
  validate_allocation(current_str, __LINE__, __FILE__);
  
  for (i = 0, local_max_entries = 10; i < local_max_entries; ++i) { 
    if (fgets(current_str, local_max_array_lgt, fp_profile) != NULL){
      sscanf(current_str, " Username: %s , Washer: %s , Dishwasher: %s", 
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
    clear_screen();
    return 0;
  } else {
    error_handler(1, __LINE__, __FILE__); /* Invalid input error handling */
  }

  return 0;
}

void create_profile(profile *profile_input) {  /* Nominated for header */
    FILE *fp = fopen("profile_data.txt", "a+");
    char *energy_label[MAX_LABEL_LENGTH] = {"A+++", "A++", "A+", "A"};
  
    check_fp(fp, __LINE__, __FILE__);

    user_name(profile_input->profile_name);
    energy_label_function(profile_input->energy_label_wash);
    energy_label_function(profile_input->energy_label_dish);
   
    if((compare_labels(profile_input->energy_label_wash, energy_label) == 1) && (compare_labels(profile_input->energy_label_dish, energy_label) == 1)) {
      
      fprintf(fp, "Username: %s, Energy label washing machine: %s, Energy label dishwasher: %s\n",
                                                                   profile_input->profile_name,
                                                                   profile_input->energy_label_wash,
                                                                   profile_input->energy_label_dish);

    }
    if (compare_labels(profile_input->energy_label_wash, energy_label) != 1) {
      error_handler(1, __LINE__, __FILE__);
    }
    if (compare_labels(profile_input->energy_label_dish, energy_label) != 1) {
      error_handler(1, __LINE__, __FILE__);
    }   

  fclose(fp);
  clear_screen();
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
  printf("\nEnter energy label, first washing machine, then dishwasher (A, A+, A++, A+++): ");
  scanres = scanf(" %s", energy_label);

  if(scanres != 1) {
    error_handler(3, __LINE__, __FILE__); /* Too many scanf conversions */
  }
}


int menu_interface(profile *profiles, double *data_array, renewable *renew_array) {
  int user_response = 0;
  
  user_response = prompt_menu(user_response);
  
  return interface_handler(user_response, profiles, data_array, renew_array);

}

int prompt_menu(int input) {

  overview_message();
  input = user_input(input);

  return input;
}

int overview_message(void) {
  printf("------------------------------------------------------------------------------------------------------------------\n");
  printf("                                           What would you like to do ?                                            \n");
  printf("------------------------------------------------------------------------------------------------------------------\n");
  printf(" '1'  to see overview of electricity and its composition in a userdefined interval\n");
  printf(" '2'  to simulate electricity-price based on profile information in given interval\n");
  printf(" '3'  to create profile\n");
  printf(" '-1' to exit\n");
  printf("------------------------------------------------------------------------------------------------------------------\n");
  printf("Input: ");
  return 0;
}

int user_input(int input) {
  scanf(" %d", &input);
  return input;
}

int interface_handler(int user_response, profile *profile_array, double *data_array, renewable *renew_array) {
  int index = -1;
  int time = 0;
  double price;
  clear_screen();
  switch (user_response) {
    case 1:
      electricity_overview(data_array, renew_array, interval_prompt());
      break;
    
    case 2:
      price = price_prompt(data_array, renew_array, &time);
      index = read_profile_data(profile_array);
      simulate_electricity_usage(profile_array[index].energy_label_wash, profile_array[index].energy_label_dish, price, time);
      break;

    case 3:
      create_profile(profile_array);
      break;
    case -1:
      return -1;
      break;
  }
  return 0;
}
      
void electricity_overview(double *data_array, renewable *renew_array, int interval){
  int time = 0;
  int current_hour = get_current_hour();
  printf("------------------------------------------------------------------------------------------------------------------\n");
  printf("                                     Overview of hourly prices in inputted interval                               \n");
  print_data_array(data_array, renew_array, interval, current_hour);
  printf("------------------------------------------------------------------------------------------------------------------\n");
  printf("                        Average, minimum and maximum values for price and share of green energy                   \n");
  printf("------------------------------------------------------------------------------------------------------------------\n");
  printf("Average price: %2.2f DKK/kWh - Average green energy share %2.2f %%\n", saving_average(data_array, interval, current_hour), renewable_average(renew_array, interval, current_hour));
  printf("Mininum price: %2.2f DKK/kWh - Minimum green energy share %2.2f %%\n", lowest_price_in_interval(data_array, interval, current_hour, &time), lowest_percent_renewable_in_interval(renew_array, interval, current_hour));
  printf("Maximum price: %2.2f DKK/kWh - Maximum green energy share %2.2f %%\n", highest_price_in_interval(data_array, interval, current_hour), highest_percent_renewable_in_interval(renew_array, interval, current_hour));
}

/* Input : Double data_array, int current_hour, int interval
 * No Output:
 * Method: Prints data_array of prices from current time, and inputted interval amount of hours forward */
void print_data_array(double *data_array, renewable *renew_array, int interval, int current_hour){
  int i;
  interval += current_hour;
  printf("------------------------------------------------------------------------------------------------------------------\n");
  for (i = current_hour; i < interval; ++i){
    printf("%2.2d:00 = %2.2f DKK/kWh - %3.2f %% green energy\n", (i % 24), data_array[i], get_current_renewable_share(renew_array, i));
  }
}

double price_prompt(double *data_array, renewable *renew_array, int *time){
  char answer   = 'n';
  int scanres   =   0,
      interval  =   0;
  double result =   0;
  clear_screen();
  printf("------------------------------------------------------------------------------------------------------------------\n");
  printf(" To calculate price of electricity usage the price of electricity in DKK/kWh is needed.\n\n Do you want to use the cheapest price within customized interval over the next 24 hours, or manually input price?\n\n'C' for Cheapest price or 'M' for Manual price: ");
  scanres = scanf(" %c", &answer);
  putchar('\n');
 
  if (scanres == 1){ 
    if (answer == 'C' || answer == 'c') {
      interval = interval_prompt();
      result = lowest_price_in_interval(data_array, interval, get_current_hour(), time);
      print_data_array(data_array, renew_array, interval, get_current_hour());
    } else if (answer == 'M' || answer == 'm') {
      result = user_input_price();
    } else{
      error_handler(1, __LINE__, __FILE__); /* Invalid input error */
    }
  } else {
    error_handler(3, __LINE__, __FILE__);
  }

  return result;
}

int interval_prompt(void) {
  int interval = 0,
      scanres  = 0;
  printf("------------------------------------------------------------------------------------------------------------------\n");
  printf("Input interval for which the prices should be shown (1-24): ");
  scanres = scanf(" %d", &interval);

  if(scanres != 1) {
    error_handler(3, __LINE__, __FILE__); /* Too many scanf conversions */
  }
  if(scanres == 1 && (interval < 0 || interval > 24)) {
    error_handler(5, __LINE__, __FILE__); /* Interval out of bounds - should be between 1 and 24 */
  }

  return interval;
}

double user_input_price(void){
  double price  = 0,
         input  = 0;
  int scanres = 0;

  printf("\nInput price of electricity in DKK/kWh - BEFORE taxes (in DK usually between 0.20 and 0.60 DKK): ");
  scanres = scanf(" %lf", &input);
  printf("------------------------------------------------------------------------------------------------------------------\n");
  if (scanres != 1) {
    error_handler(3, __LINE__, __FILE__); /* Too many scanf conversions */
  } else {
    price = input;
  }

  return price;
}
void print_current_price(double *data_array, int current_hour, renewable* renew_array){
  printf("                            The current price is: %2.2lf DKK/kWh - %2.2lf %% green energy                          \n", get_current_price(data_array, current_hour), get_current_renewable_share(renew_array, current_hour));
}