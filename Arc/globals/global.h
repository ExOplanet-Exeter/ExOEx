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
//#include "../globals/utilities.h"


//── DEBUG CONTROL ────────────────────────────────────────────┤
// Turns off/on debug output with 0/1 respectively.
#define DEBUG	1

//── GLOBAL DEFINES ───────────────────────────────────────────┤
// 1) Sudo NULL type for int.
// 2) Mathmatical constant pi.
// 3) Maximum word length when reading config files.
// 4) Maximum comment length when reading config files.
#define INT_NULL			1234567890
#define PI					3.14159265359
#define MAX_WORD_LENGTH		64
#define MAX_COMMENT_LENGTH	128


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
	double 	*lRadius;
} Planet;

//── ENUMERATIONS ─────────────────────────────────────────────┤
// Set X, Y & Z to 0, 1 & 2 for clarity when using array
// dimension elements. Note that these are capatalised.
enum Dimensions{
	X,
	Y,
	Z,
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