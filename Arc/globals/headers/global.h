/*═════════════════════════════════════════════════════════════╗
├──────────────────────────────────────────────────────────────┤
		        __ _| | ___ | |__   __ _| | | |__  
			   / _` | |/ _ \| '_ \ / _` | | | '_ \ 
			  | (_| | | (_) | |_) | (_| | |_| | | |
			   \__, |_|\___/|_.__/ \__,_|_(_)_| |_|
			   |___/
├──────────────────────────────────────────────────────────────┤
	Contains all the global variables used in Arc.
	Be careful when editing as it will cause global changes.
├──────────────────────────────────────────────────────────────┤
╚═════════════════════════════════════════════════════════════*/


//── CONDITIONAL ──────────────────────────────────────────────┤
#ifndef global
#define global


//── INCLUDES ─────────────────────────────────────────────────┤
// 1) Printing and reading functions.
// 2) C standard general utilities functions.
// 3) Contains various useful string related functions. 
// 4) Intermediate mathmatical functions sin() etc.
// 5) ExOEx group created utility functions.
#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>


//── DEBUG CONTROL ────────────────────────────────────────────┤
// Turns off/on debug output with 0/1 respectively.
#define DEBUG	1

//── GLOBAL DEFINES ───────────────────────────────────────────┤
// 1) Sudo NULL type for int.
// 2) Sudo NULL type for double.
// 3) Mathmatical constant pi.
// 4) Maximum name length for a material.
// 5) Maximum word length when reading config files.
// 6) Maximum comment length when reading config files.
// 7) Distance photons are set at when being emitted from star.
#define INT_NULL			1234567890
#define DOUBLE_NULL			0.123456789

#define PI					3.14159265359

#define MAX_NAME_LENGTH		16
#define MAX_WORD_LENGTH		64
#define MAX_COMMENT_LENGTH	128

#define STAR_DIST			10.0


//── STRUCTURES ───────────────────────────────────────────────┤
// Planet structure type. 
// Some arrays delared as pointers which will have memory
// allocated for them at start of main.c.
// 1.1) Total number of photons to be simulated.
// 1.2) Number of exoplanet layers.
// 1.3) Scattering type of each layer (enum).
// 1.4) Optical length of the layer material.
// 1.5) Layer albedo.
// 1.6) Radial position of layer (upper boundary).
typedef struct planet{
	int 	nPhot;
	int 	nLayers;
	int 	*lType;
	double  *lKappa;
	double 	*lAlbedo;
	double	*lRadius;
} Planet;

// Particle structure type.
// 2.1) ID number of particle.
// 2.2) Current layer in which particle is located.
// 2.3) Particle wavelength.
// 2.4) Position array of particle.
// 2.5) Direction vector of particle travel.
// 2.6) Emission angle of particle.
// 2.7) Is particle alive? 1 = True, 0 = False.
typedef struct particle{
	int 	IDNum;
	int		curLayer;
	double	wavelength;
	double 	pos[3];
	double 	dirVec[3];
	double 	alpha;
	bool	life;
} Particle;

// Structure for storing data.
// 3.1) Array for raw lightcurve data;
// 3.2) Array for lightcurve after consideration of solid angle.
typedef struct datasystem{
	int lightCurve[180];
	double fittedCurve[180];
} Datasystem;

//── ENUMERATIONS ─────────────────────────────────────────────┤
// Set X, Y & Z to 0, 1 & 2 for clarity when using array
// dimension elements. Note that these are capatalised.
enum Dimensions{
	X,
	Y,
	Z,
};


enum ScatterTypes{
	ISO,
	RAY,
	MIE,
};

//── TERMINAL OUTPUT COLOURS ──────────────────────────────────┤
// These defines are used for terminal colouring.
// Will only work when used within unix terminal.
#define ARED     "\x1b[31m"
#define AGREEN   "\x1b[32m"
#define AYELLOW  "\x1b[33m"
#define ABLUE    "\x1b[34m"
#define AMAGENTA "\x1b[35m"
#define ACYAN    "\x1b[36m"
#define ARESET   "\x1b[0m"


//── CONDITIONAL ──────────────────────────────────────────────┤
#endif