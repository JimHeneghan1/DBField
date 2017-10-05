/* Header file to accompany ezinc3.c. */

#ifndef _EZINC_H   /*@ \label{ezincHA} @*/
#define _EZINC_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "fdtd-macro-tmz.h"

void ezIncInit(Grid *g);
double ezInc(double time, double location);

#endif  /* matches #ifndef _EZINC3_H */
