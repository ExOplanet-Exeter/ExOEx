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
#include <unistd.h>


//== STRUCTURES ================================================


//== FUNCTION IN PROGRESS ======================================                             
static inline void progressBar(int x, int n, int r, int w)
{
  // Only update r times.
  if ( x % (n/r +1) != 0 ) return;
 
  // Calculuate the ratio of complete-to-incomplete.
  float ratio = x/(float)n;
  int   c     = ratio * w;
 
  // Show the percentage complete.
  printf("%3d%% [", (int)(ratio*100) );
 
  // Show the load bar.
  for (int x=0; x<c; x++)
     printf("=");
 
  for (int x=c; x<w; x++)
     printf(" ");
 
  // ANSI Control codes to go back to the
  // previous line and clear it.
  printf("]\n\033[F\033[J");
}

//== MAIN FUNCTION =============================================
int main(){
  
  for (int i=0; i<=100; i++){
    progressBar(i, 100, 101, 50);
    usleep(10000);
  }

  return 0;
}
