/*==============================================================
----------------------------------------------------------------
    ad88                       88                ad88
   d8"                         88               d8"
   88                          88               88
 MM88MMM  8b,dPPYba,   ,adPPYb,88  ,adPPYba,  MM88MMM
   88     88P'   "Y8  a8"    `Y88  I8[    ""    88
   88     88          8b       88   `"Y8ba,     88   88
   88     88          "8a,   ,d88  aa    ]8I    88   88
   88     88           `"8bbdP"Y8  `"YbbdP"'    88   88
88       88  8b,dPPYba,    ,adPPYba,  ,adPPYba,      88,dPPYba,
88       88  88P'   `"8a  a8"     ""  I8[    ""      88P'    "8a
88       88  88       88  8b           `"Y8ba,       88       88
"8a,   ,a88  88       88  "8a,   ,aa  aa    ]8I  88  88       88
 `"YbbdP'Y8  88       88   `"Ybbd8"'  `"YbbdP"'  88  88       88
----------------------------------------------------------------
  This header file contains Freddys completed test functions.
----------------------------------------------------------------
==============================================================*/


//== INCLUDES ==================================================
// Allows the use of everything found in Arc's global.h header.
// If functions are moved into the Arc build then they must
// comply with global.h, so it's useful to keep this in.
#include "../../Arc/globals/headers/global.h"


//== FUNCTIONS =================================================
// This function is just used as an example of how to use
// functions from a header file.
void exampleFunction(){
  printf(ACYAN "This is Freddy's testing area...\n" ARESET);

  return;
}
