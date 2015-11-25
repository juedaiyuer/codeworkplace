/*
 * =====================================================================================
 *
 *       Filename:  io.h
 *
 *    Description:  dealing with inputs and outputs
 *
 *        Version:  1.0
 *        Created:  07/02/2012 09:28:51 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YANG Anran (), 08to09@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef  IO_H_
#define  IO_H_

#include "datadefs.h"

int readInput ( TraceNode* out_result, char *filename );
void writeOutput ( ResultRecord *result, int count, char *filename );

#endif
