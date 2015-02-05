/*==============================================================
----------------------------------------------------------------
        .88b  d88.  .d8b.  d888888b d8b   db     .o88b.
        88'YbdP`88 d8' `8b   `88'   888o  88    d8P  Y8
        88  88  88 88ooo88    88    88V8o 88    8P
        88  88  88 88~~~88    88    88 V8o88    8b
        88  88  88 88   88   .88.   88  V888 db Y8b  d8
        YP  YP  YP YP   YP Y888888P VP   V8P VP  `Y88P'
----------------------------------------------------------------
               This is Freddy's testing 'main.c'.
            Note that this is not the main 'main.c'.
----------------------------------------------------------------
==============================================================*/


//== HEADERS ===================================================
#include <stdio.h>
#include "frdsFuncs.h"
#include <time.h>

#define BIG_NUMBER 100000


//== STRUCTURES ================================================
typedef struct block{
  int ID;
  double data1;
  double data2;
  double data3;
  double data4;
  double data5;
} Block;


//== FUNCTION IN PROGRESS ======================================                             
void changeID(Block *data, int i){
  data->ID = i;
  return;
}


//== MAIN FUNCTION =============================================
int main(){
  
  float  loopTime1, loopTime2;
  int    runTime1, runTime2, diff;
  Block data[BIG_NUMBER] = {0};
 
  
  loopTime1 = clock();
  for(int i=0; i<BIG_NUMBER; i++){
    changeID(&data[i], i);
  }
  runTime1 = clock() - loopTime1;

  loopTime2 = clock();
  for(int i=0; i<BIG_NUMBER; i++){
    data[i].ID = i;
  }
  runTime2 = clock() - loopTime2;

  diff = runTime1 - runTime2;

  printf(AMAGENTA "\nLong loop: %i ms\n" ARESET, runTime1);
  printf(ACYAN "Short loop: %i ms\n\n" ARESET, runTime2);
 
  if (diff >= 0){
    printf(AGREEN "Short loop is: %i ms faster!\n\n" ARESET, diff);
  }
  else{
    printf(ARED "Short loop is: %i ms slower!\n\n" ARESET, diff);
  }
  
  return 0;
}
