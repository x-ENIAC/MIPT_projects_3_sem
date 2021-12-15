#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <ctime>

#include "GUI/animation_manager.h"
#include "Editor/view_manager.h"
#include "Utils/my_vector.h"
#include "Plugins/plugin_manager.h"

#ifndef APP_H
#define APP_H

#define PATTERN_SINGLETON

extern const double TIME_DELTA;

enum SDL_STATUSES {
	SDL_OKEY		   = 0,
	BAD_SDL_INIT       = 1,
	BAD_TTF_INIT       = 2,
	WINDOW_NOT_CREATE  = 3,
	SURFACE_NOT_CREATE = 4,
	RENDER_NOT_CREATE  = 5,
	PICTURE_NOT_INIT   = 6,
	TEXTURE_NOT_CREATE = 7,
};

class View_manager;

class App {
  private:
	static App* app;

	PAppInterface* app_interface;

	SDL_Window* window;
	SDL_Renderer* render;
	SDL_Texture* texture;
	SDL_Surface* screen;
	TTF_Font* font;

	int width_screen, height_screen;
	long long begin_era;

	View_manager* view_manager;

	Colour screen_color;

	App() {
		window = NULL;
		render = NULL;
		texture = NULL;
		screen = NULL;

		screen_color = BLACK;

		width_screen  = 920;
		height_screen = 720;
	}

	~App() {}

  public:

	void initialize(const int width_screen, const int height_screen);

	void deinitialize();

	void update();

	Canvas* get_active_canvas();

	void fill_app_interface();

	SDL_Renderer* get_render();

	static App* get_app();

	Painter_tools_and_plugins* get_painter_tools_and_plugins();

	long long get_begin_era();

	long long get_width_screen();

	long long get_height_screen();

	View_manager* get_view_manager();

	PAppInterface* get_app_interface();
};

#endif