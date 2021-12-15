#include <dlfcn.h>
#include "plugin_interface.h"

#ifndef PLUGIN_H
#define PLUGIN_H

class Plugin : public View_object {
  public:
	void* library;
	PPluginInterface* plugin_interface;

	int plugin_type;

	Plugin() : View_object() {

		rect->set_width(50);
		rect->set_height(50);

		library = NULL;
		plugin_interface = NULL;
		plugin_type = -1;
	}

	Plugin(const char* file_name, const PAppInterface* app_interface, Widget_types par_yourself_type) : View_object() {
		yourself_type = par_yourself_type;
		rect->set_width(50);
		rect->set_height(50);

		printf("begin load plugin\n");

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

		printf("end load plugin\n");
	}

	~Plugin() {
		plugin_interface->general.deinit();
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

	bool on_press(const float mouse_x, const float mouse_y) {
		plugin_interface->tool.on_press({mouse_x, mouse_y});
		return true;
	}

	bool on_release(const float mouse_x, const float mouse_y) {
		plugin_interface->tool.on_release({mouse_x, mouse_y});
		return true;
	}

	bool on_move(const Point old_pos, const Point new_pos) {
		plugin_interface->tool.on_move({(float)old_pos.x, (float)old_pos.y}, {(float)new_pos.x, (float)new_pos.y});
		return true;
	}
};

#endif