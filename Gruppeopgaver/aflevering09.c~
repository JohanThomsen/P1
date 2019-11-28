#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH_OF_KULOER             6
#define ANTAL_SPILLEKORT_I_ET_SPIL_KORT 55

enum kuloer {Hjerter = 1, Ruder, Spar, Kloer};

struct spillekort{
  int  kuloer;
  int  vaerdi;
};
typedef struct spillekort spillekort;

spillekort smart_function(int vaerdi, int kuloer);

int main(void){
  spillekort* et_spil_kort = calloc(ANTAL_SPILLEKORT_I_ET_SPIL_KORT, sizeof(spillekort));
  int i;

  for(i = 0; i < 13; ++i){
    et_spil_kort[i]    = smart_function(i+1, 1);
    et_spil_kort[i+13] = smart_function(i+1, 2);
    et_spil_kort[i+26] = smart_function(i+1, 3);
    et_spil_kort[i+39] = smart_function(i+1, 4);

  }

  for(i = 0; i < 52; ++i){
    printf("%s %2d\n", et_spil_kort[i].kuloer == 1 ? "Hjerter" : et_spil_kort[i].kuloer == 2 ? "Ruder" : et_spil_kort[i].kuloer == 3 ? "Spar" : "Kloer", et_spil_kort[i].vaerdi);
  }

  return 0;
}

spillekort smart_function(int vaerdi, int kuloer){
  spillekort genereret_kort;

  if(kuloer == Hjerter){
    genereret_kort.kuloer = kuloer;
    genereret_kort.vaerdi = vaerdi; 
  }  
  if(kuloer == Kloer){
    genereret_kort.kuloer = kuloer;
    genereret_kort.vaerdi = vaerdi; 
  }
  if(kuloer == Ruder){
    genereret_kort.kuloer = kuloer;
    genereret_kort.vaerdi = vaerdi; 
  }
  if(kuloer == Spar){
    genereret_kort.kuloer = kuloer;
    genereret_kort.vaerdi = vaerdi; 
  }
  
  return genereret_kort;

}




