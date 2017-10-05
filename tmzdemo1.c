/* TMz simulation with Ricker source at center of grid. */

#include "fdtd-alloc1.h"
#include "fdtd-macro-tmz.h"
#include "fdtd-proto1.h"
#include "ezinc.h"

int main()
{
  Grid *g;

  ALLOC_1D(g, 1, Grid); // allocate memory for Grid

  gridInit(g);        // initialize the grid
  abcInit(g);     // initialize ABC
  tfsfInit(g);    //initialize TFSF boundary
 // ezIncInit(g);
  snapshotInit2d(g);  // initialize snapshots

  /* do time stepping */
  for (Time = 0; Time < MaxTime; Time++) {
    updateH2d(g);     // update magnetic field
    tfsfUpdate(g);          //apply TFSF boundary
    updateE2d(g);     // update electric field
    updateD2d(g);
    //Ez(30, 30) = ezInc(Time, 0.0); // add a source /*@ \label{tmzdemo1A} @*/
    abc(g);                 //apply ABC     
    Transmission(g, Time);
    snapshot2d(g);    // take a snapshot (if appropriate)
  } // end of time-stepping

  return 0;
}
