/*═════════════════════════════════════════════════════════════╗
├──────────────────────────────────────────────────────────────┤
              _   _| |_(_) (_) |_(_) ___  ___   ___ 
			 | | | | __| | | | __| |/ _ \/ __| / __|
			 | |_| | |_| | | | |_| |  __/\__ \| (__ 
			  \__,_|\__|_|_|_|\__|_|\___||___(_)___|
├──────────────────────────────────────────────────────────────┤
╚═════════════════════════════════════════════════════════════*/


//── INCLUDES ─────────────────────────────────────────────────┤
#include "../../globals/headers/global.h"


//── FUNCTIONS ────────────────────────────────────────────────┤
// Prints the title of ExOEx to the terminal.
void printTitle(){
	printf( ABLUE""
	"\n╦═════════════════════════════════════╦═════════════════"
	"═══════╦\n"
    "║oooooooooooo               .oooooo.  ║oooooooooooo       "
    "     ║ \n"
	"║`888'     `8              d8P'  `Y8b ║`888'     `8       "
	"     ║ \n"
	"║ 888         oooo    ooo 888      888║ 888         oooo  "
	"  ooo║ \n"
	"║ 888oooo8     `88b..8P'  888      888║ 888oooo8     `88b."
	".8P' ║ \n"
	"║ 888    \"       Y888'    888      888║ 888    \"       Y"
	"888'   ║\n"
	"║ 888       o  .o8\"'88b   `88b    d88'║ 888       o  .o8"
	"\"'88b  ║\n"
	"║o888ooooood8 o88'   888o  `Y8bood8P' ║o888ooooood8 o88'  "
	" 888o║\n"
	"╩═════════════════════════════════════╩═══════════════════"
	"═════╩\n\n"
	"" ARESET);
	return;
}

// Reads an integer value out of a file.
// Requires file name and parameter name.
int readInt(char *fileName, char *paramName){
	
	// Declerations
	FILE *file;
	char *path = "dependencies/";
	char *filePath = malloc(strlen(path) + strlen(fileName));
	char word[MAX_WORD_LENGTH];
	char comment[MAX_COMMENT_LENGTH];
	int  readInt = INT_NULL;
	
	// Concate for full file position.
	strcpy(filePath, path);
	strcat(filePath, fileName);
	
	// Open file and check it has been opened successfully.
	file = fopen(filePath,"r");
	if (file == NULL)
		printf("ERROR! Unable to open %s!\n",
		fileName);
	
	// Reading loop
	while (1){
		fscanf(file,"%s",word);
		if (strcmp(word,"END") == 0){
			if (readInt == INT_NULL){
				printf("Warning: %s not found.\n",
				paramName);
			}
			break;
		}
		else if (strcmp(word,paramName) == 0){
			if (strcmp(paramName,"Scatter") == 0){
				fscanf(file,"%s",word);
				if (strcmp(word,"ISO") == 0)
					return ISO;
				if (strcmp(word,"RAY") == 0)
					return RAY;
				if (strcmp(word,"MIE") == 0)
					return MIE;
			}
			fscanf(file,"%i",&readInt);
		}
	}
	
	return readInt;
}

// Reads an double value out of a file.
// Requires file and parameter name.
double readDouble(char *fileName, char *paramName){

	// Declerations
	FILE *file;
	char *path = "dependencies/";
	char *filePath = malloc(strlen(path) + strlen(fileName));
	char word[MAX_WORD_LENGTH];
	char comment[MAX_COMMENT_LENGTH];
	double  readDouble = DOUBLE_NULL;
	
	// Concate for full file position.
	strcpy(filePath, path);
	strcat(filePath, fileName);
	
	// Open file and check it has been opened successfully.
	file = fopen(filePath,"r");
	if (file == NULL)
		printf("ERROR! Unable to open %s!\n",
		fileName);
	
	// Reading loop
	while (1){
		fscanf(file,"%s",word);
		if (strcmp(word,"END") == 0){
			if (readDouble == DOUBLE_NULL){
				printf("Warning: %s not found.\n",
				paramName);
			}
			break;
		}
		else if (strcmp(word,paramName) == 0){
			fscanf(file,"%lf",&readDouble);
		}
	}
	
	return readDouble;
}

// Generates a random double between the given min and max
// values.
double arcRand(double min, double max){
	
	double range = max - min;
	double div = RAND_MAX / range;
	
	return min + (rand() / div);
}