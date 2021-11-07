#include <SDL2/SDL.h>
#include "point.h"
#include "view.h"
#include "pencil.h"
#include "colour.h"

#ifndef INTERPOLATION_CANVAS_H
#define INTERPOLATION_CANVAS_H

const int MAX_COUNT_OF_POINTS = 100;

class Interpolation_canvas : public View_object {
  public:
	Pencil* pencil;
	Point* points;
	size_t count_of_points;

	Interpolation_canvas(const Point par_point, const double par_width, const double par_height, 
		  const Colour par_color, Pencil* par_pencil, Mouse_click_state* par_mouse_click_state) :
	  View_object (par_point, par_width, par_height, par_color, Widget_types::INTERPOLATION_CANVAS) {

		pencil = par_pencil;
		points = new Point[MAX_COUNT_OF_POINTS];
		count_of_points = 0;
	}

	~Interpolation_canvas() {
		delete[] points;
		count_of_points = 0;
	}

	void add_point(const double x, const double y, const Colour color = BLACK) {
		points[count_of_points] = Point(x, y, color);
		++count_of_points;
	}

	bool check_click(const double mouse_x, const double mouse_y, const Mouse_click_state* par_mouse_status) override {
		if(is_active) {
			if(*par_mouse_status == Mouse_click_state::MOUSE_DOWN)
				if(rect->is_point_belongs_to_rectangle( Point(mouse_x, mouse_y))) {
					add_point(mouse_x, mouse_y);
					return true;
				}
		}

		return false;
	}

	void draw(SDL_Renderer** render, SDL_Texture** texture, SDL_Surface** screen) override {
		if(is_visible) {
			rect->draw(*render);

			for(size_t i = 0; i < count_of_points; ++i) {
				points[i].draw_big_point(*render, 10);
			}
		}
	}

	void update_position_from_delta(Point delta) {
		rect->set_center(rect->get_center() - delta);

		for(size_t i = 0; i < count_of_points; ++i) {
			points[i] -= delta;
		}
	}
};

#endif