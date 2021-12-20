#include "slider.h"

#ifndef SLIDER_FIELD_H
#define SLIDER_FIELD_H

class Slider_field : public View_object {
  public:

  	Button_delegate* delegate;
  	Slider* slider;
	int min_limit, max_limit;

	Slider_field(Button_delegate* par_delegate, const Point par_center, const double par_height,
				const int par_min_limit, const int par_max_limit,
				const Widget_types par_widget_types = Widget_types::SLIDER_FIELD,
				const char par_path_to_picture[] = NON_PATH_TO_PUCTURE) : View_object(par_center, par_max_limit - par_min_limit,
																						par_height, LIGHT_GREY_4, par_widget_types, par_path_to_picture) {

		slider = new Slider(par_center, 20, 20, par_min_limit, par_max_limit,
							rect->get_left_up_corner().x + 10, rect->get_right_up_corner().x - 20,
							Widget_types::SLIDER, PATH_TO_PICTURE_SLIDER);

		delegate = par_delegate;

		min_limit = par_min_limit;
		max_limit = par_max_limit;
	}

	void draw(SDL_Renderer** render, SDL_Texture** texture, SDL_Surface** screen) override {
		if(is_visible) {
			//rect->draw(*render);
			Rectangle r(rect->center, rect->width, rect->height / 5, rect->color);
			r.draw(*render);

			slider->draw(render, texture, screen);			
		}
	}

	bool check_click(const float mouse_x, const float mouse_y, const Mouse_click_state* par_mouse_status) override {
		if(rect->is_point_belongs_to_rectangle( Point(mouse_x, mouse_y) )) {
			if(*par_mouse_status == Mouse_click_state::MOUSE_DOWN) {
				if(slider->check_click(mouse_x, mouse_y, par_mouse_status))
					return true;
				delegate->click_reaction(mouse_x, mouse_y);
			}
		}

		return false;
	}

	bool check_motion(Point old_mouse, Point now_mouse, const Mouse_click_state* par_mouse_status) override {
		if(rect->is_point_belongs_to_rectangle( Point(now_mouse.x, now_mouse.y) )) {
			//printf("field !!! %d\n", *par_mouse_status);
			if(slider->check_motion(old_mouse, now_mouse, par_mouse_status))
				return true;
		}

		return false;
	}

	void update_position_from_delta(const Point delta) {
		rect->center -= delta;

		slider->update_position_from_delta(delta);
	}
};

#endif