#include <SDL2/SDL.h>
#include "point.h"
#include "colour.h"
#include "rectangle.h"

#ifndef CIRCLE_BUTTON_H
#define CIRCLE_BUTTON_H

class Circle_button : public Button {
  public:
	Circle shape_circle;
	Button_status status;

	Circle_button(const Point par_point, const Colour par_color, const double par_width, const double par_height) :

	  shape_circle(par_point,30., 0., 0., par_color,  par_width,    par_height, BUTTON, false) {

		status = IS_NOT_PUSH;
	}

	void draw_button(SDL_Renderer* render) {
		shape_rect.draw_molecule(render);
	}

	void add_new_object(Shape_manager* shape_manager) {
		Circle* new_rect = new Circle;

		new_rect->set_center ( Point(rand() % 500, rand() % 500) );
		new_rect->set_mass   ( 1 );
		new_rect->set_x_speed( rand() % 10 + 1 );

		new_rect->set_y_speed( rand() % 10 * -1 + 1 );
		new_rect->set_width  ( rand() % 30 + 10 );
		new_rect->set_height ( rand() % 30 + 10 );

		new_rect->set_type   ( CIRCLE );
		new_rect->set_colour ( Colour(rand() % 256, rand() % 256, rand() % 256, 128) );


		shape_manager->add_object(new_rect);
	}
};

#endif