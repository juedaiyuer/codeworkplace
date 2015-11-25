/*
 * =====================================================================================
 *
 *       Filename:  datadefs.h
 *
 *    Description:  the definitions of data structure
 *
 *        Version:  1.0
 *        Created:  07/05/2012 04:39:39 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YANG Anran (), 08to09@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef  DATADEFS_H_
#define  DATADEFS_H_

typedef struct point {
	double y;
	double x;
} Point;

typedef struct bound {
	double lx; /* left x */
	double by; /* bottom y */
	double rx; /* right x */
	double ty; /* top y */
} Bound; /* bound box */

struct node;
typedef struct edge {
	long id;
	struct node* head;
	struct node* tail;
	double cost;
	double length;
	struct point* pointlist;
	long pointcount;
} Edge;

typedef struct node {
	long id;
	int indegree;
	int outdegree;
	/* I try to record the edgelist of nodes here but it is too space consuming
	 * so I won't use it when create a simplest algorithm \
	 * Also consider building it after do all the io */
	struct edge** inedges;
	struct edge** outedges;
	struct point loc;
} Node;

typedef struct roads {
	struct node *nodelist;
	long nodecount;
	struct edge *edgelist;
	long edgecount;
} Roads;

typedef struct subroads {
	struct node **noderefs;
	long nodecount;
	struct edge **edgerefs;
	long edgecount;
} SubRoads;

typedef struct traceNode {
	long t;
	Point data;
} TraceNode;

typedef struct resultRecord {
	long t;
	long edgeId;
	float confidence;
} ResultRecord;

/* TO BE CONTINUED */

/* Following is proposed only as suggestion */
/* Candidate sets = Candidate sets[inputcount][MAXCAND] plus int candcounts[inputcount] */
typedef struct candidate {
	Point loc;
	struct edge *edge;
	long segId;
	struct node *nextNode;
	struct node *prevNode;
	double distance;
} Candidate;

/* Path in Road/Candidate graph = double path[inputcount] */

#endif
