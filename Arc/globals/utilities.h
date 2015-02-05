/*═════════════════════════════════════════════════════════════╗
├──────────────────────────────────────────────────────────────┤
            _   _| |_(_) (_) |_(_) ___  ___  | |__  
           | | | | __| | | | __| |/ _ \/ __| | '_ \ 
           | |_| | |_| | | | |_| |  __/\__ \_| | | |
            \__,_|\__|_|_|_|\__|_|\___||___(_)_| |_|
├──────────────────────────────────────────────────────────────┤
	Contains a variety of useful functions.
├──────────────────────────────────────────────────────────────┤
╚═════════════════════════════════════════════════════════════*/


//── FUNCTION PROTOTYPES ──────────────────────────────────────┤
int readInt(char*,char*);


//── COMPLETED FUNCTIONS ──────────────────────────────────────┤
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
		printf(ARED "ERROR! Unable to open %s\n" ARESET,
		fileName);
	
	// Reading loop
	while (1){
		fscanf(file,"%s",word);
		if (strcmp(word,"END") == 0){
			if (readInt == INT_NULL){
				printf(AYELLOW "Warning: %s not found.\n"
				ARESET, paramName);
			}
			break;
		}
		else if (strcmp(word,paramName) == 0){
			fscanf(file,"%i",&readInt);
			printf(AMAGENTA "%s = %i\n" ARESET,
			paramName,readInt);
		}
	}
	
	return readInt;
}