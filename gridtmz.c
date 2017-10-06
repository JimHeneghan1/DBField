#include "fdtd-macro-tmz.h"
#include "fdtd-alloc1.h"
#include <math.h>

void gridInit(Grid *g) {
  double imp0 = 377.0;
  int mm, nn;
  Type = tmZGrid;                          /*@ \label{gridtmzA} @*/
  SizeX = 1001;             // x size of domain
  SizeY = 81;              // y size of domain
  MaxTime = 4000;           // duration of simulation
  Cdtds = 1.0/ sqrt(2.0); // Courant number

  ALLOC_2D(g->hx,   SizeX, SizeY - 1, double);  /*@ \label{gridtmzB} @*/
  ALLOC_2D(g->chxh, SizeX, SizeY - 1, double);
  ALLOC_2D(g->chxe, SizeX, SizeY - 1, double);
  ALLOC_2D(g->hy,   SizeX - 1, SizeY, double);
  ALLOC_2D(g->chyh, SizeX - 1, SizeY, double);
  ALLOC_2D(g->chye, SizeX - 1, SizeY, double);
  ALLOC_2D(g->ez,   SizeX, SizeY, double);
  ALLOC_2D(g->ceze, SizeX, SizeY, double);
  ALLOC_2D(g->cezh, SizeX, SizeY, double);    /*@ \label{gridtmzC} @*/
  ALLOC_2D(g->curlH, SizeX, SizeY , double);
  ALLOC_2D(g->dz,   SizeX, SizeY, double);
  ALLOC_2D(g->epsRzz, SizeX, SizeY, double);
  ALLOC_2D(g->bx,   SizeX, SizeY - 1, double); 
  ALLOC_2D(g->by,   SizeX - 1, SizeY, double);
  ALLOC_2D(g->muRxx, SizeX, SizeY - 1, double);
  ALLOC_2D(g->muRyy, SizeX - 1, SizeY, double);


  /* set electric-field update coefficients */
  for (mm = 0; mm < SizeX; mm++)
    for (nn = 0; nn < SizeY; nn++) {
      Ceze(mm, nn) = 1.0;
      Cezh(mm, nn) = Cdtds * imp0;
    }
/*Set coefficients for Dielectric square*/ 
/*
  for (mm = 200; mm < 1390; mm++) {
                for (nn = 0; nn < SizeY; nn++) {
			Ceze(mm, nn) = 1.0;
      			Cezh(mm, nn) = (Cdtds*imp0)/4.0;
		}
   }
  for (mm = 1390; mm < 1410; mm++) {
                for (nn = 0; nn < SizeY; nn++) {
                        Ceze(mm, nn) = 1.0; 
                        Cezh(mm, nn) = (Cdtds*imp0)/2.0;
                }
   }
*/
/* Setting permitivity to be 1 for all space*/
   for (mm = 0; mm < SizeX; mm++)
   	for (nn = 0; nn < SizeY; nn++) {
		EpsRzz(mm,nn) = 1.0;
   }
  
/* set magnetic-field update coefficients */
  for (mm = 0; mm < SizeX; mm++)
    for (nn = 0; nn < SizeY - 1; nn++) {
      Chxh(mm, nn) = 1.0;
      Chxe(mm, nn) = Cdtds / imp0;
    }

  for (mm = 0; mm < SizeX - 1; mm++)
    for (nn = 0; nn < SizeY; nn++) {
      Chyh(mm, nn) = 1.0;
      Chye(mm, nn) = Cdtds / imp0;
    }
  for (mm = 0; mm < SizeX - 1; mm++)
    	for (nn = 0; nn < SizeY; nn++) {
  		MuRyy(mm, nn) = 1.0;
  }

  for (mm = 0; mm < SizeX; mm++)
	for (nn = 0; nn < SizeY - 1; nn++) {
		MuRxx(mm, nn) = 1.0;
	}

  return;
}
