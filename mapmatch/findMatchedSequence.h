/*
 * =====================================================================================
 *
 *       Filename:  FindMatchedSequence.h
 *
 *    Description: find the match sequence from the candidate graphic
 *
 *        Version:  1.0
 *        Created:  07/23/2012 21:04 PM
 *       Revision:  none
 *       Compiler:  vs2008
 *
 *         Author:  Zhan Lijun (), 06lksyzlj@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef  FINDMATCHEDSEQUENCEE_H_
#define  FINDMATCHEDSEQUENCEE_H_

//#define MAXCAND 10;


/*
int candcounts[inputcount],
double* tranitionF = new double[inputcount][MAXCAND*MAXCAND],
double* ObsePiblity = new double[inputcount][MAXCAND],
double* score = new double[inputcount][MAXCAND],
int parent[inputcount][MAXCAND],
int* result = new int[inputcount]
*/
void findMatchSequence(double** tranitionF, double** ObsePiblity , int* candcounts, int inputcount, double** score, int** parent, int* result);

#endif