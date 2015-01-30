/*==============================================================
----------------------------------------------------------------
                                           88               88
                                           88               88
                                           88               88
 88,dPYba,,adPYba,    ,adPPYba,    ,adPPYb,88  88       88  88
 88P'   "88"    "8a  a8"     "8a  a8"    `Y88  88       88  88
 88      88      88  8b       d8  8b       88  88       88  88
 88      88      88  "8a,   ,a8"  "8a,   ,d88  "8a,   ,a88  88
 88      88      88   `"YbbdP"'    `"8bbdP"Y8   `"YbbdP'Y8  88
                                                     88
                                                     88
                                                     88
                                     ,adPPYba,       88,dPPYba,
                                    a8P_____88       88P'    "8a
                                    8PP"""""""       88       88
                                    "8b,   ,aa  888  88       88
                                     `"Ybbd8"'  888  88       88
----------------------------------------------------------------
 This header file contains the function prototypes for the core
                    modules used within Arc.
----------------------------------------------------------------
==============================================================*/


//== FUNCTION PROTOTYPES =======================================
// Input function for reading from .cfg files and parseing data
// into relevant structure types.
Planet input(Planet);
// Main photonLoop function for core simulation calculations.
void photonLoop(Particle photon[], Planet exo);
// Output function for writing aspects of photon[] to data
// files.
void output(Particle photon[], Planet exo, Datasystem data);


// Grabs the number of layers from config.cfg so that correctly
// sied memory allocation may occure.
int grabNumberOfLayers(){
    int nLayers;
    FILE *config;
    char word[MAX_WORD_LENGTH];
    config = fopen("dependencies/config.cfg","r");
    if (config == NULL){
        printf(ARED "ERROR! Could not open config.cfg!\n" ARESET);
    }
    while (1){
        fscanf(config,"%s",word);
        if (strcmp(word,"END") == 0){
            break;
        }
        else if (strcmp(word,"nLayers") == 0){
            return nLayers;
        }
    }
    // Returns default value if no other found.
    return 1000;
}


// Prints the title of ExOEx to the terminal.
void printTitle(){
  printf(ARED""
    "╔═════════════════════════════════════════════════════════"
           "══════╗\n"
    "║8888888888                 ,ad888ba,    8888888888       "
           "      ║\n"
    "║88                        d8\"'   `\"8b   88             "
           "        ║\n"
    "║88                       d8'       `8b  88               "
           "      ║\n"
    "║88aaaa      8b,     ,d8  88         88  88aaaa      8b,  "
           "   ,d8║\n"
    "║88\"\"\"\"       `Y8, ,8P'   88         88  88\"\"\"\"   "
           "    `Y8, ,8P' ║\n"
    "║88             )888(     Y8,       ,8P  88             )8"
           "88(   ║\n"
    "║88           ,d8\" \"8b,    Y8a.   .a8P   88           ,d"
           "8\" \"8b, ║\n"
    "║8888888888  8P'     `Y8    `\"Y888Y\"'    8888888888  8P'"
           "     `Y8║\n"
    "╚═════════════════════════════════════════════════════════"
           "══════╝\n"
	 ""ARESET);
  return;
}
