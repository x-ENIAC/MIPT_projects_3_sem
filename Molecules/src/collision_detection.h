#include "object.h"
#include "circle.h"
#include "rectangle.h"
#include "my_vector.h"

#ifndef COLLISION_DETECTION_TABLE_H
#define COLLISION_DETECTION_TABLE_H

typedef bool (*Ptr_to_func_into_detection)(Object*, Object*);

bool collision_detection_circle_with_circle  (Circle * first, Circle * second);
bool collision_detection_circle_with_rectangle (Circle * first, Rectangle* second);
bool collision_detection_rectangle_with_circle (Rectangle* first, Circle * second);
bool collision_detection_rectangle_with_rectangle(Rectangle* first, Rectangle* second);
double get_square_distance_between_points(double x1, double y1, double x2, double y2);
bool is_point_belongs_to_rectangle(Rectangle* rect, Point point);

struct Collision_detection_table {
  public:
	Ptr_to_func_into_detection collide_table[3][3];
	int size_table;

	Collision_detection_table(const int par_size_table) {
		size_table  = par_size_table;

		collide_table[CIRCLE]   [CIRCLE]    = (Ptr_to_func_into_detection)collision_detection_circle_with_circle;
		collide_table[CIRCLE]   [RECTANGLE] = (Ptr_to_func_into_detection)collision_detection_circle_with_rectangle;
		collide_table[RECTANGLE][CIRCLE]    = (Ptr_to_func_into_detection)collision_detection_rectangle_with_circle;
		collide_table[RECTANGLE][RECTANGLE] = (Ptr_to_func_into_detection)collision_detection_rectangle_with_rectangle;

		printf("Collision_detection_table construct is okey\n");
	}
};

#endif
