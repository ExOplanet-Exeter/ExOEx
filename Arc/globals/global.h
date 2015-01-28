/*==============================================================
----------------------------------------------------------------
  ██████╗ ██╗      ██████╗ ██████╗  █████╗ ██╗        ██╗  ██╗ 
 ██╔════╝ ██║     ██╔═══██╗██╔══██╗██╔══██╗██║        ██║  ██║
 ██║  ███╗██║     ██║   ██║██████╔╝███████║██║        ███████║
 ██║   ██║██║     ██║   ██║██╔══██╗██╔══██║██║        ██╔══██║
 ╚██████╔╝███████╗╚██████╔╝██████╔╝██║  ██║███████╗██╗██║  ██║
  ╚═════╝ ╚══════╝ ╚═════╝ ╚═════╝ ╚═╝  ╚═╝╚══════╝╚═╝╚═╝  ╚═╝
----------------------------------------------------------------
         Contains all the global variables used in Arc.
 Be careful when editing as it will cause global changes (duh!)
----------------------------------------------------------------
==============================================================*/

//== INCLUDES ==================================================
#include <stdio.h>


//== DEBUG CONTROL =============================================
// Turns debug output off/on with 0/1 respectively.
#define DEBUG           1
// The maximum number of layers an exoplanet may have.
#define MAX_NLAYERS     10


//== GLOBAL DEFINES ============================================
// Physical and mathmatical constant defines.
#define PI              3.14159265359
// These are the values taken by default during planet setup
// if no other values have been found.
#define DEFAULT_NPHOT   10000000
#define DEFAULT_NLAYERS 1
#define DEFAULT_KAPPA   1.0
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
  ISO,
  RAY,
  MIE,
};


//== STRUCTURES ================================================
// Planet structure setup (this is likely to be changed soon.
typedef struct planet {
  int    nPhot;
  int    nLayers;
  int    layerType[MAX_NLAYERS];
  double layerKappa[MAX_NLAYERS];
  double layerRadius[MAX_NLAYERS];
} Planet;

// particle structure. Will commonly be used for photons.
typedef struct particle {
  // IDNum used for identifying specific photons.
  int IDNum;
  // The current and old positions of the photon, respectively.
  double curPos[3];
  int    curLayer;
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
