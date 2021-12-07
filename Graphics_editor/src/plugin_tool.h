#include <dlfcn.h>
#include "plugin_interface.h"

#ifndef PLUGIN_TOOL_H
#define PLUGIN_TOOL_H

const char WAY_TO_LOOCHEK_BRUSH[] = "src/loochek_brush.so";

class Plugin_tool: public Tool {
  public:

  	//PAppInterface* app_interface;
  	void* library;
  	PPluginInterface* plugin_interface;

	Plugin_tool(const char* file_name, const PAppInterface* app_interface) :
	  Tool(Point(0, 0), 50, 50) {

		library = dlopen(file_name, RTLD_NOW);
		if(library == NULL) {
			printf("error dlopen\n");
			return;
		}

		PPluginInterface* (*get_plugin_interface)() = (PPluginInterface* (*)())dlsym(library, PGET_INTERFACE_FUNC);
		if(!get_plugin_interface) {
			printf("error dlsym\n");
			return;
		}

		plugin_interface = get_plugin_interface();

		PPluginStatus status = plugin_interface->general.init(app_interface);
		if(status != PPS_OK) {
			printf("error init\n");
			return;
		}
	}

	void draw(SDL_Renderer** render, SDL_Texture** texture, SDL_Surface** screen) {
		if(this->texture->is_using_texture) {
			SDL_Rect rect_;
			rect_.w = rect->get_width();
			rect_.h = rect->get_height();			
			rect_.x = rect->get_center().x - rect_.w / 2.0;
			rect_.y = rect->get_center().y - rect_.h / 2.0;

			this->texture->draw_texture(&rect_);
		} else {
			printf("plugin tool don't have texture\n");
		}
	}

	bool check_click(const float mouse_x, const float mouse_y, const Mouse_click_state* par_mouse_status) override {
		printf("check click plugin tool\n");
		plugin_interface->tool.on_press({mouse_x, mouse_y});
		return true;
	}
};

#endif