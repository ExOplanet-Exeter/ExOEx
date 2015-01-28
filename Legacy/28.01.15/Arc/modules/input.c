/*==============================================================                
----------------------------------------------------------------
        ██╗███╗   ██╗██████╗ ██╗   ██╗████████╗ ██████╗
        ██║████╗  ██║██╔══██╗██║   ██║╚══██╔══╝██╔════╝
        ██║██╔██╗ ██║██████╔╝██║   ██║   ██║   ██║     
        ██║██║╚██╗██║██╔═══╝ ██║   ██║   ██║   ██║     
        ██║██║ ╚████║██║     ╚██████╔╝   ██║██╗╚██████╗
        ╚═╝╚═╝  ╚═══╝╚═╝      ╚═════╝    ╚═╝╚═╝ ╚═════╝
----------------------------------------------------------------
 The input function reads in data either from a config file or 
        allows the user to enter parameters manually.
----------------------------------------------------------------                
==============================================================*/


//== INCLUDES ==================================================
//-- SYSTEM HEADERS --------------------------------------------
// Required for string comparison.
#include <string.h>


//-- LOCAL HEADERS ---------------------------------------------
// The directory path of '..' means move up one directory.
#include "../globals/global.h"


//== DEFINES ===================================================
#define MAX_WORD_LENGTH    32
#define MAX_COMMENT_LENGTH 128
#define MAX_PARAMETERS     3
#define MAX_LOOP_COUNT     50

//== FUNCTION IN PROGRESS ======================================
// When functions are working as intended move to header please. 

// Print values that exo entered with.
void printDefaultPlanetValues(Planet exo){
  printf(ACYAN "Values before reading config:\n"
	 "nPhot   = %i\n"
	 "nLayers = %i\n"
	 ARESET, exo.nPhot, exo.nLayers);
  for (int i=0; i<exo.nLayers; i++){
    printf(ACYAN "L%i Kappa = %lf\n" 
	   ARESET, i, exo.layerKappa[i]);
  }
  return;
}

// Print the exo values that should now have been changed
void printChangedPlanetValues(Planet exo){
  printf(AGREEN "Values before reading config:\n"
         "nPhot   = %i\n"
         "nLayers = %i\n" ARESET, exo.nPhot, exo.nLayers);
  for (int i=0; i<exo.nLayers; i++){
    printf(AGREEN "L%i Kappa = %lf\n"
           ARESET, i, exo.layerKappa[i]);
  }
  return;
}

// Prints a warning if any parameter value has not been changed.
void changeCheck(Planet exo, int altered[MAX_PARAMETERS]){
  // If statement checks if value was changed in read loop.
  if (altered[0] == 0)
    printf(AYELLOW "WARNING: nPhot undefined. Using default.\n"
	   ARESET);
  if (altered[1] == 0)
    printf(AYELLOW "WARNING: nLayers undefined. Using default."
	   "\n" ARESET);

  return;
}


//== INPUT FUNCTION ============================================
Planet input(Planet exo){

//-- ENTRY -----------------------------------------------------
  // Debug printing.
  if (DEBUG){
    printf(ACYAN "Input Running:\n" ARESET);
    printDefaultPlanetValues(exo);
  }

//-- DECLERATIONS ----------------------------------------------
  // Creates pointers for files.
  // 'config' used for setting up the exo.
  FILE *config;
  // 'structure' used for determining exo material structure.
  FILE *structure;
  // 'mat' used for reading a material file.
  FILE *mat;
  // String (similar to character array) for holding read words.
  char word[MAX_WORD_LENGTH];
  // Used for rading in integers
  int layerNumber;
  // Records if parameters were changed from default values.
  int altered[MAX_PARAMETERS] = {0};
  // Records number of time read loop has looped.
  int loopCount = 0;

//-- ASSIGNMENTS -----------------------------------------------
  // Open config files for reading. Path relative to makefile!
  config = fopen("dependencies/config.cfg","r");
  structure = fopen("dependencies/structure.cfg","r");

//-- ERROR CHECKING --------------------------------------------
  // Prints error message if config file can't be opened.
  if (config == NULL || structure == NULL){
    printf(ARED "ERROR! Config file could not open!\n" ARESET);
    printf(ARESET "Resetting console colour.\n");
  }

//-- MAIN READING AND ASSIGNMENT LOOP --------------------------
  // Runs loop until exit is found.
  while (1){
    // Breaks if file has been looped to many times.
    if (loopCount > MAX_LOOP_COUNT){
      printf(ARED "ERROR! File has looped over %i times!\n"
                     "Check if END missing from .cfg file!\n" 
	     ARESET, MAX_LOOP_COUNT);
      break;
    }
    loopCount ++;

    // Scans open file for next word.
    fscanf(config,"%s",word);

    // The function strcmp compares one string to another.
    // This 'if' statement will break out loop when 'END' found.
    if (strcmp(word,"END") == 0)
      break;

    // Assigns a value to exo if parameter is recognised.
    else if (strcmp(word,"NPHOT") == 0){
      fscanf(config,"%i",&exo.nPhot);
      altered[0] = 1;
    }
    else if (strcmp(word,"NLAYERS") == 0){
      fscanf(config,"%i",&exo.nLayers);
      if (exo.nLayers > MAX_NLAYERS){
	printf(ARED "ERROR! nLayers  = %i\n"
	       "Allowed maximum = %i\n"
	       "Only first %i values used.\n"
	       ARESET, exo.nLayers, MAX_NLAYERS, MAX_NLAYERS);
      }
      altered[1] = 1;
    }

    // Checks for comment flag '!' and ignores the rest of the
    // line if it is found.
    // 'strncmp' compares one element of string to char.
    else if (strncmp(&word[0],"!",1) == 0){
      char comment[MAX_COMMENT_LENGTH];
      fgets(comment,MAX_COMMENT_LENGTH,config);
    }

    // Prints a warning if a unknown parameter is found.
    else{
      printf(AYELLOW "WARNING: Unknown variable: %s\n"
	     ARESET, word);
      char comment[MAX_COMMENT_LENGTH];
      fgets(comment,MAX_COMMENT_LENGTH,config);
    }
  }

//-- MATERIAL READING LOOP -------------------------------------
  while (1){
    
    // THIS CODE IS USED TWICE AND NEED TO BE MOVED INTO A FUNC!
    // Breaks if file has been looped to many times.
    if (loopCount > MAX_LOOP_COUNT){
      printf(ARED "ERROR! File has looped over %i times!\n"
                     "Check if  missing from .cfg file!\n" 
	     ARESET, MAX_LOOP_COUNT);
      break;
    }
    loopCount ++;

    fscanf(structure,"%i",&layerNumber);

    // Breaks if '1234' is found. THIS IS VERY MESSY!
    if (layerNumber == 1234)
      break;

    for (int i=0; i<exo.nLayers; i++){
      if (layerNumber == i){
	fscanf(structure,"%s",word);
        printf("Layer %i is %s\n",i,word);
	// THIS IS A HUGE FUDGE AND NEEDS TO BE FIXED!!!!!!!!!!!!!!!!!!
	exo.layerKappa[i]=1.2;
      }
    }
    
  }

//-- DATA CHECKING ---------------------------------------------
  changeCheck(exo,altered);
 
//-- EXIT ------------------------------------------------------
  if (DEBUG){
    printf(AGREEN "Input Complete.\n" ARESET);
    printChangedPlanetValues(exo);
  }

  return exo;
}
