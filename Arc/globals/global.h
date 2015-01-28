/*==============================================================
----------------------------------------------------------------
             88               88                       88
             88               88                       88
             88               88                       88
 ,adPPYb,d8  88   ,adPPYba,   88,dPPYba,   ,adPPYYba,  88
a8"    `Y88  88  a8"     "8a  88P'    "8a  ""     `Y8  88
8b       88  88  8b       d8  88       d8  ,adPPPPP88  88
"8a,   ,d88  88  "8a,   ,a8"  88b,   ,a8"  88,    ,88  88
 `"YbbdP"Y8  88   `"YbbdP"'   8Y"Ybbd8"'   `"8bbdP"Y8  88
 aa,    ,88
 "Y8bbdP"
                                                     88
                                                     88
                                                     88
                                                     88,dPPYba,
                                                     88P'    "8a
                                                     88       88
                                                888  88       88
                                                888  88       88
----------------------------------------------------------------
         Contains all the global variables used in Arc.
 Be careful when editing as it will cause global changes (duh!)
----------------------------------------------------------------
==============================================================*/

//== INCLUDES ==================================================
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//== DEBUG CONTROL =============================================
// Turns debug output off/on with 0/1 respectively.
#define DEBUG           1


//== GLOBAL DEFINES ============================================
// Physical and mathmatical constant defines.
#define PI              3.14159265359
// These are the values taken by default during planet setup
// if no other values have been found.
#define DEFAULT_NPHOT   10000000
#define DEFAULT_NLAYERS 1
#define DEFAULT_KAPPA   1.0
// Defines used within 'input.c'
#define MAX_NAME_LENGTH 64
// Defines used within 'photonLoop.c'
#define STAR_DIST       10.0


//== ENUMERATIONS ==============================================
// X, Y & Z set to 0, 1 & 2 for clarity when using arrays etc.
// Take note that these are capatalised. x, y & z can still be
// used for variable names (though best to avoid that).
enum Dimensions {
  X,
  Y,
  Z,
};

enum ScatterTypes{
  // Isotropic.
  ISO,
  // Rayleigh.
  RAY,
  // Mie (using Henyey-Greenstein approximation).
  MIE,
};


//== STRUCTURES ================================================
// Planet structure setup (this is likely to be changed soon.
// Arrays now declared as pointers which will then have memory
// allocated for them in input.c. This is neater than having a
// array of greater than needed size as a work arround.
typedef struct planet {
  // Total number of photons to be simulated for this planet.
  int    nPhot;
  // Total number of layers making up the planet.
  int    nLayers;
  // The scattering type of each layer (enumeration key).
  int    *layerType;
  // Optical length of the layer material.
  double *layerKappa;
  // Albedo of layer.
  double *layerAlbedo;
  // Radial position of the layer (lower boundary).
  double *layerRadius;
} Planet;

// This is structure is designed to hold the information about
// a type of material so that the material properties may then
// be used to construct the planet.
typedef struct material {
  char   name[4];
  double kappa;
  double albedo;
} Material;

// particle structure. Will commonly be used for photons.
typedef struct particle {
  // IDNum used for identifying specific photons.
  int    IDNum;
  // The three dimensional position of the photon.
  double pos[3];
  // The layer in which the photon currently sits in.
  int    curLayer;
  // The determined direction of scattering. Photon will next
  // scatter at some point along this vector.
  double dirVec[3];
  // The emission angle of the photon from the Exoplanet.
  double alpha;
} Particle;

// Data structure, used to store all the semi-analysed data.
typedef struct datasystem {
  // Array to store lightcurve data.
  int    lightcurve[180];
  double normalisedLightcurve[180];
} Datasystem;

//== TERMINAL OUTPUT COLOURS ===================================
// These defines may be used for terminal colouring.
// They may not work unless used in terminal. May cause strange
// Xcode output for example.
#define ARED     "\x1b[31m"
#define AGREEN   "\x1b[32m"
#define AYELLOW  "\x1b[33m"
#define ABLUE    "\x1b[34m"
#define AMAGENTA "\x1b[35m"
#define ACYAN    "\x1b[36m"
#define ARESET   "\x1b[0m"
