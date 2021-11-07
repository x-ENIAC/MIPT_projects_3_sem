#include "point.h"
#include "view.h"

#ifndef INTERPOLATION_POINT_H
#define INTERPOLATION_POINT_H

class Interpolation_point : public View_object {
  public:

  	Mouse_click_state* mouse_click_state;
  	int index;

  	Interpolation_point(): View_object() {}

  	Interpolation_point(const Point par_point, const Colour par_color, Mouse_click_state* par_mouse_click_state, const int par_index):
  	  View_object(par_point, 10, 10, par_color, Widget_types::INTERPOLATION_POINT) {

  	  	rect->center.color = par_color;
  	  	mouse_click_state = par_mouse_click_state;

  	  	index = par_index;
  	}

  	void draw(SDL_Renderer** render, SDL_Texture** texture, SDL_Surface** screen) override {
  		if(is_visible) {
  			rect->center.draw_big_point(*render, 5);
  		}
  	}

	bool check_click(const double mouse_x, const double mouse_y, const Mouse_click_state* par_mouse_status) override {
		if(is_active) {
			printf("click!\n");
			return true;
		}

		return false;
	}

	bool check_motion(Point old_mouse, Point now_mouse, const Mouse_click_state* par_mouse_status) override {
		//printf("motion!\n");
		//printf("%d, %d -> %d, %d\n", (int)rect->get_center().x, (int)rect->get_center().y, (int)now_mouse.x, (int)now_mouse.y);
		rect->set_center(now_mouse);
		return true;
	}
};

#endif