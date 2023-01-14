#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>


char* decimal_to_binary(int decimal_num, int* size)
{
	*size = sizeof(int) * 4;
	int index = *size - 1;
	char* arr = (char*)calloc(*size, 1);
	for (int i = 0; i < *size; i++)
	{
		if (decimal_num & (1 << i))
		{
			arr[index - i] = 1;
		}
		else
		{
			arr[index - i] = 0;
		}
	}
	return arr;
}

int read_from_file(const char* filename, int* decimal_num)
{
	FILE* fin; int fopen_err;
	fopen_err = fopen(&fin, filename, "r");
	if (fopen_err == 0)
	{
		if (fscanf(fin, "%d", decimal_num) == 1)
		{
			fclose(fin);
			return 0;
		}
		return -2;
	}
	return -1;
}

int write_to_file(const char* filename, char* binary_num, int size)
{
	FILE* fout; int fopen_err;
	fopen_err = fopen(&fout, filename, "w");
	if (fopen_err == 0)
	{
		for (int i = 0; i < size; i++)
		{
			fprintf(fout, "%d", binary_num[i]);
		}
		fclose(fout);
		return 0;
	}
	return -1;
}

int main()
{
	
	const char filename_in[] = "fin.txt";
	const char filename_out[] = "fout.txt";
	int decimal_num = 0, size = 0; char* binary_num;

	if (read_from_file(filename_in, &decimal_num) == 0)
	{	
		binary_num = decimal_to_binary(decimal_num, &size);
		write_to_file(filename_out, binary_num, size);
	}

	return 0;
}