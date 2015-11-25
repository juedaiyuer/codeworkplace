/*
 * =====================================================================================
 *
 *       Filename:  geoutils.h
 *
 *    Description:  some tool functions of geographical calculation
 *
 *        Version:  1.0
 *        Created:  07/02/2012 09:51:16 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YANG Anran (), 08to09@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef  GEOUTILS_H_
#define  GEOUTILS_H_

#include "datadefs.h"
#include "libs/proj4/proj_api.h"

#define R 6371000
#define PI 3.14159265

int lineBoundOverBound ( Point *head, Point *tail, Bound *box );
void extendBound ( double lat, double lon, Bound *box );
double m2Degree ( double m, double lon );
double point2linedist ( Point *p, Point *seghead, Point *segtail, Point *out_nearest);
double dist( Point *p1, Point *p2 );
double bearing ( Point *p1, Point *p2 );
double abs_d ( double x );
int inBound ( Point *p, Bound *box );
Point project ( projPJ pj, double lon, double lat );
double cosangle ( double x1, double y1, double x2, double y2 );

#endif
