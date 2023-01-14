#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

double double_rand(int min, int max)
{	
	if (min && max)
	{
		return min + rand() % (1000 * (max - min)) / 1000.0;
	}
	min = 10, max = 100;
	return min + rand() % (1000 * (max - min)) / 1000.0;
}

int get_matrix_size(const char* filename, int* matrix_size, FILE** fin)
{
	*fin = fopen(filename, "r");
	if (*fin)
	{
		if (fscanf(*fin, "%d", matrix_size) > 0)
		{
			return 0;
		}
		return -2;
	}
	return -1;
}

int fill_initial_file(const char* filename, int matrix_size)
{
	FILE *fin = fopen(filename, "w");
	if (fin)
	{
		double rand_value;
		for (int i = 0; i < matrix_size; i++)
		{
			for (int j = 0; j < matrix_size; j++)
			{	
				rand_value = double_rand(10, 100);
				fprintf(fin, "%.4lf ", rand_value);
			}
			fprintf(fin, "\n");
		}
		fclose(fin);
		return 0;
	}
	return -1;
}

int read_from_file(double** matrix, int matrix_size, FILE* fin)
{
	for (int i = 0; i < matrix_size; i++)
	{
		matrix[i] = (double*)malloc(sizeof(double) * matrix_size);
		for (int j = 0; j < matrix_size; j++)
		{	
			fscanf(fin, "%lf", &matrix[i][j]);
		}
	}
	fclose(fin);
	return 0;
}

int write_to_file(const char* filename, int result)
{
	FILE* fout;
	fout = fopen(filename, "w");
	if (fout)
	{
		fprintf(fout, "%d", result);
		fclose(fout);
		return 0;
	}
	return -1;
}

int get_line_number(double** matrix, int matrix_size)
{
	int line_number = 0; double sum = 0;
	double* sum_arr = (double*)malloc(sizeof(double) * matrix_size);
	for (int i = 0; i < matrix_size; i++)
	{
		for (int j = 0; j < matrix_size; j++)
		{
			sum += matrix[i][j];
		}
		sum_arr[i] = sum;
		sum = 0;
	}

	double max = sum_arr[0];
	for (int i = 0; i < matrix_size; i++)
	{
		if (max < sum_arr[i])
		{
			max = sum_arr[i];
			line_number = i;
		}
	}
	free(sum_arr);
	return line_number;
}

int main()
{	
	srand(time(NULL));
	const char filename_in[] = "fin.txt";
	const char filename_out[] = "fout.txt";
	int read_err, write_err, matrix_size = 0;
	FILE* fin; double** matrix;
	
	read_err = get_matrix_size(filename_in, &matrix_size, &fin);
	if (read_err == 0)
	{
		fill_initial_file(filename_in, matrix_size);
		matrix = (double**)malloc(sizeof(double*) * matrix_size);
		read_from_file(matrix, matrix_size, fin);
	
		write_err = write_to_file(filename_out, get_line_number(matrix, matrix_size));
		free(matrix);
		if (write_err == 0)
		{
			return 0;
		}
		return -2;
	}
	return -1;
}