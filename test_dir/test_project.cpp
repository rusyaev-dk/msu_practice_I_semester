#include <stdio.h>
#include <stdlib.h>

int read_from_file(const char* filename, int* number)
{
	FILE* fin;
	fin  = fopen(filename, "r");
	if (fin)
	{
		if (fscanf(fin, "%d", number) > 0)
		{
			fclose(fin);
			return 0;
		}
		fclose(fin);
		return 1;
	}
	return 2;
}

void dec_to_binary(int number, int** bin_number)
{   
    int size = sizeof(int) * 8;
	*bin_number = (int*)malloc(size);
	for (int i = size - 1; i >= 0; i--)
	{
		if (number & 1)
		{
			(*bin_number)[i] = 1;
		}
		else
		{
			(*bin_number)[i] = 0;
		}
		number = number >> 1;
	}
}

int write_to_file(const char* filename, int* bin_number)
{
	FILE* fout;
	fout = fopen(filename, "w");
	if (fout)
	{   
        int size = sizeof(int) * 8;
		for (int i = 0; i < size; i++)
		{
			fprintf(fout, "%d", bin_number[i]);
		}
		fclose(fout);
	}
	return 0;
}

int main()
{
	const char filename_input[] = "/Users/denisrusyaev/Visual Studio Code/MSU_Practice/test_dir/input.txt";
	const char filename_output[] = "/Users/denisrusyaev/Visual Studio Code/MSU_Practice/test_dir/output.txt";
	int number = 0;
	int* bin_number;
	read_from_file(filename_input, &number);
	dec_to_binary(number, &bin_number);
	write_to_file(filename_output, bin_number);

	return 0;
}