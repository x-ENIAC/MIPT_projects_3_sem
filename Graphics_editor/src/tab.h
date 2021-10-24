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

const size_t MAX_SIZE_OF_TEXT_ON_TAB = 20;

class Tab : public View_object {
  public:
  	Button_manager* button_manager;
  	size_t number_of_title_in_button_manager;

  	Tab() : View_object() {
	  	button_manager = new Button_manager[MAX_COUNT_OF_VIEW_OBJECTS];
  	}

  	Tab(const Point par_center, const double par_width, const double par_height, const Colour par_color, const int par_number_of_tab,
  								Mouse_click_state* par_mouse_click_state, bool* par_is_visible, bool* par_is_active, bool* par_is_alive) :
	  View_object(par_center, par_width, par_height, par_color, Widget_types::TABS) {

	  	button_manager = new Button_manager[MAX_COUNT_OF_VIEW_OBJECTS];

	  	add_new_tab(par_center, par_number_of_tab, par_mouse_click_state, par_is_visible, par_is_active, par_is_alive);
  	}

  	void add_new_tab(const Point par_center, const int par_number_of_tab, 
  					 Mouse_click_state* par_mouse_click_state, bool* par_is_visible, bool* par_is_active, bool* par_is_alive) {

  		Tab_title_delegate*  tab_title_delegate = new Tab_title_delegate(par_mouse_click_state, par_is_visible, par_is_active);

  		char* text_on_tab = new char[MAX_SIZE_OF_TEXT_ON_TAB];

  		sprintf(text_on_tab, "canvas %d", par_number_of_tab);

        Button* title_button = new Button(tab_title_delegate, par_center, LIGHT_LIGHT_GREY, WIDTH_TABS_BUTTON, HEIGHT_TABS_BUTTON, text_on_tab, BLACK);

		number_of_title_in_button_manager = button_manager->count_of_buttons;
  		button_manager->add_view_object(title_button);

        //--------------- add close button ---------------------------

  		Point center = par_center;
  		center += Point(WIDTH_TABS_BUTTON / 2.0 + WIDTH_CLOSE_BUTTON / 2.0, 0);

  		Close_delegate*  close_delegate = new Close_delegate(par_mouse_click_state, par_is_alive);

        Button* close_button = new Button(close_delegate, center, LIGHT_LIGHT_GREY, WIDTH_CLOSE_BUTTON, HEIGHT_CLOSE_BUTTON, "x", BLACK);

  		button_manager->add_view_object(close_button);  

  		//printf("\nend add new tab %p\n\n", par_mouse_click_state);
  	}

  	bool check_click(const double mouse_x, const double mouse_y, const Mouse_click_state* par_mouse_status) override {
  		printf("click Tab\n");
              		
  		return button_manager->check_click(mouse_x, mouse_y, par_mouse_status);
  	}

	void draw(SDL_Renderer** render, SDL_Texture** texture) override {
		//rect->draw(*render);
		//printf("!!! tab center (%lg, %lg)\n", rect->center.x, rect->center.y);

		button_manager->draw(render, texture);
	}

	void delete_all() {
		printf("begin tab delete_all\n");
		button_manager->delete_all();
		delete[] button_manager;
		printf("end tab delete_all\n");
	}

	void update_tabs_offset(const Point new_center) {
		printf("... (%lg, %lg)\n", new_center.x, new_center.y);
		Point old_center(center);

		center = rect->center = new_center;

		Point new_left_up_corner = rect->get_left_up_corner();

		for(size_t i = 0; i < button_manager->count_of_buttons; ++i) {
			Point now_center(button_manager->buttons[i]->rect->center);
			now_center += new_center;
			now_center -= old_center;

			button_manager->buttons[i]->update_position(now_center);
			//printf("\t... (%lg, %lg)\n", now_center.x, now_center.y);
		}

	}

	void update_tabs_number(const size_t new_number) {
		size_t count_objects = button_manager->buttons[number_of_title_in_button_manager]->count_of_views;

		for(size_t i = 0; i < count_objects; ++i) {
			if(button_manager->buttons[number_of_title_in_button_manager]->view_objects[i]->yourself_type == Widget_types::TEXT) {
				Text* text = (Text*)(button_manager->buttons[number_of_title_in_button_manager]->view_objects[i]);
				delete[] text->text;

		  		char* text_on_tab = new char[MAX_SIZE_OF_TEXT_ON_TAB];
  				sprintf(text_on_tab, "canvas %d", new_number);
				
				text->text = text_on_tab;
			}
		}
	}	
};

#endif