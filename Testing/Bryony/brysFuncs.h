/*==============================================================
----------------------------------------------------------------
88                                                  ad88
88                                                 d8"
88                                                 88
88,dPPYba,   8b,dPPYba,  8b       d8  ,adPPYba,  MM88MMM
88P'    "8a  88P'   "Y8  `8b     d8'  I8[    ""    88
88       d8  88           `8b   d8'    `"Y8ba,     88
88b,   ,a8"  88            `8b,d8'    aa    ]8I    88
8Y"Ybbd8"'   88              Y88'     `"YbbdP"'    8888
                             d8'                     88
                            d8'                      88
88       88  8b,dPPYba,    ,adPPYba,  ,adPPYba,      88,dPPYba,
88       88  88P'   `"8a  a8"     ""  I8[    ""      88P'    "8a
88       88  88       88  8b           `"Y8ba,       88       88
"8a,   ,a88  88       88  "8a,   ,aa  aa    ]8I  88  88       88
 `"YbbdP'Y8  88       88   `"Ybbd8"'  `"YbbdP"'  88  88       88
----------------------------------------------------------------
  This header file contains Bryony's completed test functions.
----------------------------------------------------------------
==============================================================*/


//== INCLUDES ==================================================
// Allows the use of everything found in Arc's global.h header.
// If functions are moved into the Arc build then they must
// comply with global.h, so it's useful to keep this in.
#include "../../Arc/globals/global.h"


//== FUNCTIONS =================================================
// This function is just used as an example of how to use
// functions from a header file.
void exampleFunction(){
    printf(ACYAN "This is Bryony's testing area...\n" ARESET);
    
    return;
}
