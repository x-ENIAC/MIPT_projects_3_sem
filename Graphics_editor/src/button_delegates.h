//#include "view_manager.h"
#include "button_delegate.h"
#include "pencil.h"
#include "view.h"

#ifndef OBJECT_DELEGATES_H
#define OBJECT_DELEGATES_H

const Point CENTER_OF_SPAWN_CANVASES = Point(300, 500);
const double DEFAULT_WIDTH = 100;
const double DEFAULT_HEIGHT = 100;

class Close_delegate : public Button_delegate {
  public:

  	Mouse_click_state* mouse_click_state;
  	bool* is_alive;

  	Close_delegate(Mouse_click_state* par_mouse_click_state, bool* par_is_alive) {
  		//view_manager = par_view_manager;
  		mouse_click_state = par_mouse_click_state;
  		is_alive = par_is_alive;
  	}

  	void click_reaction() override {
  		printf("Close_delegate\n");

  		if(*mouse_click_state == Mouse_click_state::MOUSE_DOWN) {
  			*is_alive = false;
  		}
  	}
};

//enum class Mouse_click_state;

class Roll_up_delegate : public Button_delegate {
  public:

  	//View_manager* view_manager;
  	Mouse_click_state* mouse_click_state;
  	bool* is_visible;
  	bool* is_active;

  	Roll_up_delegate(Mouse_click_state* par_mouse_click_state, bool* par_is_visible, bool* par_is_active) {
  		//view_manager = par_view_manager;
  		mouse_click_state = par_mouse_click_state;
  		is_visible = par_is_visible;
  		is_active  = par_is_active;
  	}

  	void click_reaction() override {
  		printf("Roll_up_delegate\n");

  		if(*mouse_click_state == Mouse_click_state::MOUSE_DOWN) {
  			*is_visible = false;
  			*is_active  = false;
  		}
	}
};

class Title_delegate : public Button_delegate {
  public:

  	//Object_manager* object_manager;

  	Title_delegate(/*Object_manager* par_object_manager*/) {
  		/*object_manager = par_object_manager;*/
  	}

  	void click_reaction() override {
  		//printf("Title_delegate\n");
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

  	void click_reaction() override {
  		//printf("!!! %p\n", mouse_click_state);
  		printf("Tab_title_delegate\n");

  		if(*mouse_click_state == Mouse_click_state::MOUSE_DOWN) {
  			*is_visible = true;
  			*is_active  = true;
  		}

  		//printf("...\n");
	}
};

class Open_panel_delegate : public Button_delegate {
  public:

  	//Object_manager* object_manager;

  	Open_panel_delegate(/*Object_manager* par_object_manager*/) {
  		/*object_manager = par_object_manager;*/
  	}

  	void click_reaction() override {
  		//printf("Open_panel_delegate\n");
	}
};

class Change_colour_delegate : public Button_delegate {
  public:

  	Pencil* pencil;
  	Colour yourself_color;

  	Change_colour_delegate(Pencil* par_pencil, const Colour par_yourself_color = BLACK) {
  		pencil = par_pencil;
  		yourself_color = par_yourself_color;
  	}

  	void click_reaction() override {
  		//printf("Change_colour_delegate\n");
  		pencil->set_color(yourself_color);
	}
};

#include "manager_of_canvas_managers.h"
class Manager_of_canvas_managers;
//enum class Mouse_click_state;

class Create_new_canvas_delegate : public Button_delegate {
  public:

  	Manager_of_canvas_managers* manager_of_canvas_managers;

  	Create_new_canvas_delegate(Manager_of_canvas_managers* par_manager_of_canvas_managers) {
  		manager_of_canvas_managers = par_manager_of_canvas_managers;
  	}

  	void click_reaction() override {
  		//printf("Create_new_canvas_delegate\n");
  		//printf("%d\n", view_manager->widget_types[(int)Widget_types::TABS]);
  		//view_manager->add_new_canvas_manager(CENTER_OF_SPAWN_CANVASES, DEFAULT_WIDTH, DEFAULT_HEIGHT);
  		//view_manager->add_new_canvas_manager(Point(rand() % 600 + 100, rand() % 500 + 250), rand() % 200 + 300, rand() % 200 + 300);

  		manager_of_canvas_managers->add_new_canvas_manager();
	}
};



#endif