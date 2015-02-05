/*
  This file contains the global variables used in ExOEx
*/

//============================================= DEBUG CONTROL ==
#define DEBUG          1                                       // Set to 0 to turn off debug printing


//=================================================== DEFINES ==
#define DEFAULT_NPHOT   100000
#define DEFAULT_NLAYERS 1
#define DEFAULT_RADIUS  22.0


//============================================== ENUMERATIONS ==
enum Dimensions {                                               // THIS MAY WELL CHANGE
  X,                                                            // Done for dimension clarity
  Y,
  Z,
};


//================================================ STRUCTURES ==
typedef struct planet {
  int    nPhot;                                                 // Number of photons to run through sim
  int    nLayers;                                               // Total number of exoplanet layers
  double radius;                                                // Exoplanet radius
  double tao;
} Planet;

typedef struct particle {
  int identity;                                                 // Id number for tracking
  double pos[3];                                                // Current position
  double oldPos[3];                                             // Previous position
  double alpha;                                                 // Emission angle
} Particle;


//=================================== TERMINAL OUTPUT COLOURS ==
#define ARED     "\x1b[31m"                                     // May be used to print in colour in terminal
#define AGREEN   "\x1b[32m"
#define AYELLOW  "\x1b[33m"
#define ABLUE    "\x1b[34m"
#define AMAGENTA "\x1b[35m"
#define ACYAN    "\x1b[36m"
#define ARESET   "\x1b[0m"
