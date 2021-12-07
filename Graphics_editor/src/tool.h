#include "view.h"
#include "point.h"
#include "colour.h"
#include "widget_types.h"

#ifndef TOOL_H
#define TOOL_H

class Tool : public View_object {
  public:
  	
  	Tool() : View_object() {}

	Tool(const Point par_center, const double par_width, const double par_height,
		 const Widget_types par_widget_types = Widget_types::VIEW_OBJECT, const char par_path_to_picture[] = NON_PATH_TO_PUCTURE) :
	  View_object(par_center, par_width, par_height, BLACK, par_widget_types, par_path_to_picture) {}


	void apply() {

	}

	bool check_click(const float mouse_x, const float mouse_y, const Mouse_click_state* par_mouse_status) override {
		printf("check click tool\n");
		return false;
	}

	//bool check_click(const float mouse_x, const float mouse_y, const Mouse_click_state* par_mouse_status) override {}

	/*void draw(SDL_Renderer** render, SDL_Texture** texture, SDL_Surface** screen) override {
		
	}*/


};

#endif