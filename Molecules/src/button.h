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

class Button : public Rectangle {
  public:
	Button_status status;

	Button(const Point par_point, const Colour par_color, const double par_width, const double par_height, const Type_object par_type) {

		set_center ( par_point );
		set_mass   (    0.0    );

		set_x_speed(    0.0    );
		set_x_speed(    0.0    );

		set_colour ( par_color );

		set_width ( par_width );
		set_height (  par_height );

		set_type   (  par_type );

		set_is_active ( false );

		status = IS_NOT_PUSH;
	}

	void draw_button(SDL_Renderer* render) {
		//printf("gigigi\n");
		draw_molecule(render);
	}

	virtual void add_new_object(Shape_manager* shape_manager) = 0;
};

#endif