#include <stdio.h>
#include <omp.h>

int main(){
  
  int i, threadID;
  int g_nLoops, p_nLoops;

  g_nLoops = 0;
  
  #pragma omp parallel private(p_nLoops, threadID)
  {
    p_nLoops = 0;
    threadID = omp_get_thread_num();
    
    #pragma omp for
    for (i=0; i<100000; i++){
      ++p_nLoops;
    }
    
    #pragma omp critical
      {
      printf("Thread %i adding %i to sum (%i)\n",threadID,p_nLoops,g_nLoops);

      g_nLoops = g_nLoops + p_nLoops;
      
      printf("Total loops = %i.\n\n",g_nLoops);
      }
  }
  
  printf("Final total loops = %i\n",g_nLoops);
  
  return 0;
}