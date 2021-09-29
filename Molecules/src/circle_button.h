#include <SDL2/SDL.h>
#include "point.h"
#include "colour.h"
#include "molecule.h"
#include "button.h"

#ifndef CIRCLE_BUTTON_H
#define CIRCLE_BUTTON_H

class Circle_button : public Button {
  public:

	Circle_button(const Point par_point, const Colour par_color, const double par_width, const double par_height) : 
	  Button(par_point, par_color, par_width, par_height) {}

	void draw_button(SDL_Renderer* render) {
		shape_rect->draw_molecule(render);
	}

	virtual void add_new_object(Shape_manager* shape_manager) {
		Molecule* new_circle = new Molecule;

		new_circle->set_center ( Point(rand() % 500, rand() % 500) );
		new_circle->set_mass   ( 1 );
		new_circle->set_radius ( rand() % 10 + 10.0 );

		new_circle->set_x_speed( rand() % 10 + 1 );
		new_circle->set_y_speed( rand() % 10 * -1 + 1 );

		new_circle->set_type   ( CIRCLE );
		new_circle->set_colour ( Colour(rand() % 256, rand() % 256, rand() % 256, 255) );

		new_circle->set_is_active ( true );
	  	new_circle->set_owner     ( SHAPE_OWNER_SHAPE_CLASS );		

		shape_manager->add_object(new_circle);
	}
};

#endif