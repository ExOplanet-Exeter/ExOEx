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
#include "../../globals/headers/global.h"
#include "../../globals/headers/utilities.h"


//── FUNCTION PROTOTYPES ──────────────────────────────────────┤
void exoSetup(Planet*);
const char * getMaterialName(int,Planet*);
void getLayerProperties(int,char*,Planet*);
void printLayerProperties(int,char*,Planet*);


//── FUNCTIONS IN PROGRESS ────────────────────────────────────┤


//── INPUT ────────────────────────────────────────────────────┤
void input(Planet *exo,Particle *photon){
	
	// Entry
	if (DEBUG)
		printf(ACYAN "Input Running:\n" ARESET);

	// Reading functions
	exoSetup(exo);
	photon->wavelength 	= readDouble("config.cfg","wavelength");

	// Exit
	if (DEBUG)
		printf(AGREEN "Input Complete.\n\n" ARESET);
				
	return;
}


//── COMPLETED FUNCTIONS ──────────────────────────────────────┤
// This function reads parameters from config files and assigns
// the read values into the planet structure.
void exoSetup(Planet *exo){
	
	char nameList[exo->nLayers][MAX_NAME_LENGTH];
	exo->nPhot = readInt("config.cfg","nPhot");
	if (DEBUG)
		printf(AMAGENTA "Number of Photons = %i\n\n" ARESET, exo->nPhot);
	for (int i=0; i<exo->nLayers; i++){
		strcpy(nameList[i],getMaterialName(i,exo));
		getLayerProperties(i,nameList[i],exo);
		printLayerProperties(i,nameList[i],exo);
	}
	
	return;
}

// Gets the name of the nth material in the struct.cfg file.
const char * getMaterialName(int i, Planet *exo){
	
	FILE *structure;
	int lineNumber = 0;
	char word[MAX_WORD_LENGTH];
	char comment[MAX_COMMENT_LENGTH];

	char *readMaterialName = (char *) malloc(sizeof(char) * MAX_NAME_LENGTH);
	
	structure = fopen("dependencies/structure.cfg","r");
	if (structure == NULL)
		printf(ARED "ERROR! Unable to open structure.cfg!\n" ARESET);
	
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

// Open named material file and copy material properties into
// planet structure.
void getLayerProperties(int i, char *name, Planet *exo){
	
	FILE *mat;

	char *path        = "materials/";
	char *extension   = ".mat";
	char *filePath    = malloc(strlen(path) + strlen(name) + strlen(extension));
	
	strcpy(filePath, path);
	strcat(filePath, name);
	strcat(filePath, extension);
	
	exo->lType[i]  = readInt(filePath,"Scatter");
	exo->lKappa[i] = readDouble(filePath,"Kappa");
	exo->lAlbedo[i]= readDouble(filePath,"Albedo");
	
	return;
}

// Prints the properties of the layer to the terminal.
void printLayerProperties(int i, char *name, Planet *exo){
	
	printf(AMAGENTA "Layer %i: %s\n"
		"	t = %i\n"
		"	k = %lf\n"
		"	r = %lf\n" ARESET,
		i,name,exo->lType[i],exo->lKappa[i],exo->lRadius[i]);
	
	return;
}