#include <algorithm>
#include "point.h"
#include "interpolation_point.h"
//#include "interpolation_canvas.h"

#ifndef INTERPOLATOR_H
#define INTERPOLATOR_H

const int MAX_COUNT_OF_POINTS = 100;

class Interpolator {
  public:
  	Point* points;
  	size_t count_of_points;

  	Interpolator() {
  		points = new Point[MAX_COUNT_OF_POINTS];
  		count_of_points = 0;
  	}

  	void add_point(const Point new_point) {
  		points[count_of_points] = new_point;
  		++count_of_points;

  		qsort(points, count_of_points, sizeof(Point), compare);
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


	int get_y_from_x(const Point p_begin, const Point p_end, const int x) {
		if(p_end.x == p_begin.x) {
			return x - p_begin.x + p_begin.y;
		} else {
			return (p_end.y - p_begin.y) * (x - p_begin.x) / (p_end.x - p_begin.x) + p_begin.y;
		}
	}  	
};

#endif