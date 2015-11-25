/*
 * =====================================================================================
 *
 *       Filename:  test.c
 *
 *    Description:  the test entry
 *
 *        Version:  1.0
 *        Created:  07/06/2012 09:50:21 AM
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
#include <string.h>

#include "minunit.h"
#include "geoutils.h"
#include "datadefs.h"
#include "textutils.h"
#include "data.h"
#include "st.h"
#include "AStar.h"
#include "proj_api.h"

#define TOL 0.003 /* rather arbitrary, feel free to adjust it */

int tests_run = 0;

int equal(double x, double y) {
	return (x - y) < 0.003 * abs_d(y) && (x - y) > -0.003 * abs_d(y);
}

char *test_dist() {
	Point p1;
	Point p2;
	//p1.y = 47.812968;
	//p1.x = -122.374842;
	//p2.y = 47.813;
	//p2.x = -122.374955;

	p1.y = 0;
	p1.x = 0;
	p2.y = 1;
	p2.x = 1;

	//mu_assert("dist fails", equal(dist(&p1, &p2), 9.157631));
	mu_assert("dist fails", equal(dist(&p1, &p2), 1.414));
	return 0;
}

char *test_p2ldist() {
	Point p1;
	Point p2;
	Point p3;
	Point nearest;

	/*p1.y = 47.812968;
	p1.x = -122.374842;
	p2.y = 47.813;
	p2.x = -122.374955;
	p3.y = 47.812174;
	p3.x = -122.374844;*/

	p1.x = 0;
	p1.y = 0;
	p2.x = 0;
	p2.y = 1;
	p3.x = 1;
	p3.y = 0;
	mu_assert("point2linedist fails", equal(point2linedist(&p3, &p1, &p2, &nearest),
			   	1));
	mu_assert("point2linedist nearest fails", nearest.x == 0 && nearest.y == 0);

	p1.y = 0.5;
	mu_assert("point2linedist fails", equal(point2linedist(&p3, &p1, &p2, &nearest),
			   	sqrt(1.25)));
	mu_assert("point2linedist nearest fails", nearest.x == 0 && nearest.y == 0.5);

	p1.x = 0;
	p1.y = 0;
	p2.y = 0;
	p2.x = 3;
	p3.y = 1;
	p3.x = 2;

	/*mu_assert("point2linedist fails", equal(point2linedist(&p2, &p1, &p3),
			   	8.444082));*/
	mu_assert("point2linedist fails", equal(point2linedist(&p3, &p1, &p2, &nearest),
			   	1));
	mu_assert("point2linedist nearest fails", nearest.x == 2 && nearest.y == 0);

	p2.x = 1;
	mu_assert("point2linedist fails", equal(point2linedist(&p3, &p1, &p2, &nearest),
			   	1.414));

	p1.y = 1;
	p1.x = 1;
	p2.y = 2;
	p2.x = 2;
	p3.y = 1.5;
	p3.x = 1.866;

	mu_assert("point2linedist fails", equal(point2linedist(&p3, &p1, &p2, &nearest),
			   	sin(15 * PI / 180)));

	p2.y = 1.5;
	p2.x = 1.5;

	mu_assert("point2linedist fails", equal(point2linedist(&p3, &p1, &p2, &nearest),
			   	0.366));
	return 0;
}

char *test_boundover() {
	Point p1;
	Point p2;
	Bound b;

	p1.x = 10;
	p1.y = 5;
	p2.x = 20;
	p2.y = 30;

	b.lx = 11;
	b.rx = 19;
	b.by = 6;
	b.ty = 40;

	mu_assert("lineBoundOverBound fails", lineBoundOverBound(&p1, &p2, &b));

	return 0;
}

char *test_boundover2() {
	Point p1;
	Point p2;
	Bound b;

	p1.x = 10;
	p1.y = 5;
	p2.x = 20;
	p2.y = 30;

	b.lx = 3;
	b.rx = 9;
	b.by = 6;
	b.ty = 40;

	mu_assert("lineBoundOverBound fails", !lineBoundOverBound(&p1, &p2, &b));

	return 0;
}

char *test_readtokens() {
	char **toks = makeStringArray(5, 10);
	char line[15] = "123,45678,0000";
	int count = readtokens(toks, line, ',');

	mu_assert("read token: count wrong", count == 3);
	mu_assert("read token: pos 0 wrong", strcmp(toks[0], "123") == 0);
	mu_assert("read token: pos 1 wrong", strcmp(toks[1], "45678") == 0);
	mu_assert("read token: pos 2 wrong", strcmp(toks[2], "0000") == 0);

	freeStringArray(toks, 5);

	return 0;
}

char *test_selection() {
	Edge edges[2];
	Node nodes[3];
	Edge *ep;
	Roads r;
	Bound b;
	SubRoads *selection;

	r.nodecount = 3;
	r.edgecount = 2;
	r.nodelist = nodes;
	r.edgelist = edges;
	r.nodelist[0].loc.y = 40;
	r.nodelist[1].loc.y = 50;
	r.nodelist[2].loc.y = 42;
	r.nodelist[0].loc.x = 122;
	r.nodelist[1].loc.x = 123;
	r.nodelist[2].loc.x = 124;
	r.nodelist[0].outedges = &r.edgelist;
	r.nodelist[0].outdegree = 1;
	r.nodelist[1].inedges = &r.edgelist;
	r.nodelist[1].indegree = 1;
	ep = r.edgelist + 1;
	r.nodelist[1].outedges = &ep;
	r.nodelist[1].outdegree = 1;
	r.nodelist[2].inedges = &ep;
	r.nodelist[2].indegree = 1;
	r.edgelist[0].head = r.nodelist;
	r.edgelist[0].tail = r.nodelist + 1;
	r.edgelist[1].head = r.nodelist + 1;
	r.edgelist[1].tail = r.nodelist + 2;

	b.lx = 120;
	b.rx = 122.5;
	b.by = 39;
	b.ty = 51;

	selection = regionSelect(&r, &b);

	mu_assert("region selection: edge count is incorrect. ",
		   	selection->edgecount == 1);
	mu_assert("region selection: node count is incorrect. ",
		   	selection->nodecount == 1);

	freeSelection(selection);
}

/* following three aims to test the third-party a* algorithm  */
void t_buildNeighbors(ASNeighborList neighbors, void *node, void *context) {
	int p = *(int*)node;
	int nodes[9] = {1, 2, 3, 2, 5, 3, 5, 4, 5};

	if (p == 0) {
		ASNeighborListAdd(neighbors, nodes + 0, 1);
		ASNeighborListAdd(neighbors, nodes + 1, 2);
		ASNeighborListAdd(neighbors, nodes + 2, 4);
	}
	else if (p == 1) {
		ASNeighborListAdd(neighbors, nodes + 3, 3);
		ASNeighborListAdd(neighbors, nodes + 4, 6);
	}
	else if (p == 2) {
		ASNeighborListAdd(neighbors, nodes + 5, 1);
		ASNeighborListAdd(neighbors, nodes + 6, 5);
	}
	else if (p == 3) {
		ASNeighborListAdd(neighbors, nodes + 7, 1);
	}
	else if (p == 4) {
		ASNeighborListAdd(neighbors, nodes + 8, 1);
	}
}

float t_heuristic(void *fromNode, void *toNode, void *context) {
    float x = *(int*)fromNode - *(int*)toNode;
	return x < 0 ? -x : x;
}

char *test_astar() {
	ASPathNodeSource graph = {
		sizeof(int),
		&t_buildNeighbors,
		&t_heuristic,
		NULL,
		NULL
	};

	int from = 0;
	int to = 2;

    ASPath path = ASPathCreate(&graph, NULL, &from, &to);

	mu_assert("astar: cost from 0 to 2 is not correct", equal(ASPathGetCost(path), 2));

    ASPathDestroy(path);

	to = 5;

    path = ASPathCreate(&graph, NULL, &from, &to);

	mu_assert("astar: cost from 0 to 5 is not correct", equal(ASPathGetCost(path), 5));

    ASPathDestroy(path);

	return 0;
}

/* This test it to test my function getEdges, which is to extract edges 
 * from the 3rd party astar algorithm result */
char *test_astar_getedges() {
	ASPathNodeSource graph = {
		sizeof(Node),
		&buildNeighbors,
		&heuristic,
		NULL,
		NULL
	};

	NodeSet set;

	Node n0;
	Node n1;
	Node n2;
	Node n3;
	Node n4;
	Node *noderefs[5] = {&n0, &n1, &n2, &n3, &n4};

	Edge e0;
	Edge e1;
	Edge e2;
	Edge e3;
	Edge e4;
	Edge e5;

	Edge *oel0[2] = {&e0, &e1};
	Edge *oel1[2] = {&e4, &e5};
	Edge *oel2[1] = {&e2};
	Edge *oel3[1] = {&e3};
	Edge *oel4[1];

	Edge *iel0[1];
	Edge *iel1[1] = {&e0};
	Edge *iel2[2] = {&e1, &e5};
	Edge *iel3[1] = {&e4};
	Edge *iel4[2] = {&e2, &e3};

	ASPath path;

	n0.id = 0;
	n1.id = 1;
	n2.id = 2;
	n3.id = 3;
	n4.id = 4;

	n0.outdegree = 2;
	n1.outdegree = 2;
	n2.outdegree = 1;
	n3.outdegree = 1;
	n4.outdegree = 0;

	n0.indegree = 0;
	n1.indegree = 1;
	n2.indegree = 2;
	n3.indegree = 1;
	n4.indegree = 2;

	n0.outedges = oel0;
	n1.outedges = oel1;
	n2.outedges = oel2;
	n3.outedges = oel3;
	n4.outedges = oel4;

	n0.inedges = iel0;
	n1.inedges = iel1;
	n2.inedges = iel2;
	n3.inedges = iel3;
	n4.inedges = iel4;

	e0.id = 0;
	e1.id = 1;
	e2.id = 2;
	e3.id = 3;
	e4.id = 4;
	e5.id = 5;

	e0.length = 1;
	e1.length = 2;
	e2.length = 2;
	e3.length = 1;
	e4.length = 1;
	e5.length = 2;

	e0.head = &n0;
	e1.head = &n0;
	e2.head = &n2;
	e3.head = &n3;
	e4.head = &n1;
	e5.head = &n1;

	e0.tail = &n1;
	e1.tail = &n2;
	e2.tail = &n4;
	e3.tail = &n4;
	e4.tail = &n3;
	e5.tail = &n2;

	set.count = 5;
	set.refs = noderefs;

    path = ASPathCreate(&graph, &set, &n0, &n4);

	mu_assert("astar get edges: count incorrect ", getEdgeCount(path) == 3);
	mu_assert("astar get edges: total length incorrect", 
			equal(ASPathGetCost(path), 3));
	mu_assert("astar get edges: 3 incorrect ", getEdges(path)[2]->id == 3);

	path = ASPathCreate(&graph, &set, &n4, &n0);

	printf("%lf", ASPathGetCost(path));

    ASPathDestroy(path);

	return 0;

}

char *test_stfunc() {
	Edge e;
	Node n1;
	Node n2;
	TraceNode tn1;
	TraceNode tn2;
	Candidate c1;
	Candidate c2;
	Point pc1;
	Point pc2;
	Point pl[2];
	Edge *el[1];

	pc1.x = 0.25;
	pc1.y = 0.25;
	pc2.x = 0.75;
	pc2.y = 0.75;
	el[0] = &e;

	e.id = 0;
	e.cost = 1;
	e.length = 1.414214;
	e.head = &n1;
	e.tail = &n2;
	e.pointcount = 2;
	e.pointlist = pl;

	n1.id = 0;
	n1.outdegree = 1;
	n1.outedges = el;
	n1.indegree = 0;
	n1.inedges = NULL;
	n1.loc.x = 0;
	n1.loc.y = 0;

	n2.id = 0;
	n2.indegree = 1;
	n2.inedges = el;
	n2.outdegree = 0;
	n2.outedges = NULL;
	n2.loc.x = 1; 
	n2.loc.y = 1;

	pl[0] = n1.loc;
	pl[1] = n2.loc;

	tn1.t = 0;
	tn2.t = 1;
	tn1.data.y = 0;
	tn1.data.x = 0.5;
	tn2.data.y = 1;
	tn2.data.x = 0.5;

	c1.edgeId = 0;
	c1.segId = 0;
	c1.loc = pc1;
	c1.nextNode = &n2;
	c1.prevNode = &n1;
	c1.distance = 0.353553;
	c2.edgeId = 0;
	c2.segId = 0;
	c2.nextNode = &n2;
	c2.prevNode = &n1;
	c2.distance = 0.353553;
	c2.loc = pc2;

	/*mu_assert("st analysis error", 
			equal(stFunc(&tn1, &tn2, &c1, &c2), 0.019944 / 0.707106));*/
	return 0;
}

char *test_proj() {
	char prjType[256];
	projPJ pj;
	Point res;
	int i;

	for(i = 0; i < 256; i++) {
		prjType[i] = '\0';
	}
	sprintf(prjType, "+proj=tmerc +ellps=WGS84 +lat_0=0 +lon_0=-120 +units=m +k=1.0");

	pj = pj_init_plus(prjType);
	res = project(pj, -122, 47);

	pj_free(pj);

	mu_assert("projection result incorrect",
		equal(res.x, -152109.880896) && equal(res.y, 5209189.002743));

	return 0;
}

char *test_angle() {
	mu_assert("angle fails", equal(-0.70706, cosangle(1, 0, -1, 1)));
	mu_assert("angle fails", equal(cos(15 * PI / 180), cosangle(1, 1, 0.866, 0.5)));
	return 0;
}

char *test_suite() {
	mu_run_test(test_dist);
	mu_run_test(test_p2ldist);
	mu_run_test(test_boundover);
	mu_run_test(test_boundover2);
	mu_run_test(test_readtokens);
	mu_run_test(test_selection);
	mu_run_test(test_astar);
	mu_run_test(test_astar_getedges);
	/*mu_run_test(test_stfunc);*/
	mu_run_test(test_proj);
	mu_run_test(test_angle);

	return 0;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  The entrance of the world  
 * =====================================================================================
 */
int main ( int argc, char *argv[] ) {
	char *result = test_suite();
	if (result != 0) {
		printf("%s\n", result);
	}
	else {
		printf("ALL tests passed\n");
	}
	printf("Tests run: %d\n", tests_run);

	return result != 0;
}				/* ----------  end of function main  ---------- */
