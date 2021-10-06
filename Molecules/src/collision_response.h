#include "object.h"
#include "circle.h"
#include "rectangle.h"

#ifndef COLLISION_RESPONSE_TABLE_H
#define COLLISION_RESPONSE_TABLE_H

typedef void (*Ptr_to_func_into_response)(Object*, Object*);

void collision_response_circle_with_circle  (Circle * first, Circle * second);
void collision_response_circle_with_rectangle (Circle * first, Rectangle* second);
void collision_response_rectangle_with_circle (Rectangle* first, Circle * second);
void collision_response_rectangle_with_rectangle(Rectangle* first, Rectangle* second);

struct Collision_response_table {
  public:
	Ptr_to_func_into_response collire_table[3][3];
	int size_table;

	Collision_response_table(const int par_size_table) {
		size_table  = par_size_table;

		collire_table[CIRCLE]   [CIRCLE]    = (Ptr_to_func_into_response)collision_response_circle_with_circle;
		collire_table[CIRCLE]   [RECTANGLE] = (Ptr_to_func_into_response)collision_response_circle_with_rectangle;
		collire_table[RECTANGLE][CIRCLE]    = (Ptr_to_func_into_response)collision_response_rectangle_with_circle;
		collire_table[RECTANGLE][RECTANGLE] = (Ptr_to_func_into_response)collision_response_rectangle_with_rectangle;		
	}

};

#endif
