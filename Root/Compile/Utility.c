#include <stdio.h>
#include "Utility.h"

void error_handler(int error_code) {
  switch (error_code) {
    case 1:
      break;

    case 2:
      break;

    case 3:
      break;

    case 4:
      break;
    
    case 5:
      break;

    case 6:
      break;
  }
  printf("Error code: %d", error_code);
}

void validate_allocation(void* input_pointer) {
  if (input_pointer == NULL) {
    error_handler(6); /* NULL POINTER */
  }
}
