/*═════════════════════════════════════════════════════════════╗
├──────────────────────────────────────────────────────────────┤
			| |_ ___ _ __ ___  _ __ | | __ _| |_ ___   ___ 
			| __/ _ \ '_ ` _ \| '_ \| |/ _` | __/ _ \ / __|
			| ||  __/ | | | | | |_) | | (_| | ||  __/| (__ 
			 \__\___|_| |_| |_| .__/|_|\__,_|\__\___(_)___|
									|_|           
├──────────────────────────────────────────────────────────────┤
	Short description of script in here.
├──────────────────────────────────────────────────────────────┤
╚═════════════════════════════════════════════════════════════*/

//── INCLUDES ─────────────────────────────────────────────────┤
#include "../globals/global.h"
#include "../globals/utilities.h"


//── FUNCTION PROTOTYPES ──────────────────────────────────────┤
bool randomTest();
bool isotropicTest();

void isotropic(Particle*);


//── TESTING ──────────────────────────────────────────────────┤
void testing(){
	
	srand(time(NULL));
	
	int p=0,f=0;
	bool pass;
	
	pass = randomTest();
	printOutcome("random",pass);
	
	pass = isotropicTest();
	printOutcome("isotropic",pass);
	
	return;
}


//─── COMPLETED FUNCTIONS ─────────────────────────────────────┤
bool isotropicTest(){
	
	Particle photon = {0};
	double u[3] ={0};
	
	for (int i=0; i<1000000; i++){
		isotropic(&photon);
		for (int i=0; i<3; i++){
			u[i] += photon.dirVec[i];
		}
	}
	
	
	return true;
}


bool randomTest(){
	
	double total = 0.0, ave = 0.0;
	
	for (int i=0; i<1000000; i++){
		total += arcRand(0.0,1.0);
	}
	
	ave = total/1000000;
	
	if ((ave > 0.49) && (ave < 0.51)){
		return true;
	}
	else {
		return false;
	}
}