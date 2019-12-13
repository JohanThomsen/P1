#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Utility.h"
#include "Get_Data.h"
#include "White_Goods.h"
#include "User_Dialogue.h"

/* The values for the energy labels and the max length of arrays are defined.
   AW is for washing machines and AD is for dishwasher*/
#define AW_VALUE    1.18
#define AWP_VALUE   1.02
#define AWPP_VALUE  0.90
#define AWPPP_VALUE 0.79
#define AD_VALUE    1.83
#define ADP_VALUE   1.62
#define ADPP_VALUE  1.45
#define ADPPP_VALUE 1.29


typedef struct {
  char    label[MAX_LABEL_LENGTH];
  double  usage;
} labels;

/*Prototyper for funktioner.*/
void function_washing_machine(char* energy_label_wash, double user_price);
void function_dishwasher(char* energy_label_dish, double user_price);


/* This function calculates the price pr use for a dishwasher. The function contains
   if-else statements for each energy label. Each energy label is assigned with a different value depending on the label.
   ADPPP (A+++) is assigned the lowest value and AW is assigned the highest value (A).
   The function takes the user input(energy label) and multiplies it with the price that comes from the analyze data module. */

void function_dishwasher(char* energy_label_dish, double user_price) {

  if(strcmp(energy_label_dish, "A") == 0) {
    printf("Your dishwasher consume %.2f kWh/per use and cost %.2f DKK/per use\n", AD_VALUE, user_price*AD_VALUE);
  }
  else if(strcmp(energy_label_dish, "A+") == 0) {
    printf("Your dishwasher consume %.2f kWh/per use and cost %.2f DKK/per use\n", ADP_VALUE, user_price*ADP_VALUE);
  }
  else if(strcmp(energy_label_dish, "A++") == 0) {
    printf("Your dishwasher consume %.2f kWh/per use and cost %.2f DKK/per use\n", ADPP_VALUE, user_price*ADPP_VALUE);
  }
  else if(strcmp(energy_label_dish, "A+++") == 0) {
    printf("Your dishwasher consume %.2f kWh/per use and cost %.2f DKK/per use\n", ADPPP_VALUE, user_price*ADPPP_VALUE);
  }
  else {
    error_handler(1, __LINE__, __FILE__);
  }
}
/* This function calculates the price pr use for a washing machine. The function contains
   if-else statements for each energy label. Each energy label is assigned with a different value depending on the label.
   AWPPP (A+++) is assigned the lowest value and AW is assigned the highest value (A).
   The function takes the user input(energy label) and multiplies it with the price that comes from the analyze data module.*/
void function_washing_machine(char* energy_label_wash, double user_price) {

  if(strcmp(energy_label_wash, "A") == 0) {
    printf("Your washing machine consume %.2f kWh/per use and cost %.2f DKK/per use\n", AW_VALUE, user_price*AW_VALUE);
  }
  else if(strcmp(energy_label_wash, "A+") == 0) {
    printf("Your washing machine consume %.2f kWh/per use and cost %.2f DKK/per use\n", AWP_VALUE, user_price*AWP_VALUE);
  }
  else if(strcmp(energy_label_wash, "A++") == 0) {
    printf("Your washing machine consume %.2f kWh/per use and cost %.2f DKK/per use\n", AWPP_VALUE, user_price*AWPP_VALUE);
  }
  else if(strcmp(energy_label_wash, "A+++") == 0) {
    printf("Your washing machine consume %.2f kWh/per use and cost %.2f DKK/per use\n", AWPPP_VALUE, user_price*AWPPP_VALUE);
  }
  else {
    error_handler(1, __LINE__, __FILE__);
  }
}
/* This function calls both functions*/
void simulate_electricity_usage(char* energy_label_wash, char* energy_label_dish, double user_price) {
  function_washing_machine( energy_label_wash, user_price);
  function_dishwasher( energy_label_dish, user_price);
  printf("-----------------------------------------------------------------------------------\n\n");
}
