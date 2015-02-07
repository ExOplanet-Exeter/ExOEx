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


//── FUNCTION PROTOTYPES ──────────────────────────────────────┤
static inline void progressBar(int,int,int,int);


//── MAIN ─────────────────────────────────────────────────────┤
int main(){
	
	// Entry
	printTitle();
	if (DEBUG)
	  printf(ACYAN "ExOEx Running:\n" ARESET);

	// Initialisation
	srand(2434);
	
	// Declerations
	int percentDone = 0;
	Planet exo;
	Particle photon;
	Datasystem data;
	
	FILE* twoDPos;
	twoDPos = fopen("data/twoDpos.dat","w");
	fclose(twoDPos);
	twoDPos = fopen("data/twoDpos.dat","a");
	if (twoDPos == NULL)
		printf(ARED "ERROR! Could not open 2Dpos.dat!\n" ARESET);
	
	exo.nLayers = readInt("config.cfg","nLayers");
	
	// Memory allocation
	exo.lType     = malloc(exo.nLayers * sizeof *exo.lType);
	exo.lKappa    = malloc(exo.nLayers * sizeof *exo.lKappa);
	exo.lAlbedo   = malloc(exo.nLayers * sizeof *exo.lAlbedo);
	exo.lRadius   = malloc(exo.nLayers * sizeof *exo.lRadius);
	  
	// Core modules
	input(&exo,&photon);
	
	if (DEBUG)
		printf(ACYAN "PhotonLoop Running:\n" AYELLOW);
	for (int i=0; i<exo.nPhot; i++){
		progressBar(i,exo.nPhot,100,58);
		photonLoop(&photon,i);
		extraction(&photon,&data,twoDPos);
	}
	if (DEBUG)
		printf(AGREEN "PhotonLoop Complete.\n\n" ARESET);
	
	output(&data);  
	
	// Clean up
	free(exo.lType);
	free(exo.lKappa);
	free(exo.lAlbedo);
	free(exo.lRadius);
	
	// Exit
	if (DEBUG)
		printf(AGREEN "ExOEx Complete.\n\n" ARESET);
			
	return 0;
}


//── COMPLETED FUNCTIONS ──────────────────────────────────────┤
// Prints out a progress bar to the terminal.
// x/n is the fraction complete.
// r is resolution of bar. w is width of bar.
static inline void progressBar(int x, int n, int r, int w){
	// Only update r times.
	if ( x % (n/r +1) != 0 ) return;
 
	// Calculuate the ratio of complete-to-incomplete.
	float ratio = x/(float)n;
	int   c     = ratio * w;
 
	// Show the percentage complete.
	printf("%3d%% [", (int)(ratio*100) );
 
	// Show the load bar.
	for (int x=0; x<c; x++)
		 printf("=");
 
	for (int x=c; x<w; x++)
		 printf(" ");
 
	// ANSI Control codes to go back to the
	// previous line and clear it.
	printf("]\n\033[F\033[J");
}