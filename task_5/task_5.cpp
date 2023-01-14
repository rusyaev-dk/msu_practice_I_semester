#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define epsilon 0.0000000001
#define tan_alpha(x1, x2, y1, y2) ((y2 - y1) / (x2 - x1))
#define free_coefficient(y, k, x) (y - k * x)

struct Point
{
	double x, y;
};

struct Segment
{
	Point begin, end;
};

void swap_coordinates(double* coor_1, double* coor_2)
{
	double temp = *coor_1;
	*coor_1 = *coor_2;
	*coor_2 = temp;
}

int are_equal(double a, double b)
{
	if (fabs(a - b) <= epsilon)
	{
		return 1;
	}
	return 0;
}

int is_bigger(double a, double b, int strictly = 1)
{
	if (strictly == 0)
	{
		if (a > b || are_equal(a, b))
			return 1;
	}
	else
	{
		if (a > b)
			return 1;
	}
	return 0;
}

int are_not_equal(double a, double b)
{
	if (fabs(a - b) > epsilon)
	{
		return 1;
	}
	return 0;
}

int are_crossing(Point p1, Point p2, Point p3, Point p4)
{
	Segment seg_1, seg_2; Point im_point;
	double k1 = 0, k2 = 0, b1, b2;
	seg_1.begin = p1;
	seg_1.end = p2;
	seg_2.begin = p3;
	seg_2.end = p4;

		if (is_bigger(seg_1.begin.x, seg_1.end.x))
	{
		swap_coordinates(&seg_1.begin.x, &seg_1.end.x);
		swap_coordinates(&seg_1.begin.y, &seg_1.end.y);
	}
	if (are_equal(seg_1.begin.x, seg_1.end.x) && is_bigger(seg_1.begin.y, seg_1.end.y))
	{
		swap_coordinates(&seg_1.begin.y, &seg_1.end.y);
	}
	if (is_bigger(seg_2.begin.x, seg_2.end.x))
	{
		swap_coordinates(&seg_2.begin.x, &seg_2.end.x);
		swap_coordinates(&seg_2.begin.y, &seg_2.end.y);
	}
	if (are_equal(seg_2.begin.x, seg_2.end.x) && is_bigger(seg_2.begin.y, seg_2.end.y))
	{
		swap_coordinates(&seg_2.begin.y, &seg_2.end.y);
	}

	if (are_equal(seg_1.begin.x, seg_1.end.x))
	{
		if (are_not_equal(seg_2.begin.x, seg_2.end.x) && are_not_equal(seg_2.begin.y, seg_2.end.y))
		{
			k2 = tan_alpha(seg_2.begin.x, seg_2.end.x, seg_2.begin.y, seg_2.end.y);
			b2 = free_coefficient(seg_2.begin.y, k2, seg_2.begin.x);
			im_point.y = k2 * seg_1.begin.x + b2;
			im_point.x = seg_1.begin.x;
			if (is_bigger(im_point.x, seg_2.begin.x, 0) && is_bigger(seg_2.end.x, im_point.x, 0)
				&& ((is_bigger(im_point.y, seg_2.begin.y, 0) && is_bigger(seg_2.end.y, im_point.y, 0))
					|| (is_bigger(seg_2.begin.y, im_point.y, 0) && is_bigger(im_point.y, seg_2.end.y, 0)))
				&& is_bigger(im_point.y, seg_1.begin.y, 0) && is_bigger(seg_1.end.y, im_point.y, 0))
			{
				return 1;
			}
		}
		else if (are_not_equal(seg_2.begin.x, seg_2.end.x))
		{
			k2 = tan_alpha(seg_2.begin.x, seg_2.end.x, seg_2.begin.y, seg_2.end.y);
			b2 = free_coefficient(seg_2.begin.y, k2, seg_2.begin.x);
			im_point.y = k2 * seg_1.begin.x + b2;
			im_point.x = seg_1.begin.x;
			if (is_bigger(seg_1.begin.y, seg_1.end.y))
			{
				if (is_bigger(im_point.x, seg_2.begin.x, 0) && is_bigger(seg_2.end.x, im_point.x, 0)
					&& is_bigger(seg_1.begin.y, im_point.y, 0) && is_bigger(im_point.y, seg_1.end.y, 0))
				{
					return 1;
				}
			}
			else
			{
				if (is_bigger(im_point.x, seg_2.begin.x, 0) && is_bigger(seg_2.end.x, im_point.x, 0)
					&& is_bigger(im_point.y, seg_1.begin.y, 0) && is_bigger(seg_1.end.y, im_point.y, 0))
				{
					return 1;
				}
			}
			return 0;
		}
		else
		{
			if ((are_equal(seg_1.begin.y, seg_2.end.y) || are_equal(seg_2.begin.y, seg_1.end.y))
				&& are_equal(seg_1.begin.x, seg_2.begin.x))
			{
				return 1;
			}
		}
		return 0;
	}
	else
	{
		k1 = tan_alpha(seg_1.begin.x, seg_1.end.x, seg_1.begin.y, seg_1.end.y);
		b1 = free_coefficient(seg_1.begin.y, k1, seg_1.begin.x);
	}

	if (are_equal(seg_2.begin.x, seg_2.end.x))
	{
		if (are_not_equal(seg_1.begin.x, seg_1.end.x) && are_not_equal(seg_1.begin.y, seg_1.end.y))
		{
			k1 = tan_alpha(seg_1.begin.x, seg_1.end.x, seg_1.begin.y, seg_1.end.y);
			b1 = free_coefficient(seg_1.begin.y, k1, seg_1.begin.x);
			im_point.y = k1 * seg_2.begin.x + b1;
			im_point.x = seg_2.begin.x;
			
			if (is_bigger(im_point.x, seg_1.begin.x, 0) && is_bigger(seg_1.end.x, im_point.x, 0)
				&& ((is_bigger(im_point.y, seg_1.begin.y, 0) && is_bigger(seg_1.end.y, im_point.y, 0))
					|| (is_bigger(seg_1.begin.y, im_point.y, 0) && is_bigger(im_point.y, seg_1.end.y, 0)))
				&& is_bigger(im_point.y, seg_2.begin.y, 0) && is_bigger(seg_2.end.y, im_point.y, 0))
			{
				return 1;
			}
		}
		else if (are_not_equal(seg_1.begin.x, seg_1.end.x))
		{	
			k1 = tan_alpha(seg_1.begin.x, seg_1.end.x, seg_1.begin.y, seg_1.end.y);
			b1 = free_coefficient(seg_1.begin.y, k1, seg_1.begin.x);
			im_point.y = k1 * seg_2.begin.x + b1;
			im_point.x = seg_2.begin.x;
			if (is_bigger(seg_2.begin.y, seg_2.end.y))
			{
				if (is_bigger(im_point.x, seg_1.begin.x, 0) && is_bigger(seg_1.end.x, im_point.x, 0)
					&& is_bigger(seg_2.begin.y, im_point.y, 0) && is_bigger(im_point.y, seg_2.end.y, 0))
				{
					return 1;
				}
			}
			else
			{
				if (is_bigger(im_point.x, seg_1.begin.x, 0) && is_bigger(seg_1.end.x, im_point.x, 0)
					&& (is_bigger(im_point.y, seg_2.begin.y, 0) && is_bigger(seg_2.end.y, im_point.y, 0)))
				{
					return 1;
				}
			}
			return 0; 
		}
		else
		{
			if ((are_equal(seg_2.begin.y, seg_1.end.y) || are_equal(seg_1.begin.y, seg_2.end.y))
				&& are_equal(seg_1.begin.x, seg_2.begin.x))
			{
				return 1;
			}
		}
		return 0;
	}
	else
	{
		k2 = tan_alpha(seg_2.begin.x, seg_2.end.x, seg_2.begin.y, seg_2.end.y);
		b2 = free_coefficient(seg_2.begin.y, k2, seg_2.begin.x);
	}


	if (are_equal(k1, k2) && are_not_equal(k1, 0) && are_not_equal(k2, 0))
	{
		return 0;
	}

	if (are_equal(k1, 0) && are_equal(k2, 0))
	{
		if (are_equal(seg_1.end.x, seg_2.begin.x) && are_equal(seg_1.end.y, seg_2.begin.y))
			return 1;
		if (are_equal(seg_2.end.x, seg_1.begin.x) && are_equal(seg_2.end.y, seg_1.begin.y))
			return 1;
		return 0;
	}

	im_point.x = ((b2 - b1) / (k1 - k2));
	im_point.y = k1 * (im_point.x) + b1;

	if (are_equal(k1, 0))
	{
		if (is_bigger(seg_1.end.x, seg_2.begin.x) && are_equal(seg_1.begin.y, seg_2.begin.y)
			&& are_equal(seg_1.begin.y, seg_2.end.y))
		{
			return 1;
		}
		else if (are_not_equal(k2, 0))
		{
			im_point.x = (seg_1.begin.y - b2) / k2;
		}
		else
		{
			return 0;
		}
	}

	if (are_equal(k2, 0))
	{
		if (is_bigger(seg_2.end.x, seg_1.begin.x) && are_equal(seg_2.begin.y, seg_1.begin.y)
			&& are_equal(seg_2.begin.y, seg_1.end.y))
		{
			return 1;
		}
		else if (are_not_equal(k1, 0))
		{
			im_point.x = (seg_2.begin.y - b1) / k1;
		}
		else
		{
			return 0;
		}
	}

	if (is_bigger(im_point.x, seg_1.begin.x, 0) && is_bigger(seg_1.end.x, im_point.x, 0)
		&& is_bigger(im_point.x, seg_2.begin.x, 0) && is_bigger(seg_2.end.x, im_point.x, 0))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int bl_self_intersects(Point *points_arr, int array_size)
{	
	if (array_size < 4)
	{
		return 0;
	}
	for (int i = 0; i < (array_size - 1); i++)
	{
		for (int j = i + 2; j < (array_size - 1); j++)
		{	
			if (are_crossing(points_arr[i], points_arr[i + 1], points_arr[j], points_arr[j + 1]))
			{
				printf("\nCROSSING:\n"); 
				printf("(%.2lf %.2lf) (%.2lf %.2lf) (%.2lf %.2lf) (%.2lf %.2lf)",
					points_arr[i].x, points_arr[i].y, points_arr[i + 1].x, points_arr[i + 1].y, 
					points_arr[j].x, points_arr[j].y, points_arr[j + 1].x, points_arr[j + 1].y);
				return 1;
			}
		}
	}
	printf("NOT CROSSING\n");
	return 0;
}

int read_from_file(const char* filename, Point** points_arr, int* array_size)
{
	FILE* fin;
	fin = fopen(filename, "r");
	if (fin)
	{	
		if (fscanf(fin, "%d", array_size) > 0)
		{	
			*points_arr = (Point*)malloc(sizeof(Point) * (*array_size));
			double x, y; Point point;
			for (int i = 0; i < (*array_size); i++)
			{
				if (fscanf(fin, "%lf", &x) > 0)
				{
					point.x = x;
				}
				else point.x = 0;

				if (fscanf(fin, "%lf", &y) > 0)
				{
					point.y = y;
				}
				else point.y = 0;

				*((*points_arr) + i) = point;
			}

			fclose(fin);
			return 0;
		}
		return -2;
	}
	return -1;
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
	else
	{
		return -1;
	}
}

int main()
{
	const char filename_in[] = "/Users/denisrusyaev/Visual Studio Code/MSU_Practice/task_5/input.txt";
	const char filename_out[] = "/Users/denisrusyaev/Visual Studio Code/MSU_Practice/task_5/output.txt";
	Point* points_arr; int array_size = 0;

	if (read_from_file(filename_in, &points_arr, &array_size) == 0)
	{
		write_to_file(filename_out, bl_self_intersects(points_arr, array_size));
	}
	return 0;
}