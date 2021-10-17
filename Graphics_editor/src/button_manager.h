#include "view.h"
#include "button.h"
#include "colour.h"

#ifndef BUTTON_MANAGER_H
#define BUTTON_MANAGER_H

class Button_manager : public View_object {
  public:
	Button** buttons;
	size_t count_of_buttons;

	Button_manager(const Point par_center, const double par_width, const double par_height, const Colour par_color) :
	  View_object(par_center, par_width, par_height, par_color) {
		count_of_buttons = 0;

  	 	buttons = new Button*[MAX_COUNT_OF_VIEW_OBJECTS];
  	 	for(size_t i = 0; i < MAX_COUNT_OF_VIEW_OBJECTS; ++i)
  	 		buttons[i] = new Button;
	}

	void add_view_object(Button* new_button) {
  	 	buttons[count_of_buttons] = new_button;
  	 	++count_of_buttons;
  	}

  	virtual bool check_click(const double mouse_x, const double mouse_y) {
  		for(size_t i = 0; i < count_of_buttons; ++i) {
  			if(buttons[i]->rect->is_point_belongs_to_rectangle( Point(mouse_x, mouse_y) )) {
  				buttons[i]->delegate->click_reaction();
  				return true;
  			}
  		}

  		return false;
  	}  	

	void draw(SDL_Renderer** render, SDL_Texture** texture) override {
		rect->draw(*render);

		for(size_t i = 0; i < count_of_buttons; ++i)
			buttons[i]->draw(render, texture);
	}
};

#endif