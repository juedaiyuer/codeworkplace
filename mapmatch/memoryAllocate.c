#include "memoryAllocate.h"
#include <stdlib.h>
#include <string.h>

Candidate** malloc_Array2D_Candidate(int row, int col)
{
	int size;
	int point_size;
	Candidate** arr;
	Candidate* head;

	size = sizeof(Candidate);
	point_size = sizeof(Candidate*);
	arr = (Candidate**)malloc(point_size*row + size*row*col);
	if (NULL != arr)
	{
		memset(arr, 0, point_size*row + size*row*col);
		head = (Candidate*)((int)arr + point_size*row);
		while (row--)
		{
			arr[row] = (Candidate*)((int)head + row*col*size);
		}
	}
	return (Candidate**)arr;
}

double** malloc_Array2D_Double(int row, int col)
{
	int size;
	int point_size;
	double** arr;
	double* head;

	size = sizeof(double);
	point_size = sizeof(double*);
	arr = (double**)malloc(point_size*row + size*row*col);
	if (NULL != arr)
	{
		memset(arr, 0, point_size*row + size*row*col);
		head = (double*)((int)arr + point_size*row);
		while (row--)
		{
			arr[row] = (double*)((int)head + row*col*size);
		}
	}
	return (double**)arr;
}

int** malloc_Array2D_Int(int row, int col)
{
	int size;
	int point_size;
	int** arr;
	int* head;

	size = sizeof(int);
	point_size = sizeof(int*);
	arr = (int**)malloc(point_size*row + size*row*col);
	if (NULL != arr)
	{
		memset(arr, 0, point_size*row + size*row*col);
		head = (int*)((int)arr + point_size*row);
		while (row--)
		{
			arr[row] = (int*)((int)head + row*col*size);
		}
	}
	return (int**)arr;
}



double** malloc_Array2D_Double_Dynamic(int row, int* candcounts)
{
	int allcounts;
	int size;
	int point_size;
	double** arr;
	double* head;
	int* offset;
	int i;

	size = sizeof(double);
	point_size = sizeof(double*);
	offset = (int*)malloc(row*sizeof(int));
	if (NULL == offset)
	{
		return NULL;
	}
	allcounts = 0;
	for (i = 0; i < row; i++)
	{
		offset[i] = allcounts;
		allcounts += candcounts[i];
	}
	arr = (double**)malloc(point_size*row + size*allcounts);

	if (NULL != arr)
	{
		memset(arr, 0, point_size*row + size*allcounts);
		head = (double*)((int)arr + point_size*row);
		while (row--)
		{
			arr[row] = (double*)((int)head + offset[row]*size);
		}
	}
	free(offset);
	return (double**)arr;
}

int** malloc_Array2D_Int_Dynamic(int row, int* candcounts)
{
	int allcounts;
	int size;
	int point_size;
	int** arr;
	int* head;
	int* offset;
	int i;

	size = sizeof(int);
	point_size = sizeof(int*);
	offset = (int*)malloc(row*sizeof(int));
	if (NULL == offset)
	{
		return NULL;
	}
	allcounts = 0;
	for (i = 0; i < row; i++)
	{
		offset[i] = allcounts;
		allcounts += candcounts[i];
	}
	arr = (int**)malloc(point_size*row + size*allcounts);

	if (NULL != arr)
	{
		memset(arr, 0, point_size*row + size*allcounts);
		head = (int*)((int)arr + point_size*row);
		while (row--)
		{
			arr[row] = (int*)((int)head + offset[row]*size);
		}
	}
	free(offset);
	return (int**)arr;
}


void free_Array2D_Double(double** arr)
{
	if (NULL != arr)
	{
		free(arr);
		arr = NULL;
	}
}

void free_Array2D_Int(int** arr)
{
	if (NULL != arr)
	{
		free(arr);
		arr = NULL;
	}
}

void free_Array2D_Candidate(Candidate** arr)
{
	if (NULL != arr)
	{
		free(arr);
		arr = NULL;
	}
}
