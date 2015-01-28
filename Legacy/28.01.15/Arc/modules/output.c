/*==============================================================                               
----------------------------------------------------------------
  ██████╗ ██╗   ██╗████████╗██████╗ ██╗   ██╗████████╗ ██████╗
 ██╔═══██╗██║   ██║╚══██╔══╝██╔══██╗██║   ██║╚══██╔══╝██╔════
 ██║   ██║██║   ██║   ██║   ██████╔╝██║   ██║   ██║   ██║    
 ██║   ██║██║   ██║   ██║   ██╔═══╝ ██║   ██║   ██║   ██║     
 ╚██████╔╝╚██████╔╝   ██║   ██║     ╚██████╔╝   ██║██╗╚██████╗
  ╚═════╝  ╚═════╝    ╚═╝   ╚═╝      ╚═════╝    ╚═╝╚═╝ ╚═════╝ 
----------------------------------------------------------------                     
  The 'output.c' function takes data in the form of a particle
                      array (of photons).
Data is then either output to a simple .txt file. Or graphically
                   utilising a QTIPlot pipe.
----------------------------------------------------------------                     
==============================================================*/


//== INCLUDES ==================================================                     
//-- SYSTEM HEADERS --------------------------------------------                     
// Allows use of math functions such as sine/cosine etc.


//-- LOCAL HEADERS ---------------------------------------------                     
#include "../globals/global.h"


//== FUNCTION IN PROGRESS ======================================                     
// When functions are working as intended move to header please.                     


//== PHOTON LOOP FUNCTION ======================================                     
void output(Planet exo, Particle photon[exo.nPhot]){

  //-- ENTRY -----------------------------------------------------
  // Debug printing.
    if (DEBUG){
    printf(ACYAN "Output Running:\n" ARESET);
  }

  return;
}
