#include "ezinc.h"

//static double cdtds, ppw = 0;

/* initialize source-function variables */
void ezIncInit(Grid *g){

  //printf("Enter the points per wavelength for Ricker source: ");
  //scanf(" %lf", &ppw);
/*
  ppw = 30;
  cdtds = Cdtds;   
  return;*/
}

/* calculate source function at given time and location */
double ezInc(double time, double location) {
/*
  double arg;

  if (ppw <= 0) {
    fprintf(stderr,
       "ezInc: ezIncInit() must be called before ezInc.\n"
       "       Points per wavelength must be positive.\n");
    exit(-1);
  }

  arg = M_PI * ((cdtds * time - location) / ppw - 1.0);
  arg = arg * arg;

  return (1.0 - 2.0 * arg) * exp(-arg);
*/
	double arg, arg1, arg2, pulse, pulse2;
        int tstep = time;

        int res = 161;
        double c0 = 2.998e8;
        double lambda = 800.0e-9;
        double omega = 2*M_PI*c0/lambda;
        double dx = lambda/res;
        double dt = dx/(sqrt(2.0)*c0);
        double Tau = 2*res*dt;
        double tdelay = 5*Tau;

        arg = tstep*dt - tdelay;
        arg1 = arg/Tau;
        arg2 = arg1*arg1/2.0;
        pulse = exp(-arg2);
        pulse2 = pulse*cos(omega*arg);

	return pulse2;
}
