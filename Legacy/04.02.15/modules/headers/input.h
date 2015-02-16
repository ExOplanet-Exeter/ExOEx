/*==============================================================
----------------------------------------------------------------
88
""                                           ,d
                                             88
88  8b,dPPYba,   8b,dPPYba,   88       88  MM88MMM
88  88P'   `"8a  88P'    "8a  88       88    88
88  88       88  88       d8  88       88    88
88  88       88  88b,   ,a8"  "8a,   ,a88    88,
88  88       88  88`YbbdP"'    `"YbbdP'Y8    "Y888
                 88                                  88
                 88                                  88
                                                     88
                                                     88,dPPYba,
                                                     88P'    "8a
                                                     88       88
                                                888  88       88
                                                888  88       88
----------------------------------------------------------------
 This header file contains the function prototypes used within
                            'input.c'.
----------------------------------------------------------------
==============================================================*/


//== DEFINES ===================================================


//== FUNCTION PROTOTYPES =======================================
Planet readStructure(Planet,Material[],int);
void printAllPlanetData(Planet);
void printExoParameters(Planet);
Planet readConfig(Planet,Material[]);
void readIndividualMats(int,Material[]);
int readMatList(int,Material[]);
Planet fixLayerRadii(Planet);


//== COMPLETED FUNCTIONS =======================================
// Checks the upper limit of exo radius and scales all the
// radii values so that upper limit of planet radius is 1.0.
Planet fixLayerRadii(Planet exo){
    double radius, scaleFactor;
    radius = exo.layerRadius[exo.nLayers-1];
    scaleFactor = 1.0 / radius;
    for (int i=0; i<exo.nLayers; i++){
        exo.layerRadius[i] = exo.layerRadius[i] * scaleFactor;
    }
    return exo;
}


// Sets up the layers of the exo Planet structure.
Planet readStructure(Planet exo, Material atmosphere[], int nMat){
    FILE *structure;
    char word[MAX_WORD_LENGTH];
    char comment[MAX_COMMENT_LENGTH];
    int  workingLayer = 0;
    
    structure = fopen("dependencies/structure.cfg","r");
    if (structure == NULL){
        printf(ARED "ERROR! Could not open structure.cfg!\n" ARESET);
    }
    
    if (DEBUG){
        printf(ACYAN "Reading: structure.cfg\n" ARESET);
    }
    
    while (1){
        fscanf(structure,"%s",word);
        if (strcmp(word,"END") == 0){
            break;
        }
        else if (strncmp(&word[0],"!",1) == 0){
            fgets(comment,MAX_COMMENT_LENGTH,structure);
        }
        
        for (int i=0; i<nMat; i++){
            if(strcmp(word,atmosphere[i].name) == 0){
                exo.layerKappa[workingLayer]  = atmosphere[i].kappa;
                exo.layerAlbedo[workingLayer] = atmosphere[i].albedo;
                exo.layerType[workingLayer] = atmosphere[i].type;
                fscanf(structure,"%lf",&exo.layerRadius[workingLayer]);
                workingLayer++;
            }
        }
    }
    
    return exo;
}


// Prints out the complete data about the exoplanet that has
// been constructed from the .cfg and .mat files.
void printAllPlanetData(Planet exo){
    printf(AMAGENTA "nPhot   = %i\n"
           "nLayers = %i\n"ARESET, exo.nPhot, exo.nLayers);
    for (int i=0; i<exo.nLayers; i++){
        printf(AMAGENTA "Layer %i)\n"
               "    type   = %i\n"
               "    radius = %lf\n"
               "    kappa  = %lf\n"
               "    albedo = %lf\n"ARESET,
               i, exo.layerType[i],exo.layerRadius[i],
               exo.layerKappa[i],exo.layerAlbedo[i]);
    }
    return;
}


// Prints the parameters of exo Planet structure to terminal.
void printExoParameters(Planet exo){
    printf("exo.nPhot   = %i\n"
           "exo.nLayers = %i\n",
           exo.nPhot, exo.nLayers);
    return;
}


Planet readConfig(Planet exo, Material atmosphere[]){
    FILE *config;
    char word[MAX_WORD_LENGTH];
    char comment[MAX_COMMENT_LENGTH];
    
    config = fopen("dependencies/config.cfg","r");
    if (config == NULL){
        printf(ARED "ERROR! Could not open config.cfg!\n" ARESET);
    }
    
    if (DEBUG){
        printf(ACYAN "Reading: config.cfg\n" ARESET);
    }
    
    while (1){
        fscanf(config,"%s",word);
        if (strcmp(word,"END") == 0){
            break;
        }
        else if (strncmp(&word[0],"!",1) == 0){
            fgets(comment,MAX_COMMENT_LENGTH,config);
        }
        else if (strcmp(word,"nPhot") == 0){
            fscanf(config,"%i",&exo.nPhot);
        }
        else if (strcmp(word,"nLayers") == 0){
            fscanf(config,"%i",&exo.nLayers);
        }
        else{
            printf(AYELLOW "WARNING: Unknown parameter: %s\n"
                   ARESET, word);
            fgets(comment,MAX_COMMENT_LENGTH,config);
        }
    }
    return exo;
}


// Reads the parameter values out of a .mat file located in the
// /dependencies/ folder.
void readIndividualMats(int nMat, Material atmosphere[]){
    FILE *mat;
    char fileName[MAX_NAME_LENGTH];
    char word[MAX_WORD_LENGTH];
    char comment[MAX_COMMENT_LENGTH];
    
    for (int i=0; i<nMat; i++){
        // strcpy copies string 2 into string 1
        strcpy(fileName,"dependencies/");
        // srtcat appends string 2 onto the end of string 1
        strcat(fileName, atmosphere[i].name);
        mat = fopen(fileName,"r");
        if (mat == NULL){
            printf(ARED "ERROR! Could not open %s!\n"
                   ARESET,atmosphere[i].name);
        }
        
        if (DEBUG){
            printf(ACYAN "Reading: %s\n" ARESET,
                   atmosphere[i].name);
	}        

        while (1){
            fscanf(mat,"%s",word);
            if (strcmp(word,"END") == 0){
                break;
            }
            else if (strncmp(&word[0],"!",1) == 0){
                fgets(comment,MAX_COMMENT_LENGTH,mat);
            }
            else if (strcmp(word,"kappa") == 0){
                fscanf(mat,"%lf",&atmosphere[i].kappa);
            }
            else if (strcmp(word,"albedo") == 0){
                fscanf(mat,"%lf",&atmosphere[i].albedo);
            }
	    else if (strcmp(word,"type") == 0){
	      fscanf(mat,"%i",&atmosphere[i].type);
            }
            else{
                printf(AYELLOW "WARNING: Unknown parameter: %s\n"
                       ARESET, word);
                fgets(comment,MAX_COMMENT_LENGTH,mat);
            }
        }
    }  
    return;
}


// Opens dependencies/materials.mat to read out the materials
// avalible and then assigns properties to relevant material
// structure.
int readMatList(int nMat, Material atmosphere[]){
    // Creates file pointers.
    FILE *list;
    FILE *mat;
    // Parameter declerations.
    char name[MAX_WORD_LENGTH];
    
    list = fopen("dependencies/materials.cfg","r");
    if (list == NULL){
        printf(ARED "ERROR! Could not open materials.cfg!\n"
               ARESET);
        exit(1);
    }
    // Read out the names of the .mat files from master .mat file.
    // These names are then saved in a material array ready for
    // reading of the individual .mat files.
    while(1){
        fscanf(list,"%s",name);
        if (strcmp(name,"END") == 0){
            break;
        }
        else {
            strcpy(atmosphere[nMat].name, name);
            nMat++;
        }
    }
    return nMat;
}
