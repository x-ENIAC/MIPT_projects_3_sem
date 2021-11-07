#include "point.h"

bool intersection_of_segments(Point first_begin, Point first_end, Point second_begin, Point second_end) {
	double a_begin_x = first_begin.x, a_begin_y = first_begin.y;
	double a_end_x = second_begin.x, a_end_y = second_begin.y;

	double b_begin_x = first_begin.x, b_begin_y = first_begin.y;
	double b_end_x = second_end.x, b_end_y = second_end.y;

	double c_begin_x = first_end.x, c_begin_y = first_end.y;
	double c_end_x = second_begin.x, c_end_y = second_begin.y;

	double d_begin_x = first_end.x, d_begin_y = first_end.y;
	double d_end_x = second_end.x, d_end_y = second_end.y;			

	a_end_x -= a_begin_x;
	a_end_y -= a_begin_y;
	a_begin_x = a_begin_y = 0;

	b_end_x -= b_begin_x;
	b_end_y -= b_begin_y;
	b_begin_x = b_begin_y = 0;

	c_end_x -= c_begin_x;
	c_end_y -= c_begin_y;
	c_begin_x = c_begin_y = 0;

	d_end_x -= d_begin_x;
	d_end_y -= d_begin_y;		
	d_begin_x = d_begin_y = 0;	

	return ((a_end_x * b_end_y - a_end_y * b_end_x) * (c_end_x * d_end_y - c_end_y * d_end_x) <= 0.0);
}

bool segment_into_segment(Point first_begin, Point first_end, Point second_begin, Point second_end) {
	return ((first_begin.x <= second_begin.x && second_end.x <= first_end.x) ||
			(first_begin.x <= second_end.x && second_begin.x <= first_end.x) ||

			(first_begin.y <= second_begin.y && second_end.y <= first_end.y) ||
			(first_begin.y <= second_end.y && second_begin.y <= first_end.y) ||

			(second_begin.x <= first_begin.x && first_end.x <= second_end.x) ||
			(second_begin.x <= first_end.x && first_begin.x <= second_end.x) ||
		   
			(second_begin.y <= first_begin.y && first_end.y <= second_end.y) ||
			(second_begin.y <= first_end.y && first_begin.y <= second_end.y));       
}

int compare(const void* p1, const void* p2) {
	Point p1_ = *(Point*)p1, p2_ = *(Point*)p2;
	return (p1_.x > p2_.x || p1_.x == p2_.x && p1_.y > p2_.y);
}