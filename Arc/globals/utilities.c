/*═════════════════════════════════════════════════════════════╗
├──────────────────────────────────────────────────────────────┤
			| |_ ___ _ __ ___  _ __ | | __ _| |_ ___   ___ 
			| __/ _ \ '_ ` _ \| '_ \| |/ _` | __/ _ \ / __|
			| ||  __/ | | | | | |_) | | (_| | ||  __/| (__ 
			 \__\___|_| |_| |_| .__/|_|\__,_|\__\___(_)___|
									|_|           
├──────────────────────────────────────────────────────────────┤
	Short description of script in here.
├──────────────────────────────────────────────────────────────┤
╚═════════════════════════════════════════════════════════════*/


//── INCLUDES ─────────────────────────────────────────────────┤
#include "global.h"


//─── COMPLETED FUNCTIONS ─────────────────────────────────────┤
// Prints the title of ExOEx to the terminal.
void printTitle(){
	
	printf(ARED
	"\n╦═════════════════════════════════════╦═════════════════"
		"═══════╦\n" AYELLOW
	    "║oooooooooooo               .oooooo.  ║oooooooooooo       "
	    "     ║ \n" AGREEN
		"║`888'     `8              d8P'  `Y8b ║`888'     `8       "
		"     ║ \n" ACYAN
		"║ 888         oooo    ooo 888      888║ 888         oooo  "
		"  ooo║ \n" ABLUE
		"║ 888oooo8     `88b..8P'  888      888║ 888oooo8     `88b."
		".8P' ║ \n" AMAGENTA
		"║ 888    \"       Y888'    888      888║ 888    \"       Y"
		"888'   ║\n" ARED
		"║ 888       o  .o8\"'88b   `88b    d88'║ 888       o  .o8"
		"\"'88b  ║\n" AYELLOW
		"║o888ooooood8 o88'   888o  `Y8bood8P' ║o888ooooood8 o88'  "
		" 888o║\n" AGREEN
		"╩═════════════════════════════════════╩═══════════════════"
		"═════╩\n\n"
	ARESET);
	
	return;
}

// Informs user code section has started.
void printStart(char *word){
	
	printf(ACYAN);
	printf(word);
	printf(" running:\n" ARESET);
	
	return;
}

// Informs user code section has finished.
void printEnd(char *word){
	
	printf(AGREEN);
	printf(word);
	printf(" complete.\n" ARESET);
	
	return;
}

// Informs user of an error.
void printErr(char *errorMessage){
	
	printf(ARED);
	printf("ERROR! ");
	printf(errorMessage);
	printf("!\n" ARESET);
	
	return;
}

// Informs user of a warning.
void printWarn(char *warningMessage){
	
	printf(AYELLOW);
	printf("WARNING: ");
	printf(warningMessage);
	printf(".\n" ARESET);
	
	return;
}

// Informs user of a test being passed.
void printOutcome(char *testName,bool pass){
	
	printf(testName);
	
	if (pass == true){
		printf(AGREEN " Passed.\n" ARESET);
	}
	else if (pass == false){
		printf(ARED " Failed.\n" ARESET);
	}
	
	return;
}

// Reads an given integer from a given filename.
int readInt(char *fileName,char *paramName){
	
	// Declerations
	bool found = false;
	int value = 0;
	FILE *file;
	char *path = malloc(strlen(configPath) + strlen(fileName));
	char word[MAX_WORD_LENGTH];
	
	// Create full file path string.
	strcpy(path,configPath);
	strcat(path,fileName);
	
	// Open file for reading and check it opened successfully.
	file = fopen(path,"r");
	if (file == NULL){
		printErr("Could not open file!");
	}
	
	// Reading loop.
	while (1){
		fscanf(file,"%s",word);
		if (strcmp(word,"END") == 0){
			if (found == false){
				printWarn("Parameter was not found");
			}
			break;
		}
		else if (strcmp(word,paramName) == 0){
			found = true;
			if (strcmp(paramName,"scatterType") == 0){
				fscanf(file,"%s",word);
				if (strcmp(word,"ISO") == 0)
					return ISO;
				if (strcmp(word,"RAY") == 0)
					return RAY;
				if (strcmp(word,"MIE") == 0)
					return MIE;
			}
			else {
				fscanf(file,"%i",&value);
			}
		}
	}
	
	return value;
}

// Reads an given double from a given filename.
int readDouble(char *fileName,char *paramName){
	
	// Declerations
	bool found = false;
	double value = 0.0;
	FILE *file;
	char *path = malloc(strlen(configPath) + strlen(fileName));
	char word[MAX_WORD_LENGTH];
	
	// Create full file path string.
	strcpy(path,configPath);
	strcat(path,fileName);
	
	// Open file for reading and check it opened successfully.
	file = fopen(path,"r");
	if (file == NULL){
		printErr("Could not open file!");
	}
	
	// Reading loop.
	while (1){
		fscanf(file,"%s",word);
		if (strcmp(word,"END") == 0){
			if (found == false){
				printWarn("Parameter was not found");
			}
			break;
		}
		else if (strcmp(word,paramName) == 0){
			found = true;
			fscanf(file,"%lf",&value);
		}
	}
	
	return value;
}

char *enumText(char *type,int i){
	
	if (type == "scatType"){
		if (i == 0){
			return "ISO";
		}
		else if (i == 1){
			return "RAY";
		}
		else if (i == 2){
			return "MIE";
		}
	}
	else {
		return "Unknown enum list.";
	}
}

// Returns a random value between a given Min and Max value.
double arcRand(double min, double max){
	
	double smallRange, bigRange, randy;
	
	smallRange 	= abs(max - min);
	bigRange 	= RAND_MAX / smallRange;
		
	randy = min + (rand() / bigRange);
		
	return randy;
}

// Converts a value in radians to degrees.
double degreeConvert(double rad){
	
	return rad*(180.0/PI);
}