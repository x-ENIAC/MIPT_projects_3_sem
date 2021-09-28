#include "my_vector.h"
#include "point.h"
#include "collision_response.h"

void collision_response_molecule_with_molecule(Molecule* first, Molecule* second) {

	/*first->set_is_active ( false );
	second->set_is_active( false );  

	first->set_colour  ( WHITE );
	second->set_colour ( WHITE );

	first->set_center  ( Point(0.0, 0.0) );
	second->set_center ( Point(0.0, 0.0) );

	first->set_radius ( 0.0 );
	second->set_radius( 0.0 );*/

	first->make_inactive();
	second->make_inactive();
}

void collision_response_molecule_with_rectangle(Molecule* first, Rectangle* second) {

	second->set_height ( second->get_height() + 30.0 );
	second->set_width  ( second->get_width()  + 30.0 );
	second->set_mass   ( second->get_mass() + first->get_mass() );

	/*first->set_is_active ( false );
	first->set_colour  ( WHITE );
	first->set_center  ( Point(0.0, 0.0) );
	first->set_radius ( 0.0 );*/
	first->make_inactive();
}

void collision_response_rectangle_with_molecule(Rectangle* first, Molecule* second) {
	collision_response_molecule_with_rectangle(second, first);
}

void collision_response_rectangle_with_rectangle(Rectangle* first, Rectangle* second) {

	/*first->set_is_active ( false );
	second->set_is_active( false );  

	first->set_colour  ( WHITE );
	second->set_colour ( WHITE );

	first->set_center  ( Point(0.0, 0.0) );
	second->set_center ( Point(0.0, 0.0) );

	first->set_height ( 0.0 );
	second->set_height( 0.0 );	

	first->set_width ( 0.0 );
	second->set_width( 0.0 );*/

	first->make_inactive();
	second->make_inactive();
}
