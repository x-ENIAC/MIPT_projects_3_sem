#include <SDL2/SDL.h>
#include "point.h"
#include "colour.h"
#include "rectangle.h"
#include "text.h"
#include "button_delegate.h"
#include "view.h"

#ifndef BUTTON_H
#define BUTTON_H

extern const size_t MAX_COUNT_OF_VIEW_OBJECTS;

enum Button_status {
	IS_PUSH 	= 1,
	IS_NOT_PUSH = 2,
};

/*enum Button_owner {
    BUTTON_OWNER_BUTTON_CLASS = 0,
    BUTTON_OWNER_USER         = 1,
    BUTTON_OWNER_OTHER_CLASS  = 2,
};*/

class Button : public View_object {
  public:
	Button_delegate* delegate;

	Rectangle* object_rect;
	Button_status status;
	//Button_owner owner;

	View_object** view_objects;
	size_t count_of_views;

	Button(Button_delegate* par_delegate, const Point par_point, const Colour par_button_color, const double par_width, const double par_height, 
								/*const Button_owner par_owner, */char* text_on_button = " ", const Colour par_text_color = BLACK) :
	  View_object (par_point, par_width, par_height, par_button_color, BUTTON_VIEW_TYPE) {

	  	delegate = par_delegate;
		object_rect = new Rectangle(par_point, par_width, par_height, par_button_color, false);

	  	status = IS_NOT_PUSH;

  	 	view_objects = new View_object*[MAX_COUNT_OF_VIEW_OBJECTS];
  	 	for(size_t i = 0; i < MAX_COUNT_OF_VIEW_OBJECTS; ++i)
  	 		view_objects[i] = new View_object;
  	 	count_of_views = 0;

	  	Point text_center = par_point;

	  	Text* text = new Text(text_center, text_on_button, par_width, par_height, par_text_color);
	  	view_objects[count_of_views++] = text;
	}

  	virtual bool check_click(const double mouse_x, const double mouse_y) {
  		if(object_rect->is_point_belongs_to_rectangle( Point(mouse_x, mouse_y) )) {
  			delegate->click_reaction();
  			return true;
  		}

  		return false;
  	}

	virtual void draw(SDL_Renderer** render, SDL_Texture** texture) {
		object_rect->draw(*render);

		for(size_t i = 0; i < count_of_views; ++i)
			view_objects[i]->draw(render, texture);
	}

	/*inline Button_owner get_owner() const {
		return owner;
	}*/

	//inline void set_owner(const Button_owner new_owner) {
	//	owner = new_owner;
	//}
};

#endif


