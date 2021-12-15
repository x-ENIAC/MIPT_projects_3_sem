//#include "view.h"
//#include "animation_manager.h"
#include "manager_of_canvas_managers.h"
#include "../GUI/button.h"
#include "canvas_manager.h"
#include "Tools/pencil.h"
#include "palette.h"
#include "thickness_palette.h"
#include "tab.h"
#include "../GUI/chart.h"
#include "../GUI/slider_manager.h"
#include "Tools/tool_manager.h"
#include "../Plugins/plugin_tool.h"
#include "../Plugins/plugin_effect.h"
#include "../Plugins/plugin_interface.h"

#ifndef VIEW_MANAGER_H
#define VIEW_MANAGER_H

#include "../app.h"

class View_manager;

class Create_new_canvas_delegate;

const double WIDTH_FILE_PANEL_BUTTON = 60;

const double WIDTH_TOOLS_WIDGET      = 100;
const double HEIGHT_TOOLS_WIDGET     = 100;

const Point CENTER_MANAGER_OF_CANVAS_MANAGERS = Point(600, 600);
const double WIDTH_MANAGER_OF_CANVAS_MANAGERS_WIDGET  = 100; // 340;
const double HEIGHT_MANAGER_OF_CANVAS_MANAGERS_WIDGET = 100; // 200;

class View_manager : public View_object {
  public:
	View_object** view_objects;
	size_t count_of_view_objects;
	int who_is_active;

	Button_manager* panel_buttons_manager;

	Manager_of_canvas_managers* manager_of_canvas_managers;

	Painter_tools_and_plugins* painter_tools_and_plugins;

	Mouse_click_state mouse_click_state;

	Point old_pos_mouse, now_pos_mouse;

	View_manager(const Point par_point, const double par_width, const double par_height, const Colour par_color) :
	  View_object(par_point, par_width, par_height, LIGHT_GREY, Widget_types::VIEW_MANAGER) {

		count_of_view_objects = 1;

		view_objects = new View_object*[MAX_COUNT_OF_VIEW_OBJECTS];
		for(size_t i = 0; i < MAX_COUNT_OF_VIEW_OBJECTS; ++i)
			view_objects[i] = new View_object;

		who_is_active = -1;

		mouse_click_state = Mouse_click_state::MOUSE_UP;

		add_tool_manager();

		add_manager_of_canvas_managers();

		Point center_button(panel_buttons_manager->buttons[panel_buttons_manager->get_count_of_buttons() - 1]->rect->get_center());

		add_palette(&center_button);

		add_thickness_palette(&center_button);

		add_slider();

		add_spline(&center_button);

		add_canvases(&center_button);

		old_pos_mouse = now_pos_mouse = Point(0, 0);

		printf("end construct view manager\n");
	}

	void add_tool_manager();

	void add_manager_of_canvas_managers();

	void add_palette(Point* center_button);

	void add_thickness_palette(Point* center_button);

	void add_slider();

	void add_spline(Point* center_button);

	void add_canvases(Point* center_button);

	void fill_panel_button_manager(Point left_up_corner, const double par_width, const double par_height);

	void fill_tool_manager();

	~View_manager() {
		printf("Destruct View_manager, %ld\n", count_of_view_objects);

		/*for(size_t i = 0; i < count_of_view_objects; ++i)
			delete[] view_objects[i];
		delete[] view_objects;

		delete[] panel_buttons_manager;
		delete[] manager_of_canvas_managers;*/

		count_of_view_objects = 0;
		who_is_active = 0;
	}

	void add_new_canvas_manager() {
		manager_of_canvas_managers->add_new_canvas_manager();
	}

	void add_view_object(View_object* new_view) {
		view_objects[count_of_view_objects] = new_view;
		++count_of_view_objects;

		++widget_types[(int)new_view->get_yourself_type()];
	}  	

	void draw(SDL_Renderer** render, SDL_Texture** texture, SDL_Surface** screen) override {
		if(is_visible) {
			rect->draw(*render);

			manager_of_canvas_managers->draw(render, texture, screen);

			for(size_t i = 0; i < count_of_view_objects; ++i) {
				// printf("vidwet %d\n", (int)(view_objects[i]->get_yourself_type()));
				view_objects[i]->draw(render, texture, screen);
			}

			// tool_manager->draw(render, texture, screen);
		}
	}

	void check_events(SDL_Event* event) {
		double x_mouse = event->button.x, y_mouse = event->button.y;

		//printf("%d\n", event->type);
		if(event->type == SDL_MOUSEBUTTONUP) {
			mouse_click_state = Mouse_click_state::MOUSE_UP;

			bool is_solved = check_click(x_mouse, y_mouse, &mouse_click_state);
		}

		else
		if(event->type == SDL_MOUSEBUTTONDOWN) {
			mouse_click_state = Mouse_click_state::MOUSE_DOWN;
			

			bool is_solved = check_click(x_mouse, y_mouse, &mouse_click_state);
		}		

		else if(event->type == SDL_MOUSEMOTION) {

			if(mouse_click_state == Mouse_click_state::MOUSE_DOWN || mouse_click_state == Mouse_click_state::MOUSE_DOWN_AND_MOTION) {
				mouse_click_state = Mouse_click_state::MOUSE_DOWN_AND_MOTION;
				//bool is_solved = check_motion(old_pos_mouse, now_pos_mouse, &mouse_click_state);

			} else 
				mouse_click_state = Mouse_click_state::MOUSE_MOTION;
				// printf("motion\n");

			now_pos_mouse = {x_mouse, y_mouse};
			bool is_solved = check_motion(old_pos_mouse, now_pos_mouse, &mouse_click_state);
			old_pos_mouse = now_pos_mouse;
			
		}

		else if(event->type == SDL_KEYDOWN) {
			bool is_solved = check_tap(event);
		}
	}

	bool check_click(const float mouse_x, const float mouse_y, const Mouse_click_state* par_mouse_status) override {
		printf("\n\nview_manager check_click, mouse (%d, %d)\n", (int)mouse_x, (int)mouse_y);

		if(is_active) {

			if(manager_of_canvas_managers->check_click(mouse_x, mouse_y, par_mouse_status)) {
				printf("manager_of_canvas_managers\n");
				find_not_alive();
				return true;
			}

			//printf("click View_manager\n");
			for(int i = count_of_view_objects - 1; i >= 0; --i) {
				if(view_objects[i]->check_click(mouse_x, mouse_y, par_mouse_status)) {
					//set_new_active_object(i);
					find_not_alive();
					return true;
				}
			}
		}

		find_not_alive();
		return false;
	}

	bool check_motion(Point old_mouse, Point now_mouse, const Mouse_click_state* par_mouse_status) override {
		//printf("\n\nview_manager check_click\n");

		if(is_active) {

			if(manager_of_canvas_managers->check_motion(old_mouse, now_mouse, par_mouse_status)) {
				return true;
			}

			//printf("click View_manager\n");
			for(int i = count_of_view_objects - 1; i >= 0; --i) {
				if(view_objects[i]->check_motion(old_mouse, now_mouse, par_mouse_status)) {
					return true;
				}
			}
		}

		return false;
	}

	bool check_tap(SDL_Event* event) {
		//if(event->key.repeat != 0) // клавиша зажата
		//	printf("NICE\n");

		switch (event->key.keysym.sym) {
			case SDLK_b:					// black
				Tool_manager::get_tool_manager()->set_pen_colour(BLACK);
				// pencil->set_color(BLACK);
				return true;

			case SDLK_r:					// RED
				Tool_manager::get_tool_manager()->set_pen_colour(RED);
				// pencil->set_color(RED);
				return true;

			case SDLK_g:					// GREEN
				Tool_manager::get_tool_manager()->set_pen_colour(GREEN);
				// pencil->set_color(GREEN);
				return true;

			case SDLK_y:					// YELLOW
				Tool_manager::get_tool_manager()->set_pen_colour(YELLOW);
				// pencil->set_color(YELLOW);
				return true;

			case SDLK_l:					// BLUE (l)
				Tool_manager::get_tool_manager()->set_pen_colour(BLUE);
				// pencil->set_color(BLUE);
				return true;

			case SDLK_p:					// BLUE (l)
				// printf("canvas??? %p\n", manager_of_canvas_managers->active_canvas->view_objects[0]);
				Plugin_effect* effect1 = new Plugin_effect(WAY_TO_KCTF_NEGATIVE, App::get_app()->get_app_interface());
				effect1->plugin_interface->effect.apply();
				delete effect1;
				//start_plagin();
				//make_negative((Canvas*)(manager_of_canvas_managers->active_canvas->view_objects[0]));
				return true;				
		}

		return false;	  		
	}

	/*void set_new_active_object(const int new_active) {
		if(who_is_active != -1)
			view_objects[who_is_active]->is_active = false;

		who_is_active = new_active;

		if(who_is_active != -1)
			view_objects[who_is_active]->is_active = true;
	}*/

	void find_not_alive() {
		//for()
		manager_of_canvas_managers->find_not_alive();
	}
};

#endif