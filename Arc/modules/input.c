/*═════════════════════════════════════════════════════════════╗
├──────────────────────────────────────────────────────────────┤
                 (_)_ __  _ __  _   _| |_   ___ 
                 | | '_ \| '_ \| | | | __| / __|
                 | | | | | |_) | |_| | |_ | (__ 
                 |_|_| |_| .__/ \__,_|\__(_)___|
                         |_|       
├──────────────────────────────────────────────────────────────┤
	This function reads data from .cfg and .mat config files
	before organising them into a Planet stucture.
├──────────────────────────────────────────────────────────────┤
╚═════════════════════════════════════════════════════════════*/

//── INCLUDES ─────────────────────────────────────────────────┤
#include "../globals/global.h"
#include "../globals/utilities.h"


//── FUNCTION PROTOTYPES ──────────────────────────────────────┤
const char * getMatName(int,Planet*);
void getLayerProperties(int,char*,Planet*);


//── INPUT ────────────────────────────────────────────────────┤
void input(Planet *exo,Particle *photon){
	
	// -- Entry
	if (DEBUG)
		printStart("Input");
	
	// -- Planet setup
	char nameList[exo->nLayers][MAX_NAME_LENGTH];
	
	exo->nPhot = readInt("config.cfg","nPhot");
	
	for (int i=0; i<exo->nLayers; i++){
		strcpy(nameList[i],getMatName(i,exo));
		getLayerProperties(i,nameList[i],exo);
	}
	
	// -- Print structure
	printf(AMAGENTA "\nnPhot  : %i\nnLayers: %i\n\n" ARESET,exo->nPhot,exo->nLayers);
	
	for (int i=0; i<exo->nLayers; i++){
		printf(AMAGENTA "Layer %i)\n"
						"	mat   : %s\n"
						"	radius: %lf\n"
						"	type  : %s\n"
						"	kappa : %lf\n"
						"	albedo: %lf\n\n"
						 ARESET,
						i,nameList[i],exo->radius[i],enumText("scatType",exo->scatType[i]),exo->kappa[i],exo->albedo[i]);
						
	}
	
	// -- Exit
	if (DEBUG)
		printEnd("Input");
	
	return;
}


//─── COMPLETED FUNCTIONS ─────────────────────────────────────┤
// Gets the name of the nth material from struct.cfg.
// Also gets the radius of the layer.
const char * getMatName(int i,Planet *exo){
	
	FILE *structure;
	int lineNumber = 0;
	char word[MAX_NAME_LENGTH];
	char comment[MAX_COMMENT_LENGTH];
	char *matName = (char *) malloc(sizeof(char) * MAX_NAME_LENGTH);
	
	structure = fopen(configPath "struct.cfg","r");
	
	while (1){
		fscanf(structure,"%s",word);
		if (strcmp(word,"END") == 0){
			printErr("Problem reading struct.cfg");
			break;
		}
		else if (lineNumber == i){
			strcpy(matName,word);
			fscanf(structure,"%lf",&exo->radius[i]);
			return matName;
		}
		else {
			fgets(comment,MAX_COMMENT_LENGTH,structure);
			lineNumber++;
		}
	}

	return matName;
}

// Reads the properties of a material from its .mat file
// and stores the data in the Planet structure.
void getLayerProperties(int i,char *name,Planet *exo){
	
	char *fileName = malloc(strlen("Materials/") + strlen(name) + strlen(".mat"));
	
	strcpy(fileName, "Materials/");
	strcat(fileName, name);
	strcat(fileName, ".mat");
	
	exo->scatType[i] = readInt(fileName,"scatterType");;//readInt(fileName,"scatterType");
	exo->kappa[i] = readDouble(fileName,"kappa");
	exo->albedo[i] = readDouble(fileName,"albedo");
	
	/*exo->scatType = readInt();
	
	int		*scatType;
	double 	*kappa;
	double 	*albedo;
	double	*radius;
	*/
	
	return;
}
