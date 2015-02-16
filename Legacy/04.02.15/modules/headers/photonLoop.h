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
double getLambda(Particle,Planet);
double getRho(Particle);
Particle getLayer(Particle,Planet);
Particle mapToExoSurface(Particle,Planet);
Particle stellarEmission(Particle);
Particle initPhoton(Particle,int);

double getAlpha(Particle);
Particle move(Particle,Planet);
Particle isoScatter(Particle);
int absorbeChance(Particle,Planet);
Particle injectPhoton(Particle,Planet);


//== COMPLETED FUNCTIONS =======================================
// Calculates the emission angle (alpha) of a photon.
double getAlpha(Particle photon){
    double alpha;
    alpha = acos(arcDot(photon.dirVec[X],photon.dirVec[Y],
                        photon.dirVec[Z],0.0,0.0,1.0));
    return alpha;
}


// Moves the photon to a new position along the direction vector
// with a total displacement lambda.
Particle move(Particle photon, Planet exo){
    double lambda;
    lambda = getLambda(photon, exo);
    for (int i=0; i<3; i++){
        photon.pos[i] = photon.pos[i] + (photon.dirVec[i] * lambda);
    }
    return photon;
}


// Create a direction vector for an isotropic scattering.
Particle isoScatter(Particle photon){
    double theta;
    theta            = arcRand(0.0,2.0*PI);
    photon.dirVec[X] = 2.0 * arcRand(0.0,1.0) - 1.0;
    photon.dirVec[Y] = sqrt(1.0 - pow(photon.dirVec[X],2.0)) *
    cos(theta);
    photon.dirVec[Z] = sqrt(1.0 - pow(photon.dirVec[X],2.0)) *
    sin(theta);
    return photon;
}

// Gives the photon a chance to be absorbed and thus removed
// from photon loop.
int absorbeChance(Particle photon, Planet exo){
    double a;
    a = arcRand(0.0,1.0);
    if (a < exo.layerAlbedo[photon.curLayer]){
        return 0;
    }
    else{
        return 1;
    }
}


// 'Inject' the photon in along direction vector connecting star
// and exoplanet, as photons are emitted normal to stellar
// surface.
Particle injectPhoton(Particle photon, Planet exo){
    photon.pos[Z] = photon.pos[Z] - getLambda(photon,exo);
    photon = getLayer(photon, exo);
    if(getRho(photon) <= 1.0){
        photon.life = absorbeChance(photon,exo);
    }
    return photon;
}



// Calculates the path length a photon will travel through the
// exoplanet.
double getLambda(Particle photon, Planet exo){
    double lambda;
    lambda = -log(arcRand(0.0,1.0)) /
    exo.layerKappa[photon.curLayer];
    return lambda;
}


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
