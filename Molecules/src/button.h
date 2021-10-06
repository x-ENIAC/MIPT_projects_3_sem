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

enum Button_owner {
    BUTTON_OWNER_BUTTON_CLASS = 0,
    BUTTON_OWNER_USER         = 1,
    BUTTON_OWNER_OTHER_CLASS  = 2,
};

class Button {
  public:
	Rectangle* object_rect;
	Button_status status;
	Button_owner owner;

	Button() {}

	Button(const Point par_point, const Colour par_color, const double par_width, const double par_height) {

		object_rect = new Rectangle;

	  	object_rect->set_center ( par_point );
	  	object_rect->set_mass   (  0.0  );

	  	object_rect->set_x_speed(  0.0  );
	  	object_rect->set_y_speed(  0.0  );

	  	object_rect->set_colour ( par_color );

	  	object_rect->set_width  ( par_width );
	  	object_rect->set_height ( par_height );

	  	object_rect->set_type   ( BUTTON );

	  	object_rect->set_is_active ( false );
	  	object_rect->set_owner     ( OBJECT_OWNER_OTHER_CLASS );

	  	status = IS_NOT_PUSH;
	  	owner  = BUTTON_OWNER_USER;
	}

	Button(const Point par_point, const Colour par_color, const double par_width, const double par_height, const Button_owner par_owner) {

		object_rect = new Rectangle;

	  	object_rect->set_center ( par_point );
	  	object_rect->set_mass   (  0.0  );

	  	object_rect->set_x_speed(  0.0  );
	  	object_rect->set_y_speed(  0.0  );

	  	object_rect->set_colour ( par_color );

	  	object_rect->set_width  ( par_width );
	  	object_rect->set_height ( par_height );

	  	object_rect->set_type   ( BUTTON );

	  	object_rect->set_is_active ( false );
	  	object_rect->set_owner     ( OBJECT_OWNER_OTHER_CLASS );


	  	status = IS_NOT_PUSH;
	  	owner = par_owner;
	}	

	void draw_button(SDL_Renderer* render) {
		object_rect->draw_molecule(render);
	}

	virtual void add_new_object(Object_manager* object_manager) {};

	inline Button_owner get_owner() const {
		return owner;
	}

	//inline void set_owner(const Button_owner new_owner) {
	//	owner = new_owner;
	//}
};

#endif