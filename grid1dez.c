#include <math.h>
#include "fdtd-macro-tmz.h"
#include "fdtd-alloc1.h"

#define NLOSS 20		//number of lossy cells at end of 1D grid
#define MAX_LOSS 0.35	//maximum loss factor in lossy layer

void gridInit1d(Grid *g){
	double imp0 = 377.0, depthInLayer, lossFactor;
	int mm;

	SizeX += NLOSS;		//size of domain
	Type = oneDGrid;	//set grid type

	ALLOC_1D (g->hy,	SizeX - 1, double);
	ALLOC_1D (g->chyh,	SizeX - 1, double);
	ALLOC_1D (g->chye,	SizeX - 1, double);
	ALLOC_1D (g->ez,	SizeX - 1, double);
	ALLOC_1D (g-> ceze,	SizeX - 1, double);
	ALLOC_1D (g->cezh,	SizeX - 1, double);
	ALLOC_1D (g->dz,        SizeX - 1, double);
        ALLOC_1D (g->epsR,      SizeX - 1, double);
	ALLOC_1D (g->by,        SizeX - 1, double);
	ALLOC_1D (g->muR,       SizeX - 1, double);
	/* set the E and H field update coefficients */

	for (mm = 0; mm < SizeX - 1; mm++){
		if (mm < SizeX - 1 - NLOSS){
			Ceze1(mm) = 1.0;
			Cezh1(mm) = Cdtds * imp0;
			Chyh1(mm) = 1.0;
			Chye1(mm) = Cdtds / imp0;
			EpsR1(mm) = 1.0;
			MuR1(mm) = 1.0;
		} else {
			depthInLayer = mm - (SizeX - 1- NLOSS) + 0.5;
			lossFactor = MAX_LOSS * pow(depthInLayer / NLOSS, 2);
			Ceze1(mm) = (1 - lossFactor) / (1.0 + lossFactor);
			Cezh1(mm) = Cdtds * imp0 / (1.0 + lossFactor);
			depthInLayer += 0.5;
			lossFactor = MAX_LOSS * pow(depthInLayer / NLOSS, 2);
			Chyh1(mm) = (1.0 - lossFactor) / (1.0 + lossFactor);
			Chye1(mm) = Cdtds / imp0 / (1.0 + lossFactor);
			EpsR1(mm) = 1.0;
                        MuR1(mm) = 1.0;
		}
	}
	return;
}
