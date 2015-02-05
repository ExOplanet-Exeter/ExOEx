/*═════════════════════════════════════════════════════════════╗
├──────────────────────────────────────────────────────────────┤
                 (_)_ __  _ __  _   _| |_   ___
                 | | '_ \| '_ \| | | | __| / __|
                 | | | | | |_) | |_| | |_ | (__ 
                 |_|_| |_| .__/ \__,_|\__(_)___|
                         |_|
├──────────────────────────────────────────────────────────────┤
	This is the function reads data on from .cfg and .mat
	config files.
├──────────────────────────────────────────────────────────────┤
╚═════════════════════════════════════════════════════════════*/


//── INCLUDES ─────────────────────────────────────────────────┤
#include "../../globals/global.h"
//#include "../../globals/utilities.h"


//── FUNCTIONS IN PROGRESS ────────────────────────────────────┤
// Gets the name of the nth material in the struct.cfg file.
const char * getMaterialName(){

    char *readMaterialName = (char *) malloc(sizeof(char) * MAX_NAME_LENGTH);
    
    return readMaterialName;
}

// This function reads parameters from config files and assigns
// the read values into the planet structure.
void exoSetup(Planet *exo){
    char nameList[exo->nLayers][MAX_NAME_LENGTH];
    exo->nPhot = readInt("config.cfg","nPhot");
    for (int i=0; i<exo->nLayers; i++){
        strcpy(nameList[i],getMaterialName(i));
        printf("l%i %s\n",i,nameList[i]);
    }
    return;
}


//── INPUT ────────────────────────────────────────────────────┤
void input(Planet *exo){
    
    // Entry
    if (DEBUG)
        printf("Input Running:\n");

    // Reading functions
    exoSetup(exo);

    // Exit
    if (DEBUG)
        printf("Input Complete.\n\n");
                
	return;
}