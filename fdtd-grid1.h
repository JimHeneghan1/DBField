#ifndef _FDTD_GRID1_H
#define _FDTD_GRID1_H

enum GRIDTYPE{oneDGrid, teZGrid, tmZGrid, threeDGrid};

struct Grid{
	double *hx, *chxh, *chxe, *curlH;
	double *hy, *chyh, *chye;
	double *hz, *chzh, *chze;
	double *ex, *cexe, *cexh;
	double *ey, *ceye, *ceyh;
	double *ez, *ceze, *cezh;
	double *dz, *epsRzz, *epsR;
	int sizeX, sizeY, sizeZ;
	int time, maxTime;
	int type;
	double cdtds;
};

typedef struct Grid Grid;

#endif
