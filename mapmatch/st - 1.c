/*
 * =====================================================================================
 *
 *       Filename:  st.c
 *
 *    Description:  ST analysis
 *
 *        Version:  1.0
 *        Created:  07/11/2012 09:13:19 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YANG Anran (), 08to09@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <assert.h>

#include "datadefs.h"
#include "geoutils.h"
#include "st.h"

void buildNeighbors(ASNeighborList neighbors, void *node, void *context) {
	int i;

	Node *p = (Node*)node;

	for (i = 0; i < p->outdegree; i++) {
		ASNeighborListAdd(neighbors, p->outedges[i]->tail, p->outedges[i]->length);
	}
}

float heuristic(void *fromNode, void *toNode, void *context) {
	Node *from = (Node*)fromNode;
	Node *to = (Node*)toNode;

	/* WARNING: Here A star algorithm used requires float	*/
    return (float)dist(&from->loc, &to->loc); 
}

double guassian(double d, double delta) {
	return exp(-(d * d) / (2 * delta * delta)) / (sqrt(2 * PI) * delta);
}

double transProb(Point *p1, Point *p2, double w) {
	double d;

	d = dist(p1, p2);

	return d / w;
}

double spatialFunc(Point *p1, Point *p2,
		Candidate *c1, Candidate *c2, ASPath path) {
	double w;

	/* WARNING: Here I use a approximation(use Euclidean distance from
	 * candidate point to node rather than the path distance) */

	w = ASPathGetCost(path)
		- dist(&c1->loc, &c1->prevNode->loc)
		- dist(&c2->loc, &c2->nextNode->loc);

	if(w == 0) { return 0; }
	else { return transProb(p1, p2, w); }
}

int getEdgeCount(ASPath path) {
	return ASPathGetCount(path) - 1;
}

/* calculate edges in the shortest path because the used algorithm does not 
 * record the edges */
Edge **getEdges(ASPath path) {
	int i, j;
	int count;
	Edge **result;
	Node *head;
	Node *tail;

	count = getEdgeCount(path);
	if(count == -1) {
		return NULL;
	}
	result = (Edge**)malloc(count * sizeof(Edge*));

	head = NULL;
	tail = (Node*)ASPathGetNode(path, 0);

	for (i = 0; i < count; i++) {
		head = tail;
		tail = (Node*)ASPathGetNode(path, i + 1);

		for (j = 0; j < head->outdegree; j++) {
			if (head->outedges[j]->tail->id == tail->id) {
				result[i] = head->outedges[j];
				break;
			}
		}
	}

	return result;
}

void freeEdges(Edge **elist) {
	if(elist != NULL) {
		free(elist);
	}
}

double averageV(ASPath path, TraceNode *p1, TraceNode *p2) {
	return ASPathGetCost(path) / (p2->t - p1->t);
}

double temporalFunc(ASPath path, TraceNode *p1, TraceNode *p2) {
	Edge **elist = getEdges(path);
	int ecount = getEdgeCount(path);
	double *vlist = (double*)malloc(sizeof(double) * ecount);
	int i;
	double above = 0;
	double below = 0;
	double length;
	double avgv = averageV(path, p1, p2);

	for (i = 0; i < ecount; i++) {
		if(elist[i]->cost == 0) { return 0; }
		vlist[i] = elist[i]->length / elist[i]->cost;
	}

	for (i = 0; i < ecount; i++) {
		above += vlist[i];
	}
	above *= avgv;

	for (i = 0; i < getEdgeCount(path); i++) {
		below += vlist[i] * vlist[i];
	}
	below *= ecount * avgv * avgv;
	below = sqrt(below);

	free(vlist);
	freeEdges(elist);
	if(below == 0) { return 0; }
	else { return above / below; }
}

double stFunc(TraceNode *p1, TraceNode *p2,
		Candidate *c1, Candidate *c2) {
	double s;
	double t;

	ASPathNodeSource graph = {
		sizeof(Node),
		&buildNeighbors,
		&heuristic,
		NULL,
		NULL
	};

	ASPath path = ASPathCreate(&graph, NULL, c1->prevNode, c2->nextNode);

	s = spatialFunc(&p1->data, &p2->data, c1, c2, path);
	t = temporalFunc(path, p1, p2);

	ASPathDestroy(path);

	return s * t;
}
