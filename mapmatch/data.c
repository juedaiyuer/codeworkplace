/*
 * =====================================================================================
 *
 *       Filename:  data.c
 *
 *    Description:  the data structure and io method
 *
 *        Version:  1.0
 *        Created:  06/28/2012 08:58:41 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YANG Anran (), 08to09@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
/* WARNING: Here I may use some int when it should be long */
#include <stdlib.h>
#include <assert.h>

#include "textutils.h"
#include "data.h"
#include "geoutils.h"

#define MAXPOINTS 20000000
#define NODES 0
#define EDGES 1
#define EDGESREF 2
#define POINTS 3
#define TOKENS 4

#ifdef PROF
#define PROFMEM(id, size) profmem(id, size)
#else
#define PROFMEM(id, size)
#endif
/* invoke when allocate/deallocate significant size of memory. It contains several
 * global var to record it */
long memuse[5];
void profmem(int id, long size) {
	memuse[id] += size;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  readNodes
 *  Description:  read nodes data
 * =====================================================================================
 */
void readNodes(Roads *dataptr, FILE *nodefp) {
	long i = 0;
	int tokencount;

	char **tokensbuf = makeStringArray(MAXFIELDS, MAXTOKENLEN);
	char linebuf[MAXLINELEN];
	Edge **edgesmem;

	projPJ pj;
	const char *prjType = "+proj=tmerc +ellps=WGS84 +lat_0=0 +lon_0=-120 +units=m +k=1.0";

	dataptr->nodelist = (Node*)malloc(MAXNODES * sizeof(Node));
	PROFMEM(NODES, MAXNODES * sizeof(Node));

	pj = pj_init_plus(prjType);

	while(readline(linebuf, nodefp, MAXLINELEN) == 0) {
		tokencount = readtokens(tokensbuf, linebuf, ' ');
		dataptr->nodelist[i].id = i;
		dataptr->nodelist[i].loc = project(pj, strtod(tokensbuf[2], NULL), strtod(tokensbuf[1], NULL));
		dataptr->nodelist[i].indegree = 0;
		dataptr->nodelist[i].outdegree = 0;
		i++;
	}
	dataptr->nodecount = i;

	edgesmem = (Edge**)malloc(2 * dataptr->nodecount * MAXDEGREE * sizeof(Edge*));
	/*init nodes' edgelist*/
	for (i = 0; i < dataptr->nodecount; i++) {
		dataptr->nodelist[i].inedges = edgesmem + 2 * i * MAXDEGREE;
		dataptr->nodelist[i].outedges = edgesmem + (2 * i + 1) * MAXDEGREE;
		PROFMEM(EDGESREF, MAXDEGREE * sizeof(Edge*));
	}

	pj_free(pj);
	freeStringArray(tokensbuf, MAXFIELDS);
}		/* -----  end of function readNodes  ----- */


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  readEdges
 *  Description:  read edges data
 * =====================================================================================
 */
void readEdges ( Roads *dataptr, FILE *edgefp ) {
	long i = 0;
	int tokencount;

	char **tokensbuf = makeStringArray(MAXFIELDS, MAXTOKENLEN);
	char linebuf[MAXLINELEN];

	Node *from, *to;

	dataptr->edgelist = (Edge*)malloc(MAXEDGES * sizeof(Edge));
	PROFMEM(EDGES, MAXEDGES * sizeof(Edge));

	while(readline(linebuf, edgefp, MAXLINELEN) == 0) {
		tokencount = readtokens(tokensbuf, linebuf, ' ');

		/* need the nodes id to be continous, which seems is the case */
		from = &dataptr->nodelist[atoi(tokensbuf[1])];
		to = &dataptr->nodelist[atoi(tokensbuf[2])];

		dataptr->edgelist[i].id = i;
		dataptr->edgelist[i].cost = strtod(tokensbuf[3], NULL);
		//assert(dataptr->edgelist[i].cost != 0);
		dataptr->edgelist[i].head = from;
		dataptr->edgelist[i].tail = to;

		from->outedges[from->outdegree] = &dataptr->edgelist[i];
		from->outdegree++;
		to->inedges[to->indegree] = &dataptr->edgelist[i];
		to->indegree++;

		i++;
	}
	dataptr->edgecount = i;

	freeStringArray(tokensbuf, MAXFIELDS);
}		/* -----  end of function readEdges  ----- */


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  readEdgeGeometry
 *  Description:  read edge geometry
 * =====================================================================================
 */
void readEdgeGeometry ( Roads *dataptr, FILE *geometryfp ) {
	long i,j = 0;
	int tokencount;
	int pointcount;
	char **pointtokens;
	long offset = 0;

	char **tokensbuf = makeStringArray(MAXEDGEPOINTS, MAXTOKENLEN);
	char linebuf[MAXLINELEN];

	Point *pointmem = (Point*)malloc(MAXPOINTS * sizeof(Point));

	projPJ pj;
	const char *prjType = "+proj=tmerc +ellps=WGS84 +lat_0=0 +lon_0=-120 +units=m +k=1.0";
	pj = pj_init_plus(prjType);

	i = 0;
	while(readline(linebuf, geometryfp, MAXLINELEN) == 0) {
		tokencount = readtokens(tokensbuf, linebuf, '^');

		dataptr->edgelist[i].length = strtod(tokensbuf[3], NULL);
		if (dataptr->edgelist[i].length == 0) {
			dataptr->edgelist[i].length = dist(&dataptr->edgelist[i].head->loc,
				&dataptr->edgelist[i].tail->loc);
		}
		/* read points */
		pointcount = (tokencount - 4) / 2;
		if (pointcount < 0) {
			pointcount = 0;
		}

		pointtokens = tokensbuf + 4;

		/*printf("l: %s\n", linebuf);*/
		/*printf("t: %d\n", tokencount);*/
		/*printf("p: %d\n", pointcount);*/
		/*printf("%d\n", i);*/

		dataptr->edgelist[i].pointcount = pointcount;
		dataptr->edgelist[i].pointlist = pointmem + offset;
		offset += pointcount;
		PROFMEM(POINTS, pointcount * sizeof(Point));

		for (j = 0; j < pointcount; j++) {
			dataptr->edgelist[i].pointlist[j] = project(pj, 
				strtod(pointtokens[j * 2 + 1], NULL), strtod(pointtokens[j * 2], NULL));
		}
		i++;
	}

	pj_free(pj);

	freeStringArray(tokensbuf, MAXEDGEPOINTS);
}		/* -----  end of function readEdgeGeometry  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  readRoads
 *  Description:  read roads data
 *                return: pointer to roads(should be freed using freeRoads by invoker)
 * =====================================================================================
 */
Roads *readRoads ( char *nodefilename, char *edgefilename, char *geometryfilename ) {
	Roads *dataptr = (Roads*)malloc(sizeof(Roads));

	FILE *nodefp = fopen(nodefilename, "r");
	FILE *edgefp = fopen(edgefilename, "r");
	FILE *geometryfp = fopen(geometryfilename, "r");

	readNodes(dataptr, nodefp);
	readEdges(dataptr, edgefp);
	readEdgeGeometry(dataptr, geometryfp);
	return dataptr;
}		/* -----  end of function readRoads  ----- */

void freeRoads( Roads* data ) {
	long i;

	free(data->edgelist[0].pointlist);

	free(data->nodelist[0].inedges);

	free(data->edgelist);
	free(data->nodelist);

	free(data);
}

/* WARNING: Not use it now because very slow!!! */
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  regionSelect
 *  Description:  select roads data using a region. 
 *                NOTICE: If a edge's node is not in the region, do not count it. 
 *                Because unless all the trace is on the same edge, if all trace nodes 
 *                on an edge cannot even reach the node(the gate to other edges) in the 
 *                next/previous timestamp, how is it possible for nodes to appear 
 *                on other edges?
 * =====================================================================================
 */
SubRoads *regionSelect ( Roads *data, Bound *box ) {
	long i, j, k;
	long ni = 0; /* indicate the node selection number now */
	long ei = 0; /* indicate the edge selection number now */
	int exist; /* when fill the edge, first check if it already exist in the result */

	SubRoads *res = (SubRoads*)malloc(sizeof(SubRoads));
	res->edgecount = 0;
	res->edgerefs = (Edge**)malloc(MAXEDGES * sizeof(Edge*));
	res->nodecount = 0;
	res->noderefs = (Node**)malloc(MAXNODES * sizeof(Node*));

	for (i = 0; i < data->nodecount; i++) {
		if (inBound(&data->nodelist[i].loc, box)) {
			res->noderefs[ni] = &data->nodelist[i];
			ni++;
		}
	}
	res->nodecount = ni;

	for (i = 0; i < data->edgecount; i++) {
		for (j = 0; j < data->edgelist[i].pointcount - 1; j++) {
			if (lineBoundOverBound(&data->edgelist[i].pointlist[j], 
				&data->edgelist[i].pointlist[j + 1], box)) {

				res->edgerefs[ei] = &data->edgelist[i];
				ei++;
				break;
			}
		}
	}
	/*for (i = 0; i < res->nodecount; i++) {
		for (j = 0; j < res->noderefs[i]->indegree; j++) {
			exist = 0;
			for (k = 0; k < ei; k++) {
				if (res->edgerefs[k]->id == res->noderefs[i]->inedges[j]->id) {
					exist = 1;
					break;
				}
			}
			if (!exist) {
				res->edgerefs[ei] = res->noderefs[i]->inedges[j];
				ei++;
			}
		}

		for (j = 0; j < res->noderefs[i]->outdegree; j++) {
			exist = 0;
			for (k = 0; k < ei; k++) {
				if (res->edgerefs[k]->id == res->noderefs[i]->outedges[j]->id) {
					exist = 1;
					break;
				}
			}
			if (!exist) {
				res->edgerefs[ei] = res->noderefs[i]->outedges[j];
				ei++;
			}
		}
	}*/
	res->edgecount = ei;

	return res;
}		/* -----  end of function regionSelect  ----- */

void freeSelection ( SubRoads *data ) {
	free(data->edgerefs);
	free(data->noderefs);
	free(data);
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  The entrance of the world  
 * =====================================================================================
 */
/*int main ( int argc, char *argv[] ) {*/
	/*int i;*/

	/*[> set memprof <]*/
	/*[>for (i = 0; i < 5; i++) {<]*/
		/*[>memuse[i] = 0;<]*/
	/*[>}<]*/

	/*Roads *ptr = readRoads(*/
			/*"/home/geohpc/mapmatch/road_data/WA_Nodes.txt",*/
			/*"/home/geohpc/mapmatch/road_data/WA_Edges.txt",*/
			/*"/home/geohpc/mapmatch/road_data/WA_EdgeGeometry.txt"*/
			/*);*/

	/*[> should be 535452, 1283540 <]*/
	/*printf("%ld\n", ptr->nodecount);*/
	/*printf("%ld\n", ptr->edgecount);*/
	/*Node *pp = &ptr->nodelist[535312];*/
	/*[> should be 47.312902 -122.3107331 <]*/
	/*printf("y: %lf; x: %lf\n", pp->data.y, pp->data.x);*/
	/*printf("edge count: %d\n", pp->degree);*/
	/*[>for (i = 0; i < pp->degree; i++) {<]*/
		/*[>printf("i: %ld\n", pp->edgelist[i] - ptr->edgelist);<]*/
	/*[>}<]*/

	/* should be 2 points:
	 * 46.8686150
	 * -122.041424
	 * 46.868203
	 * -122.041191 */
	/*Edge *eg = &ptr->edgelist[10881];*/
	/*printf("point count: %d\n", eg->pointcount);*/
	/*for (i = 0; i < eg->pointcount; i++) {*/
		/*printf("point %d: y: %lf; x: %lf\n", i, eg->pointlist[i].y, eg->pointlist[i].x);*/
	/*}*/

	/*[> print memory usage <]*/
	/*[>printf("nodes: %ld\n", memuse[NODES]);<]*/
	/*[>printf("edges: %ld\n", memuse[EDGES]);<]*/
	/*[>printf("edges ref: %ld\n", memuse[EDGESREF]);<]*/
	/*[>printf("points: %ld\n", memuse[POINTS]);<]*/

	/*freeRoads(ptr);*/
	/*return 0;*/
/*}				[> ----------  end of function main  ---------- <]*/
