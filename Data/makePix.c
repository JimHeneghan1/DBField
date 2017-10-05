// To compile, run and look at the image on OSX do the following:
// gcc makepix.c -o makepix
// ./makepix
// convert -identify raw2.196.pgm raw2.196.png
// open raw2.196.png



#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Image and array constants
#define IMAX 2002 
#define JMAX 80
#define CMAX 65535
#define MAX (IMAX*JMAX)

// File constants
#define FMAX 399

int main()
{
  // Array of two-byte unsigned integers
  unsigned short ix[MAX];
  float x[MAX];
  FILE *dest;
  FILE *source;
  float temp, MaxVal = -9999;
  char filename[100];
  char filenamedest[100];
  int i, j;


  // I  read only one file here so I have changed the loop
  for(j = 1; j<=FMAX; j++){
    sprintf(filename, "Test1.%d.dat", j);
    printf("%s\n", filename);
    source = fopen(filename, "r");
    i = 0;
    while (i < MAX){      
      fscanf(source, "%f", &temp);     
      //fread(&temp, sizeof(float), 1, source);
      x[i] = fabs(temp);
      // Calculate the maximum value
      if(MaxVal<x[i]) {
	MaxVal = x[i];
      }
      i++;
    }

     fclose(source);
  }

  printf("---> %f\n", MaxVal);

 for(j = 1; j<=FMAX; j++){
   sprintf(filename, "Test1.%d.dat", j);
   source = fopen(filename, "r");
   // Normalize to CMAX
   i = 0;
   while (i < MAX){
     fscanf(source, "%f", &temp);     
     //fread(&temp, sizeof(float), 1, source);
     x[i] = fabs(temp);
/*
*     The following if else statement creates greater image resolution 
*     for field strengths of less than half the maximum value. 
*     All values greater than Maxval/2 are set to the maximum
*/
 /*
    if(x[i] > (MaxVal/10))
     	ix[i] = (int) (CMAX);
     else
     	ix[i] = (int) (x[i]*CMAX*10)/MaxVal;
 */ 
     ix[i] = (int) (x[i]*CMAX)/MaxVal;
     // The byte or for 16 bit pgm files need to be big endian
     ix[i] = (ix[i]>>8) | (ix[i]<<8);
     i++;
   }
   fclose(source);

   // Output the 16 bit portable gray map file
   sprintf(filenamedest, "Test1/Test1.%d.pgm", j);
   dest = fopen(filenamedest, "wb");

   // Print the pgm file header
   fprintf(dest, "P5 \n");
   fprintf(dest, "%d %d\n", IMAX, JMAX);
   fprintf(dest, "%d\n", CMAX);

   // Print the image data
   fwrite(ix, sizeof(unsigned short), sizeof(ix) , dest);
   fclose(dest);
 }
 
  return 0;
}
