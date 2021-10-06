#include <SDL2/SDL.h>
#include "point.h"
#include "colour.h"
#include "rectangle.h"
#include "button.h"

#ifndef RECTANGLE_BUTTON_H
#define RECTANGLE_BUTTON_H

class Rectangle_button : public Button {
  public:

	Rectangle_button(const Point par_point, const Colour par_color, const double par_width, const double par_height) :
	  Button(par_point, par_color, par_width, par_height) {}

	void draw_button(SDL_Renderer* render) {
		object_rect->draw_molecule(render);
	}

	virtual void add_new_object(Object_manager* object_manager) {
		Rectangle* new_rect = new Rectangle;

		new_rect->set_center ( Point(rand() % 500, rand() % 500) );
		new_rect->set_mass   ( rand() % 9 + 1 );

		new_rect->set_x_speed( rand() % 10 + 1 );
		new_rect->set_y_speed( rand() % 10 * -1 + 1 );

		new_rect->set_width  ( rand() % 30 + 10 );
		new_rect->set_height ( rand() % 30 + 10 );

		new_rect->set_type   ( RECTANGLE );
		new_rect->set_colour ( Colour(rand() % 256, rand() % 256, rand() % 256, 255) );

		new_rect->set_is_active ( true );
		new_rect->set_owner     ( OBJECT_OWNER_OTHER_CLASS );

		object_manager->add_object(new_rect);
	}
};

#endif