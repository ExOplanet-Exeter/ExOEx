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
#include "../../globals/utilities.h"


//── FUNCTIONS IN PROGRESS ────────────────────────────────────┤
// Open named material file and copy material properties into
// planet structure.
void getLayerProperties(int i, char *name, Planet* exo){
    
    FILE *mat;

    char *path        = "materials/";
    char *extension   = ".mat";
    char *filePath    = malloc(strlen(path) + strlen(name) + strlen(extension));
    
    strcpy(filePath, path);
    strcat(filePath, name);
    strcat(filePath, extension);
    
    exo->lType[i]  = readInt(filePath,"Scatter");
    
    return;
}

// Gets the name of the nth material in the struct.cfg file.
const char * getMaterialName(int i, Planet* exo){
    
    FILE *structure;
    int lineNumber = 0;
    char word[MAX_WORD_LENGTH];
    char comment[MAX_COMMENT_LENGTH];

    char *readMaterialName = (char *) malloc(sizeof(char) * MAX_NAME_LENGTH);
    
    structure = fopen("dependencies/structure.cfg","r");
    if (structure == NULL)
        printf("ERROR! Unable to open structure.cfg!\n");
    
    while (1){
        fscanf(structure,"%s",word);
        if (strcmp(word,"END") == 0)
            break;
        else if (strncmp(&word[0],"!",1) == 0)
            fgets(comment,MAX_COMMENT_LENGTH,structure);
        else if (lineNumber == i){
            strcpy(readMaterialName,word);
            fscanf(structure,"%lf",&exo->lRadius[i]);
            break;
        }
        else{
            lineNumber++;
            fgets(comment,MAX_COMMENT_LENGTH,structure);
        }
    }
    return readMaterialName;
}

// This function reads parameters from config files and assigns
// the read values into the planet structure.
void exoSetup(Planet *exo){
    char nameList[exo->nLayers][MAX_NAME_LENGTH];
    exo->nPhot = readInt("config.cfg","nPhot");
    for (int i=0; i<exo->nLayers; i++){
        strcpy(nameList[i],getMaterialName(i,exo));
        getLayerProperties(i,nameList[i],exo);
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
