/*
 * =====================================================================================
 *
 *       Filename:  fileutils.c
 *
 *    Description:  utils to deal with text(file)
 *
 *        Version:  1.0
 *        Created:  06/28/2012 04:50:11 PM
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

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  makeStringArray
 *  Description:  allocate a string array
 * =====================================================================================
 */
char **makeStringArray( int count, int stringSize ) {
	char **result;
	int i;

	result = ( char ** )calloc( count, sizeof( char * ) );
	for ( i = 0; i < count; i++ ) {
		result[i] = ( char * )calloc( stringSize, sizeof( char ) );
		memset( result[i], '\0', stringSize );
	}

	return result;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  freeStringArray
 *  Description:  deallocate a string array. need to know the element count for 
 *                deallocate each element
 * =====================================================================================
 */
void freeStringArray( char **a, int count ) {
	int i;
	for ( i = 0; i < count; i++ ) {
		free( a[i] );
	}
	free( a );
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  readline
 *  Description:  read a line from a text file into a char array
 * =====================================================================================
 */
int readline ( char *out_line, FILE *fp, long maxlen ) {
	memset(out_line, '\0', maxlen);
	if(fgets ( out_line, maxlen, fp ) != NULL) {
		return 0;
	}
	else {
		return -1;
	}
}		/* -----  end of function readline  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  readtokens
 *  Description:  read a token given a string and the delimiter
 * =====================================================================================
 */
int readtokens ( char **out_token, char *input, char delimiter ) {
	int i = 0;
	int j = 0;
	char *cursor = input;

	while(*cursor != '\0') {
		i = 0;
		while (*cursor != delimiter && *cursor != '\0') {
			i++;
			cursor++;
		}
		
		strncpy(out_token[j], cursor - i, i);
		out_token[j][i] = '\0';

		if (*cursor != '\0') {
			cursor++;
		}
		j++;
	}

	return j;
}		/* -----  end of function readtoken  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  The entrance of the world  
 * =====================================================================================
 */
/*int main ( int argc, char *argv[] ) {*/
	/*char buf[32768];*/
	/*FILE *fp = fopen("/home/geohpc/mapmatch/devarea/file.txt", "r");*/
	/*int i;*/
	/*char **tokens = makeStringArray(32, 1024);*/

	/*readline(buf, fp);*/
	/*printf("%s\n", buf);*/
	/*char *end;*/
	
	/*readtokens(tokens, buf, '^');*/
	/*printf("%s\n", tokens[0]);*/
	/*printf("%s\n", tokens[1]);*/
	/*printf("%s\n", tokens[2]);*/
	/*printf("%s\n", tokens[3]);*/
	/*readline(buf, fp);*/
	/*[>printf("%s\n", buf);<]*/
	/*readline(buf, fp);*/
	/*[>printf("%s\n", buf);<]*/

	/*freeStringArray(tokens, 32);*/
	/*return 0;*/
/*}				[> ----------  end of function main  ---------- <]*/
