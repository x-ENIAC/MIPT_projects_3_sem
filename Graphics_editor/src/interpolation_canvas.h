#include <SDL2/SDL.h>
#include "point.h"
#include "view.h"
#include "pencil.h"
#include "colour.h"
#include "interpolation_point.h"
#include "interpolator.h"

#ifndef INTERPOLATION_CANVAS_H
#define INTERPOLATION_CANVAS_H

extern const int MAX_COUNT_OF_POINTS;

class Interpolation_canvas : public View_object {
  public:
	Pencil* pencil;
	Interpolation_point** points;
	size_t count_of_points;

	Interpolator* interpolator;

	Point* visual_points;

	Mouse_click_state* mouse_click_state;

	Interpolation_canvas(const Point par_point, const double par_width, const double par_height, 
		  const Colour par_color, Pencil* par_pencil, Mouse_click_state* par_mouse_click_state) :
	  View_object (par_point, par_width, par_height, par_color, Widget_types::INTERPOLATION_CANVAS) {

		pencil = par_pencil;

		points = new Interpolation_point*[MAX_COUNT_OF_POINTS];
		for(size_t i = 0; i < MAX_COUNT_OF_POINTS; ++i)
			points[i] = new Interpolation_point;

		count_of_points = 0;

		interpolator = new Interpolator;

		mouse_click_state = par_mouse_click_state;

		visual_points = new Point[(int)par_width + 1];
		for(size_t i = 0; i <= (int)par_width; ++i)
			visual_points[i].x = i;

		add_point(rect->get_left_up_corner().x, rect->get_left_up_corner().y + par_height);
		add_point(rect->get_left_up_corner().x + par_width, rect->get_left_up_corner().y);
	}

	~Interpolation_canvas() {
		delete[] points;
		count_of_points = 0;
	}

	void add_point(const double x, const double y, const Colour color = BLACK) {
		Interpolation_point* new_point = new Interpolation_point(Point(x, y), color, mouse_click_state, interpolator->count_of_points);
		points[count_of_points] = new_point;
		++count_of_points;

		visual_points[(int)(x - rect->get_left_up_corner().x)].y = y; //  - rect->get_left_up_corner().y
		interpolator->add_point(Point(x, y));

		if(count_of_points > 1) {
			interpolator->update_coords(visual_points, rect->get_width() + 1, rect->get_left_up_corner());
		}
	}

	bool check_click(const double mouse_x, const double mouse_y, const Mouse_click_state* par_mouse_status) override {
		if(is_active && rect->is_point_belongs_to_rectangle( Point(mouse_x, mouse_y))) {
			if(*par_mouse_status == Mouse_click_state::MOUSE_DOWN) {

				bool flag = false;
				for(size_t i = 0; i < count_of_points; ++i) {
					if(points[i]->rect->is_point_belongs_to_rectangle( Point(mouse_x, mouse_y))) 
						flag = points[i]->check_click(mouse_x, mouse_y, par_mouse_status);
				}

				if(!flag)
					add_point(mouse_x, mouse_y);

				return true;
			}
		}

		return false;
	}

	bool check_motion(Point old_mouse, Point now_mouse, const Mouse_click_state* par_mouse_status) override {
		//printf("!!!\n");
		if(is_active && rect->is_point_belongs_to_rectangle( Point(now_mouse.x, now_mouse.y))) {
			if(*par_mouse_status == Mouse_click_state::MOUSE_DOWN_AND_MOTION) {

				for(size_t i = 0; i < count_of_points; ++i) {
					if(points[i]->rect->is_point_belongs_to_rectangle( Point(now_mouse.x, now_mouse.y))) {
						//printf("%d\n", *par_mouse_status);

						if(points[i]->check_motion(old_mouse, now_mouse, par_mouse_status)) {
							interpolator->points[this->points[i]->index] = now_mouse;
							interpolator->update_coords(visual_points, rect->get_width() + 1, rect->get_left_up_corner());
							return true;
						}
					}
				}
			}

			else
			if(*par_mouse_status == Mouse_click_state::MOUSE_MOTION) {
				interpolator->update_coords(visual_points, rect->get_width() + 1, rect->get_left_up_corner());
			}
		}

		return false;
	}	

	void draw(SDL_Renderer** render, SDL_Texture** texture, SDL_Surface** screen) override {
		if(is_visible) {
			rect->draw(*render);

			int width = rect->get_width();
			for(int i = 0; i < width; ++i) {
				Point now(i + rect->get_left_up_corner().x, visual_points[i].y);
				now.draw_big_point(*render, 1.5);
				//visual_points[i].
			}

			for(int i = 0; i < count_of_points; ++i) {
				points[i]->draw(render, texture, screen);
			}
		}
	}

	void update_position_from_delta(Point delta) {
		rect->set_center(rect->get_center() - delta);

		for(int i = 0; i < count_of_points; ++i) {
			points[i]->rect->center -= delta;
		}
	}
};

#endif