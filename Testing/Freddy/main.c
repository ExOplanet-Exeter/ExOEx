#include <stdio.h>

int main(int argc, char **argv)
{ 

  int i = 0, j= 0;
   #pragma omp parallel
  {
    for (i;i<100;i++)
    printf("%i\n");
    j++;
  }
  printf("%i\n",j);

  return 0;
}