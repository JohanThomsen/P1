#include <stdio.h>
#include "Utility.h"

void error_handler(int error_code) {
  switch (error_code) {
    case 1:
      printf("Error_code: %.2d - Invalid input\n", error_code);
      break;

    case 2:
      printf("Error_code: %.2d - Could not find or open desired file\n", error_code);
      break;

    case 3:
      printf("Error_code: %.2d - Too many or too few scanf() conversions\n", error_code);
      break;

    case 4:
      printf("Error_code: %.2d - Too many input characters\n", error_code);
      break;
    
    case 5:
      printf("Error_code: %.2d - Index out of bounds\n", error_code);
      break;

    case 6:
      printf("Error_code: %.2d - NULL Pointer\n", error_code);
      break;
  }
}

void validate_allocation(void* input_pointer) {
  if (input_pointer == NULL) {
    error_handler(6); /* NULL POINTER */
  }
}
