#include "object_manager.h"
#include "button_delegate.h"

#ifndef OBJECT_DELEGATES_H
#define OBJECT_DELEGATES_H

class Add_circle_delegate : public Button_delegate {
  public:

  	Object_manager* object_manager;

  	Add_circle_delegate(Object_manager* par_object_manager) {
  		object_manager = par_object_manager;
  	}

  	void click_reaction() override {
		Circle* new_circle = new Circle(Point(rand() % 500, rand() % 500), rand() % 10 + 10.0, 1.0, rand() % 10 + 1, rand() % 10 * -1 + 1,
										Colour(rand() % 256, rand() % 256, rand() % 256, 255), true, OBJECT_OWNER_OBJECT_CLASS);			

		object_manager->add_object(new_circle);
	}
};

class Add_rectangle_delegate : public Button_delegate {
  public:

  	Object_manager* object_manager;

  	Add_rectangle_delegate(Object_manager* par_object_manager) {
  		object_manager = par_object_manager;
  	}

  	void click_reaction() override {
		Rectangle* new_rect = new Rectangle(Point(rand() % 500, rand() % 500), rand() % 9 + 1, rand() % 10 + 1, rand() % 10 * -1 + 1,
											Colour(rand() % 256, rand() % 256, rand() % 256, 255), rand() % 30 + 10, rand() % 30 + 10, RECTANGLE,
											true);

		object_manager->add_object(new_rect);
	}
};

#endif