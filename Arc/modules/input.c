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
                  88                                   ,adPPYba,
                  88                                  a8"     ""
                                                      8b
                                                 888  "8a,   ,aa
                                                 888   `"Ybbd8"'
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
#include "headers/input.h"


//== FUNCTIONS IN PROGRESS =====================================
// Sets up the layers of the exo Planet structure.
Planet readStructure(Planet exo, Material atmosphere[], int nMat){
  FILE *structure;
  char word[MAX_WORD_LENGTH];
  char comment[MAX_COMMENT_LENGTH];
  int  workingLayer = 0;

  structure = fopen("dependencies/structure.cfg","r");
  if (structure == NULL){
    printf(ARED "ERROR! Could not open structure.cfg!\n" ARESET);
  }

  if (DEBUG){
    printf(ACYAN "Reading: structure.cfg\n" ARESET);
  }

  while (1){
    fscanf(structure,"%s",word);
    if (strcmp(word,"END") == 0){
      break;
    }
    else if (strncmp(&word[0],"!",1) == 0){
      fgets(comment,MAX_COMMENT_LENGTH,structure);
    }

    for (int i=0; i<nMat; i++){
      if(strcmp(word,atmosphere[i].name) == 0){
	exo.layerKappa[workingLayer]  = atmosphere[i].kappa;
	exo.layerAlbedo[workingLayer] = atmosphere[i].albedo;
	exo.layerType[workingLayer] = atmosphere[i].type;
	fscanf(structure,"%lf",&exo.layerRadius[workingLayer]);
	workingLayer++;
      }
    }
  }

  return exo;
}

// Prints out the complete data about the exoplanet that has
// been constructed from the .cfg and .mat files.
void printAllPlanetData(Planet exo){
  printf(AMAGENTA "nPhot   = %i\n"
	 "nLayers = %i\n"ARESET, exo.nPhot, exo.nLayers);
  for (int i=0; i<exo.nLayers; i++){
    printf(AMAGENTA "Layer %i)\n"
	   "    type   = %i\n"
	   "    radius = %lf\n"
	   "    kappa  = %lf\n"
	   "    albedo = %lf\n"ARESET,
	   i, exo.layerType[i],exo.layerRadius[i],
	   exo.layerKappa[i],exo.layerAlbedo[i]);
  }
  return;
}


//== INPUT FUNCTION ============================================
Planet input(Planet exo){

//-- ENTRY -----------------------------------------------------
  // Debug printing.
  if (DEBUG)
    printf(ACYAN "Input Running:\n" ARESET);

//-- INITIALISATION --------------------------------------------
  // Create structures for the known materials.
  Material atmosphere[MAX_NUMBER_OF_MATERIALS];
  int nMat = 0;

  // Reading functions.
  nMat = readMatList(nMat, atmosphere);
  readIndividualMats(nMat, atmosphere);
  exo = readConfig(exo, atmosphere);
  exo = readStructure(exo, atmosphere, nMat);

  printAllPlanetData(exo);

  if (DEBUG)
    printf(AGREEN "Input Done.\n" ARESET);
  return exo;
}
