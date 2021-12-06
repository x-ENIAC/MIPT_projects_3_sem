#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <ctime>

#include "animation_manager.h"
#include "view_manager.h"
#include "my_vector.h"

#define PATTERN_SINGLTONE

#ifndef APP_H
#define APP_H

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

extern Animation_manager* anim_manager;

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

	Colour screen_color, pen_colour;
	float pen_size;

  protected:
	App() {
		window = NULL;
		render = NULL;
		texture = NULL;
		screen = NULL;

		screen_color = BLACK;

		width_screen  = 920;
		height_screen = 720;

		pen_size = 10;
	}

	~App() {}

  public:

	void initialize(const int width_screen, const int height_screen);

	void deinitialize();

	void update();

	void fill_app_interface();

	SDL_Renderer* get_render();

	static App* get_app();

	long long get_begin_era();

	Colour get_pen_colour();

	float get_pen_size();

	long long get_width_screen();

	long long get_height_screen();

	View_manager* get_view_manager();
};

#endif