/*
 * =====================================================================================
 *
 *       Filename:  data.h
 *
 *    Description:  data structures and io methods
 *
 *        Version:  1.0
 *        Created:  07/02/2012 08:41:33 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YANG Anran (), 08to09@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef  DATA_H_
#define  DATA_H_

#include "datadefs.h"

#define MAXNODES 1000000
#define MAXEDGES 2000000
#define MAXFIELDS 20 /* the max fields count in both nodes and edges file */
#define MAXEDGEPOINTS 2048
#define MAXTOKENLEN 128
#define MAXLINELEN 65536
#define MAXDEGREE 20 /* one direction */

/*#define PROF*/

Roads *readRoads ( char *nodefilename, char *edgefilename, char *geometryfilename );
void freeRoads( Roads* data );

SubRoads *regionSelect ( Roads *data, Bound *box );
void freeSelection ( SubRoads *data );

#endif
