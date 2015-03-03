/*═════════════════════════════════════════════════════════════╗
├──────────────────────────────────────────────────────────────┤
              __ _| | ___ | |__   __ _| | | |__  
             / _` | |/ _ \| '_ \ / _` | | | '_ \ 
            | (_| | | (_) | |_) | (_| | |_| | | |
             \__, |_|\___/|_.__/ \__,_|_(_)_| |_|
             |___/        
├──────────────────────────────────────────────────────────────┤
	Contains all global variables and settings to be used
	within ./arc. Be careful with editing as it will cause
	global scope changes.
├──────────────────────────────────────────────────────────────┤
╚═════════════════════════════════════════════════════════════*/

//── BEGIN CONDITIONAL ────────────────────────────────────────┤
#ifndef global
#define global


//── INCLUDES ─────────────────────────────────────────────────┤
/*
1) Terminal printing and reading.
2) C string functions.
3) C standard general utilities functions.
4) Itermediate mathmatical functions, sin() etc.
5) C bool library.
6) Functions for grabbing time.
&) Contains usleep() among other useful functions.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>


//── DEBUGGER CONTROL ─────────────────────────────────────────┤
/*
Turns debug printing off/on with 0/1 respectively.
*/
#define DEBUG 1


//── RUNNING MODE CONTROL ──────────────────────────────────────┤
/*
Determines what mode the program will run in.
*/
int globalRunningMode;


//── GLOBAL DEFINES ───────────────────────────────────────────┤
/*
0) Local path from ./arc program to /configure/ folder.
1) Mathmatical constant Pi.
2) Maximum name length for a material.
3) Maximum string length for a read word from a config file.
4) Maximum string length for a read comment in a config file.
5) Distance new photons are set at when being emitted from star.
*/
#define configPath			"../../Configure/"
#define outputPath			"../../Output/"
#define PI 					3.14159265359
#define MAX_NAME_LENGTH 	16
#define MAX_WORD_LENGTH 	64
#define MAX_COMMENT_LENGTH 	128
#define STAR_DIST			10.0


//─── STRUCTURES ──────────────────────────────────────────────┤
/*
	Planet structure type.
	Some arrays are declared as pointers which will have
	required memory allocated for them at the start of main.c

1.1) Number of photons to be simulated.
1.2) Number of layers the exoplanet has.
1.3) Scattering type of planet layer.
1.4) Kappa value of planet layer.
1.5) Albedo value of planet layer.
1.6) Outer radius of planet layer.
*/
typedef struct planet{
	int 	nPhot;
	int		nLayers;
	int		*scatType;
	double 	*kappa;
	double 	*albedo;
	double	*radius;
} Planet;


/*
	Particle structure type.
	This structure will mainly be used for photons.
2.1) Is photon alive? True = yes, false = no.
2.2) Current layer particle is found on.
2.3) Wavelength of particle.
2.4) Position of particle in three dimensions.
2.5) Direction vector of particle travel.
2.6) Emission angle of particle from planet.
2.7) Polarisation four vector.
*/
typedef struct particle{
	bool 	life;
	int 	curLayer;
	double 	wavelength;
	double 	pos[3];
	double 	dirVec[3];
	double 	alpha;
	double	pol[4];
} Particle;


/*
	Data structure type.
	Used for storing all high level data output.
3.1) Total number of dead particles.
3.2) Array for raw emitted lightcurve.
3.3) Array for lightcurve after fitting function applied.
*/
typedef struct datasystem{
	int 	nDead;
	int 	lightcurve[180];
	double 	fittedCurve[180];
} Datasystem;


/*
	Private thread information structure.
	An initialised copy is passed to each thread for it to
	store all it's data.
	These seperate strucutures may then be compiled into a
	single, total, data structure.
4.1) Thread identification number.
4.2) Number of loops completed by that thread.
4.3) Copy of a data structure for storage of high level data.
*/
typedef struct threadInfo{
	int 	id;
	int 	nLoop;
	int		startTime;
	Datasystem data;
} ThreadInfo;


//── ENUMERATIONS ──────────────────────────────────────────┤
/*
	Sets NORMAL, LAMBERT as an enumeration for clarity.
*/
enum Modes{
	NORMAL,
	TEST,
	LAMBERT,
};


/*
	Sets X, Y & Z to 0, 1 & 2 for clarity when manipulating
	array dimensions. Note that these are capatalised.
*/
enum Dimensions{
	X,
	Y,
	Z,
};


/*
	Sets ISO, RAY & MIE to 0, 1 & 2 so that the names may be 
	used in array arguments for clarity.
*/
enum ScatterTypes{
	ISO,
	RAY,
	MIE,
};


//── TERMINAL OUTPUT COLOURS ──────────────────────────────────┤
/*
	Defines used for colouring terminal output.
	Note that these will only work in a unix enviroment with
	ansi support.
*/
#define ARED		"\x1b[31m"
#define AGREEN 		"\x1b[32m"
#define AYELLOW	 	"\x1b[33m"
#define ABLUE 		"\x1b[34m"
#define AMAGENTA	"\x1b[35m"
#define ACYAN 		"\x1b[36m"
#define ARESET 		"\x1b[0m"


//── END CONDITIONAL ──────────────────────────────────────────┤
#endif