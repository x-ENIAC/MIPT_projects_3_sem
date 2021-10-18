#include <stdio.h>
#include <stdlib.h>

#include "point.h"
#include "button.h"
#include "button_delegates.h"
#include "button_manager.h"

#ifndef TAB_H
#define TAB_H

extern const size_t MAX_COUNT_OF_VIEW_OBJECTS;
extern const double DELTA_BETWEEN_BUTTONS;
extern const double WIDTH_CLOSE_BUTTON;
extern const double HEIGHT_CLOSE_BUTTON;
extern const double WIDTH_TABS_BUTTON;
extern const double HEIGHT_TABS_BUTTON;

class Tab : public View_object {
  public:
  	Button_manager* button_manager;

  	Tab() : View_object() {

	  	button_manager = new Button_manager[MAX_COUNT_OF_VIEW_OBJECTS];
  	}  	

  	Tab(const Point par_center, const double par_width, const double par_height, const Colour par_color, const int par_number_of_tab) :
	  View_object(par_center, par_width, par_height, par_color, Widget_types::TABS) {

	  	button_manager = new Button_manager[MAX_COUNT_OF_VIEW_OBJECTS];

	  	add_new_tab(par_center, par_width, par_height, par_number_of_tab);
  	}

  	void add_new_tab(const Point par_center, const double par_width, const double par_height, const int par_number_of_tab) {
  		Title_delegate*  title_delegate = new Title_delegate;

  		char* text_on_tab = new char[30];

  		sprintf(text_on_tab, "canvas %d", par_number_of_tab);

        Button* title_button = new Button(title_delegate, par_center, MIDDLE_GREY, par_width, par_height, text_on_tab, BLACK);

  		button_manager->add_view_object(title_button);
  	}

  	virtual bool check_click(const double mouse_x, const double mouse_y) {

  		return false;
  	}  	

	void draw(SDL_Renderer** render, SDL_Texture** texture) override {
		//rect->draw(*render);

		button_manager->draw(render, texture);
	}  	
};

#endif