#include "point.h"
#include "colour.h"

#ifndef VIEW_H
#define VIEW_H

enum View_type {
	NO_TYPE_VIEW_TYPE = 0,
	BUTTON_VIEW_TYPE  = 1,
	TEXT_VIEW_TYPE    = 2,
	CHART_VIEW_TYPE   = 3,
};

class View_object {
  public:
	Point center;
	Colour color;
	View_type type;

	View_object(const View_type par_view_type = NO_TYPE_VIEW_TYPE) {
		center = Point(0, 0);
		color = {0, 0, 0, 0};
		type = par_view_type;
	}	

	View_object(const Point par_center, const Colour par_color, const View_type par_view_type = NO_TYPE_VIEW_TYPE) {
		center = par_center;
		color = par_color;
		type = par_view_type;
	}

	virtual void draw(SDL_Renderer** render, SDL_Texture** texture) {
		printf("view draw\n");
	}

	virtual bool check_click(const double mouse_x, const double mouse_y) {
		printf("check ckick view???\n");
		return true;
	}	
};

#endif