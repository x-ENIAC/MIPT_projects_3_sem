#include "collision_detection.h"

double get_square_distance_between_points(double x1, double y1, double x2, double y2) {
	return ((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

double get_square_distance_between_points(Point first, Point second) {
	return ((first.x - second.x) * (first.x - second.x) + (first.y - second.y) * (first.y - second.y));
}

bool is_point_belongs_to_rectangle(Rectangle* rect, Point point) {
	double x_left_up = rect->get_x_center() - rect->width  / 2.0;
	double y_left_up = rect->get_y_center() - rect->height / 2.0;

	double x_right_down = rect->get_x_center() + rect->width  / 2.0;
	double y_right_down = rect->get_y_center() + rect->height / 2.0;

	double x_point = point.x, y_point = point.y;	

	return (x_left_up <= x_point && x_point <= x_right_down) &&
		   (y_left_up <= y_point && y_point <= y_right_down);
}

bool collision_detection_circle_with_circle(Circle* first, Circle* second) {
	return ( (first->get_x_center() - second->get_x_center()) * (first->get_x_center() - second->get_x_center()) + 
             (first->get_y_center() - second->get_y_center()) * (first->get_y_center() - second->get_y_center()) <= 
             (first->get_radius()   + second->get_radius())   * (first->get_radius()   + second->get_radius()) );	
}

bool collision_detection_circle_with_rectangle(Circle* first, Rectangle* second) {
	double x_left_up = second->get_x_center() - second->width  / 2.0;
	double y_left_up = second->get_y_center() - second->height / 2.0;

	double x_right_down = second->get_x_center() + second->width  / 2.0;
	double y_right_down = second->get_y_center() + second->height / 2.0;	

	Point circle_center = first->get_center();
	double x_center = circle_center.x, y_center = circle_center.y, radius = first->get_radius();

	/*if(x_center <= x_left_up && y_center <= y_left_up && get_square_distance_between_points(first->get_center(), Point(x_left_up, y_left_up)) <= radius * radius 									||
	  
	   x_left_up <= x_center && x_center <= x_right_down && y_center <= y_left_up && get_square_distance_between_points(first->get_center(), Point(x_center, y_left_up)) <= radius * radius 		||

	   x_right_down <= x_center && y_center <= y_left_up && get_square_distance_between_points(first->get_center(), Point(x_right_down, y_left_up)) <= radius * radius 								||

	   x_center <= x_left_up && y_left_up <= y_center && y_center <= y_right_down && get_square_distance_between_points(first->get_center(), Point(x_left_up, y_center)) <= radius * radius 		||

	   is_point_belongs_to_rectangle(second, first->get_center())																																	||

	   x_right_down <= x_center && y_left_up <= y_center && y_center <= y_right_down && get_square_distance_between_points(first->get_center(), Point(x_right_down, y_center)) <= radius * radius 	||

	   x_center <= x_left_up && y_right_down <= y_center && get_square_distance_between_points(first->get_center(), Point(x_left_up, y_right_down)) <= radius * radius 								||

	   x_left_up <= x_center && x_center <= x_right_down && y_right_down <= y_center && get_square_distance_between_points(first->get_center(), Point(x_center, y_right_down)) <= radius * radius 	||

	   x_right_down <= x_center && y_right_down <= y_center && get_square_distance_between_points(first->get_center(), Point(x_right_down, y_right_down)) <= radius * radius)	   
		
		return true;*/
	

	if(distance_from_point_to_segment( circle_center, Point(x_left_up, y_left_up), Point(x_right_down, y_left_up)) <= radius ||
	   distance_from_point_to_segment( circle_center, Point(x_right_down, y_left_up), Point(x_right_down, y_right_down)) <= radius ||
	   distance_from_point_to_segment( circle_center, Point(x_left_up, y_right_down), Point(x_right_down, y_right_down)) <= radius ||
	   distance_from_point_to_segment( circle_center, Point(x_left_up, y_left_up), Point(x_left_up, y_right_down)) <= radius) {

		//printf("center (%lg, %lg), radius %lg\n", x_center, y_center, radius);
		//printf("x_left_up %lg, x_right_down %lg, y_left_up %lg, y_right_down %lg\n", x_left_up, x_right_down, y_left_up, y_right_down);

		/*printf("%lg, %lg, %lg, %lg\n", distance_from_point_to_segment( circle_center, Point(x_left_up, y_left_up), Point(x_right_down, y_left_up)),
								   	   distance_from_point_to_segment( circle_center, Point(x_right_down, y_left_up), Point(x_right_down, y_right_down)),
	   								   distance_from_point_to_segment( circle_center, Point(x_left_up, y_right_down), Point(x_right_down, y_right_down)),
	   								   distance_from_point_to_segment( circle_center, Point(x_left_up, y_left_up), Point(x_left_up, y_right_down)));	
	   	printf("radius %lg\n\n", radius);	*/
	   	return true;
	}

	return false;
}

bool collision_detection_rectangle_with_circle(Rectangle* first, Circle* second) {
	return collision_detection_circle_with_rectangle(second, first);
}

bool collision_detection_rectangle_with_rectangle(Rectangle* first, Rectangle* second) {
	double first_x_left_up = first->get_x_center() - first->width  / 2.0;
	double first_y_left_up = first->get_y_center() - first->height / 2.0;

	double first_x_right_down = first->get_x_center() + first->width  / 2.0;
	double first_y_right_down = first->get_y_center() + first->height / 2.0;	


	double second_x_left_up = second->get_x_center() - second->width  / 2.0;
	double second_y_left_up = second->get_y_center() - second->height / 2.0;

	double second_x_right_down = second->get_x_center() + second->width  / 2.0;
	double second_y_right_down = second->get_y_center() + second->height / 2.0;	
 
	Point first_left_up (first_x_left_up,    first_y_left_up), first_left_down (first_x_left_up,    first_y_right_down);
	Point first_right_up(first_x_right_down, first_y_left_up), first_right_down(first_x_right_down, first_y_right_down);

	Point second_left_up (second_x_left_up,    second_y_left_up), second_left_down (second_x_left_up,    second_y_right_down);
	Point second_right_up(second_x_right_down, second_y_left_up), second_right_down(second_x_right_down, second_y_right_down);

	/*if(intersection_of_segments(first_right_up, first_right_down, second_left_up, second_left_down) &&
	   intersection_of_segments(second_left_up, second_left_down, first_right_up, first_right_down)    || 

	   intersection_of_segments(first_left_up, first_left_down, second_right_up, second_right_down) &&
	   intersection_of_segments(second_right_up, second_right_down, first_left_up, first_left_down)    ||

	   intersection_of_segments(first_left_up, first_right_up, second_left_down, second_right_down) && 
	   intersection_of_segments(second_left_down, second_right_down, first_left_up, first_right_up)    || 

	   intersection_of_segments(first_left_down, first_right_down, second_left_up, second_left_down) &&
	   intersection_of_segments(second_left_up, second_left_down, first_left_down, first_right_down))
		return true;

	if(segment_into_segment(first_right_up, first_right_down, second_left_up, second_left_down) &&
	   segment_into_segment(second_left_up, second_left_down, first_right_up, first_right_down)    || 

	   segment_into_segment(first_left_up, first_left_down, second_right_up, second_right_down) &&
	   segment_into_segment(second_right_up, second_right_down, first_left_up, first_left_down)    ||

	   segment_into_segment(first_left_up, first_right_up, second_left_down, second_right_down) && 
	   segment_into_segment(second_left_down, second_right_down, first_left_up, first_right_up)    || 

	   segment_into_segment(first_left_down, first_right_down, second_left_up, second_left_down) &&
	   segment_into_segment(second_left_up, second_left_down, first_left_down, first_right_down))
		return true;*/

	if(is_point_belongs_to_rectangle(second, Point( first_x_left_up, first_y_left_up ))    	  || 
	   is_point_belongs_to_rectangle(second, Point( first_x_left_up, first_y_right_down )) 	  || 
	   is_point_belongs_to_rectangle(second, Point( first_x_right_down, first_y_left_up ))    || 
	   is_point_belongs_to_rectangle(second, Point( first_x_right_down, first_y_right_down )))
		return true;

	//if(intersection_of_segments( Point() ))

	return false;
}
