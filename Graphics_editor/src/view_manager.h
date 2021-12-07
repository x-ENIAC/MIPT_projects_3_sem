//#include "view.h"
//#include "animation_manager.h"
#include "manager_of_canvas_managers.h"
#include "button.h"
#include "canvas_manager.h"
#include "pencil.h"
#include "palette.h"
#include "thickness_palette.h"
#include "tab.h"
#include "chart.h"
#include "slider_manager.h"
#include "tool_manager.h"
#include "plugin_tool.h"
#include "plugin_interface.h"

#ifndef VIEW_MANAGER_H
#define VIEW_MANAGER_H

//class Animation_manager;
class View_manager;

//#include "app.h"
//class App;

class Create_new_canvas_delegate;
//class Tool_manager;

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

	Pencil* pencil;

	Button_manager* panel_buttons_manager;
	// Tool_manager* tool_manager;
	Manager_of_canvas_managers* manager_of_canvas_managers;

	Mouse_click_state mouse_click_state;

	Point old_pos_mouse, now_pos_mouse;

	//PAppInterface* app_interface;

	View_manager(const Point par_point, const double par_width, const double par_height, const Colour par_color/*, Animation_manager* par_animation_manager*/) :
	  View_object(par_point, par_width, par_height, LIGHT_GREY, Widget_types::VIEW_MANAGER) {

		count_of_view_objects = 1;

		view_objects = new View_object*[MAX_COUNT_OF_VIEW_OBJECTS];
		for(size_t i = 0; i < MAX_COUNT_OF_VIEW_OBJECTS; ++i)
			view_objects[i] = new View_object;

		who_is_active = -1;

		mouse_click_state = Mouse_click_state::MOUSE_UP;

		//pencil = new Pencil;

		/* ----------------------- add tool manager ---------------------------------------------------------- */

		Tool_manager::get_tool_manager()->initialize(Point(200, 500), 150, 150, DARK_GREY_2, Widget_types::TOOL_MANAGER);

		// tool_manager = new Tool_manager(Point(200, 500), 150, 150, DARK_GREY_2, Widget_types::TOOL_MANAGER); //, PATH_TO_PICTURE_WITH_TITLE_BUTTON);
		fill_tool_manager();

		add_view_object(Tool_manager::get_tool_manager());

		/* ----------------------- add manager of canvas managers ---------------------------------------------------------- */		

		printf("Start initialize the manager_of_canvas_managers\n");
		manager_of_canvas_managers = new Manager_of_canvas_managers(CENTER_MANAGER_OF_CANVAS_MANAGERS,
																	WIDTH_MANAGER_OF_CANVAS_MANAGERS_WIDGET,
																	HEIGHT_MANAGER_OF_CANVAS_MANAGERS_WIDGET,
																	LIGHT_LIGHT_GREY,
																	pencil, 
																	false,
																	&mouse_click_state);

		Point center_of_button_manager(par_width / 2.0, HEIGHT_CLOSE_BUTTON / 2.0), left_up_corner = rect->get_left_up_corner();
		center_of_button_manager += left_up_corner;

		panel_buttons_manager = new Button_manager(center_of_button_manager, par_width, HEIGHT_CLOSE_BUTTON, DARK_GREY_2, PATH_TO_PICTURE_WITH_TITLE_BUTTON);
		add_view_object(panel_buttons_manager);

		fill_panel_button_manager(left_up_corner, par_width, par_height);

		/* ----------------------- add colour palette ---------------------------------------------------------- */

		Point center_button(panel_buttons_manager->buttons[panel_buttons_manager->get_count_of_buttons() - 1]->rect->get_center());

		Palette* palette = new Palette(par_width - WIDTH_CLOSE_BUTTON, HEIGHT_CLOSE_BUTTON * 3, pencil, &mouse_click_state);
		add_view_object(palette);

		Open_window_delegate* open_colour_palette_delegate = new Open_window_delegate(&(palette->is_visible));

		center_button += Point(WIDTH_FILE_PANEL_BUTTON, 0);
		Button* colour_palette_button = new Button(open_colour_palette_delegate, center_button, DARK_GREY, WIDTH_FILE_PANEL_BUTTON, HEIGHT_CLOSE_BUTTON,
											   TEXT_PALETTE_1, BLACK);
		colour_palette_button->texture->add_new_texture(PATH_TO_PICTURE_WITH_PALETTE_BUTTON);
		panel_buttons_manager->add_view_object(colour_palette_button);

		/* ----------------------- add thickness palette ---------------------------------------------------------- \\	  */

		Thickness_palette* thickness_palette = new Thickness_palette(0 + 10 * WIDTH_CLOSE_BUTTON, HEIGHT_CLOSE_BUTTON * 3, pencil, &mouse_click_state);
		add_view_object(thickness_palette);

		Open_window_delegate* open_thickness_palette_delegate = new Open_window_delegate(&(thickness_palette->is_visible));

		center_button += Point(WIDTH_FILE_PANEL_BUTTON, 0);
		Button* thickness_palette_button = new Button(open_thickness_palette_delegate, center_button, DARK_GREY, WIDTH_FILE_PANEL_BUTTON, HEIGHT_CLOSE_BUTTON,
											   TEXT_PALETTE_2, BLACK);
		thickness_palette_button->texture->add_new_texture(PATH_TO_PICTURE_WITH_THICKNESS_BUTTON);
		panel_buttons_manager->add_view_object(thickness_palette_button);

		Chart* chart = new Chart(Point(600, 300), 255, 255, WHITE, pencil, manager_of_canvas_managers, false, &mouse_click_state);
		add_view_object(chart);

		/* ----------------------- add slider ---------------------------------------------------------- \\	  */

		Slider_manager* slider_manager = new Slider_manager(Point(300, 100), 10, 0, 100, &mouse_click_state);
		add_view_object(slider_manager);

		/* ----------------------- add spline screen ---------------------------------------------------------- */

		/*Point center_button(view_objects[count_of_view_objects - 1]->rect->get_center()*/
		center_button += Point(WIDTH_FILE_PANEL_BUTTON, 0);

		Open_window_delegate* open_spline_delegate = new Open_window_delegate(&(chart->is_visible));

		Button* spline_panel_button = new Button(open_spline_delegate, center_button, DARK_GREY, WIDTH_FILE_PANEL_BUTTON, HEIGHT_CLOSE_BUTTON,
											   TEXT_SPLINE, BLACK);

		spline_panel_button->texture->add_new_texture(PATH_TO_PICTURE_WITH_SPLINE_BUTTON);
		panel_buttons_manager->add_view_object(spline_panel_button);

		/* ----------------------- add canvases ---------------------------------------------------------- */

		//Point center_button(view_objects[count_of_view_objects - 1]->rect->get_center());
		center_button += Point(WIDTH_FILE_PANEL_BUTTON, 0);

		Open_window_delegate* open_canvases_delegate = new Open_window_delegate(&(manager_of_canvas_managers->is_visible));

		Button* canvas_panel_button = new Button(open_canvases_delegate, center_button, DARK_GREY, WIDTH_FILE_PANEL_BUTTON, HEIGHT_CLOSE_BUTTON,
											   TEXT_CANVASES, BLACK);
		canvas_panel_button->texture->add_new_texture(PATH_TO_PICTURE_WITH_CANVAS_BUTTON);
		panel_buttons_manager->add_view_object(canvas_panel_button);

		//sdl_ticks = SDL_GetTicks();
		//printf("%d\n", sdl_ticks);

		//fill_app_interface();

		old_pos_mouse = now_pos_mouse = Point(0, 0);
	}

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

		++widget_types[new_view->get_yourself_type()];
	}  	

	void draw(SDL_Renderer** render, SDL_Texture** texture, SDL_Surface** screen) override {
		if(is_visible) {
			rect->draw(*render);

			manager_of_canvas_managers->draw(render, texture, screen);

			for(size_t i = 0; i < count_of_view_objects; ++i) {
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
				//printf("motion\n");

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
				pencil->set_color(BLACK);
				return true;

			case SDLK_r:					// RED
				pencil->set_color(RED);
				return true;

			case SDLK_g:					// GREEN
				pencil->set_color(GREEN);
				return true;

			case SDLK_y:					// YELLOW
				pencil->set_color(YELLOW);
				return true;

			case SDLK_l:					// BLUE (l)
				pencil->set_color(BLUE);
				return true;

			case SDLK_p:					// BLUE (l)
				printf("canvas??? %p\n", manager_of_canvas_managers->active_canvas->view_objects[0]);
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