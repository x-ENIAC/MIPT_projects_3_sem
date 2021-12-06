#include <stdio.h>
#include <cstdlib>

#include "point.h"
#include "button.h"
#include "button_delegates.h"
#include "button_manager.h"

#ifndef TAB_H
#define TAB_H

//extern const double DELTA_BETWEEN_BUTTONS;
// extern const double WIDTH_CLOSE_BUTTON;
// extern const double HEIGHT_CLOSE_BUTTON;
// extern const double WIDTH_TABS_BUTTON;
// extern const double HEIGHT_TABS_BUTTON;

const size_t MAX_SIZE_OF_TEXT_ON_TAB = 20;

class Tab : public View_object {
  public:
	Button_manager* button_manager;
	size_t number_of_title_in_button_manager;

	Tab() : View_object() {
		button_manager = new Button_manager();
	}

	Tab(const Point par_center, const double par_width, const double par_height, const Colour par_color, const int par_number_of_tab,
								Mouse_click_state* par_mouse_click_state, bool* par_is_visible, bool* par_is_active, bool* par_is_alive) :
	  View_object(par_center, par_width, par_height, par_color, Widget_types::TABS) {

	  	Point pt = par_center;
	  	pt += Point(WIDTH_CLOSE_BUTTON / 2, 0);
	  	//printf("center button manager? (%lg, %lg), %lg, %lg\n", par_center.x, par_center.y, par_width, par_height);
		button_manager = new Button_manager(pt, par_width, par_height, par_color);

		add_new_tab(par_center, par_number_of_tab, par_mouse_click_state, par_is_visible, par_is_active, par_is_alive);
	}

	void add_new_tab(const Point par_center, const int par_number_of_tab, 
					 Mouse_click_state* par_mouse_click_state, bool* par_is_visible, bool* par_is_active, bool* par_is_alive) {

		Tab_title_delegate*  tab_title_delegate = new Tab_title_delegate(par_mouse_click_state, par_is_visible, par_is_active);

		char text_on_tab[MAX_SIZE_OF_TEXT_ON_TAB];

		sprintf(text_on_tab, "canvas %d", par_number_of_tab);
		//printf("!!! %s\n", text_on_tab);

		Button* title_button = new Button(tab_title_delegate, par_center, LIGHT_LIGHT_GREY, WIDTH_TABS_BUTTON, HEIGHT_TABS_BUTTON,
										  text_on_tab, WHITE);

		//printf("@ tab, center title (%lg, %lg), %lg, %lg\n", par_center.x, par_center.y, WIDTH_TABS_BUTTON, HEIGHT_TABS_BUTTON);
		title_button->texture->add_new_texture(PATH_TO_PICTURE_WITH_GREY_1_BUTTON);
		number_of_title_in_button_manager = button_manager->count_of_buttons;
		button_manager->add_view_object(title_button);

		//--------------- add close button ---------------------------

		Point center = par_center;
		center += Point(WIDTH_TABS_BUTTON / 2.0 + WIDTH_CLOSE_BUTTON / 2.0, 0);

		//printf("@ tab, center close (%lg, %lg), %lg, %lg\n", center.x, center.y, WIDTH_CLOSE_BUTTON, HEIGHT_CLOSE_BUTTON);
		Button* close_button = new Button(NULL, center, LIGHT_LIGHT_GREY, WIDTH_CLOSE_BUTTON, HEIGHT_CLOSE_BUTTON, "x", BLACK);
		close_button->texture->add_new_texture(PATH_TO_PICTURE_WITH_GREY_1_CLOSE_BUTTON);

		Close_delegate*  close_delegate = new Close_delegate(close_button, par_mouse_click_state, par_is_alive);
		close_button->delegate = close_delegate;

		button_manager->add_view_object(close_button);  

		//printf("\nend add new tab %p\n\n", par_mouse_click_state);
	}

	bool check_click(const double mouse_x, const double mouse_y, const Mouse_click_state* par_mouse_status) override {
		//printf("click Tab\n");
		//printf("\ttab: (%lg, %lg) width %lg, height %lg\n", rect->center.x, rect->center.y, rect->get_width(), rect->get_height());
		return button_manager->check_click(mouse_x, mouse_y, par_mouse_status);
	}

	bool check_motion(Point old_mouse, Point now_mouse, const Mouse_click_state* par_mouse_status) override {
		//printf("\n\nview_manager check_click\n");

		return button_manager->check_motion(old_mouse, now_mouse, par_mouse_status);
	}

	void draw(SDL_Renderer** render, SDL_Texture** texture, SDL_Surface** screen) override {
		//rect->draw(*render);
		//printf("!!! tab center (%lg, %lg)\n", rect->center.x, rect->center.y);

		button_manager->draw(render, texture, screen);

		button_manager->buttons[number_of_title_in_button_manager]->view_objects[0]->draw(render, texture, screen); // draw text
	}

	void delete_all() {
		printf("begin tab delete_all\n");
		button_manager->delete_all();
		delete[] button_manager;
		printf("end tab delete_all\n");
	}

	void update_tabs_offset(const Point new_center) {
		//printf("... (%lg, %lg)\n", new_center.x, new_center.y);
		Point delta(rect->get_center());
		Point old_center(rect->get_center());
		delta -= new_center;

		set_new_center(new_center);

		Point new_left_up_corner = rect->get_left_up_corner();

		for(size_t i = 0; i < button_manager->count_of_buttons; ++i) {
			Point now_center(button_manager->buttons[i]->rect->center);
			now_center += new_center;
			now_center -= old_center;

			button_manager->buttons[i]->update_center_position(now_center);
		}

	}

	void update_tabs_number(const size_t new_number) {
		size_t count_objects = button_manager->buttons[number_of_title_in_button_manager]->count_of_views;

		for(size_t i = 0; i < count_objects; ++i) {
			if(button_manager->buttons[number_of_title_in_button_manager]->view_objects[i]->yourself_type == Widget_types::TEXT) {
				Text* text = (Text*)(button_manager->buttons[number_of_title_in_button_manager]->view_objects[i]);

				char text_on_tab[MAX_SIZE_OF_TEXT_ON_TAB];
				sprintf(text_on_tab, "canvas %ld", new_number);
				
				strcpy(text->text, text_on_tab);
			}
		}
	}

	void tick(const double delta_time) override {
		button_manager->tick(delta_time);
	}

	void set_new_center(const Point new_center) {
		printf("tab. was (%lg, %lg) -> ", rect->center.x, rect->center.y);

		Point delta = rect->center;
		delta -= new_center;

		rect->center = new_center;
		printf("now (%lg, %lg)\n", rect->center.x, rect->center.y);
		button_manager->rect->center = rect->center;
		button_manager->rect->center += Point(WIDTH_CLOSE_BUTTON / 2, 0);

		//button_manager->update_position_from_delta(delta);
	}

	void update_position_from_delta(const Point delta) {
		printf("tab. was (%lg, %lg) -> ", rect->center.x, rect->center.y);
		rect->center = rect->get_center() - delta;
		printf("now (%lg, %lg)\n", rect->center.x, rect->center.y);
		button_manager->rect->center = rect->center;
		button_manager->rect->center += Point(WIDTH_CLOSE_BUTTON / 2, 0);

		button_manager->update_position_from_delta(delta);
	}
};

#endif