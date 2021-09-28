#include <SDL2/SDL.h>
#include "point.h"
#include "colour.h"
#include "rectangle.h"

#ifndef BUTTON_H
#define BUTTON_H

enum Button_status {
	IS_PUSH 	= 1,
	IS_NOT_PUSH = 2,
};

class Button {
  public:
	Rectangle* shape_rect;
	Button_status status;

	Button() {}

	Button(const Point par_point, const Colour par_color, const double par_width, const double par_height) {

		shape_rect = new Rectangle;

	  	shape_rect->set_center ( par_point );
	  	shape_rect->set_mass   (  0.0  );

	  	shape_rect->set_x_speed(  0.0  );
	  	shape_rect->set_y_speed(  0.0  );

	  	shape_rect->set_colour ( par_color );

	  	shape_rect->set_width  ( par_width );
	  	shape_rect->set_height ( par_height );

	  	shape_rect->set_type   ( BUTTON );

	  	shape_rect->set_is_active ( false );

	  	status = IS_NOT_PUSH;
	}

	void draw_button(SDL_Renderer* render) {
		shape_rect->draw_molecule(render);
	}

	virtual void add_new_object(Shape_manager* shape_manager) {};
};

#endif