#include "button.h"

#ifndef SLIDER_H
#define SLIDER_H

#include "../Editor/Tools/tool_manager.h"

class Slider: public View_object {
  public:

	int min_limit, max_limit;
	int x_left_limit, x_right_limit;
	int now_value;

	Slider (const Point par_center, const double par_width, const double par_height,
			const int par_min_limit, const int par_max_limit,
			const int par_x_left_limit, const int par_x_right_limit,
			const Widget_types par_widget_types = Widget_types::SLIDER,
			const char par_path_to_picture[] = NON_PATH_TO_PUCTURE) :
	  View_object(par_center, par_width, par_height, BLACK, par_widget_types, par_path_to_picture) {

		min_limit = par_min_limit;
		max_limit = par_max_limit;

		x_left_limit  = par_x_left_limit;
		x_right_limit = par_x_right_limit;

		now_value = (max_limit + min_limit) / 2.0;
		Tool_manager::get_tool_manager()->set_pen_size(now_value);

		if(strcmp(par_path_to_picture, NON_PATH_TO_PUCTURE))
			this->texture->add_new_texture(par_path_to_picture);
	}

	void draw(SDL_Renderer** render, SDL_Texture** texture, SDL_Surface** screen) override {
		if(is_visible) {
			//rect->draw(*render);
			if(this->texture->is_using_texture) {
				SDL_Rect sdl_rect;
				sdl_rect.w = rect->get_width();
				sdl_rect.h = rect->get_height();
				sdl_rect.x = rect->get_center().x - sdl_rect.w / 2.0;
				sdl_rect.y = rect->get_center().y - sdl_rect.h / 2.0;

				this->texture->draw_texture(&sdl_rect);
			}
		}
	}

	/*bool check_click(const float mouse_x, const float mouse_y, const Mouse_click_state* par_mouse_status) override {
		if(rect->is_point_belongs_to_rectangle( Point(mouse_x, mouse_y) )) {
			if(*par_mouse_status == Mouse_click_state::MOUSE_DOWN)
				delegate->click_reaction(mouse_x, mouse_y);

			return true;
		}

		return false;
	}*/

	bool check_motion(Point old_mouse, Point now_mouse, const Mouse_click_state* par_mouse_status) override {
		if(rect->is_point_belongs_to_rectangle( Point(now_mouse.x, now_mouse.y) ) ||
			rect->is_point_belongs_to_rectangle( Point(old_mouse.x, old_mouse.y) )) {
			//printf("!!! %d\n", *par_mouse_status);
			if(*par_mouse_status == Mouse_click_state::MOUSE_DOWN_AND_MOTION)
				update_coords(now_mouse);

			return true;
		}

		return false;
	}


	void update_coords(const Point new_center) {
		int x_delta = rect->center.x - new_center.x;

		x_left_limit -= x_delta;
		x_right_limit -= x_delta;

		rect->center.x = new_center.x;		
	}

	void update_position_from_delta(const Point delta) {
		// printf("rect->center.x %d - delta %d >= corner %d\n", (int)(rect->get_center().x), (int)(delta.x), (int)(rect->get_left_up_corner().x));
		// printf("rect->center.x %d + delta %d <= corner %d\n", (int)(rect->get_center().x), (int)(delta.x), (int)(rect->get_right_up_corner().x));

		rect->center -= delta;
	}

	bool check_if_can_change(const Point delta) {
		if(delta.x > 0 && rect->get_center().x - delta.x >= x_left_limit ||
			delta.x < 0 && rect->get_center().x + delta.x <= x_right_limit)
			return true;
		return false;
	}

	bool is_valid_value(const int delta) {
		printf("min %d, now %d, delta %d, max %d\n", min_limit, now_value, delta, max_limit);
		if(delta < 0 && now_value - delta > min_limit ||
			delta > 0 && now_value + delta < max_limit)
			return true;
		return false;
	}
};

#endif