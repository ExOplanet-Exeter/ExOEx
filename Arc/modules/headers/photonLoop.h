/*==============================================================
----------------------------------------------------------------
             88
             88                         ,d
             88                         88
8b,dPPYba,   88,dPPYba,    ,adPPYba,  MM88MMM  ,adPPYba,
88P'    "8a  88P'    "8a  a8"     "8a   88    a8"     "8a
88       d8  88       88  8b       d8   88    8b       d8
88b,   ,a8"  88       88  "8a,   ,a8"   88,   "8a,   ,a8"
88`YbbdP"'   88       88   `"YbbdP"'    "Y888  `"YbbdP"'
88     88
88     88
       88
       8b,dPPYba,   88           ,adPPYba,    ,adPPYba,
       88P'   `"8a  88          a8"     "8a  a8"     "8a
       88       88  88          8b       d8  8b       d8
       88       88  88          "8a,   ,a8"  "8a,   ,a8"
       88       88  88888888888  `"YbbdP"'    `"YbbdP"'
                                                     88
                                                     88
                                                     88
                                   8b,dPPYba,        88,dPPYba,
                                   88P'    "8a       88P'    "8a
                                   88       d8       88       88
                                   88b,   ,a8"  888  88       88
                                   88`YbbdP"'   888  88       88
                                   88
                                   88
----------------------------------------------------------------
 This header file contains the function prototypes used within
                          'photonLoop.c'.
----------------------------------------------------------------
==============================================================*/


//== FUNCTION PROTOTYPES =======================================
// Determines the photons current distance from the exoplanet
// core.
double getRho(Particle photon){
    return sqrt(pow(photon.pos[X],2.0) + pow(photon.pos[Y],2.0) +
                pow(photon.pos[Z],2.0));
}


// Determines and records the layer that the photon is currently
// within.
Particle getLayer(Particle photon, Planet exo){
    double rho, layer;
    rho = getRho(photon);
    if (rho > 1.0){
        photon.curLayer = -1;
        photon.life = 0;
    }
    for (int i=exo.nLayers-1; i>=0; i--){
        if (rho <= exo.layerRadius[i]){
            photon.curLayer = i;
        }
    }
    return photon;
}


// Maps photons from stellar surface, to skin of exoplanet.
Particle mapToExoSurface(Particle photon, Planet exo){
    double rho;
    photon.curLayer = exo.nLayers - 1;
    rho = sqrt(pow(photon.pos[X],2.0) + pow(photon.pos[Y],2.0));
    photon.pos[Z] = sqrt(1.0 - pow(rho,2.0));
    return photon;
}


// Moves photon to stellar surface.
Particle stellarEmission(Particle photon){
    double rho = 2.0;
    photon.pos[Z] = STAR_DIST;
    while (rho > 1.0){
        photon.pos[X] = arcRand(-1.0,1.0);
        photon.pos[Y] = arcRand(-1.0,1.0);
        rho = sqrt(pow(photon.pos[X],2.0)+pow(photon.pos[Y],2.0));
    }
    return photon;
}


// Initialise the parameters of a new photon;
Particle initPhoton(Particle photon, int n){
    photon.IDNum    = n;
    photon.curLayer = -1;
    photon.alpha    = 0.0;
    photon.life     = 1;
    
    for (int i=0; i<3; i++){
        photon.pos[i]    = 0.0;
        photon.dirVec[i] = 0.0;
    }
    
    return photon;
}