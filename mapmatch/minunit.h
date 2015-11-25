/*
 * =====================================================================================
 *
 *       Filename:  minunit.h
 *
 *    Description:  minimalistic test framework from www.jera.com
 *
 *        Version:  1.0
 *        Created:  07/05/2012 08:48:56 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  JTNs (), www.jera.com/techinfo/jtns/jtn002.html
 *   Organization:  
 *
 * =====================================================================================
 */

#define mu_assert(message, test) do { if (!(test)) return message; } while (0)
#define mu_run_test(test) do { char *message = test(); tests_run++; \
							   if (message) return message; } while(0)
extern int tests_run;
