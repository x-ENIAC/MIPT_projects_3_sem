#include <SDL2/SDL.h>
#include "point.h"
#include "view.h"
#include "colour.h"
#include "spline_point.h"
#include "spline.h"
#include "manager_of_canvas_managers.h"

#include <unistd.h>

#ifndef SPLINE_CANVAS_H
#define SPLINE_CANVAS_H

extern const int MAX_COUNT_OF_POINTS;

enum Color_management {
	MAN_RED,
	MAN_GREEN,
	MAN_BLUE
};

class Spline_canvas : public View_object {
  public:
	Spline_point** points;
	size_t count_of_points;

	Spline* spline;
	Manager_of_canvas_managers* manager_of_canvas_managers;

	Point* visual_points;

	Mouse_click_state* mouse_click_state;
	Color_management color_management;

	Spline_canvas() : View_object() {}

	Spline_canvas(const Point par_point, const double par_width, const double par_height, 
		  			const Colour par_color, Manager_of_canvas_managers* par_manager_of_canvas_managers,
		  			Color_management par_color_management, Mouse_click_state* par_mouse_click_state) :
	  View_object (par_point, par_width, par_height, par_color, Widget_types::SPLINE_CANVAS) {

		points = new Spline_point*[MAX_COUNT_OF_POINTS];
		for(size_t i = 0; i < MAX_COUNT_OF_POINTS; ++i)
			points[i] = new Spline_point;

		count_of_points = 0;

		spline = new Spline;
		manager_of_canvas_managers = par_manager_of_canvas_managers;

		mouse_click_state = par_mouse_click_state;

		color_management = par_color_management;

		//printf("%lg, %lg\n", par_width, par_height);

		visual_points = new Point[(int)par_width + 1];
		for(size_t i = 0; i <= (int)par_width; ++i) {
			visual_points[i].x = i;
			visual_points[i].color = get_color(color_management);
		}

		add_point(rect->get_left_up_corner().x - 10, rect->get_left_up_corner().y + par_height + 11);
		add_point(rect->get_left_up_corner().x + par_width + 11, rect->get_left_up_corner().y - 11);

		add_point(rect->get_left_up_corner().x, rect->get_left_up_corner().y + par_height);
		add_point(rect->get_left_up_corner().x + par_width, rect->get_left_up_corner().y);

		check_count_of_points();
	}

	~Spline_canvas() {

		delete spline;
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

		Spline_point* new_point = new Spline_point(Point(x, y, get_color(color_management)), get_color(color_management), mouse_click_state, now_index);
		points[count_of_points] = new_point;
		//printf("color %lg, %lg, %lg\n", points[count_of_points]->rect->get_colour().red, points[count_of_points]->rect->get_colour().green, points[count_of_points]->rect->get_colour().blue);

		((Change_color_with_spline_delegate*)(points[count_of_points]->button->delegate))->manager_of_canvas_managers = manager_of_canvas_managers;

		++count_of_points;

		spline->catmull_rom(visual_points, rect->get_width() + 1, rect->get_left_up_corner(), count_of_points);
	}

	bool check_click(const float mouse_x, const float mouse_y, const Mouse_click_state* par_mouse_status) override {
		if(is_active && rect->is_point_belongs_to_rectangle( Point(mouse_x, mouse_y))) {
			if(*par_mouse_status == Mouse_click_state::MOUSE_DOWN) {

				bool flag = false;
				for(size_t i = 0; i < count_of_points; ++i) {
					//printf("\ttry %d\n", i);
					if(points[i]->rect->is_point_belongs_to_rectangle( Point(mouse_x, mouse_y))) 
						flag = points[i]->check_click(mouse_x, mouse_y, par_mouse_status);
				}

				if(!flag) {
					if(fabs(visual_points[(int)(mouse_x - rect->get_left_up_corner().x)].y - mouse_y) < 3) {
						add_point(mouse_x, mouse_y);
						flag = true;
					}
				}

				//if(!flag)
				//	add_point(mouse_x, mouse_y);

				return flag;
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

						if(points[i]->check_motion(old_mouse, now_mouse, par_mouse_status)) {
							spline->points[this->points[i]->index] = now_mouse;
							spline->catmull_rom(visual_points, rect->get_width() + 1, rect->get_left_up_corner(), count_of_points);
							//spline->update_coords(visual_points, rect->get_width() + 1, rect->get_left_up_corner());

							update_colors_into_canvas();

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

	void draw(SDL_Renderer** render, SDL_Texture** texture, SDL_Surface** screen) override {
		if(is_visible) {
			//rect->draw(*render);

			int width = rect->get_width();
			for(int i = 0; i < width; ++i) {
				Point now(i + rect->get_left_up_corner().x, visual_points[i].y, visual_points[i].color);

				if(rect->is_point_belongs_to_rectangle(now))
					now.draw_big_point(*render, 1.5);
			}

			for(int i = 0; i < count_of_points; ++i) {
				Point now(points[i]->rect->get_center(), points[i]->rect->get_colour());

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


	void update_colors_into_canvas() {
		//printf("%p, (%lg, %lg)\n", manager_of_canvas_managers, manager_of_canvas_managers->active_canvas->tab->rect->get_center().x,
		//													   manager_of_canvas_managers->active_canvas->tab->rect->get_center().y);
		if(!manager_of_canvas_managers || !manager_of_canvas_managers->active_canvas) 
			return;

		//Canvas* canvas; // = new Canvas;
		//canvas = (Canvas*)(manager_of_canvas_managers->active_canvas->view_objects[0]);
		int width = rect->get_width(), canvas_width  = manager_of_canvas_managers->active_canvas->view_objects[0]->rect->get_width(),
									   canvas_height = manager_of_canvas_managers->active_canvas->view_objects[0]->rect->get_height();

		Point left_down_corner = {points[0]->rect->center.x,points[0]->rect->center.y};

		for(int i = 0; i <= width; ++i) {

			double find_value = visual_points[i].x - left_down_corner.x;
			double new_value  = left_down_corner.y - visual_points[i].y;

			if(find_value == new_value)
				continue;

			for(int i = 0; i <= canvas_width; ++i) {
				for(int j = 0; j <= canvas_height; ++j) {
					//printf("\t%d, %d\n", i, j);
					//printf("\t%p\n", canvas->cells_color[i]);
					if(color_management == Color_management::MAN_RED &&
					  ((Canvas*)(manager_of_canvas_managers->active_canvas->view_objects[0]))->cells_color[i][j].begin_color.red == find_value) {
						//if(((Canvas*)(manager_of_canvas_managers->active_canvas->view_objects[0]))->cells_color[i][j].begin_color.red != 255)
							//printf("!!! %lg -> %lg\n", ((Canvas*)(manager_of_canvas_managers->active_canvas->view_objects[0]))->cells_color[i][j].begin_color.red, new_value);
						//if(find_value < 255)
						//	printf("(%lg, %lg, %lg) ->", ((Canvas*)(manager_of_canvas_managers->active_canvas->view_objects[0]))->cells_color[i][j].color_after_correction.red,
						//									((Canvas*)(manager_of_canvas_managers->active_canvas->view_objects[0]))->cells_color[i][j].color_after_correction.green,
						//									((Canvas*)(manager_of_canvas_managers->active_canvas->view_objects[0]))->cells_color[i][j].color_after_correction.blue);
						((Canvas*)(manager_of_canvas_managers->active_canvas->view_objects[0]))->cells_color[i][j].color_after_correction.red = new_value;
						//	printf("(%lg, %lg, %lg)\n \n", ((Canvas*)(manager_of_canvas_managers->active_canvas->view_objects[0]))->cells_color[i][j].color_after_correction.red,
						//									((Canvas*)(manager_of_canvas_managers->active_canvas->view_objects[0]))->cells_color[i][j].color_after_correction.green,
						//									((Canvas*)(manager_of_canvas_managers->active_canvas->view_objects[0]))->cells_color[i][j].color_after_correction.blue);

					}
					else
					if(color_management == Color_management::MAN_GREEN &&
					  ((Canvas*)(manager_of_canvas_managers->active_canvas->view_objects[0]))->cells_color[i][j].begin_color.green == find_value) {
						((Canvas*)(manager_of_canvas_managers->active_canvas->view_objects[0]))->cells_color[i][j].color_after_correction.green = new_value;
					}
					else
					if(color_management == Color_management::MAN_BLUE &&
					  ((Canvas*)(manager_of_canvas_managers->active_canvas->view_objects[0]))->cells_color[i][j].begin_color.blue == find_value) {
						((Canvas*)(manager_of_canvas_managers->active_canvas->view_objects[0]))->cells_color[i][j].color_after_correction.blue = new_value;
					}					
				}
			}
		}
	}

	Colour get_color(const Color_management m_color) {
		if(m_color == Color_management::MAN_RED)
			return RED;
		else
		if(m_color == Color_management::MAN_GREEN)
			return GREEN;
		//else
		//if(m_color == Color_management::MAN_BLUE)
			return BLUE;

	}

	void func() {
		for(int i = 0; i < count_of_points; ++i)
			printf("(%d, %d), ", (int)points[i]->rect->center.x, (int)(points[i]->rect->center.y));
		printf("\n");

		for(int i = 0; i < spline->count_of_points; ++i)
			printf("(%d, %d), ", (int)spline->points[i].x, (int)spline->points[i].y);
		printf("\n\n");		
	}	
};

#endif