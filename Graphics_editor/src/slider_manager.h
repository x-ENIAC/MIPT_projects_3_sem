#include "slider_field.h"
#include "button_delegates.h"

#ifndef SLIDER_MANAGER_H
#define SLIDER_MANAGER_H

class Slider_manager: public View_object {
  public:

	Slider_field* slider_field;
	Button_manager* panel;

	Slider_manager (const Point par_center, const double par_height, const long long par_min_limit,
					const long long par_max_limit, Mouse_click_state* par_mouse_click_state,
					const Widget_types par_widget_types = Widget_types::VIEW_OBJECT,
					const char par_path_to_picture[] = NON_PATH_TO_PUCTURE) :
	  View_object(par_center, par_max_limit - par_min_limit + 10, par_height + 20, DARK_GREY, par_widget_types, par_path_to_picture) {


		slider_field = new Slider_field(NULL, par_center, par_height + 20, par_min_limit, par_max_limit);
		Slider_field_delegate* slider_delegate = new Slider_field_delegate(slider_field, &(slider_field->slider->rect->center));
		slider_field->delegate = slider_delegate;

		Point center_of_button_manager(par_center);
		center_of_button_manager -= Point(0, par_height + HEIGHT_CLOSE_BUTTON / 2);
		
		panel = new Button_manager(center_of_button_manager, rect->width, HEIGHT_CLOSE_BUTTON, WHITE);

		center_of_button_manager -= Point(rect->width / 2, par_height);

		fill_button_manager(center_of_button_manager, rect->width, par_height, par_mouse_click_state);
	}

	void fill_button_manager(Point left_up_corner, const double par_width, const double par_height,
														 Mouse_click_state* par_mouse_click_state) {
		//--------------- add close button ---------------------------

		Point center_button(par_width - WIDTH_CLOSE_BUTTON / 2.0,  HEIGHT_CLOSE_BUTTON / 2.0);
		center_button += left_up_corner;

		Button* close_button = new Button(NULL, center_button, BLACK, WIDTH_CLOSE_BUTTON, HEIGHT_CLOSE_BUTTON,
										  TEXT_CLOSE, BLACK);
		close_button->texture->add_new_texture(PATH_TO_PICTURE_WITH_BLACK_CLOSE_BUTTON);

		Close_delegate*  close_delegate = new Close_delegate(close_button, par_mouse_click_state, &is_alive);
		close_button->delegate = close_delegate;

		panel->add_view_object(close_button);

		//--------------- add roll up button ---------------------------
		Roll_up_delegate*  roll_up_delegate = new Roll_up_delegate(par_mouse_click_state, &is_visible, &is_active);

		center_button = Point(WIDTH_CLOSE_BUTTON / 2.0, HEIGHT_CLOSE_BUTTON / 2.0);
		center_button += left_up_corner;

		Button* roll_up_button = new Button(roll_up_delegate, center_button, BLACK, WIDTH_CLOSE_BUTTON, HEIGHT_CLOSE_BUTTON,
											TEXT_ROLL_UP, BLACK, PATH_TO_PICTURE_WITH_ROLL_UP_BUTTON);
		roll_up_button->texture->add_new_texture(PATH_TO_PICTURE_WITH_ROLL_UP_BUTTON);
		panel->add_view_object(roll_up_button);

		//--------------- add title button ---------------------------
		Title_delegate*  title_delegate = new Title_delegate(this);

		center_button = Point(par_width / 2.0, HEIGHT_CLOSE_BUTTON / 2.0);
		center_button += left_up_corner;

		Button* title_button = new Button(title_delegate, center_button, DARK_GREY, par_width - 2 * WIDTH_CLOSE_BUTTON, HEIGHT_CLOSE_BUTTON,
										  TEXT_TITLE, BLACK, PATH_TO_PICTURE_WITH_TITLE_BUTTON);
		title_button->texture->add_new_texture(PATH_TO_PICTURE_WITH_TITLE_BUTTON);
		panel->add_view_object(title_button);
	}	

	void draw(SDL_Renderer** render, SDL_Texture** texture, SDL_Surface** screen) override {
		if(is_visible) {
			rect->draw(*render);
			slider_field->draw(render, texture, screen);
			panel->draw(render, texture, screen);
		}
	}

	bool check_click(const float mouse_x, const float mouse_y, const Mouse_click_state* par_mouse_status) override {
		if(rect->is_point_belongs_to_rectangle( Point(mouse_x, mouse_y) )) {
			if(*par_mouse_status == Mouse_click_state::MOUSE_DOWN) {

				if(panel->rect->is_point_belongs_to_rectangle( Point(mouse_x, mouse_y) ))
					return panel->check_click(mouse_x, mouse_y, par_mouse_status);

				if(slider_field->rect->is_point_belongs_to_rectangle( Point(mouse_x, mouse_y) ))
					return slider_field->check_click(mouse_x, mouse_y, par_mouse_status);
			}
		}

		return false;
	}

	bool check_motion(Point old_mouse, Point now_mouse, const Mouse_click_state* par_mouse_status) override {
		//printf("panel??? (%d)\n", panel->rect->is_point_belongs_to_rectangle(now_mouse));
		if(panel->rect->is_point_belongs_to_rectangle( Point(now_mouse.x, now_mouse.y) ) ||
		   panel->rect->is_point_belongs_to_rectangle( Point(old_mouse.x, old_mouse.y) )	) {
			return panel->check_motion(old_mouse, now_mouse, par_mouse_status);
		}

		if(slider_field->rect->is_point_belongs_to_rectangle( Point(now_mouse.x, now_mouse.y) ) ||
		   slider_field->rect->is_point_belongs_to_rectangle( Point(old_mouse.x, old_mouse.y) )	) {
			return slider_field->check_motion(old_mouse, now_mouse, par_mouse_status);
		}

		return false;
	}

	void update_view_object_position(const double mouse_x, const double mouse_y) override {
		update_slider_manager_position(mouse_x, mouse_y);
	}

	void update_slider_manager_position(const double mouse_x, const double mouse_y) {

		Point mouse(mouse_x, mouse_y);
		Point delta(panel->rect->get_center());
		delta -= mouse;

		rect->set_center(rect->get_center() - delta);

		panel->rect->set_center(mouse);
		panel->update_position_from_delta(delta);

		slider_field->update_position_from_delta(delta);
	}	

};

#endif
