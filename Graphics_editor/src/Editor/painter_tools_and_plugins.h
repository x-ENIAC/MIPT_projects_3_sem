#include "Tools/tool_manager.h"
#include "../Plugins/plugin_manager.h"

#ifndef PAINTER_TOOLS_AND_PLUGINS_H
#define PAINTER_TOOLS_AND_PLUGINS_H

enum Active_instrument {
	NOBODY_ACTIVE		= 0,
	TOOL_ACTIVE 		= 1,
	PLUGIN_TOOL_ACTIVE 	= 2
};

class Painter_tools_and_plugins : public View_object {
  public:
	Plugin_manager* plugin_manager;
	Tool_manager* tool_manager;

	Active_instrument who_is_active; 

	Painter_tools_and_plugins(const Point par_point, const double par_width, const double par_height) :
	  View_object(par_point, par_width, par_height, BLACK) {
		plugin_manager = new Plugin_manager;

		who_is_active = Active_instrument::NOBODY_ACTIVE;
	}

	~Painter_tools_and_plugins() {
		delete plugin_manager;
	}

	void set_plugin_manager(Plugin_manager* new_plugin_manager) {
		plugin_manager = new_plugin_manager;
	}

	void set_tool_manager(Tool_manager* new_tool_manager) {
		tool_manager = new_tool_manager;
	}

	void update_positions() {
		printf("begin update\n");
		
		Point center(rect->get_left_up_corner());
		Point now = center;
		now += Point(30, 30);

		int height = rect->get_height(), tools   = tool_manager->get_count_of_tools(),
										 plugins = plugin_manager->get_count_of_plugins();

		for(size_t i = 0; i < tools; ++i) {
			tool_manager->get_tools()[i]->rect->set_center(now);
			now += Point(0, 60);

			if(now.y > center.y + height) {
				now.x += 60;
				now.y = center.y + 30;
			}
		}

		for(size_t i = 0; i < plugins; ++i) {
			plugin_manager->plugins[i]->rect->set_center(now);
			now += Point(0, 60);

			if(now.y > center.y + height) {
				now.x += 60;
				now.y = center.y + 30;
			}
		}				
	}

	void draw(SDL_Renderer** render, SDL_Texture** texture, SDL_Surface** screen) override {
		rect->draw(*render);

		int tools = tool_manager->get_count_of_tools(), plugins = plugin_manager->get_count_of_plugins();

// 		Point center(rect->get_left_up_corner());
// 		center += Point(30, 30);

		for(size_t i = 0; i < tools; ++i) {
			// tool_manager->get_tools()[i]->rect->set_center(center);
			tool_manager->get_tools()[i]->draw(render, texture, screen);
			// center += Point(0, 60);

			// if(center.y > rect->get_left_up_corner().y + rect->get_height()) {
			// 	center.x += 60;
			// 	center.y = rect->get_left_up_corner().y + 30;
			// }
		}

		for(size_t i = 0; i < plugins; ++i) {
			// plugin_manager->plugins[i]->rect->set_center(center);
			plugin_manager->plugins[i]->draw(render, texture, screen);
			// center += Point(0, 60);

			// if(center.y > rect->get_left_up_corner().y + rect->get_height()) {
			// 	center.x += 60;
			// 	center.y = rect->get_left_up_corner().y + 30;
			// }
		}
	}

	bool check_click(const float mouse_x, const float mouse_y, const Mouse_click_state* par_mouse_status) override {
		printf("check!!!\n");
		if(rect->is_point_belongs_to_rectangle( Point(mouse_x, mouse_y) )) {
			if(*par_mouse_status == Mouse_click_state::MOUSE_DOWN) {

				printf("\tDOWN MOUSE\n");
				if(tool_manager->check_click(mouse_x, mouse_y, par_mouse_status)) {
					who_is_active = Active_instrument::TOOL_ACTIVE;
					printf("tool\n");
					return true;
				}

				// printf("ptr? %p\n", plugin_manager);
				if(plugin_manager->check_click(mouse_x, mouse_y, par_mouse_status)) {
					who_is_active = Active_instrument::PLUGIN_TOOL_ACTIVE;
					printf("plugin\n");
					return true;
				}
			}

			return false;
		}

		return false;
	}

	bool check_motion(Point old_mouse, Point now_mouse, const Mouse_click_state* par_mouse_status) override {
		// printf("HERE???????????????\n");
		return false;
	}

	// bool on_move(Point old_pos, Point new_pos, const Mouse_click_state* par_mouse_status) {
	// 	if(*par_mouse_status == Mouse_click_state::MOUSE_DOWN_AND_MOTION) {

	// 		// if(active_tool->get_yourself_type() == Widget_types::TOOL)
	// 		if(tool_manager->on_move(old_pos, new_pos, par_mouse_status)) {
	// 			printf("tool\n");
	// 			return true;
	// 		}

	// 		if(plugin_manager->check_motion(old_pos, new_pos, par_mouse_status)) {
	// 			printf("plugin\n");
	// 			return true;
	// 		}

	// 		return true;
	// 	}

	// 	return false;
	// }
};

#endif