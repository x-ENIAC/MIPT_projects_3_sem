//#include "view_manager.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "button_delegate.h"
#include "pencil.h"
#include "view.h"
#include "animation_manager.h"

#ifndef OBJECT_DELEGATES_H
#define OBJECT_DELEGATES_H


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
	//Texture* texture;
	Mouse_click_state* mouse_click_state;
	bool* is_alive;

	Close_delegate(View_object* par_view_object, Mouse_click_state* par_mouse_click_state, bool* par_is_alive) {
		//view_object_manager = par_view_object_manager;
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

	void reactive_reaction(const double mouse_x, const double mouse_y) override {
		anim_manager->add_animation(render, "textures/black_close.bmp", "textures/grey_1_close.bmp", view_object, TIME_DELTA * 10);
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

	void reactive_reaction(const double mouse_x, const double mouse_y) override {
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

	void reactive_reaction(const double mouse_x, const double mouse_y) override {}
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

	void reactive_reaction(const double mouse_x, const double mouse_y) override {}
};





class Change_colour_delegate : public Button_delegate {
  public:

	Pencil* pencil;
	Colour yourself_color;

	Change_colour_delegate(Pencil* par_pencil, const Colour par_yourself_color = BLACK) {
		pencil = par_pencil;
		yourself_color = par_yourself_color;
	}

	void click_reaction(const double mouse_x, const double mouse_y) override {
		//printf("Change_colour_delegate\n");
		pencil->set_color(yourself_color);
	}

	void motion_reaction(const double mouse_x, const double mouse_y) override {}

	void reactive_reaction(const double mouse_x, const double mouse_y) override {}
};





class Change_thickness_delegate : public Button_delegate {
  public:

	Pencil* pencil;
	size_t yourself_thickness;

	Change_thickness_delegate(Pencil* par_pencil, const size_t par_yourself_thickness = 24) {
		pencil = par_pencil;
		yourself_thickness = par_yourself_thickness;
	}

	void click_reaction(const double mouse_x, const double mouse_y) override {
		//printf("Change_thickness_delegate\n");
		pencil->set_thickness(yourself_thickness);
	}

	void motion_reaction(const double mouse_x, const double mouse_y) override {}

	void reactive_reaction(const double mouse_x, const double mouse_y) override {}
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

	void reactive_reaction(const double mouse_x, const double mouse_y) override {}
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

	void reactive_reaction(const double mouse_x, const double mouse_y) override {}
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

	void reactive_reaction(const double mouse_x, const double mouse_y) override {}
};



#endif