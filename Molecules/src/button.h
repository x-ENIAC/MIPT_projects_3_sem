#include <SDL2/SDL.h>
#include "point.h"
#include "colour.h"
#include "rectangle.h"
#include "text.h"
#include "button_delegate.h"

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

class Button : public View_object {
  public:
	Button_delegate* delegate;

	Rectangle* object_rect;
	Button_status status;
	Button_owner owner;

	View_manager view_manager;

	//Button() {}

	/*Button(button_delegate* par_delegate, const Point par_point, const Colour par_color, const double par_width, const double par_height) {

		View_object (par_point, par_color);

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

	  	view_manager = {};
	}

	Button(button_delegate* par_delegate, const Point par_point, const Colour par_color, const double par_width, const double par_height, const Button_owner par_owner) {

		View_object (par_point, par_color);

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

	  	view_manager = {};
	}*/

	Button(Button_delegate* par_delegate, const Point par_point, const Colour par_button_color, const double par_width, const double par_height, 
								const Button_owner par_owner, char* text_on_button, const Colour par_text_color = BLACK) :
	  View_object (par_point, par_button_color, BUTTON_VIEW_TYPE) {

	  	delegate = par_delegate;

		object_rect = new Rectangle;

	  	object_rect->set_center ( par_point );
	  	object_rect->set_mass   (  0.0  );

	  	object_rect->set_x_speed(  0.0  );
	  	object_rect->set_y_speed(  0.0  );

	  	object_rect->set_colour ( par_button_color );

	  	object_rect->set_width  ( par_width );
	  	object_rect->set_height ( par_height );

	  	object_rect->set_type   ( BUTTON );

	  	object_rect->set_is_active ( false );
	  	object_rect->set_owner     ( OBJECT_OWNER_OTHER_CLASS );

	  	status = IS_NOT_PUSH;
	  	owner = par_owner;

	  	view_manager = {};

	  	Point text_center = par_point;

	  	Text* text = new Text(text_center, text_on_button, par_text_color);
	  	view_manager.add_view_object(text);

	}

  	virtual bool check_click(const double mouse_x, const double mouse_y) {
  		printf("e\n");
  		if(object_rect->is_point_belongs_to_rectangle( Point(mouse_x, mouse_y) )) {
  			delegate->click_reaction();
  			return true;
  		}

  		return false;
  	}	

	virtual void draw(SDL_Renderer** render, SDL_Texture** texture) {
		object_rect->draw_molecule(*render);
		view_manager.draw(render, texture);

	}

	virtual void add_new_object(Object_manager* object_manager) {};
	//void add_object()

	inline Button_owner get_owner() const {
		return owner;
	}

	//inline void set_owner(const Button_owner new_owner) {
	//	owner = new_owner;
	//}
};

#endif


