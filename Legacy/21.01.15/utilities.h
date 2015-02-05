/*                                                     
  This file contains some useful utility functions                                       
*/

//================================================== INCLUDES ==
#include <stdio.h>
#include <stdlib.h>

//================================================= FUNCTIONS ==

double arcRand(double min, double max) {
  double range = max - min;
  double div = RAND_MAX / range;
  return min + (rand() / div);
}
