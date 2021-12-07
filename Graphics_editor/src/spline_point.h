#include "point.h"
#include "view.h"
#include "button.h"

#ifndef SPLINE_POINT_H
#define SPLINE_POINT_H

class Spline_point : public View_object {
  public:

  	Button* button;
  	Mouse_click_state* mouse_click_state;
  	int index;

  	Spline_point(): View_object() {}

  	Spline_point(const Point par_point, const Colour par_color, Mouse_click_state* par_mouse_click_state, const int par_index):
  	  View_object(par_point, 10, 10, par_color, Widget_types::SPLINE_POINT) {

  	  	Change_color_with_spline_delegate*  change_color_with_spline_delegate = new Change_color_with_spline_delegate(NULL);

  	  	button = new Button(change_color_with_spline_delegate, par_point, par_color, 10, 10);

  	  	rect->center.color = par_color;

  	  	mouse_click_state = par_mouse_click_state;

  	  	index = par_index;
  	}

  	void draw(SDL_Renderer** render, SDL_Texture** texture, SDL_Surface** screen) override {
  		if(is_visible) {
  			//printf("%lg %lg %lg\n", rect->get_colour().red, rect->get_colour().green, rect->get_colour().blue);
  			rect->center.draw_big_point(*render, 5);
  		}
  	}

	bool check_click(const float mouse_x, const float mouse_y, const Mouse_click_state* par_mouse_status) override {
		//if(is_active) {
			printf("click!\n");
			return true;
		//}

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