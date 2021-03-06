#include <SDL2/SDL.h>
#include "../Utils/point.h"
#include "../Utils/colour.h"
#include "../Utils/rectangle.h"
#include "../GUI/view.h"
#include "../GUI/button_delegates.h"
#include "canvas_manager.h"
#include "../GUI/button_manager.h"
#include "tab.h"

#ifndef MANAGER_OF_CANVAS_MANAGERS_H
#define MANAGER_OF_CANVAS_MANAGERS_H

class Title_delegate;
class Create_new_canvas_delegate;

class Manager_of_canvas_managers : public View_object {
  public:

	Canvas_manager** canvas_managers;
	size_t count_of_canvas_managers;

	Button_manager* button_manager;
	Point any_canvas_center;
	double any_canvas_width;
	double any_canvas_height;

	Mouse_click_state* mouse_click_state;

	int who_is_active;
	Canvas_manager* active_canvas;
	Painter_tools_and_plugins* painter_tools_and_plugins;

	Manager_of_canvas_managers(const Point par_point, const double par_width, const double par_height, 
							   const Colour par_color, const bool par_is_active, Mouse_click_state* par_mouse_click_state,
							   Painter_tools_and_plugins* par_painter_tools_and_plugins) :

	  View_object (par_point, par_width, par_height, par_color, Widget_types::CANVAS_MANAGER_MANAGER) {

		canvas_managers = new Canvas_manager*[MAX_COUNT_OF_VIEW_OBJECTS];
		for(size_t i = 0; i < MAX_COUNT_OF_VIEW_OBJECTS; ++i)
			canvas_managers[i] = new Canvas_manager;
		count_of_canvas_managers = 0;


		Point center_of_button_manager(par_width / 2.0, HEIGHT_CLOSE_BUTTON / 2.0);
		center_of_button_manager += rect->get_left_up_corner();

		button_manager = new Button_manager(center_of_button_manager, par_width, HEIGHT_CLOSE_BUTTON, WHITE);
		++widget_types[(int)Widget_types::BUTTON_MANAGER];

		fill_button_manager(rect->get_left_up_corner(), par_width, par_height, par_mouse_click_state);

		center_of_button_manager += Point(0.0, HEIGHT_TABS_BUTTON);
		any_canvas_center = par_point;
		any_canvas_center += Point(0, HEIGHT_TABS_BUTTON / 2.0);

		any_canvas_width = par_width;
		any_canvas_height = par_height - HEIGHT_CLOSE_BUTTON;

		mouse_click_state = par_mouse_click_state;

		who_is_active = -1;
		active_canvas = new Canvas_manager;

		painter_tools_and_plugins = par_painter_tools_and_plugins;
	}

	~Manager_of_canvas_managers() {
		for(int i = 0; i < MAX_COUNT_OF_VIEW_OBJECTS; ++i)
			delete canvas_managers[i];
		delete[] canvas_managers;

		delete button_manager;
	}

	void add_canvas_manager(Canvas_manager* new_canvas_manager);

	void fill_button_manager(Point left_up_corner, const double par_width, const double par_height, Mouse_click_state* par_mouse_click_state);

	void add_new_canvas_manager();

	bool check_click(const float mouse_x, const float mouse_y, const Mouse_click_state* par_mouse_status) override {
		printf("view_manager check_click, now active %d\n", who_is_active);

		//if(is_active) {

			if(rect->is_point_belongs_to_rectangle( Point(mouse_x, mouse_y) )) {

				if(button_manager->check_click(mouse_x, mouse_y, par_mouse_status))
					return true;

				//printf("%d\n", count_of_canvas_managers);
				//for(int i = count_of_canvas_managers - 1; i >= 0; --i) {
				//    printf("%d ", canvas_managers[i])

				for(int i = count_of_canvas_managers - 1; i >= 0; --i) {

					//printf("\tcall canvas_manager number %d - (is belong %d) (((, mouse (%lg, %lg), center (%lg, %lg)\n", i,
					//				rect->is_point_belongs_to_rectangle( Point(mouse_x, mouse_y) ), mouse_x, mouse_y, 
					//				canvas_managers[i]->rect->center.x, canvas_managers[i]->rect->center.y);

					if(canvas_managers[i]->check_click(mouse_x, mouse_y, par_mouse_status)) {

						//printf("set new active??? %d mouse, i = %d\n", *par_mouse_status, i);
						if(*par_mouse_status == Mouse_click_state::MOUSE_DOWN)
						   set_new_active_object(i);

						/*printf("is_active\n");
						for(size_t i = 0; i < count_of_canvas_managers; ++i)
							printf("%d ", canvas_managers[i]->is_active);
						printf("\n\n");*/

						return true;
					}
				}
			}
		//}

		return false;
	}

	bool check_motion(Point old_mouse, Point now_mouse, const Mouse_click_state* par_mouse_status) override {
		//printf("\n\nview_manager check_click\n");

		if(rect->is_point_belongs_to_rectangle( Point(now_mouse.x, now_mouse.y) ) ||
		   rect->is_point_belongs_to_rectangle( Point(old_mouse.x, old_mouse.y) )		) {

			if(button_manager->check_motion(old_mouse, now_mouse, par_mouse_status)) {
				for(int i = count_of_canvas_managers - 1; i >= 0; --i) {
					canvas_managers[i]->check_motion(old_mouse, now_mouse, par_mouse_status);
				}
			} else {
				for(int i = count_of_canvas_managers - 1; i >= 0; --i) {
					canvas_managers[i]->check_motion(old_mouse, now_mouse, par_mouse_status);
				}
			}

			return true;
		}

		return false;
	}

	void set_new_active_object(const int new_active);

	void draw(SDL_Renderer** render, SDL_Texture** texture, SDL_Surface** screen) override {
		rect->draw(*render);        
		
		button_manager->draw(render, texture, screen);

		draw_tabs_area(render, texture, screen);

		if(is_visible) {
			for(size_t i = 0; i < count_of_canvas_managers; ++i)
				canvas_managers[i]->draw(render, texture, screen);
		}
	}

	void draw_tabs_area(SDL_Renderer** render, SDL_Texture** texture, SDL_Surface** screen);

	void find_not_alive();

	void array_shift(const size_t pos);

	void update_tabs_offset(const size_t pos);

	void update_view_object_position(const double mouse_x, const double mouse_y) override {
		update_canvas_manager_position(mouse_x, mouse_y);
	}

	void update_canvas_manager_position(const double mouse_x, const double mouse_y);

	void tick(const double delta_time) override;
};

#endif