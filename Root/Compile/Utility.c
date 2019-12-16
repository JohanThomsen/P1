#include <stdio.h>
#include <stdlib.h>
#include "Utility.h"

void error_handler(int error_code, int line_number, char *file) {
  char *errors[] = {"NULL Pointer",
                    "Invalid input",
                    "Could not find or open desired file",
                    "Too many or too few scanf() conversions",
                    "Too many input characters",
                    "Index out of bounds",
                    };

  printf("Error_code: %.2d %s in '%s' on line '%.2d'\n", error_code, errors[error_code], file, line_number);
  exit(EXIT_FAILURE);
}

void validate_allocation(void* input_pointer, int line_number, char *file) {
  if (input_pointer == NULL) {
    error_handler(0, line_number, file); /* NULL POINTER */
  }
}

void init_profile(void) {
  FILE *fp = fopen("profile_data.txt", "a+");
  
  check_fp(fp, __LINE__, __FILE__);

  fprintf(fp, "Username: %s , Washer: %s , Dishwasher: %s\n",
                                         "Holder_Username",
                                         "A++",
                                         "A+++");


  fclose(fp);
}

void check_fp(FILE *file_pointer, int line_number, char *file) { /* Utility function */
  if (file_pointer == NULL) {
    error_handler(2, line_number, file); /* Could not open or access the desired file */
  }
}

void clear_screen(){
    #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
        system("clear");
    #endif

    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #endif
}

