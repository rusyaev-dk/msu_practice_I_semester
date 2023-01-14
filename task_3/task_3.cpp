#include <stdio.h>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>


int* create_fib_subsequence(int fib_size)
{
	int *fib_subsequence = (int*)malloc(sizeof(int) * fib_size);
	*(fib_subsequence) = 1;
	*(fib_subsequence+1) = 1;

	int f0 = 1, f1 = 1;

	for (int i = 2; i < fib_size; i++)
	{
		*(fib_subsequence+i) = f0 + f1;
		f0 = f1;
		f1 = *(fib_subsequence+i);
	}

	return fib_subsequence;
}

int read_from_file(const char* filename, int* fib_size)
{
	FILE* fin; int fopen_err;
	fopen_err = fopen_s(&fin, filename, "r");
	if (fopen_err == 0)
	{
		if (fscanf_s(fin, "%d", fib_size) > 0)
		{
			fclose(fin);
			return 0;
		}
	}
	else
	{
		return -1;
	}
}

int write_to_file(const char* filename, int* fib_subsequence, int fib_size)
{
	FILE* fout; int fopen_err;
	fopen_err = fopen_s(&fout, filename, "w");
	if (fopen_err == 0)
	{
		if (fib_size == 0)
		{
			fprintf_s(fout, "%d", 0);
		}
		else
		{
			for (int i = 0; i < fib_size; i++)
			{
				fprintf_s(fout, "%d ", fib_subsequence[i]);
			}
		}
		fclose(fout);
		printf_s("\nCompleted\n");
		return 0;
	}
	else
	{
		return -1;
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));

	const char filename_in[] = "fin.txt";
	const char filename_out[] = "fout.txt";
	int fib_size = 0, * fib_subsequence; 

	if (read_from_file(filename_in, &fib_size) == 0)
	{	
		fib_subsequence = create_fib_subsequence(fib_size);
		if (fib_subsequence)
		{
			write_to_file(filename_out, fib_subsequence, fib_size);
		}
	}

	return 0;
}