#include "my_vector.h"
#include "point.h"
#include "collision_response.h"

void collision_response_molecule_with_molecule(Molecule* first, Molecule* second) {

	first->make_inactive();
	second->make_inactive();
}

void collision_response_molecule_with_rectangle(Molecule* first, Rectangle* second) {

	second->set_height ( second->get_height() + 30.0 );
	second->set_width  ( second->get_width()  + 30.0 );
	second->set_mass   ( second->get_mass() + first->get_mass() );

	first->make_inactive();
}

void collision_response_rectangle_with_molecule(Rectangle* first, Molecule* second) {
	collision_response_molecule_with_rectangle(second, first);
}

void collision_response_rectangle_with_rectangle(Rectangle* first, Rectangle* second) {
	first->make_inactive();
	second->make_inactive();
}
