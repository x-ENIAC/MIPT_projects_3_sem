#include <SDL2/SDL.h>
#include "../Utils/point.h"
#include "../Utils/colour.h"
#include "../Utils/rectangle.h"
#include "../GUI/view.h"
#include "../GUI/button_delegates.h"
#include "Tools/tool_manager.h"
	
#ifndef CANVAS_H
#define CANVAS_H

class Canvas;

#include "painter_tools_and_plugins.h"
// #include "../app.h"

struct Cell {
	Colour begin_color;
	Colour color_after_correction;
	size_t thickness;

	Cell() {
		begin_color = color_after_correction = WHITE;
		thickness = 0;
	}

	Cell(const Colour par_color, const size_t par_thickness) {
		begin_color = color_after_correction = par_color;
		thickness = par_thickness;
	}

	Colour get_color() {
		return color_after_correction;
	}

	void set_color(const Colour new_color) {
		begin_color = color_after_correction = new_color;
	}
};

class Canvas : public View_object {
  public:
	//Rectangle* object_rect;
	//Button_owner owner;

	//View_object** view_objects;
	//size_t count_of_views;
	// Pencil* pencil;

	// Tool* active_tool;

	Painter_tools_and_plugins* painter_tools_and_plugins;
	Cell** cells_color;

	Canvas() : View_object() {}

	Canvas(const Point par_point, const double par_width, const double par_height, const Colour par_button_color,
			Painter_tools_and_plugins* par_painter_tools_and_plugins /*const Button_owner par_owner, */) :
	  View_object(par_point, par_width, par_height, par_button_color, Widget_types::CANVAS) {

		cells_color = new Cell*[(int)par_width + 1];

		for(size_t i = 0; i <= par_width; ++i)
			cells_color[i] = new Cell[(int)par_height + 1];

		for(size_t i = 0; i <= par_width; ++i)
			for(size_t j = 0; j <= par_height; ++j) {
				cells_color[i][j].begin_color = cells_color[i][j].color_after_correction = par_button_color;
				cells_color[i][j].thickness = 24;
			}

		printf("CANVAAS !! %d !! %d\n", (int)par_width, (int)par_height);

		painter_tools_and_plugins = par_painter_tools_and_plugins;

		// load_picture();
	}

	void load_picture() {

		printf("???????????\n");
		SDL_Surface* m_surface = IMG_Load("textures/sun1.png");

	 	// void *target_pixel = ((Uint8*)surface->pixels + y * surface->pitch + x * surface->format->BytesPerPixel);

		// void* mPixels;
		// int mPitch;

		// SDL_Texture* ntexture = IMG_LoadTexture(render, "textures/sun1.png");
		// SDL_LockTexture( ntexture, NULL, &mPixels, &mPitch );
		printf("here\n");

		// printf("!!! inage %d, %d\n", ntexture->w, ntexture->h);
		for(int y = 0; y < rect->get_height(); ++y)
			for(int x = 0; x < rect->get_width(); ++x) {
				printf("!!!!\n");
				Uint32 pixel = *((Uint32*) m_surface->pixels + (m_surface->h - y) * m_surface->w + x);
				printf("@@@\n");
			    Uint8 r, g, b, a;
			    printf(".......\n");
			    SDL_GetRGBA(pixel, m_surface->format, &r, &g, &b, &a);
				printf("i = %d, j = %d\n", x, y);
				// cells_color[i][j].begin_color =
				// cells_color[i][j].color_after_correction = *((Colour*)mPixels);
				// cells_color[i][j].begin_color.print();
				// ++mPixels;
			}

		// SDL_UnlockTexture(ntexture);
	}

	~Canvas() {
		int width = rect->get_width();

		for(int i = 0; i < width; ++i)
			free(cells_color[i]);
		free(cells_color);
	}


	bool check_click(const float mouse_x, const float mouse_y, const Mouse_click_state* par_mouse_status) override {
		if(is_active) {
			if(rect->is_point_belongs_to_rectangle( Point(mouse_x, mouse_y) )) {
				if(*par_mouse_status == Mouse_click_state::MOUSE_DOWN) {

					// printf("\tDOWN MOUSE\n");
					if(painter_tools_and_plugins->who_is_active == Active_instrument::TOOL_ACTIVE)
						Tool_manager::get_tool_manager()->on_press(mouse_x, mouse_y, par_mouse_status);
					else
					if(painter_tools_and_plugins->who_is_active == Active_instrument::PLUGIN_TOOL_ACTIVE)
						painter_tools_and_plugins->plugin_manager->active_plugin->on_press(mouse_x, mouse_y);
					
				} else if(*par_mouse_status == Mouse_click_state::MOUSE_UP) {
					// printf("\tMOUSE UP\n");
					// Tool_manager::get_tool_manager()->on_release(mouse_x, mouse_y, par_mouse_status);

					if(painter_tools_and_plugins->who_is_active == Active_instrument::TOOL_ACTIVE)
						Tool_manager::get_tool_manager()->on_release(mouse_x, mouse_y, par_mouse_status);
					else
					if(painter_tools_and_plugins->who_is_active == Active_instrument::PLUGIN_TOOL_ACTIVE)
						painter_tools_and_plugins->plugin_manager->active_plugin->on_release(mouse_x, mouse_y);
				}

				return true;
			}
		}

		return false;
	}

	bool check_motion(Point old_mouse, Point now_mouse, const Mouse_click_state* par_mouse_status) override {
		if(is_active) {
			// printf("MOTIOOOOOOOOOOOOOOOOOOOOOOON\n");
			// Tool_manager::get_tool_manager()->on_move(old_mouse, now_mouse, par_mouse_status);
			if(*par_mouse_status == Mouse_click_state::MOUSE_DOWN_AND_MOTION) {
				if(painter_tools_and_plugins->who_is_active == Active_instrument::TOOL_ACTIVE)
					Tool_manager::get_tool_manager()->on_move(old_mouse, now_mouse, par_mouse_status);
				else
				if(painter_tools_and_plugins->who_is_active == Active_instrument::PLUGIN_TOOL_ACTIVE) {
					painter_tools_and_plugins->plugin_manager->active_plugin->on_move(old_mouse, now_mouse);
				}
				else
					return false;

				return true;
			}
		}

		return false;
	}    

	void draw(SDL_Renderer** render, SDL_Texture** texture, SDL_Surface** screen) override {
		if(is_visible) {
			rect->draw(*render);

			Point left_up_corner(rect->get_center().x - rect->width / 2, rect->get_center().y - rect->height / 2);

			for(size_t i = 0; i <= rect->width; ++i)
				for(size_t j = 0; j <= rect->height; ++j) {
					Colour now_color = cells_color[i][j].color_after_correction, old_color = cells_color[i][j].begin_color;
					Point new_point(i + left_up_corner.x, j + left_up_corner.y, now_color);

					if(old_color != color) {
						Rectangle new_rect(new_point, cells_color[i][j].thickness / 2.0, cells_color[i][j].thickness / 2.0, now_color, false);
						new_rect.draw(*render);
					} else
						new_point.draw_point(*render);
				}
		}
	}

	void delete_all() {
		double width  = rect->get_width();
		double height = rect->get_height();

		for(size_t i = 0; i < width; ++i)
			delete[] cells_color[i];
		delete[] cells_color;
	}

	void update_position_from_delta(const Point delta) {
		rect->set_center( rect->get_center() - delta );
	}


	/*inline Button_owner get_owner() const {
		return owner;
	}*/

	//inline void set_owner(const Button_owner new_owner) {
	//  owner = new_owner;
	//}

	//void tick(const double delta_time) override {}
};

#endif


