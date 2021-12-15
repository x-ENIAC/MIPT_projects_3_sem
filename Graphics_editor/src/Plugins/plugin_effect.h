#include "plugin.h"

#ifndef PLUGIN_EFFECT_H
#define PLUGIN_EFFECT_H

const char WAY_TO_KCTF_NEGATIVE[] = "src/Plugins/kctf_negative_effect.so";

class Plugin_effect : public Plugin {
  public:

	Plugin_effect(const char* file_name, const PAppInterface* app_interface) :
	  Plugin(file_name, app_interface, Widget_types::PLUGIN_EFFECT) {
		// yourself_type = Widget_types::PLUGIN_EFFECT;
		plugin_type = PPluginType::PPT_EFFECT;
	}

	~Plugin_effect() {}

	void draw(SDL_Renderer** render, SDL_Texture** texture, SDL_Surface** screen) {
		if(this->texture->is_using_texture) {
			SDL_Rect rect_;
			rect_.w = rect->get_width();
			rect_.h = rect->get_height();			
			rect_.x = rect->get_center().x - rect_.w / 2.0;
			rect_.y = rect->get_center().y - rect_.h / 2.0;

			this->texture->draw_texture(&rect_);
		} else {
			printf("plugin effect don't have texture\n");
		}
	}

	bool check_click(const float mouse_x, const float mouse_y, const Mouse_click_state* par_mouse_status) {
		printf("check click plugin effect\n");
		//plugin_interface->tool.on_press({mouse_x, mouse_y});
		return true;
	}
};

#endif