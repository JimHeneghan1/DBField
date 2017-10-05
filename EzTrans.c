#include <stdio.h>
#include <stdlib.h>
#include "fdtd-macro-tmz.h"

void Transmission(Grid *g, double time){
        char filename[100];
        double Time1;
        FILE *out;

        sprintf(filename, "Coefficients/Ez900.txt");
        out = fopen(filename, "a");
        Time1 = time*9.62e-18;
        /* print the time stamp and the Ex field right before the QWS*/
        fprintf(out, "%f \t %f \n", Time1, Ez(900, 40));
        fclose(out);

	sprintf(filename, "Coefficients/Ez200.txt");
        out = fopen(filename, "a");
        Time1 = time*9.62e-18;
        /* print the time stamp and the Ex field right before the QWS*/
        fprintf(out, "%f \t %f \n", Time1, Ez(200, 40));
        fclose(out);
}//end of Transmission

