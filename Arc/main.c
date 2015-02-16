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

// Lee & Kim 2004 mnras 347 p802
// Dalgano & Williams 1962 apj 136 p690

//── INCLUDES ─────────────────────────────────────────────────┤
#include "globals/headers/global.h"
#include "globals/headers/utilities.h"
#include "modules/headers/module.h"
#include <omp.h>


//── FUNCTION PROTOTYPES ──────────────────────────────────────┤
static inline void progressBar(int,int,int,int);


//── MAIN ─────────────────────────────────────────────────────┤
int main(){
	
	chdir("/Users/FreddyWordingham/Desktop/ExOEx/Arc");
	
	// Entry
	printTitle();
	if (DEBUG)
	  printf(ACYAN "ExOEx Running:\n" ARESET);

	// Initialisation
	
	// Declerations
	int nThreads, p_threadID, p_nLoop, g_nLoop = 0;
	int percentDone = 0;
	Planet exo;
	Particle photon;
	Datasystem g_data;
	Datasystem p_data;
	
	g_data.nDead = 0;
	for (int n=0; n<180; n++){
		g_data.lightCurve[n] = 0;		
	}
	
	FILE* twoDPos;
	FILE* threeDPos;
	twoDPos   = fopen("~/Desktop/ExOEx/Arc/data/twoDpos.dat","w");
		fclose(twoDPos);
	threeDPos = fopen("data/threeDpos.dat","w");
		fclose(threeDPos);
	twoDPos   = fopen("data/twoDpos.dat","a");
	threeDPos = fopen("data/threeDpos.dat","a");
	if (twoDPos == NULL)
		printf(ARED "ERROR! Could not open twoDpos.dat!\n" ARESET);
	twoDPos = fopen("data/twoDpos.dat","a");
	if (threeDPos == NULL)
		printf(ARED "ERROR! Could not open threeDpos.dat!\n" ARESET);
	
	exo.nLayers = readInt("config.cfg","nLayers");
	
	// Memory allocation
	exo.lType     = malloc(exo.nLayers * sizeof *exo.lType);
	exo.lKappa    = malloc(exo.nLayers * sizeof *exo.lKappa);
	exo.lAlbedo   = malloc(exo.nLayers * sizeof *exo.lAlbedo);
	exo.lRadius   = malloc(exo.nLayers * sizeof *exo.lRadius);
	  
	// Core modules
	input(&exo,&photon);
	
	if (DEBUG)
		printf(ACYAN "PhotonLoop Running:\n" ABLUE);
	
	int t1 = clock();
	
	#pragma omp parallel private(p_nLoop, p_threadID, photon, p_data)
	{
		#pragma omp critical
		{
			srand(clock());
		}
		
		nThreads = omp_get_num_threads();
		p_nLoop = 0;
		p_threadID = omp_get_thread_num();
	
		p_data.nDead = 0;
		for (int n=0; n<180; n++){
			p_data.lightCurve[n] = 0;		
		}

		if (p_threadID == 0)
			printf("Running with %i strings.\n",nThreads);
	
		#pragma omp for
		for (int i=0; i<exo.nPhot; i++){
			if (p_threadID == 0 && p_nLoop == (exo.nPhot/(100*nThreads)))
				estimatedTimeUntilCompletion(t1,nThreads);			
			if (p_threadID == 0)
				progressBar(i,exo.nPhot/nThreads,100,58);
			photonLoop(i,&photon,&exo);
			if (photon.life == false)
				p_data.nDead++;
			
			p_data.lightCurve[degreeConvert(photon.alpha)]++;
			
			//extraction(&photon,&data);
			p_nLoop++;
		}

		#pragma omp critical
		{
			printf("	Thread %i ran %i/%i iterations.\n",p_threadID,p_nLoop,exo.nPhot);
			printf("nDead = %i\n",p_data.nDead);
			g_nLoop = p_nLoop + g_nLoop;
			for (int k=0; k<180; k++){
				g_data.lightCurve[k] = g_data.lightCurve[k] + p_data.lightCurve[k];
			}
		}
	}
		
	printf("%i / %i photons run successfully.\n",g_nLoop,exo.nPhot);
		
	computationTime(t1,nThreads);
	
	if (DEBUG)
		printf(AGREEN "PhotonLoop Complete.\n\n" ARESET);
	
	output(&g_data,&exo);  
	
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
	printf(AYELLOW "%3d%% [" ARESET, (int)(ratio*100) );
 
	// Show the load bar.
	for (int x=0; x<c; x++)
		 printf(AYELLOW "=" ARESET);
 
	for (int x=c; x<w; x++)
		 printf(" ");
 
	// ANSI Control codes to go back to the
	// previous line and clear it.
	printf(AYELLOW "]\n\033[F\033[J" ABLUE);
}
