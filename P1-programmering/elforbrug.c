#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define AW_VALUE 1.18
#define APW_VALUE 1.02
#define APPW_VALUE 0.9
#define APPPW_VALUE 0.79
#define AD_VALUE 1.83
#define ADP_VALUE 1.62
#define ADPP_VALUE 1.45
#define ADPPP_VALUE 1.29

struct white_goods {
  char energy_label;
}white_goods;

/*Prototyper. Energy_type er en struct*/
void prompt_for_white_goods(char* energy_label);
void function_white_goods(char* energy_label);

/*Calloc sætter alle bytes i arrayet til nul*/
  int main(void) {
  char* energy_label = calloc(4, sizeof(white_goods));

  prompt_for_white_goods(energy_label);
  function_white_goods(energy_label); 

  return 0;
}

void prompt_for_washing_machine(char* energy_label) {
  

    white_goods el;
    el.energy_label = energy_label;

    printf("Enter the energy label of your washing machine: ");  
    scanf(" %s", el.energy_label);
    printf(" %s\n", el.energy_label;
}
void function_dishwasher(char* energy_label_dish) {

  double sum = 0;

  if(strcmp(energy_label, " A")) {
    sum = (AD_VALUE * );
    printf(" %.2f kWh/per use", sum);
  }
  else if(strcmp(energy_label, " A+")) {
    sum = ADPP_VALUE *;
    printf(" %.2f kWh/per use", sum);
  }
  else if(strcmp(energy_label, " A++")) {
    sum = ADPP_VALUE *;
    printf(" %.2f kWh/per use", sum);
  }
  else if(strcmp(energy_label, " A+++")) {
    sum = ADPPP_VALUE *;
    printf(" %.2f kWh/per use", sum);
  }
  else {
    printf("Wrong input");
  }
}
