/*
 * =====================================================================================
 *
 *       Filename:  mapmatch.c
 *
 *    Description:  the map match algorithm
 *
 *        Version:  1.0
 *        Created:  07/02/2012 08:43:57 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YANG Anran (), 08to09@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

#include "data.h"
#include "io.h"
#include "geoutils.h"
#include "memoryAllocate.h"
#include "st.h"
#include "findMatchedSequence.h"
#include "libs/bigzaphod-astar/AStar.h"
#include "eval.h"

#define MAXINPUT 5000 /* max record count of inputs */
#define MAX_MAXCAND 200
#define GPSTOLERANCE 20 /* gps tolerance, unit: m */
#define MAXSPEED 30 /* max speed per second */
#define MAXCANREACHED 5000 /* the max number of possible nodes which lies in the reachable regions of two adjecent trace nodes */
/*#define WINSIZE 5 [> smoothing window size <]*/
#define COSANGLETOL 0 /* angle tolerance by cos, now is the most tolerable */

#define DELTA 10 /* standard deviation of N */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  getBound
 *  Description:  get the bound of trace node, enlarged by given error tolerances
 * =====================================================================================
 */
Bound getBound(TraceNode *input, int count, double xtol, double ytol) {
	Bound result;
	int i;

	result.lx = input->data.x;
	result.rx = input->data.x;
	result.by = input->data.y;
	result.ty = input->data.y;

	for (i = 1; i < count; i++) {
		extendBound(input[i].data.x, input[i].data.y, &result);
	}

	result.lx = result.lx - xtol;
	result.rx = result.rx + xtol;
	result.by = result.by - ytol;
	result.ty = result.ty + ytol;

	return result;
} /* -----  end of function getBound  ----- */

int cmpCand ( const void *a , const void *b )
{
	return ((Candidate*)a)->distance - ((Candidate*)b)->distance;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  rectBuffer
 *  Description:  get rectangle buffer of a point
 * =====================================================================================
 */
Bound rectBuffer(Point *p, double tol) {
	Bound nodebox;

	nodebox.lx = p->x - tol;
	nodebox.rx = p->x + tol;
	nodebox.by = p->y - tol;
	nodebox.ty = p->y + tol;

	return nodebox;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  match
 *  Description:  The match algorithm. return the output record count
 * =====================================================================================
 */
int match(TraceNode *input, long inputcount, ResultRecord *output, Roads *datasource) {
	const int MAXCAND = 5;
	FILE* fdebug;
	long i, j, k, l, m;
	long outputcount = inputcount;
	Edge *e;
	Bound tracebox;
	Bound nodebox;
	double distance;
	
	Candidate **candsets = malloc_Array2D_Candidate(inputcount, MAXCAND);
	int *fit = (int*)malloc(sizeof(int) * inputcount);

	double ytol = GPSTOLERANCE + MAXSPEED;
	double xtol = GPSTOLERANCE + MAXSPEED;
	Point *head;
	Point *tail;
	SubRoads *data;
	Candidate candcandset[MAX_MAXCAND];
	int candcandcount;
	Candidate candbuf;
	Point nearest;
	double **obsePiblity = malloc_Array2D_Double(inputcount, MAXCAND);
	int *candcounts = (int*)malloc(sizeof(int) * inputcount);
	double **transitionF = malloc_Array2D_Double(inputcount, MAXCAND*MAXCAND);
	int *result = (int*)malloc(sizeof(int) * inputcount);
	int **parent = malloc_Array2D_Int(inputcount, MAXCAND);
	double **score = malloc_Array2D_Double(inputcount, MAXCAND);

	double maxleavedist;
	Bound candbox1;
	Bound candbox2;
	NodeSet searched;
	searched.refs = (Node**)malloc(sizeof(Node*) * MAXCANREACHED);
	memset(searched.refs, 0, sizeof(Node*) * MAXCANREACHED);

	for (i = 0; i < outputcount; i++) {
		output[i].t = input[i].t;
	}

	for (i = 0; i < inputcount; i++) {
		fit[i] = 0;
	}

	//printf("clip...\n");
	tracebox = getBound(input, inputcount, xtol, ytol);
	data = regionSelect(datasource, &tracebox);

	//printf("calculate candsets...\n");
	/* for each trace node */
	for (k = 0; k < inputcount; k++) {
		candcandcount = 0;
		/* for each segment */
		for (i = 0; i < data->edgecount; i++) {
			for (j = 0; j < data->edgerefs[i]->pointcount - 1; j++) {
				head = &data->edgerefs[i]->pointlist[j];
				tail = &data->edgerefs[i]->pointlist[j + 1];
				/*printf("%ld,%ld\n", i, j);*/
				/* if the segment's bbox does not overlap the trace's, skip it */
				/*if (!lineBoundOverBound(head, tail, &tracebox)) {*/
				/*continue;*/
				/*}*/

				/* if the segment not overlap with node buffer, skip */
				nodebox = rectBuffer(&input[k].data, GPSTOLERANCE);
				if(!lineBoundOverBound(head, tail, &nodebox)) {
					continue;
				}

				/* calculate distance */
				distance = point2linedist(&input[k].data, head, tail, &nearest);

				if( distance < GPSTOLERANCE) {
					candbuf.distance = distance;
					candbuf.edge = data->edgerefs[i];
					candbuf.segId = j;
					candbuf.nextNode = data->edgerefs[i]->tail;
					candbuf.prevNode = data->edgerefs[i]->head;
					candbuf.loc = nearest;

					candcandset[candcandcount] = candbuf; 
					candcandcount++;
				}

				/* select top MAXCAND candcand */
				if(candcandcount > MAXCAND) {
					qsort(candcandset, candcandcount, sizeof(Candidate), cmpCand);
					candcounts[k] = MAXCAND;
				}
				else {
					candcounts[k] = candcandcount;
				}
				
				for(l = 0; l < candcounts[k]; l++) {
					candsets[k][l] = candcandset[l];
				}
			}
		}
		/*if (k%100 == 0 && k > 0) {
			printf("%ld processed\n", k);
		}*/
	}

	//printf("calculate candgraph\n");
	for(i = 0; i < inputcount; i++) {
		for(j = 0; j < candcounts[i]; j++) {
			obsePiblity[i][j] = guassian(candsets[i][j].distance, DELTA);
		}
	}

	for(i = 0; i < inputcount - 1; i++) {
		for(j = 0; j < candcounts[i]; j++) {
			for(k = 0; k < candcounts[i + 1]; k++) {
				/* if two cands are on the opposite road, mark them as disconnected */
				if(candsets[i][j].prevNode->id == candsets[i + 1][k].nextNode->id) {
					/*if(i == 87) {
						printf("87th, %ld with %ld\n", j, k);
					}*/
					transitionF[i][j * MAXCAND + k] = -10000;
				}
				else if(candsets[i][j].edge->id == candsets[i + 1][k].edge->id
					&& candsets[i][j].segId > candsets[i + 1][k].segId) {
						transitionF[i][j * MAXCAND + k] = -20;
				}
				else if(candsets[i][j].edge->id == candsets[i + 1][k].edge->id
					&& candsets[i][j].segId == candsets[i + 1][k].segId
					&& (
					(candsets[i][j].loc.x > candsets[i + 1][k].loc.x 
					&& candsets[i][j].edge->pointlist[candsets[i][j].segId].x < candsets[i][j].edge->pointlist[candsets[i][j].segId + 1].x)
					|| (candsets[i][j].loc.x < candsets[i + 1][k].loc.x 
					&& candsets[i][j].edge->pointlist[candsets[i][j].segId].x > candsets[i][j].edge->pointlist[candsets[i][j].segId + 1].x)
					)) {
						transitionF[i][j * MAXCAND + k] = -20;
				}
				else if((candsets[i][j].nextNode->id == candsets[i + 1][k].nextNode->id 
					&& candsets[i][j].prevNode->id != candsets[i + 1][k].prevNode->id)
					|| (candsets[i][j].prevNode->id == candsets[i + 1][k].prevNode->id 
					&& candsets[i][j].nextNode->id != candsets[i + 1][k].nextNode->id)) {
						transitionF[i][j * MAXCAND + k] = -10000;
				}
				else {
					/* get nodes should be searched */
					maxleavedist = MAXSPEED * (input[i + 1].t - input[i].t); 
					candbox1 = rectBuffer(&candsets[i][j].loc, maxleavedist);
					candbox2 = rectBuffer(&candsets[i + 1][k].loc, maxleavedist);

					searched.headnext = candsets[i][j].nextNode;
					searched.tailprev = candsets[i + 1][k].prevNode;
					searched.firstlen = candsets[i][j].edge->length;
					searched.lastlen = candsets[i + 1][k].edge->length;

					searched.refs[0] = candsets[i][j].prevNode;
					searched.refs[1] = candsets[i + 1][k].nextNode;
					searched.count = 2;
					for(l = 0; l < data->nodecount; l++) {
						if(inBound(&data->noderefs[l]->loc, &candbox1)
							|| inBound(&data->noderefs[l]->loc, &candbox2)) {
								searched.refs[searched.count] = data->noderefs[l];
								searched.count++;
						}
					}
					/*if(i == 98) {
						printf("%ldth, %ld with %ld\n", i, j, k);
					}*/
					transitionF[i][j * MAXCAND + k] = stFunc(&input[i], &input[i + 1],
						&candsets[i][j], &candsets[i + 1][k], &searched);
				}
			}
		}
		
		
		/*if (i%100 == 0 && i > 0) {
			printf("%ld processed\n", i);
		}*/
	}

	/* correct conditions where no candidates are given */
	for(i = 0; i < inputcount; i++) {
		if(candcounts == 0) {
			candsets[i][0].edge = NULL;
			candcounts[i] = 1;
			obsePiblity[i][0] = 0;
			
			for(j = 0; j < MAXCAND; j++) {
				if(i > 0) {
					transitionF[i - 1][j * MAXCAND] = -0.001;
				}
				if(i < inputcount - 1) {
					transitionF[i][j] = -0.001;
				}
			}
		}
	}
	//printf("find sequence\n");
	findMatchSequence(transitionF, obsePiblity, candcounts, inputcount, score, parent, result);

	for(i = 0; i < inputcount; i++) {
		if(NULL == candsets[i][result[i]].edge) {
			output[i].edgeId = -1;
		}
		else {
			output[i].edgeId = candsets[i][result[i]].edge->id;
		}
	}

	/*fdebug = fopen("E:\\zhanlj\\out\\debug.txt", "w");
	for(i = 0; i < inputcount - 1; i++) {
		fprintf(fdebug, "%d: %lf\n", i, transitionF[i][result[i] * MAXCAND + result[i + 1]]);
	}
	fclose(fdebug);*/

	/*printf("smoothing start\n");*/

	/*for (i = WINSIZE / 2; i < outputcount - WINSIZE / 2; i++) {*/
		/* if at least 1 node on head and 2 nodes on tail say they are on the 
		 * same road, or vice versa,  set the center point to the road */
		/*if (output[i - WINSIZE / 2].edgeId == output[i + WINSIZE / 2].edgeId) {*/
			/*if (*/
					/*output[i - WINSIZE / 2 + 1].edgeId == output[i - WINSIZE / 2].edgeId ||*/
					/*output[i + WINSIZE / 2 - 1].edgeId == output[i - WINSIZE / 2].edgeId */
					/*) {*/
					/*output[i].edgeId = output[i - WINSIZE / 2].edgeId;*/
			/*}*/
		/*}*/

		/*if (i%1000 == 0 && i > 0) {*/
			/*printf("%ld processed\n", i);*/
		/*}*/
	/*}*/

	freeSelection(data);
	free(fit);
	free(candcounts);
	free(searched.refs);
	free_Array2D_Candidate(candsets);
	free_Array2D_Double(transitionF);
	free_Array2D_Double(obsePiblity);
	free(result);
	free_Array2D_Int(parent);
	free_Array2D_Double(score);

	return inputcount;
}

ResultRecord *makeOutput(int count) {
	int i, j;

	ResultRecord *output = (ResultRecord*)malloc(count * sizeof(ResultRecord));
	for (i = 0; i < count; i++) {
		output[i].t = 0;
		output[i].edgeId = -1;
		output[i].confidence = 1;
		/*output[i].next = NULL;*/
	}
	
	return output;
}

void freeOutput(ResultRecord *output, int count) {
	/*int i;*/
	/*ResultRecord *cursor;*/
	/*ResultRecord *temp = cursor;*/

	/*for (i = 0; i < count; i++) {*/
		/*cursor = output[i].next;*/
		/*while(cursor != NULL) {*/
			/*temp = cursor->next;*/
			/*free(cursor);*/
			/*cursor = temp;*/
		/*}*/
	/*}*/
	free(output);
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  The entrance of the world  
 * =====================================================================================
 */
int main ( int argc, char *argv[] ) {
	long count;
	char nodeFile[1024];
	char edgeFile[1024];
	char geometryFile[1024];
	char inputFile[1024];
	char outputFile[1024];
	int inputId = 1;
	Roads *dataptr;
	TraceNode input[MAXINPUT];
	ResultRecord *output;

	long i;

	memset(nodeFile, '\0', 1024);
	memset(edgeFile, '\0', 1024);
	memset(geometryFile, '\0', 1024);

	sprintf(nodeFile, "%s\\WA_Nodes.txt", argv[1]);
	sprintf(edgeFile, "%s\\WA_Edges.txt", argv[1]);
	sprintf(geometryFile, "%s\\WA_EdgeGeometry.txt", argv[1]);

	dataptr = readRoads(nodeFile, edgeFile, geometryFile);

	output = makeOutput(MAXINPUT);

	while(1) {
		memset(inputFile, '\0', 1024);

		if(inputId < 10) {
			sprintf(inputFile, "%s\\input_0%d.txt", argv[2], inputId);
		}
		else {
			sprintf(inputFile, "%s\\input_%d.txt", argv[2], inputId);
		}

		count = readInput(input, inputFile);
		if(count < 0) {
			break;
		}

		count = match(input, count, output, dataptr);

		memset(outputFile, '\0', 1024);

		if(inputId < 10) {
			sprintf(outputFile, "%s\\output_0%d.txt", argv[3], inputId);
		}
		else {
			sprintf(outputFile, "%s\\output_%d.txt", argv[3], inputId);
		}

		writeOutput(output, count, outputFile);

		inputId++;
	}

	freeOutput(output, MAXINPUT);
	freeRoads(dataptr);

	return 0;
}				/* ----------  end of function main  ---------- */
