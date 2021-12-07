#include "colour.h"
#include "tool.h"

#ifndef PENCIL_H
#define PENCIL_H

#include "app.h"
class Pencil : public Tool {
  public:
	Colour* color;
	size_t thickness;

  public:

	Pencil() : Tool() {
		*color = {255, 255, 0, 255};
		thickness = 10;
	}

	Pencil(const Point par_center, const double par_width, const double par_height, Colour* par_color,
		   const Widget_types par_widget_types = Widget_types::VIEW_OBJECT, const char par_path_to_picture[] = NON_PATH_TO_PUCTURE) :
	  Tool(par_center, par_width, par_height, par_widget_types, par_path_to_picture) /*{const Colour par_color, const size_t par_thickness)*/ {
		// color = par_color;
		// thickness = par_thickness;
		color = par_color;
		thickness = 10;	
	}

	void draw(SDL_Renderer** render, SDL_Texture** texture, SDL_Surface** screen) override {
		if(this->texture->is_using_texture) {
			SDL_Rect sdl_rect;

			sdl_rect.w = rect->get_width();
			sdl_rect.h = rect->get_height();
			sdl_rect.x = rect->get_center().x - sdl_rect.w / 2.0;
			sdl_rect.y = rect->get_center().y - sdl_rect.h / 2.0;

			this->texture->draw_texture(&sdl_rect);
		} else {
			printf("pencil doesn't have texture!\n");
		}
	}

	bool check_click(const float mouse_x, const float mouse_y, const Mouse_click_state* par_mouse_status) override {

		if(rect->is_point_belongs_to_rectangle(mouse_x, mouse_y)) {
			// printf("activate pencil\n");
			return true;
		}

		//printf("return false Button_manager\n");

		return false;
	}

	bool on_press(const float mouse_x, const float mouse_y) override {
		printf("press pencil\n");

		Canvas* active_canvas = App::get_app()->get_active_canvas();
		Point left_up_corner(active_canvas->rect->get_center().x - active_canvas->rect->width / 2,
							 active_canvas->rect->get_center().y - active_canvas->rect->height / 2);

		active_canvas->cells_color[(int)(mouse_x - left_up_corner.x)][(int)(mouse_y - left_up_corner.y)].begin_color			= Tool_manager::get_tool_manager()->get_pen_colour();
		active_canvas->cells_color[(int)(mouse_x - left_up_corner.x)][(int)(mouse_y - left_up_corner.y)].color_after_correction	= Tool_manager::get_tool_manager()->get_pen_colour();
		active_canvas->cells_color[(int)(mouse_x - left_up_corner.x)][(int)(mouse_y - left_up_corner.y)].thickness				= Tool_manager::get_tool_manager()->get_pen_size() * 2;



		//Point left_up_corner(rect->get_center().x - rect->width / 2, rect->get_center().y - rect->height / 2);

                    // cells_color[(int)(mouse_x - left_up_corner.x)][(int)(mouse_y - left_up_corner.y)].begin_color            = Tool_manager::get_tool_manager()->get_pen_colour();
                    // cells_color[(int)(mouse_x - left_up_corner.x)][(int)(mouse_y - left_up_corner.y)].color_after_correction = Tool_manager::get_tool_manager()->get_pen_colour();
                    // cells_color[(int)(mouse_x - left_up_corner.x)][(int)(mouse_y - left_up_corner.y)].thickness              = Tool_manager::get_tool_manager()->get_pen_size();
		return true;
	}

	bool on_release(const float mouse_x, const float mouse_y) override {
		// printf("release pencil\n");
		return true;
	}

	bool on_move(const Point old_pos, const Point new_pos) override {
		// printf("move pencil\n");

		int mouse_x = new_pos.x, mouse_y = new_pos.y;

		Canvas* active_canvas = App::get_app()->get_active_canvas();
		Point left_up_corner(active_canvas->rect->get_center().x - active_canvas->rect->width / 2,
							 active_canvas->rect->get_center().y - active_canvas->rect->height / 2);

		active_canvas->cells_color[(int)(mouse_x - left_up_corner.x)][(int)(mouse_y - left_up_corner.y)].begin_color			= Tool_manager::get_tool_manager()->get_pen_colour();
		active_canvas->cells_color[(int)(mouse_x - left_up_corner.x)][(int)(mouse_y - left_up_corner.y)].color_after_correction	= Tool_manager::get_tool_manager()->get_pen_colour();
		active_canvas->cells_color[(int)(mouse_x - left_up_corner.x)][(int)(mouse_y - left_up_corner.y)].thickness				= Tool_manager::get_tool_manager()->get_pen_size() * 2;

		return true;
	}

	inline size_t get_thickness() const {
		return thickness;
	}

	inline Colour get_color() const {
		return *color;
	}

	inline void set_color(const Colour new_color) {
		*color = new_color;
	}

	inline void set_thickness(const size_t new_thickness) {
		thickness = new_thickness;
	}
};

#endif