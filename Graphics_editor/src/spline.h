#include <algorithm>
#include "point.h"
#include "spline_point.h"
//#include "interpolation_canvas.h"

#ifndef SPLINE_H
#define SPLINE_H

const int MAX_COUNT_OF_POINTS = 100;

class Spline {
  public:
	Point* points;
	size_t count_of_points;

	Spline() {
		points = new Point[MAX_COUNT_OF_POINTS];
		count_of_points = 0;
	}

	int add_point(const Point new_point) {
		points[count_of_points] = new_point;
		++count_of_points;
	
		qsort(points, count_of_points, sizeof(Point), compare);
	
		for(int i = 0; i < count_of_points; ++i)
			if(points[i] == new_point)
				return i;
		return 0;
	}

	void update_coords(Point* &visual_points, const int n, Point left_corner) {
		int index = 0;

		//printf("\tinterpolation_point\n");
		for(size_t i = 0; i < n; ++i) {
			//printf("%d <= %d && %d <= %d\n", (int)points[index].x, i + (int)left_corner.x,
			//								i + (int)left_corner.x, (int)points[index + 1].x);
			if(!((int)points[index].x <= i + (int)left_corner.x &&
				 i + (int)left_corner.x <= (int)points[index + 1].x)) {
				//printf("%d\n", index);
				++index;
			}

			visual_points[i].y = get_y_from_x(points[index], points[index + 1], i + left_corner.x);
		}
	}

	void catmull_rom(Point* &visual_points, const int n, Point left_corner, const int count_of_base_points);

	double get_t(const Point& p1, const Point& p2, const double t, const double alpha) {
		Point d = p2;
		d -= p1;

		double scalar = d.scalar_mult(d);
		scalar = std::pow(scalar, alpha * 0.5);

		return scalar + t;
	}

	double linear_spline(const double a, const double b, const double t) {
		if(t >= 0 && t <= 1)
			return a + (b - a) * t;
		if(t < 0)
			return a;
		return b;
	}

	int catmull_rom_get_y_from_x(const double x, Point& p1, Point& p2, Point& p3, Point& p4, double t, const double alpha = 0.5) {
		double t1 = 0;
		double t2 = get_t(p1, p2, t1, alpha);
		double t3 = get_t(p2, p3, t2, alpha);
		double t4 = get_t(p3, p4, t3, alpha);

		t = linear_spline(t2, t3, t);

		Point A1 = p1 * ((t2 - t) / (t2 - t1)) + p2 * ((t - t1) / (t2 - t1));
		Point A2 = p2 * ((t3 - t) / (t3 - t2)) + p3 * ((t - t2) / (t3 - t2));
		Point A3 = p3 * ((t4 - t) / (t4 - t3)) + p4 * ((t - t3) / (t4 - t3));

		Point B1 = A1 * ((t3 - t) / (t3 - t1)) + A2 * ((t - t1) / (t3 - t1));
		Point B2 = A2 * ((t4 - t) / (t4 - t2)) + A3 * ((t - t2) / (t4 - t2));

		Point C= B1 * ((t3 - t) / (t3 - t2)) + B2 * ((t - t2) / (t3 - t2));

		return C.y;
	}

	int get_y_from_x(const Point p_begin, const Point p_end, const int x) {
		if(p_end.x == p_begin.x) {
			return x - p_begin.x + p_begin.y;
		} else {
			return (p_end.y - p_begin.y) * (x - p_begin.x) / (p_end.x - p_begin.x) + p_begin.y;
		}
	}

	void update_position_from_delta(Point delta) {
		for(int i = 0; i < count_of_points; ++i)
			points[i] -= delta;
	}	
};

#endif