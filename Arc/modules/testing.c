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


//── DEFINES ──────────────────────────────────────────────────┤
#define NPHOT 10000000

/*
//── FUNCTION PROTOTYPES ──────────────────────────────────────┤
bool randomTest();
bool isotropicTest();
bool isotropicTest2();
bool rayleighTest();

void isotropic(Particle*);

*/
//── TESTING ──────────────────────────────────────────────────┤
void testing(){
	/*
	srand(time(NULL));
	
	int p=0,f=0;
	bool pass;
	
	pass = randomTest();
	printOutcome("random",pass);
	
	//pass = isotropicTest();
	//printOutcome("isotropic",pass);
	
	pass = isotropicTest2();
	printOutcome("isotropic",pass);
	
	pass = rayleighTest();
	printOutcome("rayleigh",pass);
	*/
	return;
}

/*
//─── COMPLETED FUNCTIONS ─────────────────────────────────────┤
bool rayleighTest(){
	
	FILE *file;
	file = fopen(outputPath "rayleighTest.dat","w");
	
	double bin[180] ={0.0};
	double A,B,theta,max = 0.0,modelValue,delta;
	Particle photon={0};
	
	for (int i=0; i<NPHOT; i++){
		
		A = 1.0;
		B = -1.0;
		
		while(A > B){
			A = arcRand(0.0,2.0);
			theta = arcRand(0.0,PI);
			B = 1.0 + pow(cos(theta),2.0);
		}
		
		bin[(int)(theta*(180.0/PI))]++;
	}
	
	for (int i=0; i<180; i++){
		if (bin[i] > max){
			max = bin[i];
		}
	}
	
	for (int i=0; i<180; i++){
		bin[i] = bin[i] / max;	
	}
	
	for (int i=0; i<180; i++){
		printf("%i %lf\n",i,bin[i]);
		fprintf(file,"%i %lf\n",i,bin[i]);
	}
	
	double x[180] = {0};
	for (int i=0; i<180; i++){
		modelValue = 1.0 + pow(cos(i*(PI/180.0)),2.0);
		delta = fabs(bin[i] - modelValue);
		printf("%i %lf\n",i,delta);
		x[i] = i*1.0;
	}

	
	gnuplot_ctrl * h1;
	h1 = gnuplot_init();
	gnuplot_cmd(h1,"set terminal x11");
	gnuplot_setstyle(h1,"points");
	gnuplot_cmd(h1,"set xrange [0:180]");
	gnuplot_cmd(h1,"set yrange [0:1]");
	
	gnuplot_plot_xy(h1,x,bin,180,"user-defined points");
	
	usleep(10000000);
	
	gnuplot_close(h1);
	

	return true;
}


bool isotropicTest2(){

	FILE *file;
	file = fopen(outputPath "isotropicTest.dat","w");
	
	double bin[180] ={0.0};
	double A,B,theta,max = 0.0;
	Particle photon={0};
	
	for (int i=0; i<NPHOT; i++){
		
		A = 1.0;
		B = -1.0;
		
		while(A > B){
			A = arcRand(0.0,1.0);
			theta = arcRand(0.0,PI);
			B = 1.0;
		}
		
		bin[(int)(theta*(180.0/PI))]++;
	}
	
	for (int i=0; i<180; i++){
		if (bin[i] > max){
			max = bin[i];
		}
	}
	
	for (int i=0; i<180; i++){
		bin[i] = bin[i] / max;	
	}
	
	for (int i=0; i<180; i++){
		printf("%i %lf\n",i,bin[i]);
		fprintf(file,"%i %lf\n",i,bin[i]);
	}
	
	return false;
}


// Tests to see if the isotropic function is working correctly.
bool isotropicTest(){
	
	Particle photon = {0};
	double t[3] = {0.0};
	
	for (int i=0; i<NPHOT; i++){
		isotropic(&photon);
		for (int i=0; i<3; i++){
			t[i] += fabs(photon.dirVec[i]);
		}
	}
	
	double min = (NPHOT / 2.0) - (NPHOT * 0.9);
	double max = (NPHOT / 2.0) + (NPHOT * 0.9);
	
	if (((t[0] > min) && (t[0] < max)) &&
	((t[1] > min) && (t[1] < max)) &&
	((t[2] > min) && (t[2] < max))){
		return true;
	}
	else {
		return false;
	}
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
*/