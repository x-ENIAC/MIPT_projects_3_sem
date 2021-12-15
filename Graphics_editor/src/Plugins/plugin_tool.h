#include "plugin.h"

#ifndef PLUGIN_TOOL_H
#define PLUGIN_TOOL_H

const char WAY_TO_LOOCHEK_BRUSH[] = "src/Plugins/loochek_brush.so";
const char WAY_TO_KCTF_SHARPY[] = "src/Plugins/kctf_sharpy.so";

class Plugin_tool: public Plugin {
  public:

	Plugin_tool(const char* file_name, const PAppInterface* app_interface) :
	  Plugin(file_name, app_interface, Widget_types::PLUGIN_TOOL) {
		// yourself_type = Widget_types::PLUGIN_TOOL;
		plugin_type = PPluginType::PPT_TOOL;
	}

	~Plugin_tool() {}

	void draw(SDL_Renderer** render, SDL_Texture** texture, SDL_Surface** screen) {
		if(this->texture->is_using_texture) {
			SDL_Rect rect_;
			rect_.w = rect->get_width();
			rect_.h = rect->get_height();
			// printf("%d %d\n", rect_.w, rect_.h);
			rect_.x = rect->get_center().x - rect_.w / 2.0;
			rect_.y = rect->get_center().y - rect_.h / 2.0;

			this->texture->draw_texture(&rect_);
		} else {
			printf("plugin tool don't have texture\n");
		}
	}

	bool check_click(const float mouse_x, const float mouse_y, const Mouse_click_state* par_mouse_status) {
		printf("check click plugin tool\n");
		//plugin_interface->tool.on_press({mouse_x, mouse_y});
		return true;
	}
};

#endif