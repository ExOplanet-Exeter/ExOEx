/*
  Reads in data from a file named config.cfg and assigns
  variables to the read data
*/

//=================================================== DEFINES ==
#define MAX_WORD_LENGTH    32                                   // Read word length allowance
#define MAX_COMMENT_LENGTH 128                                  // Read comment length allowance
#define MAX_PARAMETERS     4                                    // Number of parameters in config

//================================================== INCLUDES ==
#include <stdio.h>
#include <string.h>                                             // Required for string comparision

#include "global.h"


//======================================= FUNCTION PROTOTYPES ==
void compCheck(Planet,int[]);
void userCheck(Planet);


//============================================= MAIN FUNCTION ==
Planet input(Planet exo){
  if (DEBUG)
    printf(ACYAN "\nStage: Input \n" ARESET);

  // Declerations
  FILE *config;                                                 // Pointer for file
  char word[MAX_WORD_LENGTH];                                   // String for holding read words
  int  altered[MAX_PARAMETERS] = {0};                           // Records if parameter changed from default val

  // Assignments
  config = fopen("config.cfg","r");                             // Open config.cfg for reading

  // Error checking
  if (config == NULL)                                           // Error if file cannot be opened
    printf(ARED "ERROR! Could not open config.txt\n" ARESET);

  // Read and assign loop
  while (1 == 1) {                                              // Runs loop until exit is found
    fscanf(config,"%s",word);                                   // Reads the next word in the file

    if      (strcmp(word,"END") == 0)                           // Compares the string to something
      break;                                                    // Exits read loop if "END" found

    else if (strncmp(&word[0],"!",1) == 0) {                    // Checks if first character is comment
      char comment[MAX_COMMENT_LENGTH];                         // Skips rest of line when comment found
      fgets(comment,MAX_COMMENT_LENGTH,config);
    }

    else if (strcmp(word,"NPHOT") == 0) {                       // Assigns value to a known variable
      fscanf(config,"%i",&exo.nPhot);
      altered[0] = 1;
    }
    else if (strcmp(word,"NLAYERS") == 0) {
      fscanf(config,"%i",&exo.nLayers);
      altered[1] = 1;
    }
    else if (strcmp(word,"RADIUS") == 0) {
      fscanf(config,"%lf",&exo.radius);
      altered[2] = 1;
    }
    else if (strcmp(word,"TAO") == 0) {
      fscanf(config,"%lf",&exo.tao);
      altered[3] = 1;
    }

    else {                                                      // Prints warning if unknown paramter is found
      printf(AYELLOW "WARNING: Unknown variable: %s\n" ARESET, word);
      char comment[MAX_COMMENT_LENGTH];
      fgets(comment,MAX_COMMENT_LENGTH,config);
    }
  }

  // Data checking
  compCheck(exo,altered);                                       // Function checks parameters changed from default
  userCheck(exo);                                               // Prints data out for user to check

  return exo;
}


//================================================= FUNCTIONS ==
// Prints warning if a variable was not changed from the default
void compCheck(Planet exo, int altered[MAX_PARAMETERS]) {
  if (altered[0] == 0)                                          // Looks to see if parameter was changed
    printf(AYELLOW "WARNING: nPhot undefined, using default value\n" ARESET);
  if (altered[1] == 0)
    printf(AYELLOW "WARNING: nLayers undefined, using default value\n" ARESET);
  if (altered[2] == 0)
    printf(AYELLOW "WARNING: radius undefined, using default value\n" ARESET);
  if (altered[3] == 0)
    printf(AYELLOW "WARNING: tao undefined, using default value\n" ARESET);

  return;
}


// Prints data to terminal allowing user to check data
void userCheck(Planet exo) {
  printf("Current data reads:\n"                                // Simple function to print out parameters
	 "nPhot      = %i\n"
	 "nLayers    = %i\n"
	 "Exo Radius = %lf\n"
	 "Exo Tao    = %lf\n"
	 ,exo.nPhot,exo.nLayers,exo.radius,exo.tao);

  return;
}
