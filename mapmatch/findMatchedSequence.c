#include "datadefs.h"
#include "findMatchedSequence.h"

//void findMatchSequence( double**  tranitionF, double** ObsePiblity, int* candcounts, int inputcount, double** score, int** parent, int* result)
 void findMatchSequence(double** tranitionF, double** ObsePiblity , int* candcounts, int inputcount, double** score, int** parent, int* result)
{
	const int MAXCAND = 5;
	int i;
	int j;
	int k;
	double maxtemp;
	double maxscore;
	double alt;


	for(i = 0; i < candcounts[0]; i++)
	{
		score[0][i] = ObsePiblity[0][i];
		
	}

	for(i = 1; i < inputcount; i++)
	{
		for(j = 0; j < candcounts[i]; j++)
		{
			parent[i][j] =  0;
			maxscore = -10000000;
			alt = 0.00000;
			for(k = 0; k <candcounts[i-1]; k++)
			{
				alt = score[i-1][k] + ObsePiblity[i][j]*tranitionF[i-1][k*MAXCAND + j];
				//alt = ObsePiblity[i-1][k] + ObsePiblity[i][j]*tranitionF[i-1][k*MAXCAND + j];
				if(alt > maxscore)
				{
					maxscore = alt;
					parent[i][j] =  k;
				}
			}
			score[i][j] = maxscore;
		}
	}

	
	 maxtemp = -10000000;
	for(j = 0; j < inputcount; j++)
	{
		result[j] = 0;
	}

	for(j = 0; j < candcounts[inputcount-1]; j++)
	{
		if(maxtemp < score[inputcount-1][j])
		{
			maxtemp = score[inputcount-1][j];
			result[inputcount-1] = j;
		}
	}
	

	for(i = inputcount-2; i >= 0; i--)
	{
		result[i] = parent[i+1][result[i+1]];
	}
}