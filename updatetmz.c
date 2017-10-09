#include "fdtd-macro-tmz.h"
#include <stdio.h>
/* update magnetic field */
void updateB2d(Grid *g) {
  int mm, nn;

  if (Type == oneDGrid) {  /*@ \label{updatetmzA} @*/
    for (mm = 0; mm < SizeX - 1; mm++)
      By1(mm) = Chyh1(mm) * By1(mm) 
	+ Chye1(mm) * (Ez1(mm + 1) - Ez1(mm));
  } else { 
    for (mm = 0; mm < SizeX; mm++) /*@ \label{updatetmzB} @*/
      for (nn = 0; nn < SizeY - 1; nn++)
	Bx(mm, nn) = Chxh(mm, nn) * Bx(mm, nn) 
	  - Chxe(mm, nn) * (Ez(mm, nn + 1) - Ez(mm, nn));

    for (mm = 0; mm < SizeX - 1; mm++)
      for (nn = 0; nn < SizeY; nn++)
	By(mm, nn) = Chyh(mm, nn) * By(mm, nn) 
	  + Chye(mm, nn) * (Ez(mm + 1, nn) - Ez(mm, nn));
  }

  return;
}


void updateH2d(Grid *g) {
  int mm, nn;
  if (Type == oneDGrid) { 
     for (mm = 0; mm < SizeX - 1; mm++){
   	   Hy1(mm) = By1(mm)/MuR1(mm);
     }
  } else{
     for (mm = 0; mm < SizeX; mm++) 
        for (nn = 0; nn < SizeY - 1; nn++){
           Hx(mm,nn) = Bx(mm,nn)/MuRxx(mm,nn);
     }
     for (mm = 0; mm < SizeX - 1; mm++)
        for (nn = 0; nn < SizeY; nn++){
	    Hy(mm,nn) = By(mm,nn)/MuRyy(mm,nn);	
     }  
  }
  return;
}
/* update electric field */
void updateD2d(Grid *g) {
  int mm, nn;
  if (Type == oneDGrid) {  /*@ \label{updatetmzC} @*/
    for (mm = 1; mm < SizeX - 1; mm++)
      Dz1(mm) = Ceze1(mm) * Dz1(mm) 
	+ Cezh1(mm) * (Hy1(mm) - Hy1(mm - 1));
  } else { 

	/* Curl equations for the E field at the boundaries*/
    

   
    for (mm = 1; mm < SizeX - 1; mm++){
	CurlH(mm, 0) = ((Hy(mm,0) - Hy(mm -1, 0)) - (Hx(mm,0) - Hx(mm, SizeY -2)));
	CurlH(mm, SizeY -1) = ((Hy(mm,0) - Hy(mm -1, 0)) - (Hx(mm,0) - Hx(mm, SizeY-2)));
    }
        
    CurlH(SizeX-1, SizeY-1) = ((Hy(0,0) - Hy(SizeX -2, SizeY-2)) - (Hx(0,0) - Hx(SizeX-2, SizeY -2)));


    for (mm = 1; mm < SizeX - 1; mm++)
      for (nn = 1; nn < SizeY - 1; nn++){
         CurlH(mm,nn)=  ((Hy(mm, nn) - Hy(mm - 1, nn)) -
                       (Hx(mm, nn) - Hx(mm, nn - 1)));
//	printf("CurlH is %f \n", CurlH(mm, nn));
	}    

    for (mm = 1; mm < SizeX-1; mm++)
      for (nn = 0; nn < SizeY; nn++)
//	temp  = CurlH(mm, nn);
//	printf("CurlH is %f \n",temp);
	Dz(mm, nn) = Ceze(mm, nn) * Dz(mm, nn) +
  	    Cezh(mm, nn) *CurlH(mm,nn);
    }

  return;
}

void updateE2d(Grid *g){
   int mm, nn;
   if (Type == oneDGrid) {  /*@ \label{updatetmzC} @*/
    for (mm = 1; mm < SizeX - 1; mm++)
        Ez1(mm) = Dz1(mm)/EpsR1(mm);
   } else {
        for (mm = 0; mm < SizeX; mm++)
           for (nn = 0; nn < SizeY; nn++)
                Ez(mm,nn) = Dz(mm,nn)/EpsRzz(mm,nn);
  }
return;
}



