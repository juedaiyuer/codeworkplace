/*
* =====================================================================================
*
*       Filename:  FindMatchedSequence.h
*
*    Description: find the match sequence from the candidate graphic
*
*        Version:  1.0
*        Created:  07/25/2012 09:46 AM
*       Revision:  none
*       Compiler:  vs2008
*
*         Author:  Zhan Lijun (), 06lksyzlj@gmail.com
*   Organization:  
*
* =====================================================================================
*/

#ifndef MEMORYALLOCATE_H_
#define MEMORYALLOCATE_H_

#include "datadefs.h"

double** malloc_Array2D_Double(int row, int col);
int** malloc_Array2D_Int(int row, int col);
Candidate** malloc_Array2D_Candidate(int row, int col);

double** malloc_Array2D_Double_Dynamic(int row, int* candcounts);
int** malloc_Array2D_Int_Dynamic(int row, int* candcounts);

void free_Array2D_Double(double** arr);
void free_Array2D_Int(int** arr);
void free_Array2D_Candidate(Candidate** arr);

#endif