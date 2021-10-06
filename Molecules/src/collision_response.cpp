#include "my_vector.h"
#include "point.h"
#include "collision_response.h"

void collision_response_circle_with_circle(Circle* first, Circle* second) {

	first->make_inactive();
	second->make_inactive();
}

void collision_response_circle_with_rectangle(Circle* first, Rectangle* second) {

	second->set_height ( second->get_height() + sqrt(first->get_radius()) );
	second->set_width  ( second->get_width()  + sqrt(first->get_radius()) );
	second->set_mass   ( second->get_mass() + first->get_mass() );

	first->make_inactive();
}

void collision_response_rectangle_with_circle(Rectangle* first, Circle* second) {
	collision_response_circle_with_rectangle(second, first);
}

void collision_response_rectangle_with_rectangle(Rectangle* first, Rectangle* second) {
	first->make_inactive();
	second->make_inactive();
}
