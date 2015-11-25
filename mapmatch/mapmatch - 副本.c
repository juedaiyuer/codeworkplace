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
#include "libs/bigzaphod-astar/AStar.h"

#define MAXINPUT 5000 /* max record count of inputs */
#define GPSTOLERANCE 20 /* gps tolerance, unit: m */
#define MAXSPEED 30 /* max speed per second */
/*#define WINSIZE 5 [> smoothing window size <]*/
#define COSANGLETOL 0.70706 /* angle tolerance by cos, not yet carefully designed. Values around here get similar scores
						  (and takes much improvement compared to the program without it), 
						  but many trace node cannot find a solution. */

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

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  match
 *  Description:  The match algorithm. return the output record count
 * =====================================================================================
 */
int match(TraceNode *input, long inputcount, ResultRecord *output, Roads *datasource) {
	long i, j, k, l, m;
	long outputcount = inputcount;
	Edge *e;
	Bound tracebox;
	Bound nodebox;
	double distance;
	double *shortest = (double*)malloc(sizeof(double) * inputcount);
	int *fit = (int*)malloc(sizeof(int) * inputcount);

	double ytol = GPSTOLERANCE + MAXSPEED;
	double xtol = GPSTOLERANCE + MAXSPEED;
	Point *head;
	Point *tail;
	SubRoads *data;

	for (i = 0; i < outputcount; i++) {
		shortest[i] = -1;
		output[i].t = input[i].t;
	}

	for (i = 0; i < inputcount; i++) {
		fit[i] = 0;
	}

	tracebox = getBound(input, inputcount, xtol, ytol);
	data = regionSelect(datasource, &tracebox);

	printf("least distance matching start...\n");
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
			/* for each trace node */
			for (k = 0; k < inputcount; k++) {
				/* if the segment not overlap with node buffer, skip */
				nodebox.lx = input[k].data.x - xtol;
				nodebox.rx = input[k].data.x + xtol;
				nodebox.by = input[k].data.y - ytol;
				nodebox.ty = input[k].data.y + ytol;
				if(!lineBoundOverBound(head, tail, &nodebox)) {
					continue;
				}

				/*if(k != inputcount - 1) {
				printf("angle %lf", cosangle(tail->x - head->x, tail->y - head->y,
						input[k + 1].data.x - input[k].data.x, 
						input[k + 1].data.y - input[k].data.y)); }*/
				/* if the direction is wrong, skip */
				if (
						k != inputcount - 1 &&
						cosangle(tail->x - head->x, tail->y - head->y,
						input[k + 1].data.x - input[k].data.x, 
						input[k + 1].data.y - input[k].data.y) < COSANGLETOL) {
					if (fit[k]) {
						continue;
					}
				}
				else {
					fit[k] = 1;
					output[k].edgeId = -1; /* remove previous direction-not-fit match */
				}

				/* calculate distance */
				distance = point2linedist(&input[k].data, head, tail);
				/*if (data->edgerefs[i]->id == 1111656 && k == 15) {
					printf("%.10lf at seg %ld\n", dist(&data->edgerefs[i]->head->loc, &input[k].data), j);
					printf("%.10lf at seg %ld\n", dist(&data->edgerefs[i]->tail->loc, &input[k].data), j);
					printf("head %lf, %lf\n", head->x, head->y);
					printf("tail %lf, %lf\n", tail->x, tail->y);
					printf("bound %lf,%lf,%lf,%lf\n", nodebox.by, nodebox.ty, nodebox.lx, nodebox.rx);
				}*/
				/*printf("dist is: %lf\n", dist);*/

				/* if it is the first node encountered, record this simply */
				if (output[k].edgeId == -1) {
					/*if (i == 33545 && j == 5 && k == 0) {*/
						/*printf("first time\n");*/
					/*}*/
					shortest[k] = distance;
					output[k].edgeId = data->edgerefs[i]->id;
				}
				/* if the distance is shortest ever, record this */
				else if (shortest[k] < distance) {
					/*if (i == 33545 && j == 5 && k == 0) {*/
						/*printf("defeat others\n");*/
					/*}*/
					/*if (k == 0 && i > 33545) {*/
						/*printf("defeated by %ld, dist is %lf\n", i, dist);*/
					/*}*/
					shortest[k] = distance;
					output[k].edgeId = data->edgerefs[i]->id;
				}
			}
		}
		if (i%2000 == 0 && i > 0) {
			printf("%ld processed\n", i);
		}
	}

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
	free(shortest);

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
	long rescount;
	//Roads *dataptr = readRoads(
	//		"E:\\zhanlj\\RoadNetworkData\\nodes_test.txt",
	//		"E:\\zhanlj\\RoadNetworkData\\edges_test.txt",
	//		"E:\\zhanlj\\RoadNetworkData\\geometry_test.txt"
	//		);

	Roads *dataptr = readRoads(
			"E:\\zhanlj\\RoadNetworkData\\WA_Nodes.txt",
			"E:\\zhanlj\\RoadNetworkData\\WA_Edges.txt",
			"E:\\zhanlj\\RoadNetworkData\\WA_EdgeGeometry.txt"
			);

	/*long i;*/
	/*double maxspeed = 0;*/
	/*double speed;*/

	/*for (i = 0; i < dataptr->edgecount; i++) {*/
		/*if (dataptr->edgerefs[i].cost == 0) {*/
			/*continue;*/
		/*}*/
		/*speed = dataptr->edgerefs[i].length / dataptr->edgerefs[i].cost;*/
		/*if (speed > maxspeed) {*/
			/*maxspeed = speed;*/
		/*}*/
	/*}*/
	/*printf("max speed limit is: %lf\n", maxspeed);*/

	TraceNode input[MAXINPUT];
	ResultRecord *output = makeOutput(MAXINPUT);
	long count = readInput(input, "E:\\zhanlj\\GIS_Contest_Training_Data\\input\\input_01.txt");
	/*long count = readInput(input, "E:\\zhanlj\\GIS_Contest_Training_Data\\input\\input_test.txt")*/;

	rescount = match(input, count, output, dataptr);

	writeOutput(output, rescount, "E:\\zhanlj\\out\\output_01.txt");
	/*writeOutput(output, rescount, "E:\\zhanlj\\out\\output_test.txt");*/

   /* Node *from = &dataptr->nodelist[0];*/
	/*Node *to = &dataptr->nodelist[4];*/

	/*ASPathNodeSource graph = {*/
		/*sizeof(Node),*/
		/*&buildNeighbors,*/
		/*&heuristic,*/
		/*NULL,*/
		/*NULL*/
	/*};*/

	/*ASPath path = ASPathCreate(&graph, NULL, from, to);*/

	/*printf("%lf\n", ASPathGetCost(path));*/

    /*ASPathDestroy(path);*/

	freeOutput(output, MAXINPUT);
	freeRoads(dataptr);

	/*Point p1;*/
	/*Point p2;*/
	/*Point p3;*/
	/*p1.y = 47.812968;*/
	/*p1.x = -122.374842;*/
	/*p2.y = 47.813;*/
	/*p2.x = -122.374955;*/
	/*p3.y = 47.812174;*/
	/*p3.x = -122.374844;*/

	/*[>printf("%lf\n", point2linedist(&p2, &p1, &p3));<]*/
	/*printf("%lf\n", distance(&p2, &p1));*/

	/*printf("%lf\n", guassian(0, 20));*/

	return 0;
}				/* ----------  end of function main  ---------- */
