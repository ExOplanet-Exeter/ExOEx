/*═════════════════════════════════════════════════════════════╗
├──────────────────────────────────────────────────────────────┤
             ___  _   _| |_ _ __  _   _| |_   ___ 
	        / _ \| | | | __| '_ \| | | | __| / __|
	       | (_) | |_| | |_| |_) | |_| | |_ | (__ 
	        \___/ \__,_|\__| .__/ \__,_|\__(_)___|
			               |_| 
├──────────────────────────────────────────────────────────────┤
	Outputs analysed data, such as lightcurves, to files.
├──────────────────────────────────────────────────────────────┤
╚═════════════════════════════════════════════════════════════*/


//── INCLUDES ─────────────────────────────────────────────────┤
#include "../../globals/headers/global.h"
#include "../../globals/headers/utilities.h"
#include "../../globals/headers/gnuplot_i.h"


//── FUNCTION PROTOTYPES ──────────────────────────────────────┤


//── FUNCTIONS IN PROGRESS ────────────────────────────────────┤


//── PHOTON LOOP ──────────────────────────────────────────────┤
void output(Datasystem *data,Planet *exo){
	
	if (DEBUG)
		printf(ACYAN "Output Running:\n" ARESET);

	printf(ARESET);
	double x[180];
	double y[180];
	FILE* lightcurve;
	lightcurve = fopen("data/lightcurve.dat","w");
	if (lightcurve == NULL)
		printf(ARED "ERROR! Could not open lightcurve.dat!\n" ARESET);
	
	// Fitting loop
	double binMax = 0;
	for (int n=0; n<180; n++){
		data->fittedCurve[n] = data->lightCurve[n] / sin((n+0.5)*(PI/180.0));
		if (data->fittedCurve[n] > binMax)
			binMax = data->fittedCurve[n];
	}
	for (int n=0; n<180; n++){
		data->fittedCurve[n] = data->fittedCurve[n] / binMax;
	}
	data->fittedCurve[0] = data->fittedCurve[1];
	
	printf("Number dead = %i/%i\n(%lf%%)\n",data->nDead,exo->nPhot,(100.0*data->nDead)/exo->nPhot);
	
	// Printing loop
	for (int n=0; n<180; n++){
		fprintf(lightcurve,"%i %lf\n",n,data->fittedCurve[n]);
		y[n] = data->fittedCurve[n];
		x[n] = n;
	}
	gnuplot_ctrl * h1;
	h1 = gnuplot_init();
	gnuplot_cmd(h1,"set terminal dumb");
	gnuplot_setstyle(h1,"lines");
	gnuplot_cmd(h1,"set xrange [0:180]");
	gnuplot_cmd(h1,"set yrange [0:1]");
	gnuplot_plot_xy(h1,x,y,180,"user-defined points");
	
	gnuplot_close(h1);
	

	if (DEBUG)
		printf(AGREEN "Output Complete.\n\n" ARESET);
		
	return;
}


//── COMPLETED FUNCTIONS ──────────────────────────────────────┤
