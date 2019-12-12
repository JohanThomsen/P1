#include <stdio.h>
#include "Utility.h"

void error_handler(int error_code, int line_number, char *file) {
  switch (error_code) {
    case 1:
      printf("Error_code: %.2d in '%s' on line '%d' - Invalid input\n", error_code, file, line_number);
      break;

    case 2:
      printf("Error_code: %.2d in '%s' on line '%d' - Could not find or open desired file\n", error_code, file, line_number);
      break;

    case 3:
      printf("Error_code: %.2d in '%s' on line '%d' - Too many or too few scanf() conversions\n", error_code, file, line_number);
      break;

    case 4:
      printf("Error_code: %.2d in '%s' on line '%d' - Too many input characters\n", error_code, file, line_number);
      break;
    
    case 5:
      printf("Error_code: %.2d in '%s' on line '%d' - Index out of bounds\n", error_code, file, line_number);
      break;

    case 6:
      printf("Error_code: %.2d in '%s' on line '%d' - NULL Pointer\n", error_code, file, line_number);
      break;

  }
}

void validate_allocation(void* input_pointer) {
  if (input_pointer == NULL) {
    error_handler(6, __LINE__, __FILE__); /* NULL POINTER */
  }
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

