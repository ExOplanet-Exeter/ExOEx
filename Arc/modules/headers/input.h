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
#define MAX_NUMBER_OF_MATERIALS 10
#define MAX_WORD_LENGTH 64


//== FUNCTION PROTOTYPES =======================================
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


void printMatList(int nMat, Material atmosphere[]){
    for (int i=0; i<nMat; i++){
        printf(ACYAN "%i) %s\n" ARESET, i, atmosphere[i].name);
    }
    return;
}