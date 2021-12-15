#include "plugin.h"

#ifndef PLUGIN_MANAGER_H
#define PLUGIN_MANAGER_H

const int MAX_COUNT_OF_PLUGINS = 5;

class Plugin_manager : public View_object {
  public:

  	Plugin** plugins;
  	int count_of_plugins;

  	Plugin* active_plugin;

  	Plugin_manager() : View_object() {
  		plugins = new Plugin*[MAX_COUNT_OF_PLUGINS];
  		for(int i = 0; i < MAX_COUNT_OF_PLUGINS; ++i)
  			plugins[i] = new Plugin;

  		// printf("create Plugin_manager %p\n", plugins);

  		active_plugin = new Plugin;

  		count_of_plugins = 0;
  	}

  	~Plugin_manager() {
  		delete[] plugins;
  	}

  	void add_plugin(Plugin* new_plugin) {
  		printf("add plugin! type %d\n", (int)(new_plugin->plugin_type));
  		plugins[count_of_plugins] = new_plugin;
  		++count_of_plugins;
  	}

	void draw(SDL_Renderer** render, SDL_Texture** texture, SDL_Surface** screen) override {
		rect->draw(*render);

		for(size_t i = 0; i < count_of_plugins; ++i) {
			plugins[i]->draw(render, texture, screen);
		}
	}

	bool check_click(const float mouse_x, const float mouse_y, const Mouse_click_state* par_mouse_status) override {
		printf("begin check plugin manager\n");
		for(size_t i = 0; i < count_of_plugins; ++i) {

			if(plugins[i]->rect->is_point_belongs_to_rectangle( Point(mouse_x, mouse_y) )) {
				if(*par_mouse_status == Mouse_click_state::MOUSE_DOWN) {
					if(plugins[i]->check_click(mouse_x, mouse_y, par_mouse_status)) {

						if(plugins[i]->plugin_type == PPluginType::PPT_TOOL) {
							printf("activate %ld plugin\n", i);
							active_plugin = plugins[i];
							// active_plugin->plugin_interface->tool.on_press({mouse_x, mouse_y});
							return true;
						}
						else
						if(plugins[i]->plugin_type == PPluginType::PPT_EFFECT) {
							printf("apply!!!\n");
							plugins[i]->plugin_interface->effect.apply();
							return true;
						}
					}
				}
			}
		}

		return false;
	}

	int get_count_of_plugins() {
		return count_of_plugins;
	}
};

#endif