/*
 * =====================================================================================
 *
 *       Filename:  io.c
 *
 *    Description:  dealing with inputs and outputs
 *
 *        Version:  1.0
 *        Created:  06/27/2012 11:12:49 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YANG Anran (), 08to09@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#define MAXRECORD 5000

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "io.h"
#include "geoutils.h"

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  readInput
 *  Description:  read from input data
 *                args: container(need to be big enough for all the record), file name
 *                return: record count
 * =====================================================================================
 */
int readInput ( TraceNode* out_result, char *filename ) {
	int count = 0;
	FILE *fp = fopen(filename, "r");
	double lon, lat;

	projPJ pj;
	const char *prjType = "+proj=tmerc +ellps=WGS84 +lat_0=0 +lon_0=-120 +units=m +k=1.0";

	pj = pj_init_plus(prjType);

	if(fp == NULL) {
		return -1;
	}
	while( 
		fscanf_s(fp, "%d,%lf,%lf", 
			&out_result[count].t, 
			&lat, 
			&lon) > 0){
		out_result[count].data = project(pj, lon, lat);
		/*printf("latlon %lf,%lf\n", lat, lon);
		printf("xy %lf,%lf\n", out_result[count].data.x, out_result[count].data.y);*/
		count++;
	}

	pj_free(pj);

	fclose(fp);
	return count;
}		/* -----  end of function readInput  ----- */


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  writeOutput
 *  Description:  write to output file
 * =====================================================================================
 */
void writeOutput ( ResultRecord *result, int count, char *filename ) {
	int i, j;
	FILE *fp = fopen(filename, "w");

	for (i = 0; i < count; i++) {
		fprintf(fp, "%ld,%ld,%lf\n", 
				result[i].t, 
				result[i].edgeId, 
				result[i].confidence);
	}
	fclose(fp);
}		/* -----  end of function writeOutput  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  The entrance of the world  
 * =====================================================================================
 */
/*int main ( int argc, char *argv[] ) {*/
	/*TraceNode input[MAXRECORD];*/
	/*ResultRecord output[MAXRECORD];*/
	/*float count = readOutput( output, "/home/geohpc/mapmatch/training_data/output/output_01.txt" );*/
	/*[>printf("count of input: %d\n", readInput( input, "/home/geohpc/mapmatch/training_data/input/input_01.txt" ));<]*/
	/*[>printf("count of output: %d\n", readOutput( output, "/home/geohpc/mapmatch/training_data/output/output_02.txt" ));<]*/
	/*return 0;*/
/*}				[> ----------  end of function main  ---------- <]*/
