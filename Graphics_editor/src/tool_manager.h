#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "tool.h"

#ifndef TOOL_MANAGER_H
#define TOOL_MANAGER_H

#define PATTERN_SINGLTONE

class Tool_manager : public View_object {
  private:

  	static Tool_manager* tool_manager;
  	
  	Tool** tools;
  	size_t count_of_tools;

  	Tool* active_tool;

	Colour pen_colour;
	float pen_size;

  protected:

	Tool_manager() : View_object() {
		printf("Start construst the tool manager\n");
	  	tools = new Tool*[MAX_COUNT_OF_VIEW_OBJECTS];
	  	for(int i = 0; i < MAX_COUNT_OF_VIEW_OBJECTS; ++i)
	  		tools[i] = new Tool;
	  	count_of_tools = 0;

	  	active_tool = new Tool;
	}

	~Tool_manager() {}

public:

	void initialize(const Point par_center, const double par_width, const double par_height,
		 const Colour par_color, const Widget_types par_widget_types = Widget_types::VIEW_OBJECT,
		 const char par_path_to_picture[] = NON_PATH_TO_PUCTURE);

	static Tool_manager* get_tool_manager();

	Tool* get_active_tool();

	void draw(SDL_Renderer** render, SDL_Texture** texture, SDL_Surface** screen) override {
		rect->draw(*render);

		for(size_t i = 0; i < count_of_tools; ++i) {
			tools[i]->draw(render, texture, screen);
		}
	}

	bool check_click(const float mouse_x, const float mouse_y, const Mouse_click_state* par_mouse_status) override {

		if(rect->is_point_belongs_to_rectangle(mouse_x, mouse_y)) {
			//printf("!!\n");
			for(size_t i = 0; i < count_of_tools; ++i) {

				// printf("center (%d, %d), width %d, height %d, mouse (%d, %d)\n", (int)tools[i]->rect->get_center().x,
				// 																 (int)tools[i]->rect->get_center().y,
				// 																 (int)tools[i]->rect->get_width(),
				// 																 (int)tools[i]->rect->get_height(),
				// 																 (int)mouse_x, (int)mouse_y);

				if(tools[i]->rect->is_point_belongs_to_rectangle( Point(mouse_x, mouse_y) )) {
					if(*par_mouse_status == Mouse_click_state::MOUSE_DOWN) {
						if(tools[i]->check_click(mouse_x, mouse_y, par_mouse_status)) {
							printf("activate %ld tool\n", i);
							active_tool = tools[i];
							return true;
						}
					}

					return true;
				}
			}
		}

		//printf("return false Button_manager\n");

		return false;
	}

	void add_tool(Tool* new_tool) {
		Point center = rect->get_left_up_corner();
		if(count_of_tools > 0) {
			center = tools[count_of_tools - 1]->rect->get_center();
			center += Point(0, 60);
		} else {
			center += Point(30, 30);
		}

		new_tool->rect->set_center(center);
		tools[count_of_tools] = new_tool;
		++count_of_tools;

		++widget_types[new_tool->get_yourself_type()];
	}

	Colour get_pen_colour();

	void set_pen_colour(const Colour new_color);

	Colour* get_ptr_to_pen_colour();

	float get_pen_size();

	void set_pen_size(float new_size);
};

#endif