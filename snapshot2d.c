//snapshot2D.c
//a code to output the data generated to an image format
//currenttly outputting in ASCII but binary output files are commented out

#include <stdio.h>
#include <stdlib.h>
#include "fdtd-macro-tmz.h"

static int temporalStride = -2, frame = 0, startTime;
static char basename[80];

void snapshotInit2d(Grid *g){

	int choice;
	
	printf("Do you want 2D snapshots? (1 for yes, 0 for no) \n");
	scanf("%d", &choice);
	printf("%d\n", choice);
	if (choice == 0) {
		temporalStride = -1;
		return;
	}

	printf("Duration of Simulation is %d steps. \n", MaxTime);
	printf("Enter start time and temporal stride: ");
	scanf(" %d %d", &startTime, &temporalStride);
	printf("Enter the base name: ");
	scanf(" %s", basename);

	return;
}


void snapshot2d(Grid *g) {
	int mm, nn;
	float /*dim1, dim2, */temp;
	char filename[100];
	FILE *out /*,*pgm*/;

	/* ensure temporal stride set to a reasonable value */
	if (temporalStride == -1) {
		return;
	} if (temporalStride < -1) {
		fprintf(stderr,
			"snapshot2d: snapshotInit2d must be called before snapshot.\n"
			" Temporal stride must be set to positive value.\n");
		exit(-1);
	}

	/* get snapshot if temporal conditions met */
	if (Time >= startTime &&
		(Time - startTime) % temporalStride == 0) {
		sprintf(filename, "Data/%s.%d.dat", basename, frame++);
		//out = fopen(filename, "wb");
		out = fopen(filename, "w");
	/*write dimensions to output file, express dimensions as floats*/
		//dim1 = (endNodeX - startNodeX)/ spatialStrideX -1;
		//dim2 = (endNodeY - startNodeY)/ spatialStrideY -1;

		//fwrite(&dim1, sizeof(float), 1, out);
		//fwrite(&dim2, sizeof(float), 1, out);

		/* write remaining data*/
		for(nn = SizeY -2; nn >= 0; nn--)
			for(mm = 0; mm <= SizeX; mm++){
				temp = (float)Ez(mm,nn); //store data as a float
				fprintf(out, "%f  \n", temp);
				//fwrite(&temp, sizeof(float), 1, out); // write the float
			}
	fclose(out); // close file

	}
	//printf("the grid is %g by %g", dim1, dim2);
	return;
}
