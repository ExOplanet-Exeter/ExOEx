#include <stdio.h>
#include <omp.h>

int main(int argc, char **argv)
{
 
  set_num_threads(4);
  
   #pragma omp parallel
  {
    printf("Hello OpenMP!\n");
  }

  return 0;
}