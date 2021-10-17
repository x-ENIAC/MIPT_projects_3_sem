//#include "view_manager.h"
#include "button_delegate.h"
#include "pencil.h"

#ifndef OBJECT_DELEGATES_H
#define OBJECT_DELEGATES_H

class Close_delegate : public Button_delegate {
  public:

  	//Object_manager* object_manager;

  	Close_delegate(/*Object_manager* par_object_manager*/) {
  		/*object_manager = par_object_manager;*/
  	}

  	void click_reaction() override {
		/*Circle* new_circle = new Circle(Point(rand() % 500, rand() % 500), rand() % 10 + 10.0, 1.0, rand() % 10 + 1, rand() % 10 * -1 + 1,
										Colour(rand() % 256, rand() % 256, rand() % 256, 255), true, OBJECT_OWNER_OBJECT_CLASS);			
		
		object_manager->add_object(new_circle);*/
		printf("Close_delegate\n");
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
  		printf("Title_delegate\n");
	}
};

class Open_panel_delegate : public Button_delegate {
  public:

  	//Object_manager* object_manager;

  	Open_panel_delegate(/*Object_manager* par_object_manager*/) {
  		/*object_manager = par_object_manager;*/
  	}

  	void click_reaction() override {
  		printf("Open_panel_delegate\n");
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

  		//pencil->get_color().print();
  		//printf(" - > ");
  		pencil->set_color(yourself_color); 
  		//pencil->get_color().print();
  		//printf("\n");
	}
};

#endif