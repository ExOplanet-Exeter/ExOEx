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