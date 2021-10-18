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

  	//View_object* view_object;

  	Close_delegate(/*View_object* par_view_object*/) {
  		//view_object = par_view_object;
  	}

  	void click_reaction() override {
		/*Circle* new_circle = new Circle(Point(rand() % 500, rand() % 500), rand() % 10 + 10.0, 1.0, rand() % 10 + 1, rand() % 10 * -1 + 1,
										Colour(rand() % 256, rand() % 256, rand() % 256, 255), true, OBJECT_OWNER_OBJECT_CLASS);			
		
		object_manager->add_object(new_circle);*/
		//printf("Close_delegate\n");
	}
};

class Roll_up_delegate : public Button_delegate {
  public:

  	//View_manager* view_manager;

  	Roll_up_delegate(/*View_manager* par_view_manager*/) {
  		//view_manager = par_view_manager;
  	}

  	void click_reaction() override {
  		//printf("Roll_up_delegate\n");
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

#include "view_manager.h"
class View_manager;

class Create_new_canvas_delegate : public Button_delegate {
  public:

  	View_manager* view_manager;

  	Create_new_canvas_delegate(View_manager* par_view_manager) {
  		view_manager = par_view_manager;
  	}

  	void click_reaction() override {
  		//printf("Create_new_canvas_delegate\n");
  		printf("%d\n", view_manager->widget_types[(int)Widget_types::TABS]);
  		//view_manager->add_new_canvas_manager(CENTER_OF_SPAWN_CANVASES, DEFAULT_WIDTH, DEFAULT_HEIGHT);
  		view_manager->add_new_canvas_manager(Point(rand() % 600 + 100, rand() % 500 + 250), rand() % 400, rand() % 300);
	}
};



#endif