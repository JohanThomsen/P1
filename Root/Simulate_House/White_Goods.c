#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

/* The values for the energy labels and the max length of arrays are defined.
   AW is for washing machines and AD is for dishwasher*/
#define MAX_USERS 10
#define MAX_NAME_LENGTH 20
#define MAX_LABEL_LENGTH 4
#define AW_VALUE 1.18
#define APW_VALUE 1.02
#define APPW_VALUE 0.9
#define APPPW_VALUE 0.79
#define AD_VALUE 1.83
#define ADP_VALUE 1.62
#define ADPP_VALUE 1.45
#define ADPPP_VALUE 1.29

/*This is a struct, that contains three char-variables*/
typedef struct{
  char *profile_name;
  char *energy_label_wash;
  char *energy_label_dish;
}profile;

/*Prototyper for funktioner.*/
void function_washing_machine(profile User1, double user_price);
void function_dishwasher(profile User1, double user_price);

int main(void) {
  /*char *energy_label[4] = {"A", "A+", "A++", "A+++"};*/

  profile  User1;
  double user_price;

  User1.profile_name = "Jens";
  User1.energy_label_wash = "A+++";
  User1.energy_label_dish = "A";

  user_price = 1.23;
  /*Here are the function calls*/
  function_dishwasher(User1, user_price);
  function_washing_machine(User1, user_price);

  return 0;
}
/* This function calculates the price pr use for a dishwasher. The function contains
   if-else statements for each energy label. Each energy label is assigned with a different value depending on the label.
   APPPW (A+++) is assigned the lowest value and AW is assigned the highest value (A).
   The function takes the user input(energy label) and multiplies it with the price that comes from the analyze data module. */

void function_dishwasher(profile User1, double user_price) {

  double kWh_pr_use ;
  double kr_pr_use ;
  if(strcmp(User1.energy_label_dish, "A") == 0) {
    kWh_pr_use = AD_VALUE;
    kr_pr_use = kWh_pr_use * user_price;
    printf("Your dishwasher consume %.2f kWh/per use and cost %.2f kr/per use\n", kWh_pr_use, kr_pr_use);
  }
  else if(strcmp(User1.energy_label_dish, "A+") == 0) {
    kWh_pr_use = ADP_VALUE;
    kr_pr_use = kWh_pr_use * user_price;
    printf("Your dishwasher consume %.2f kWh/per use and cost %.2f kr/per use\n", kWh_pr_use, kr_pr_use);
  }
  else if(strcmp(User1.energy_label_dish, "A++") == 0) {
    kWh_pr_use = ADPP_VALUE;
    kr_pr_use = kWh_pr_use * user_price;
    printf("Your dishwasher consume %.2f kWh/per use and cost %.2f kr/per use\n", kWh_pr_use, kr_pr_use);
  }
  else if(strcmp(User1.energy_label_dish, "A+++") == 0) {
    kWh_pr_use = ADPPP_VALUE;
    kr_pr_use = kWh_pr_use * user_price;
    printf("Your dishwasher consume %.2f kWh/per use and cost %.2f kr/per use\n", kWh_pr_use, kr_pr_use);
  }
  else {
    printf("Wrong input");
  }
}
/* This function calculates the price pr use for a washing machine. The function contains
   if-else statements for each energy label. Each energy label is assigned with a different value depending on the label.
   ADDDP (A+++) is assigned the lowest value and AW is assigned the highest value (A).
   The function takes the user input(energy label) and multiplies it with the price that comes from the analyze data module. */
void function_washing_machine(profile User1, double user_price) {

  double kWh_pr_use = 0.0;
  double kr_pr_use = 0.0;

  if(strcmp(User1.energy_label_wash, "A") == 0) {
    kWh_pr_use = AW_VALUE;
    kr_pr_use = kWh_pr_use * user_price;
    printf("Your washing machine consume %.2f kWh/per use and cost %.2f kr/per use\n", kWh_pr_use, kr_pr_use);
  }
  else if(strcmp(User1.energy_label_wash, "A+") == 0) {
    kWh_pr_use = APW_VALUE;
    kr_pr_use = kWh_pr_use * user_price;
    printf("Your washing machine consume %.2f kWh/per use %.2f and cost kr/per use\n", kWh_pr_use, kr_pr_use);
  }
  else if(strcmp(User1.energy_label_wash, "A++") == 0) {
    kWh_pr_use = APPW_VALUE;
    kr_pr_use = kWh_pr_use * user_price;
    printf("Your washing machine consume %.2f kWh/per use and cost %.2f kr/per use\n", kWh_pr_use, kr_pr_use);
  }
  else if(strcmp(User1.energy_label_wash, "A+++") == 0) {
    kWh_pr_use = APPPW_VALUE;
    kr_pr_use = kWh_pr_use * user_price;
    printf("Your washing machine consume %.2f kWh/per use and cost %.2f kr/per use\n", kWh_pr_use, kr_pr_use);
  }
  else {
    printf("Wrong input");
  }
}
/*void prompt_for_profile() {
  char answer;

  printf("Do you have a profile?(Y/N)\n");
  scanf(" %c", &answer );

  if(answer == 'Y') {
    FILE *fp
    fp = fopen(fp, )
  }
  else if (answer == 'N') {
    prompt_for_white_goods(User1);
  }
  else {
      printf("Wrong input - try again (Y/N)");
  }
}*/
