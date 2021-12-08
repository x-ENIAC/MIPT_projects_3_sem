#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "tool.h"
#include "plugin_tool.h"

#ifndef TOOL_MANAGER_H
#define TOOL_MANAGER_H

#define PATTERN_SINGLETON

class Tool_manager : public View_object {
  private:

  	static Tool_manager* tool_manager;
  	
  	Tool** tools;
  	size_t count_of_tools;

  	Tool* active_tool;

	Colour pen_colour;
	float pen_size;

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

							// if(active_tool->get_yourself_type() == Widget_types::TOOL)
							// 	active_tool->apply();

							// else if(active_tool->get_yourself_type() == Widget_types::PLUGIN_TOOL)
							// 	((Plugin_tool*)(active_tool))->plugin_interface->tool.on_press({mouse_x, mouse_y});

							return true;
						}
					}

					return true;
				}
			}
		}

		return false;
	}

	bool on_press(const float mouse_x, const float mouse_y, const Mouse_click_state* par_mouse_status) {
		if(*par_mouse_status == Mouse_click_state::MOUSE_DOWN) {

			if(active_tool->get_yourself_type() == Widget_types::TOOL)
				active_tool->on_press(mouse_x, mouse_y);

			else if(active_tool->get_yourself_type() == Widget_types::PLUGIN_TOOL) {
				printf("\\\\\\\\\\\\\\\\\\ PLUGIN press \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ \n");
				((Plugin_tool*)(active_tool))->plugin_interface->tool.on_press({mouse_x, mouse_y});
			}

			return true;
		}

		return false;
	}

	bool on_release(const float mouse_x, const float mouse_y, const Mouse_click_state* par_mouse_status) {
		if(*par_mouse_status == Mouse_click_state::MOUSE_UP) {

			if(active_tool->get_yourself_type() == Widget_types::TOOL)
				active_tool->on_release(mouse_x, mouse_y);

			else if(active_tool->get_yourself_type() == Widget_types::PLUGIN_TOOL) {
				printf("\\\\\\\\\\\\\\\\\\ PLUGIN release \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ \n");
				((Plugin_tool*)(active_tool))->plugin_interface->tool.on_release({mouse_x, mouse_y});
			}

			return true;
		}

		return false;
	}

	bool on_move(Point old_pos, Point new_pos, const Mouse_click_state* par_mouse_status) {
		if(*par_mouse_status == Mouse_click_state::MOUSE_DOWN_AND_MOTION) {

			if(active_tool->get_yourself_type() == Widget_types::TOOL)
				active_tool->on_move(old_pos, new_pos);

			else if(active_tool->get_yourself_type() == Widget_types::PLUGIN_TOOL) {
				printf("\\\\\\\\\\\\\\\\\\ PLUGIN move \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ \n");
				((Plugin_tool*)(active_tool))->plugin_interface->tool.on_move({(float)old_pos.x, (float)old_pos.y}, {(float)new_pos.x, (float)new_pos.y});
			}

			return true;
		}

		return false;
	}

	void add_tool(Tool* new_tool) {
		tools[count_of_tools] = new_tool;
		++count_of_tools;

		++widget_types[(int)new_tool->get_yourself_type()];
	}

	Colour get_pen_colour();

	void set_pen_colour(const Colour new_color);

	Colour* get_ptr_to_pen_colour();

	float get_pen_size();

	void set_pen_size(float new_size);
};

#endif