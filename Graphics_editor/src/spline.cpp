#include "spline.h"

void Spline::catmull_rom(Point* &visual_points, const int n, Point left_corner, const int count_of_base_points) {
	int index = 0;

	for(size_t i = 1; i < n - 3; ++i) {
		while(!  ((int)points[index].x <= i + (int)left_corner.x 	&&
				i + (int)left_corner.x <= (int)points[index + 1].x) &&
				index + 2 < count_of_base_points) {
			++index;
		}

		double now_x = i + left_corner.x;
		visual_points[i].y = catmull_rom_get_y_from_x(now_x, points[index - 1], points[index], points[index + 1], points[index + 2],
														(now_x - points[index].x) / (points[index + 1].x - points[index].x));
	}
}
