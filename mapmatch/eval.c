/*
 * =====================================================================================
 *
 *       Filename:  eval.c
 *
 *    Description:  evaluate the correctness of mapping
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
#define MAXNODES 2048 /* WARNING: rather arbitrary choice!! */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "eval.h"

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  calcScore
 *  Description:  calculate score using output compared to the truth, along with the
 *                execution time
 *                args: output, truth, record count of output, execution time
 *                return: score
 * =====================================================================================
 */
float calcScore ( ResultRecord* output, ResultRecord* truth, int outcount, double exetime, FILE *resultfile ) {
	float score = 0;
	int i;
	int j = 0;
	int correct = 0;
	int wrong = 0;

	FILE *fp = fopen("E:\\zhanlj\\out\\miss.txt", "w");

	fprintf(fp, "id, result, truth\n");
	/* assuming both record lists are sorted, and each time only bind to one record in 
	 * truth set, which seems is the case */
	for (i = 0; i < outcount; i++) {
		if (truth[j].t != output[i].t) {
			j++;
		}

		if (output[i].edgeId == truth[j].edgeId) {
			score += output[i].confidence;
			correct++;
		}
		else {
			score -= output[i].confidence;
			wrong++;
			fprintf(fp, "%d, %ld, %ld\n", i, output[i].edgeId, truth[i].edgeId);
		}
	}

	score = score / exetime;

	printf("%d correct\n", correct);
	printf("%d wrong\n", wrong);
	printf("correct ratio is: %f\n", ((double)correct) / outcount * 100);
	fprintf(resultfile, "%d correct\n", correct);
	fprintf(resultfile, "%d wrong\n", wrong);
	fprintf(resultfile, "correct ratio is: %f\n", ((double)correct) / outcount * 100);

	fclose(fp);

	return score;
}		/* -----  end of function eval  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  readOutput
 *  Description:  read from output data
 *                args: container(need to be big enough for all the record), file name
 *                return: record count
 * =====================================================================================
 */
int readOutput ( ResultRecord* out_result, char *filename ) {
	int count = 0;
	FILE *fp = fopen(filename, "r");

	assert(fp != NULL);
	while(
		fscanf(fp, "%d,%d,%f", 
			&(out_result[count]).t,
			&(out_result[count]).edgeId,
			&(out_result[count]).confidence) > 0) {
		count++;
	}
	return count;
}		/* -----  end of function readOutput  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  eval
 *  Description:  The entrance to eval the world  
 * =====================================================================================
 */
int eval ( ResultRecord* output, int count, int interval, int i ) {
	TraceNode input[MAXRECORD];
	ResultRecord answer[MAXRECORD];
	char ansfile[1024];
	float anscount;
	FILE *result = fopen("E:\\zhanlj\\out\\result", "w");
	double score;
	
	sprintf(ansfile, "E:\\zhanljData\\GPSData\\output_%ds\\output_%d.txt", interval, i);
	
	anscount = readOutput( answer, ansfile );
	score = calcScore(output, answer, count, 1, result);

	/*printf("count of input: %d\n", readInput( input, "/home/geohpc/mapmatch/training_data/input/input_01.txt" ));*/
	/*printf("count of output: %d\n", readOutput( output, "/home/geohpc/mapmatch/training_data/output/output_02.txt" ));*/
	printf("score is: %f\n", score);
	fprintf(result, "score is: %f\n", score);

	fclose(result);
	return 0;
}				/* ----------  end of function eval ---------- */
