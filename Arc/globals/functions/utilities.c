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

// Determines the dot product of two vectors.
double arcDot(double Ax,double Ay,double Az,double Bx,double By,double Bz){
	
	return (Ax*Bx)+(Ay*By)+(Az*Bz);
}

// Converts double from radians to more lovely degrees.
int degreeConvert(double rad){

	int deg = ((180.0 * rad)/PI);

	return deg;
}

// Estimates how long it will be until photon loop is done.
void estimatedTimeUntilCompletion(int t1,int nThreads){
	int t2 = (clock() - t1)/nThreads;
	double sec = ((t2*1.0)/1000000.0);
	double etc = (sec*99.0);

	if (0 < etc && etc < 120)
		printf("An estimated %lf sec until completion.\n",etc);
	else if (120 <= etc && etc < 7200)
		printf("An estimated %lf min until completion.\n",etc/60);
	else if (7200 <= etc && etc < 86400)
		printf("An estimated %lf hrs until completion.\n",etc/(60*60));
	else
		printf("This may take over a day to complete.\n");
		
	return;
}

// Prints out the time taken to run photonLoop
void computationTime(int t1,int nThreads){
	
	double timeTaken = ((clock() - t1)*1.0)/(1000000*(nThreads*1.0));
	
	if (0 < timeTaken && timeTaken < 120)
		printf("%lf sec taken.\n",timeTaken);
	else if (120 <= timeTaken && timeTaken < 7200)
		printf("%lf min taken.\n",timeTaken/60);
	else if (7200 <= timeTaken && timeTaken < 86400)
		printf("%lf hrs taken.\n",timeTaken/(60*60));
	else
		printf("Taken over a day! Patient one, you are!\n");
	
	return;
}