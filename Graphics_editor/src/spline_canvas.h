#include <SDL2/SDL.h>
#include "point.h"
#include "view.h"
#include "pencil.h"
#include "colour.h"
#include "spline_point.h"
#include "spline.h"
#include "canvas_manager.h"

#ifndef SPLINE_CANVAS_H
#define SPLINE_CANVAS_H

extern const int MAX_COUNT_OF_POINTS;

class Spline_canvas : public View_object {
  public:
	Pencil* pencil;
	Spline_point** points;
	size_t count_of_points;

	Spline* spline;
	Canvas_manager* canvas;

	Point* visual_points;

	Mouse_click_state* mouse_click_state;

	Spline_canvas(const Point par_point, const double par_width, const double par_height, 
		  const Colour par_color, Pencil* par_pencil, Canvas_manager* par_canvas, Mouse_click_state* par_mouse_click_state) :
	  View_object (par_point, par_width, par_height, par_color, Widget_types::SPLINE_CANVAS) {

		pencil = par_pencil;

		points = new Spline_point*[MAX_COUNT_OF_POINTS];
		for(size_t i = 0; i < MAX_COUNT_OF_POINTS; ++i)
			points[i] = new Spline_point;

		count_of_points = 0;

		spline = new Spline;
		canvas = par_canvas;

		mouse_click_state = par_mouse_click_state;

		visual_points = new Point[(int)par_width + 1];
		for(size_t i = 0; i <= (int)par_width; ++i)
			visual_points[i].x = i;

		add_point(rect->get_left_up_corner().x - 10, rect->get_left_up_corner().y + par_height + 11);
		add_point(rect->get_left_up_corner().x + par_width + 11, rect->get_left_up_corner().y - 11);

		add_point(rect->get_left_up_corner().x, rect->get_left_up_corner().y + par_height);
		add_point(rect->get_left_up_corner().x + par_width, rect->get_left_up_corner().y);

		check_count_of_points();
	}

	~Spline_canvas() {
		delete[] points;
		count_of_points = 0;
	}

	void check_count_of_points() {
		if(count_of_points == 4) { // two don't visible!
			int width = rect->get_width();
			double left_x = rect->get_left_up_corner().x;

			for(int i = 0; i <= width; ++i) {
				double x = i + left_x;
				double y = get_y_from_x(points[0], points[1], x);

				visual_points[i].x = x;
				visual_points[i].y = y;
			}
		}
	}

	int get_y_from_x(const Spline_point* ip_begin, const Spline_point* ip_end, const int x) {
		Point p_begin = ip_begin->rect->center;
		Point p_end   = ip_end->rect->center;

		if(p_end.x == p_begin.x) {
			return x - p_begin.x + p_begin.y;
		} else {
			return (p_end.y - p_begin.y) * (x - p_begin.x) / (p_end.x - p_begin.x) + p_begin.y;
		}
	}	

	void add_point(const double x, const double y, const Colour color = BLACK) {
		visual_points[(int)(x - rect->get_left_up_corner().x)].y = y;
		int now_index = spline->add_point(Point(x, y));

		Spline_point* new_point = new Spline_point(Point(x, y), color, mouse_click_state, now_index);
		points[count_of_points] = new_point;
		++count_of_points;

		if(count_of_points > 4) {
			spline->catmull_rom(visual_points, rect->get_width() + 1, rect->get_left_up_corner(), count_of_points);
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
							spline->points[this->points[i]->index] = now_mouse;
							spline->catmull_rom(visual_points, rect->get_width() + 1, rect->get_left_up_corner(), count_of_points);
							//spline->update_coords(visual_points, rect->get_width() + 1, rect->get_left_up_corner());
							return true;
						}
					}
				}
			}

			else
			if(*par_mouse_status == Mouse_click_state::MOUSE_MOTION) {

				//spline->update(visual_points, rect->get_width() + 1, rect->get_left_up_corner(), count_of_points, now_mouse);
				/*if(count_of_points >= 4) {
					spline->catmull_rom(visual_points, rect->get_width() + 1, rect->get_left_up_corner(), count_of_points);
				}*/
				//spline->update_coords(visual_points, rect->get_width() + 1, rect->get_left_up_corner());
			}
		}

		return false;
	}

	void func() {
		for(int i = 0; i < count_of_points; ++i)
			printf("(%d, %d), ", (int)points[i]->rect->center.x, (int)(points[i]->rect->center.y));
		printf("\n");

		for(int i = 0; i < spline->count_of_points; ++i)
			printf("(%d, %d), ", (int)spline->points[i].x, (int)spline->points[i].y);
		printf("\n\n");		
	}

	void draw(SDL_Renderer** render, SDL_Texture** texture, SDL_Surface** screen) override {
		if(is_visible) {
			rect->draw(*render);

			int width = rect->get_width();
			for(int i = 0; i < width; ++i) {
				Point now(i + rect->get_left_up_corner().x, visual_points[i].y);

				if(rect->is_point_belongs_to_rectangle(now))
					now.draw_big_point(*render, 1.5);
			}

			for(int i = 0; i < count_of_points; ++i) {
				Point now(points[i]->rect->get_center());

				if(rect->is_point_belongs_to_rectangle(now))
					points[i]->draw(render, texture, screen);
			}
		}
	}

	void update_position_from_delta(Point delta) {
		rect->set_center(rect->get_center() - delta);

		for(int i = 0; i < count_of_points; ++i) {
			points[i]->rect->center -= delta;
		}
		for(int i = 0; i < rect->get_width(); ++i)
			visual_points[i] -= delta;

		spline->update_position_from_delta(delta);
	}
};

#endif