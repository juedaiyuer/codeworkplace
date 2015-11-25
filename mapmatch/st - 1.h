/*
 * =====================================================================================
 *
 *       Filename:  st.h
 *
 *    Description:  ST analysis
 *
 *        Version:  1.0
 *        Created:  07/11/2012 09:13:38 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YANG Anran (), 08to09@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef  ST_H_
#define  ST_H_

#include "AStar.h"
#include "datadefs.h"

#define INFINITY 999999

double stFunc(
		TraceNode *p1, TraceNode *p2,
		Candidate *c1, Candidate *c2
	);

Edge **getEdges(ASPath path);
int getEdgeCount(ASPath path);

void buildNeighbors(ASNeighborList neighbors, void *node, void *context);
float heuristic(void *fromNode, void *toNode, void *context);
double guassian(double d, double delta);

#endif
