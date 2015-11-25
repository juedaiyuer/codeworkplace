/*
 * =====================================================================================
 *
 *       Filename:  geoutils.c
 *
 *    Description:  some tool functions of geographical calculation
 *
 *        Version:  1.0
 *        Created:  06/28/2012 09:28:26 AM
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
#include <math.h>
#include <string.h>

#include "textutils.h"
#include "geoutils.h"

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  project
 *  Description:  project from geographical coordinates to the projected ones(tmerc)
 *                I use projPJ here because the init operation is time-consuming
 * =====================================================================================
 */
Point project ( projPJ pj, double lon, double lat ) {
	Point res;
	projUV p;

	p.u = lon * DEG_TO_RAD;
	p.v = lat * DEG_TO_RAD;
	p = pj_fwd(p,pj);
	
	res.x = p.u;
	res.y = p.v;

	return res;
}		/* -----  end of function project  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  abs_d
 *  Description:  absolute value from double to double
 * =====================================================================================
 */
double abs_d ( double x ) {
	return x < 0 ? -x : x;
}		/* -----  end of function abs  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  m2Degree
 *  Description:  AT SMALL SCALE, a approximately(so also fast) conversion from distance 
 *                in meter to degree on latitude circle.
 *                When wishing to convert to longitude, 
 *                you can fill latitude to longitude parameter,
 *                with some loss of precision because the earth is taken as sphere
 *                WARNING: Here I calculate small circle arc, but since every 
 *                greate circle arc connect between the original boundary and 
 *                extended boundary will be greater than it, 
 *                (maybe) there is no corretness problem.
 *               
 * =====================================================================================
 */
double m2Degree ( double m, double lon ) {
	return abs_d(m / (R * cos(lon * PI / 180)) * 180 / PI);
}		/* -----  end of function m2Degree  ----- */


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  inBound
 *  Description:  check if a given point is in given bound
 * =====================================================================================
 */
int inBound ( Point *p, Bound *box ) {
	return (p->x > box->lx) && (p->x < box->rx)
		&& (p->y > box->by && p->y < box->ty);
}		/* -----  end of function inBound  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  lineBoundOverBound
 *  Description:  check if a line's bbox overlaps given bound
 * =====================================================================================
 */
int lineBoundOverBound ( Point *head, Point *tail, Bound *box ) {
	double left, right, bottom, top;  

	if(head->x < tail->x) { 
		left = head->x;
		right = tail->x;
	}
	else { 
		right = head->x;
		left = tail->x;
	}

	if (head->y < tail->y) {
		bottom = head->y;
		top = tail->y;
	}
	else {
		top = head->y;
		bottom = tail->y;
	}

	if (left < box->rx && right > box->lx) {
	}
	else {
		/*printf("%lf\n", left);*/
		/*printf("%lf\n", right);*/
		/*printf("%lf\n", box->lx);*/
		/*printf("%lf\n", box->rx);*/

		return 0;
	}

	if (bottom < box->ty && top > box->by) {
	}
	else {
		/*printf("%lf\n", bottom);*/
		/*printf("%lf\n", top);*/
		/*printf("%lf\n", box->by);*/
		/*printf("%lf\n", box->ty);*/

		return 0;
	}

	return 1;
}		/* -----  end of function lineInBound  ----- */


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  angle
 *  Description:  calculate angle(radius, from 0 to PI)
 * =====================================================================================
 */
/* Seems wrong!! */
/*double angle ( Point *cross, Point *p1, Point *p2 ) {*/
	/*double result = bearing(p1, cross) - bearing(p2, cross);*/
	/*if (result < 0) {*/
		/*result += 2 * PI;*/
	/*}*/
	/*if (result > PI) {*/
		/*result = 2 * PI - result;*/
	/*}*/

	/*return result;*/
/*}		[> -----  end of function angle  ----- <]*/

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  extendBound
 *  Description:  if the given point is not in the given bound, enlarge the bound to 
 *                include it
 * =====================================================================================
 */
void extendBound ( double x, double y, Bound *box ) {
	if (x > box->rx) { box->rx = x; }
	if (x < box->lx) { box->lx = x; }
	if (y > box->ty) { box->ty = y; }
	if (y < box->by) { box->by = y; }
}		/* -----  end of function extendBound  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  dist
 *  Description:  calculate distance between 2 geographical point(unit: m)
 * =====================================================================================
 */
/* sphere version */
/* double dist ( Point *p1, Point *p2 ) {
	double dLat = (p1->y - p2->y) * PI / 180;
	double dLon = (p1->x - p2->x) * PI / 180;
	double lat1 = p1->y * PI / 180;
	double lat2 = p2->y * PI / 180;

	double a = sin(dLat / 2) * sin(dLat / 2) +
		sin(dLon / 2) * sin(dLon / 2) * cos(lat1) * cos(lat2); 
	double c = 2 * atan2(sqrt(a), sqrt(1 - a)); 
	return R * c;
}		/* -----  end of function dist  ----- */

double dist ( Point *p1, Point *p2 ) {
	return sqrt((p1->x - p2->x) * (p1->x - p2->x) + (p1->y - p2->y) * (p1->y - p2->y));
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  cosangle
 *  Description:  calculate the cos of the angle of two vector(radius)
 * =====================================================================================
 */
double cosangle ( double x1, double y1, double x2, double y2 ) {
	return (x1 * x2 + y1 * y2) / 
		sqrt((x1 * x1 + y1 * y1) * (x2 * x2 + y2 * y2));
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  bearing
 *  Description:  calculate bearing(radius)
 * =====================================================================================
 */
double bearing ( Point *p1, Point *p2 ) {
	double dLon = (p2->x - p1->x) * PI / 180;
	double lat1 = p1->y * PI / 180;
	double lat2 = p2->y * PI / 180;
	double y = sin(dLon) * cos(lat2);
	double x = cos(lat1) * sin(lat2) - 
		sin(lat1) * cos(lat2) * cos(dLon);
	return atan2(y, x);
}		/* -----  end of function bearing  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  point2linedist
 *  Description:  point to linestring distance
 * =====================================================================================
 */
/* sphere version */
/* double point2linedist ( Point *p, Point *seghead, Point *segtail) {
	double d = asin(sin(dist(seghead, p) / R) * sin(bearing(seghead, p) 
				- bearing(seghead, segtail))) * R;
	return d < 0 ? d * -1 : d;
}		/* -----  end of function point2linedist  ----- */

double point2linedist ( Point *p, Point *seghead, Point *segtail, Point *out_nearest) {
	double a;
	double b;
	double l; /* the seg length */
	double ax = p->x - seghead->x;
	double ay = p->y - seghead->y;
	double lx = segtail->x - seghead->x;
	double ly = segtail->y - seghead->y;

	double cosal; /* the cos of the angle between a and l */
	double aOnLx;
	double aOnLy;
	double aOnL; /* a's shadow length on l */

	a = dist(p, seghead);
	b = dist(p, segtail);
	l = dist(seghead, segtail);

	cosal = (ax * lx + ay * ly) / (a * l);

	if(cosal < 0) {
		out_nearest->x = seghead->x;
		out_nearest->y = seghead->y;
		return a;
	}
	
	aOnL = a * cosal;

	if(a * cosal > l) {
		out_nearest->x = segtail->x;
		out_nearest->y = segtail->y;
		return b;
	}

	aOnLx = lx * aOnL / l;
	aOnLy = ly * aOnL / l;
	out_nearest->x = p->x - (ax - aOnLx);
	out_nearest->y = p->y - (ay - aOnLy);
	return sqrt(a * a - aOnL * aOnL);
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  The entrance of the world  
 * =====================================================================================
 */
/*int main ( int argc, char *argv[] ) {*/
	/*Point front;*/
	/*front.y = 0;*/
	/*front.x = 90;*/
	/*Point back;*/
	/*back.y = 40;*/
	/*back.x = 90;*/
	/*[>printf("%lf\n", bearing(&front, &back));<]*/

	/*Point start;*/
	/*start.y = 47.735;*/
	/*start.x = -122.186;*/
	/*Point end;*/
	/*end.y = 47.7151;*/
	/*end.x = -122.186;*/
	/*printf("%lf\n", distance(&start, &end));*/

	/*Point p;*/
	/*p.y = 47.735;*/
	/*p.x = -122.186;*/
	/*Point p2;*/
	/*p2.y = 47.629;*/
	/*p2.x = -122.341;*/
	/*Point line[2];*/
	/*line[0].y = 47.7151;*/
	/*line[0].x = -122.186;*/
	/*line[1].y = -47.7151;*/
	/*line[1].x = 57.814;*/
	/*[>line[1].y = 0;<]*/
	/*[>line[1].x = 0;<]*/
	/*[>printf("%lf\n", distance(&p, line));<]*/
	/*printf("%lf\n", bearing(&p, line));*/
	/*printf("%lf\n", bearing(line, line + 1));*/
	/*printf("%lf\n", point2linedist(&p, line[0], line[1]));*/
	/*return 0;*/
/*}				[> ----------  end of function main  ---------- <]*/

