//#include "view_manager.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "button_delegate.h"
#include "pencil.h"
#include "view.h"
#include "animation_manager.h"
#include "slider_field.h"

#ifndef OBJECT_DELEGATES_H
#define OBJECT_DELEGATES_H

#include "tool_manager.h"

extern SDL_Renderer* render;

class Animation_manager;
extern Animation_manager* anim_manager;
extern const double TIME_DELTA;

const Point CENTER_OF_SPAWN_CANVASES = Point(300, 500);
const double DEFAULT_WIDTH = 100;
const double DEFAULT_HEIGHT = 100;

class Close_delegate : public Button_delegate {
  public:

	View_object* view_object;
	Mouse_click_state* mouse_click_state;
	bool* is_alive;

	Close_delegate(View_object* par_view_object, Mouse_click_state* par_mouse_click_state, bool* par_is_alive) {
		view_object = par_view_object;
		mouse_click_state = par_mouse_click_state;
		is_alive = par_is_alive;
	}

	void click_reaction(const double mouse_x, const double mouse_y) override {
		printf("Close_delegate\n");

		if(*mouse_click_state == Mouse_click_state::MOUSE_DOWN) {
			*is_alive = false;
		}
	}

	void motion_reaction(const double mouse_x, const double mouse_y) override {}

	void reactive_reaction(Point old_mouse, Point now_mouse) override {
		bool old_lie = view_object->rect->is_point_belongs_to_rectangle(old_mouse);
		bool now_lie = view_object->rect->is_point_belongs_to_rectangle(now_mouse);

		if(!old_lie && now_lie)
			anim_manager->add_animation(render, view_object->texture->path_to_picture, "textures/grey_1_close.bmp", view_object, TIME_DELTA);
		
		else
		if(old_lie && !now_lie)
			anim_manager->add_animation(render, view_object->texture->path_to_picture, "textures/black_close.bmp", view_object, TIME_DELTA);
	}
};




class Roll_up_delegate : public Button_delegate {
  public:

	//View_manager* view_manager;
	Mouse_click_state* mouse_click_state;
	bool* is_visible;
	bool* is_active;

	Roll_up_delegate(Mouse_click_state* par_mouse_click_state, bool* par_is_visible, bool* par_is_active) {
		mouse_click_state = par_mouse_click_state;
		is_visible = par_is_visible;
		is_active  = par_is_active;
	}

	void click_reaction(const double mouse_x, const double mouse_y) override {
		//printf("Roll_up_delegate\n");

		if(*mouse_click_state == Mouse_click_state::MOUSE_DOWN) {
			*is_visible = false;
			*is_active  = false;
		}
	}

	void motion_reaction(const double mouse_x, const double mouse_y) override {}

	void reactive_reaction(Point old_mouse, Point now_mouse) override {
		//anim_manager->add_animation(render, "textures/black_close.bmp", "textures/grey_1_close.bmp", view_object, TIME_DELTA * 10);		
	}
};




class Tab_title_delegate : public Button_delegate {
  public:

	Mouse_click_state* mouse_click_state;
	bool* is_visible;
	bool* is_active;

	Tab_title_delegate(Mouse_click_state* par_mouse_click_state, bool* par_is_visible, bool* par_is_active) {

		mouse_click_state = par_mouse_click_state;
		is_visible = par_is_visible;
		is_active  = par_is_active;
	}

	void click_reaction(const double mouse_x, const double mouse_y) override {
		printf("Tab_title_delegate\n");

		if(*mouse_click_state == Mouse_click_state::MOUSE_DOWN) {
			*is_visible = true;
			*is_active  = true;
			//*is_reactive = true;
		}
	}

	void motion_reaction(const double mouse_x, const double mouse_y) override {}

	void reactive_reaction(Point old_mouse, Point now_mouse) override {}
};




class Open_panel_delegate : public Button_delegate {
  public:

	//Object_manager* object_manager;

	Open_panel_delegate(/*Object_manager* par_object_manager*/) {
		/*object_manager = par_object_manager;*/
	}

	void click_reaction(const double mouse_x, const double mouse_y) override {
		//printf("Open_panel_delegate\n");
	}

	void motion_reaction(const double mouse_x, const double mouse_y) override {}

	void reactive_reaction(Point old_mouse, Point now_mouse) override {}
};





class Change_colour_delegate : public Button_delegate {
  public:

	Colour yourself_color;

	Change_colour_delegate(const Colour par_yourself_color = BLACK) {
		yourself_color = par_yourself_color;
	}

	void click_reaction(const double mouse_x, const double mouse_y) override {
		//printf("Change_colour_delegate\n");
		Tool_manager::get_tool_manager()->set_pen_colour(yourself_color);
	}

	void motion_reaction(const double mouse_x, const double mouse_y) override {}

	void reactive_reaction(Point old_mouse, Point now_mouse) override {}
};





class Change_thickness_delegate : public Button_delegate {
  public:

	size_t yourself_thickness;

	Change_thickness_delegate(const size_t par_yourself_thickness = 24) {
		yourself_thickness = par_yourself_thickness;
	}

	void click_reaction(const double mouse_x, const double mouse_y) override {
		printf("\tbegin Change_thickness_delegate, pencil %ld\n", yourself_thickness);
		Tool_manager::get_tool_manager()->set_pen_size(yourself_thickness);
		printf("\tend Change_thickness_delegate, pencil\n");
	}

	void motion_reaction(const double mouse_x, const double mouse_y) override {}

	void reactive_reaction(Point old_mouse, Point now_mouse) override {}
};




class Open_window_delegate : public Button_delegate {
  public:

	bool* is_visible;

	Open_window_delegate(bool* par_is_visible) {
		is_visible = par_is_visible;
	}

	void click_reaction(const double mouse_x, const double mouse_y) override {
		*is_visible = true;
	}

	void motion_reaction(const double mouse_x, const double mouse_y) override {}

	void reactive_reaction(Point old_mouse, Point now_mouse) override {}
};





class Slider_field_delegate : public Button_delegate {
  public:

	Slider_field* slider_field;
	Point* center;

	Slider_field_delegate(Slider_field* par_slider_field, Point* par_center) {
		slider_field = par_slider_field;
		center = par_center;
		//printf("tttttttttttt!\n");
	}

	void click_reaction(const double mouse_x, const double mouse_y) override {
		center->x = mouse_x;
	}

	void motion_reaction(const double mouse_x, const double mouse_y) override {
		//printf("motion slider!\n");
	}

	void reactive_reaction(Point old_mouse, Point now_mouse) override {
		//printf("reactive slider!\n");
	}
};





#include "manager_of_canvas_managers.h"
class Manager_of_canvas_managers;

class Title_delegate : public Button_delegate {
  public:

	//Manager_of_canvas_managers* manager_of_canvas_managers;
	View_object* view_object;

	Title_delegate(View_object* par_view_object) {
		view_object = par_view_object;
	}

	void click_reaction(const double mouse_x, const double mouse_y) override {
		printf("Title_delegate\n");
	}

	void motion_reaction(const double mouse_x, const double mouse_y) override {
		//manager_of_canvas_managers->update_canvas_manager_position(mouse_x, mouse_y);
		view_object->update_view_object_position(mouse_x, mouse_y);
	}

	void reactive_reaction(Point old_mouse, Point now_mouse) override {}
};




class Create_new_canvas_delegate : public Button_delegate {
  public:

	Manager_of_canvas_managers* manager_of_canvas_managers;

	Create_new_canvas_delegate(Manager_of_canvas_managers* par_manager_of_canvas_managers) {
		manager_of_canvas_managers = par_manager_of_canvas_managers;
	}

	void click_reaction(const double mouse_x, const double mouse_y) override {
		//printf("Create_new_canvas_delegate\n");
		//printf("%d\n", view_manager->widget_types[(int)Widget_types::TABS]);
		//view_manager->add_new_canvas_manager(CENTER_OF_SPAWN_CANVASES, DEFAULT_WIDTH, DEFAULT_HEIGHT);
		//view_manager->add_new_canvas_manager(Point(rand() % 600 + 100, rand() % 500 + 250), rand() % 200 + 300, rand() % 200 + 300);

		manager_of_canvas_managers->add_new_canvas_manager();
	}

	void motion_reaction(const double mouse_x, const double mouse_y) override {}

	void reactive_reaction(Point old_mouse, Point now_mouse) override {}
};



class Change_color_with_spline_delegate : public Button_delegate {
  public:

	Manager_of_canvas_managers* manager_of_canvas_managers;

	Change_color_with_spline_delegate(Manager_of_canvas_managers* par_manager_of_canvas_managers) {
		manager_of_canvas_managers = par_manager_of_canvas_managers;
	}

	void click_reaction(const double mouse_x, const double mouse_y) override {
		//printf("Create_new_canvas_delegate\n");
		//printf("%d\n", view_manager->widget_types[(int)Widget_types::TABS]);
		//view_manager->add_new_canvas_manager(CENTER_OF_SPAWN_CANVASES, DEFAULT_WIDTH, DEFAULT_HEIGHT);
		//view_manager->add_new_canvas_manager(Point(rand() % 600 + 100, rand() % 500 + 250), rand() % 200 + 300, rand() % 200 + 300);

		//manager_of_canvas_managers->add_new_canvas_manager();
	}

	void motion_reaction(const double mouse_x, const double mouse_y) override {}

	void reactive_reaction(Point old_mouse, Point now_mouse) override {}
};



#endif