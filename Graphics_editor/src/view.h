#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "point.h"
#include "colour.h"
#include "rectangle.h"
#include "widget_types.h"

#ifndef VIEW_H
#define VIEW_H

enum class Mouse_click_state {
	MOUSE_MOTION   		  = 1,
	MOUSE_DOWN 			  = 2,
	MOUSE_DOWN_AND_MOTION = 3,
	MOUSE_UP 			  = 4,
};

const size_t MAX_COUNT_OF_VIEW_OBJECTS = 30;

class View_object {
  public:
	Point center;
	Colour color;

	Rectangle* rect;
	int* widget_types;
	Widget_types yourself_type;

	bool is_visible;
	bool is_active;
	bool is_alive;

	View_object(const Widget_types par_widget_types = Widget_types::VIEW_OBJECT) {
		center = Point(0, 0);
		color = {0, 0, 0, 0};

		rect = new Rectangle;

		widget_types = new int[COUNT_OF_TYPES];

		for(size_t i = 0; i < COUNT_OF_TYPES; ++i)
			widget_types[i] = 0;

		yourself_type = par_widget_types;

		is_visible = is_active = is_alive = true;
	}

	View_object(const Point par_center, const double par_width, const double par_height,
			    const Colour par_color, const Widget_types par_widget_types = Widget_types::VIEW_OBJECT) {

		center = par_center;
		color = par_color;

		rect = new Rectangle(par_center, par_width, par_height, par_color, false);

		widget_types = new int[COUNT_OF_TYPES];

		for(size_t i = 0; i < COUNT_OF_TYPES; ++i)
			widget_types[i] = 0;

		yourself_type = par_widget_types;

		is_visible = is_active = is_alive = true;
	}

	~View_object() {
		printf("~View_object\n");
		
		// delete rect;
		// delete[] widget_types;
	}

	virtual void draw(SDL_Renderer** render, SDL_Texture** texture) {
		if(is_visible)
			rect->draw(*render);
	}

	virtual bool check_click(const double mouse_x, const double mouse_y, const Mouse_click_state* par_mouse_status) {
		if(is_active)
			return true;
		return false;
	}

	size_t get_yourself_type() const {
		return (size_t)yourself_type;
	}

	void delete_all() {
		printf("begin View_object delete_all\n");

		delete rect;
		delete[] widget_types;

		is_visible = is_active = false;
		is_alive = false;

		printf("end VIEW_OBJECT delete_all\n");
	}
};

#endif