#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main(void)
{
  void create_profile(profile *profile_input, char **energy_label) {
    int i;
    FILE *fp = fopen("profile_data.txt", "a+");

    printf("Enter username (max 20 characters): ");
    scanf(" %s", profile_input->profile_name);
    printf("Enter your energy label for your washing machine: ");
    scanf(" %s", profile_input->energy_label_wash);
    for ( i = 0; i < 4; i++) {
      if((strcmp(profile_input->energy_label_wash, energy_label[i]) == 0)){
        printf("you succesfully entered energy_label_wash\n" );
      } else if ((strcmp(profile_input->energy_label_wash, energy_label[0]) != 0) &&
      (strcmp(profile_input->energy_label_wash, energy_label[1]) != 0) &&
      (strcmp(profile_input->energy_label_wash, energy_label[2]) != 0) &&
      (strcmp(profile_input->energy_label_wash, energy_label[3]) != 0)) {
        printf("failed to input wash label..\n");
        i=4;
      }
    }
    printf("Enter your energy label for your dishwasher: ");
    scanf(" %s", profile_input->energy_label_dish);

    for ( i = 0; i < 4; i++) {
      if((strcmp(profile_input->energy_label_dish, energy_label[i]) == 0)){
        printf("you succesfully entered energy_label_dish\n" );
      } else if ((strcmp(profile_input->energy_label_dish, energy_label[0]) != 0) &&
      (strcmp(profile_input->energy_label_dish, energy_label[1]) != 0) &&
      (strcmp(profile_input->energy_label_dish, energy_label[2]) != 0) &&
      (strcmp(profile_input->energy_label_dish, energy_label[3]) != 0)) {
        printf("failed to input dish label..\n");
        i=4;
      }
    }




      /*if(strcmp(profile_input->energy_label_dish, energy_label[i]) == 0){
        printf("Profile succeeded\n" );
      }
      else{
        printf("Wrong input, dsatry again\n");
      }*/

    fprintf(fp, "Username: %s, Energy label washing machine: %s, Energy label dishwasher: %s\n",
                                                                 profile_input->profile_name,
                                                                 profile_input->energy_label_wash,
                                                                 profile_input->energy_label_dish);



    /*for(i = 0; i < 4; i++) {
    printf("%s\n", energy_label[i] );
  }*/

    fclose(fp);
  }

    return 0;
}
