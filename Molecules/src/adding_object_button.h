/*#include <SDL2/SDL.h>
#include "point.h"
#include "colour.h"
#include "circle.h"
#include "button.h"

#ifndef ADDING_OBJECT_BUTTON_H
#define ADDING_OBJECT_BUTTON_H

class Adding_object_button : public Button {
  public:
  	Type_object type_adding_object;

	Adding_object_button(const Point par_point, const Colour par_color, const double par_width, const double par_height, const Type_object par_type_adding_object) : 
	  Button(par_point, par_color, par_width, par_height) {
	  	type_adding_object = par_type_adding_object;
	  }

	void draw_button(SDL_Renderer* render) {
		object_rect->draw_molecule(render);
	}

	virtual void add_new_object(Object_manager* object_manager) {
		Object* new_object = new Object;
		if(type_adding_object == CIRCLE) {
			Circle* new_circle = new Circle;
			
			new_circle->set_center ( Point(rand() % 500, rand() % 500) );
			new_circle->set_mass   ( 1 );
			new_circle->set_radius ( rand() % 10 + 10.0 );

			new_circle->set_x_speed( rand() % 10 + 1 );
			new_circle->set_y_speed( rand() % 10 * -1 + 1 );

			new_circle->set_type   ( CIRCLE );
			new_circle->set_colour ( Colour(rand() % 256, rand() % 256, rand() % 256, 255) );

			new_circle->set_is_active ( true );
		  	new_circle->set_owner     ( OBJECT_OWNER_OBJECT_CLASS );
		  	new_object = new_circle;
		} else {
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

			new_object = new_rect;
		}

		object_manager->add_object(new_object);
	}
};

#endif*/