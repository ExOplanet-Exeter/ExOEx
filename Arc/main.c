/*═════════════════════════════════════════════════════════════╗
├──────────────────────────────────────────────────────────────┤
 __________                  ______     __________
|          |                /      \   |          |  
|  ________| ___    ____   /   __   \  |  ________| ____    ____
|       |    \   \  /   / |   /  \   | |       |    \   \  /   /
|     __|     \   \/   /  |  |    |  | |     __|     \   \/   / 
|    |         \      /   |  |    |  | |    |         \      / 
|    |_____    /  __  \   |   \__/   | |    |_____    /  __  \
|          |  /  /  \  \   \        /  |          |  /  /  \  \ 
|__________| /__/    \__\   \______/   |__________| /__/    \__\

├──────────────────────────────────────────────────────────────┤
                   _ __ ___   __ _(_)_ __    ___ 
                  | '_ ` _ \ / _` | | '_ \  / __|
                  | | | | | | (_| | | | | || (__
                  |_| |_| |_|\__,_|_|_| |_(_)___|           
├──────────────────────────────────────────────────────────────┤
		This program simulates polarised light observed from an
		irradiated extrasolar planet.
├──────────────────────────────────────────────────────────────┤
╚═════════════════════════════════════════════════════════════*/


//── INCLUDES ─────────────────────────────────────────────────┤
#include "globals/headers/global.h"
#include "globals/headers/utilities.h"
#include "modules/headers/module.h"


//── MAIN ─────────────────────────────────────────────────────┤
int main(){
	
	// Entry
	printTitle();
	if (DEBUG)
	  printf("ExOEx Running:\n");

	// Initialisation
	srand(2434);
	
	// Declerations
	Planet exo;
	Particle photon;
	Datasystem data;
	
	exo.nLayers = readInt("config.cfg","nLayers");
	
	// Memory allocation
	exo.lType     = malloc(exo.nLayers * sizeof *exo.lType);
	exo.lKappa    = malloc(exo.nLayers * sizeof *exo.lKappa);
	exo.lAlbedo   = malloc(exo.nLayers * sizeof *exo.lAlbedo);
	exo.lRadius   = malloc(exo.nLayers * sizeof *exo.lRadius);
	  
	// Core modules
	input(&exo);
	
	if (DEBUG)
		printf("PhotonLoop Running:\n");
	for (int i=0; i<exo.nPhot; i++){
		photonLoop(&photon,i);
		extraction(&photon,&data);
	}
	if (DEBUG)
		printf("PhotonLoop Complete.\n\n");
	  
	// Clean up
	free(exo.lType);
	free(exo.lKappa);
	free(exo.lAlbedo);
	free(exo.lRadius);
	
	// Exit
	if (DEBUG)
		printf("ExOEx Complete.\n\n");
			
	return 0;
}