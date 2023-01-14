#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define tan_alpha(x1, x2, y1, y2) ((y2 - y1) / (x2 - x1))
#define free_coefficient(y, k, x) (y - k * x)
#define points_distance(x1, x2, y1, y2) (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)))
#define epsilon 0.0000000001

struct Point
{
	double x, y;
};

struct Segment
{
	Point begin, end;
	double k, b;
};

struct Rectangle
{
	Point* points_arr;
	Segment* segments_arr;
};

void swap_coordinates(double* coor_1, double* coor_2)
{
	double temp = *coor_1;
	*coor_1 = *coor_2;
	*coor_2 = temp;
}

int are_equal(double a, double b)
{
	if (fabs(a - b) <= epsilon * fmax(fabs(a), fabs(b)))
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

int are_crossing(Segment seg_1, Segment seg_2)
{
	Point im_point;
	double k1 = 0, k2 = 0, b1, b2;

	if (is_bigger(seg_1.begin.x, seg_1.end.x))
	{
		swap_coordinates(&seg_1.begin.x, &seg_1.end.x);
		swap_coordinates(&seg_1.begin.y, &seg_1.end.y);
	}
	if (is_bigger(seg_2.begin.x, seg_2.end.x))
	{
		swap_coordinates(&seg_2.begin.x, &seg_2.end.x);
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
				&& ((is_bigger(im_point.y, seg_2.begin.y) && is_bigger(seg_2.end.y, im_point.y))
					|| (is_bigger(seg_2.begin.y, im_point.y) && is_bigger(im_point.y, seg_2.end.y)))
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

			if (is_bigger(im_point.x, seg_2.begin.x, 0) && is_bigger(seg_2.end.x, im_point.x, 0)
				&& is_bigger(im_point.y, seg_1.begin.y, 0) && is_bigger(seg_1.end.y, im_point.y, 0))
			{
				return 1;
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
				&& ((is_bigger(im_point.y, seg_1.begin.y) && is_bigger(seg_1.end.y, im_point.y))
					|| (is_bigger(seg_1.begin.y, im_point.y) && is_bigger(im_point.y, seg_1.end.y)))
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

			if (is_bigger(im_point.x, seg_1.begin.x, 0) && is_bigger(seg_1.end.x, im_point.x, 0)
				&& is_bigger(im_point.y, seg_2.begin.y, 0) && is_bigger(seg_2.end.y, im_point.y, 0))
			{
				return 1;
			}
			return 0;
		}
		else
		{
			printf("%.4lf %.4lf", seg_2.begin.y, seg_1.end.y);
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

double get_segments_dist(Segment seg_1, Segment seg_2)
{
	double* distances_arr = (double*)malloc(sizeof(double) * 4);
	double min_distance;

	if (are_crossing(seg_1, seg_2))
	{
		return 0;
	} 

	if (are_equal(seg_1.begin.x, seg_1.end.x) && (are_equal(seg_2.begin.y, seg_1.begin.y) || are_equal(seg_2.begin.y, seg_1.end.y))) 
	{
		if (are_equal(seg_2.begin.x, seg_2.end.x)) 
		{	
			min_distance = fabs(seg_1.begin.x - seg_2.begin.x);
			return min_distance;
		}
	}
	else
	{
		seg_1.k = tan_alpha(seg_1.begin.x, seg_1.end.x, seg_1.begin.y, seg_1.end.y);
		seg_1.b = free_coefficient(seg_1.begin.y, seg_1.k, seg_1.begin.x);
	}

	if (are_equal(seg_2.begin.x, seg_2.end.x) && (are_equal(seg_2.begin.y, seg_1.begin.y) || are_equal(seg_2.begin.y, seg_1.end.y)))
	{
		if (are_equal(seg_1.begin.x, seg_1.end.x))
		{	
			seg_1.k = tan_alpha(seg_1.begin.x, seg_1.end.x, seg_1.begin.y, seg_1.end.y);
			min_distance = fabs(seg_1.begin.x - seg_2.begin.x);
			return min_distance;
		}
	}
	else
	{
		seg_2.k = tan_alpha(seg_2.begin.x, seg_2.end.x, seg_2.begin.y, seg_2.end.y);
		seg_2.b = free_coefficient(seg_2.begin.y, seg_2.k, seg_2.begin.x);
	}

	distances_arr[0] = points_distance(seg_1.begin.x, seg_2.begin.x, seg_1.begin.y, seg_2.begin.y);
	distances_arr[1] = points_distance(seg_1.begin.x, seg_2.end.x, seg_1.begin.y, seg_2.end.y);

	distances_arr[2] = points_distance(seg_1.end.x, seg_2.end.x, seg_1.end.y, seg_2.end.y);
	distances_arr[3] = points_distance(seg_1.end.x, seg_2.begin.x, seg_1.end.y, seg_2.begin.y);

	min_distance = distances_arr[0];
	for (int i = 1; i < 4; i++)
	{
		if (min_distance > distances_arr[i])
		{
			min_distance = distances_arr[i];
		}
	}
	free(distances_arr);
	return min_distance;	
}

double get_rectangles_dist(Rectangle* rectangles_arr)
{	
	Rectangle rec_1 = rectangles_arr[0], rec_2 = rectangles_arr[1];
	int h = 0;
	double min_distance, distance;
	double* distances_arr = (double*)malloc(sizeof(double) * 16);
	Segment seg;

	for (int i = 0; i < 4; i++)
	{
		for (int c = 0; c < 4; c++)
		{
			distance = get_segments_dist(rec_1.segments_arr[i], rec_2.segments_arr[c]);
			distances_arr[h] = distance;
			h++;
		}
	}

	min_distance = distances_arr[0];
	for (int i = 1; i < 16 - 1; i++)
	{
		if (min_distance > distances_arr[i])
		{
			min_distance = distances_arr[i];
		}
	}
	printf("\n%.4lf\n", min_distance);
	free(distances_arr);
	return min_distance;
}

int read_from_file(const char* filename, Rectangle** rectangles_arr)
{
	FILE* fin;
	fin = fopen(filename, "r");
	if (fin)
	{
		*rectangles_arr = (Rectangle*)malloc(sizeof(Rectangle) * 2);
		
		(*rectangles_arr)->points_arr = (Point*)malloc(sizeof(Point) * 4);
		(*rectangles_arr + 1)->points_arr = (Point*)malloc(sizeof(Point) * 4);
		
		(*rectangles_arr)->segments_arr = (Segment*)malloc(sizeof(Segment) * 4);
		(*rectangles_arr + 1)->segments_arr = (Segment*)malloc(sizeof(Segment) * 4);
		
		double x, y;
		Point r1_1, r1_3, r2_1, r2_3;
		Point buffer_p; Segment buffer_s;
		Rectangle *rec_1 = (*rectangles_arr);
		Rectangle *rec_2 = (*rectangles_arr + 1);

		for (int i = 0; i < 2; i++)
		{
			x = 0; y = 0;
			fscanf(fin, "%lf %lf", &x, &y);
			buffer_p.x = x;
			buffer_p.y = y;
			rec_1->points_arr[2 * i] = buffer_p;
		}

		for (int i = 0; i < 2; i++)
		{
			x = 0; y = 0;
			fscanf(fin, "%lf %lf", &x, &y);
			buffer_p.x = x;
			buffer_p.y = y;
			rec_2->points_arr[2 * i] = buffer_p;
		}
		fclose(fin);
		
		r1_1 = rec_1->points_arr[0];
		r1_3 = rec_1->points_arr[2];
		r2_1 = rec_2->points_arr[0];
		r2_3 = rec_2->points_arr[2];

		if (r1_1.x > r1_3.x)
		{
			swap_coordinates(&r1_1.x, &r1_3.x);
			swap_coordinates(&r1_1.y, &r1_3.y);
		}
		if (r2_1.x > r2_3.x)
		{
			swap_coordinates(&r2_1.x, &r2_3.x);
			swap_coordinates(&r2_1.y, &r2_3.y);
		}

		buffer_p.x = r1_1.x;
		buffer_p.y = r1_3.y;
		rec_1->points_arr[1] = buffer_p;

		buffer_p.x = r1_3.x;
		buffer_p.y = r1_1.y;
		rec_1->points_arr[3] = buffer_p;

		buffer_p.x = r2_1.x;
		buffer_p.y = r2_3.y;
		rec_2->points_arr[1] = buffer_p;

		buffer_p.x = r2_3.x;
		buffer_p.y = r2_1.y;
		rec_2->points_arr[3] = buffer_p;

		for (int i = 0; i < 4; i++)
		{	
			buffer_s.begin = rec_1->points_arr[i];
			if (i == 3)
			{
				buffer_s.end = rec_1->points_arr[0];
			}
			else
			{
				buffer_s.end = rec_1->points_arr[i + 1];
			}
			rec_1->segments_arr[i] = buffer_s;

			buffer_s.begin = rec_2->points_arr[i];
			if (i == 3)
			{
				buffer_s.end = rec_2->points_arr[0];
			}
			else
			{
				buffer_s.end = rec_2->points_arr[i + 1];
			}
			rec_2->segments_arr[i] = buffer_s;
		}
		(*rectangles_arr)[0] = *rec_1;
		(*rectangles_arr)[1] = *rec_2;
		return 0;
	}
	return -1;
}

int write_to_file(const char* filename, double distance)
{
	FILE* fout;
	fout = fopen(filename, "w");
	if (fout)
	{
		fprintf(fout, "%lf", distance);
		fclose(fout);
		return 0;
	}
	return -1;
}

int main()
{
	const char filename_in[] = "/Users/denisrusyaev/Visual Studio Code/MSU_Practice/task_8/input.txt";
	const char filename_out[] = "/Users/denisrusyaev/Visual Studio Code/MSU_Practice/task_8/output.txt";
	Rectangle* rectangles_arr;
	int read_err = read_from_file(filename_in, &rectangles_arr), write_err;
	
	if (read_err == 0)
	{
		write_err = write_to_file(filename_out, get_rectangles_dist(rectangles_arr));
		free(rectangles_arr);
	}

	if (write_err == 0)
	{
		return 0;
	}
	return -1;
}