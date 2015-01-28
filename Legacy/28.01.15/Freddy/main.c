/*==============================================================
----------------------------------------------------------------
          ███╗   ███╗ █████╗ ██╗███╗   ██╗    ██████╗
          ████╗ ████║██╔══██╗██║████╗  ██║   ██╔════╝
          ██╔████╔██║███████║██║██╔██╗ ██║   ██║
          ██║╚██╔╝██║██╔══██║██║██║╚██╗██║   ██║
          ██║ ╚═╝ ██║██║  ██║██║██║ ╚████║██╗╚██████╗
          ╚═╝     ╚═╝╚═╝  ╚═╝╚═╝╚═╝  ╚═══╝╚═╝ ╚═════╝
----------------------------------------------------------------
               This is Freddy's testing 'main.c'.
            Note that this is not the main 'main.c'.
----------------------------------------------------------------
==============================================================*/


//== INCLUDES ==================================================
//-- SYSTEM HEADERS --------------------------------------------
// These will be found in system library files and do not need
// to be included locally. They use <> containers.
#include <stdio.h>

//-- LOCAL HEADERS ---------------------------------------------
// These local header files must be placed within the working
// directory. They use "" containers.
#include "frdsFuncs.h"


//== FUNCTION IN PROGRESS ======================================                               
// When functions are working as intended move to header please.
// Below is an example of a function being worked on before
// being moved to 'frdsFunc.h'.
void functionBeingWorkedOn(){
  int x = 0, y = 0, z = 0;
  z = x + y;
  return;
}


//== MAIN FUNCTION =============================================
int main(){
  exampleFunction();
  functionBeingWorkedOn();
  return 0;
}
