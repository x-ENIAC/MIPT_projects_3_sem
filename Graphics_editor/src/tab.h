#include <stdio.h>
#include <stdlib.h>

#include "point.h"
#include "button.h"
#include "button_delegates.h"
#include "button_manager.h"

#ifndef TAB_H
#define TAB_H

extern const size_t MAX_COUNT_OF_VIEW_OBJECTS;
//extern const double DELTA_BETWEEN_BUTTONS;
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

  	Tab(const Point par_center, const double par_width, const double par_height, const Colour par_color, const int par_number_of_tab,
  								Mouse_click_state* par_mouse_click_state, bool* par_is_visible, bool* par_is_active) :
	  View_object(par_center, par_width, par_height, par_color, Widget_types::TABS) {

	  	button_manager = new Button_manager[MAX_COUNT_OF_VIEW_OBJECTS];

	  	add_new_tab(par_center, par_number_of_tab, par_mouse_click_state, par_is_visible, par_is_active);
  	}

  	void add_new_tab(const Point par_center, const int par_number_of_tab, 
  											 Mouse_click_state* par_mouse_click_state, bool* par_is_visible, bool* par_is_active) {

  		Tab_title_delegate*  tab_title_delegate = new Tab_title_delegate(par_mouse_click_state, par_is_visible, par_is_active);

  		char* text_on_tab = new char[30];

  		sprintf(text_on_tab, "canvas %d", par_number_of_tab);

        Button* title_button = new Button(tab_title_delegate, par_center, MIDDLE_GREY, WIDTH_TABS_BUTTON, HEIGHT_TABS_BUTTON, text_on_tab, BLACK);

  		button_manager->add_view_object(title_button);

        //--------------- add close button ---------------------------

  		Point center = par_center;
  		center += Point(WIDTH_TABS_BUTTON / 2.0 + WIDTH_CLOSE_BUTTON / 2.0, 0);

  		Close_delegate*  close_delegate = new Close_delegate(par_mouse_click_state, par_is_visible, par_is_active);

        Button* close_button = new Button(close_delegate, center, BLACK, WIDTH_CLOSE_BUTTON, HEIGHT_CLOSE_BUTTON, "x", WHITE);

  		button_manager->add_view_object(close_button);  

  		//printf("\nend add new tab %p\n\n", par_mouse_click_state);
  	}

  	bool check_click(const double mouse_x, const double mouse_y, const Mouse_click_state* par_mouse_status) override {
  		//printf("click Tab\n");
              		
  		if(is_active) {
  			return button_manager->check_click(mouse_x, mouse_y, par_mouse_status);
  		}
  		return true;
  	}

	void draw(SDL_Renderer** render, SDL_Texture** texture) override {
		//rect->draw(*render);

		button_manager->draw(render, texture);
	}

	bool delete_object() override {
		button_manager->delete_object();
		delete[] button_manager;
	}
};

#endif