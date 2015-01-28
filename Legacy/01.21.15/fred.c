#include "utilities.h"
#include <stdio.h>

int main(){
  printf("This is Fred's testing area:\n");
  double total, average;
  for (int i=0; i<10; i++) {
    double R=arcRand(0.0,2.0);
    printf("%lf\n",R);
    total = total + R;
  }
  average = total/10.0;
  printf("average = %lf\n",average);

  if (abs(average - 1.0) < 0.25){
    printf("WORKING!\n");
  }
  else {
    printf("NOT WORKING!\n");
  }
}
