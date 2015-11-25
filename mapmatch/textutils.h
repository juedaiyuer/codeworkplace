/*
 * =====================================================================================
 *
 *       Filename:  textutils.h
 *
 *    Description:  utils to handle text(file)
 *
 *        Version:  1.0
 *        Created:  06/28/2012 08:55:29 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YANG Anran (), 08to09@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef  TEXTUTILS_H_
#define  TEXTUTILS_H_

#include <stdio.h>

char **makeStringArray( int count, int stringSize );
void freeStringArray( char **a, int count );
int readline ( char *out_line, FILE *fp, long maxlen );
int readtokens ( char **out_token, char *input, char delimiter );

#endif
