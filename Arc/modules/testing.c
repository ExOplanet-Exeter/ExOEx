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
#include "../globals/gnuplot_i.h"
#include "../modules/modules.h"


//── DEFINES ──────────────────────────────────────────────────┤
#define NPHOT 100000000


//── FUNCTION PROTOTYPES ──────────────────────────────────────┤
bool randomTest();
bool isotropicTest();
bool rayleighTest();
bool polTest();

void isotropic(Particle*);
void rayleigh(Particle*);
void initialisePhoton(Particle*);
void observerPol(Particle*);


//── TESTING ──────────────────────────────────────────────────┤
void testing(){
	
	srand(time(NULL));
	
	int p=0,f=0;
	bool pass;
	
	pass = randomTest();
	printOutcome("random",pass);
	
	pass = isotropicTest();
	printOutcome("isotropic",pass);
	
	pass = rayleighTest();
	printOutcome("rayleigh",pass);
	
	pass = polTest();
	printOutcome("polarisation",pass);
	
	return;
}


//─── COMPLETED FUNCTIONS ─────────────────────────────────────┤
// Test the polarisation matrix
bool polTest(){
	
	FILE *file;
	file = fopen(outputPath "polTest.dat","w");
	
	Particle photon = {0.0};
	Datasystem data = {0};
	int bin;
	
	for (int i=0; i<NPHOT; i++){		
		initialisePhoton(&photon);

		photon.dirVec[Z] = 1.0;
		
		rayleigh(&photon);
		
		photon.alpha = acos(photon.dirVec[Z]);
		
		bin = photon.alpha * (180.0/PI);
		
		data.nDead++;
		data.lightcurve[bin]++;
		data.IPol[bin] += photon.pol[I];
		data.QPol[bin] += photon.pol[Q];
		data.UPol[bin] += photon.pol[U];
		data.VPol[bin] += photon.pol[V];
		
		//observerPol(&photon);
	}
	
	double maxF = 0.0, maxI = 0.0, maxQ = 0.0, maxU = 0.0, maxV = 0.0;
	for (int i=0; i<180; i++){
		data.fittedCurve[i] = data.lightcurve[i] / sin((i+0.5)*(PI/180.0));
		data.IPol[i] = data.IPol[i] / sin((i+0.5)*(PI/180.0));
		data.QPol[i] = data.QPol[i] / sin((i+0.5)*(PI/180.0));
		data.UPol[i] = data.UPol[i] / sin((i+0.5)*(PI/180.0));
		data.VPol[i] = data.VPol[i] / sin((i+0.5)*(PI/180.0));
	
		if (data.fittedCurve[i] > maxF){
			maxF = data.fittedCurve[i];
		}
		if (data.IPol[i] > maxI){
			maxI = data.IPol[i];
		}
		if (data.QPol[i] > maxQ){
			maxQ = data.QPol[i];
		}
		if (data.UPol[i] > maxU){
			maxU = data.UPol[i];
		}
		if (data.VPol[i] > maxV){
			maxV = data.VPol[i];
		}
	}
	
	for (int i=0; i<180; i++){
		data.fittedCurve[i] = data.fittedCurve[i]/maxF;
		data.IPol[i] = data.IPol[i]/maxI;
		data.QPol[i] = data.QPol[i]/maxQ;
		data.UPol[i] = data.UPol[i]/maxU;
		data.VPol[i] = data.VPol[i]/maxV;
	}
	
	for (int i=0; i<180; i++){
		fprintf(file,"%i %lf %lf %lf %lf %lf\n",i,data.fittedCurve[i],data.IPol[i],data.QPol[i],data.UPol[i],data.VPol[i]);
	}
	
	fclose(file);
	
	return false;
}


// Tests to see if the isotropic function is performing correctly.
bool rayleighTest(){

	FILE *file;
	file = fopen(outputPath "rayleighTest.dat","w");
	
	Particle photon = {0.0};
	int lightcurve[180] = {0};
	double fittedCurve[180] = {0.0};
	double alpha, max = 0.0;
	
	for (int i=0; i<NPHOT; i++){
		photon.dirVec[X] = 0.0;
		photon.dirVec[Y] = 0.0;
		photon.dirVec[Z] = 1.0;
		rayleigh(&photon);
		//isotropic(&photon);
		alpha = acos(photon.dirVec[Z]*1.0);
		//printf("a = %lf\n",alpha);
		lightcurve[(int)((alpha*180)/PI)]++;
	}
	
	for (int i=0; i<180; i++){
		fittedCurve[i] = lightcurve[i] / sin((i+0.5)*(PI/180.0));
		if (fittedCurve[i] > max){
			max = fittedCurve[i];
		}
	}

	for (int i=0; i<180; i++){
		fittedCurve[i] = fittedCurve[i] / max;
		fprintf(file,"%i %lf\n",i,fittedCurve[i]);
	}
	
	return true;
}

// Tests to see if the isotropic function is performing correctly.
bool isotropicTest(){

	FILE *file;
	file = fopen(outputPath "isotropicTest.dat","w");
	
	Particle photon = {0.0};
	int lightcurve[180] = {0};
	double fittedCurve[180] = {0.0};
	double alpha, max = 0.0;
	
	for (int i=0; i<NPHOT; i++){
		isotropic(&photon);
		alpha = acos(photon.dirVec[Z]*1.0);
		lightcurve[(int)((alpha*180)/PI)]++;
	}
	
	for (int i=0; i<180; i++){
		fittedCurve[i] = lightcurve[i] / sin((i+0.5)*(PI/180.0));
		if (fittedCurve[i] > max){
			max = fittedCurve[i];
		}
	}

	for (int i=0; i<180; i++){
		fittedCurve[i] = fittedCurve[i] / max;
		fprintf(file,"%i %lf\n",i,fittedCurve[i]);
	}
	
	return true;
}

// Tests that random numbers are being produced correctly.
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