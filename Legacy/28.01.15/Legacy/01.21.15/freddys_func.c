//
//  freddys_func.c
//  ExOEx
//
//  Created by Freddy Wordingham on 01/12/2014.
//  Copyright (c) 2014 FreddyWordingham. All rights reserved.
//

#include <stdlib.h>
#include <math.h>
#include "global.h"

// This is an example function that creates a path length
double travelLength(Body exo){
    double T;
    T = -log(rand())*exo.tau;
    return T;
}

// Returns a random double between a preset min and max value
double arcRand(double min, double max){
    double range = max - min;
    return (((double)(range)/RAND_MAX) * rand() + min);
}
