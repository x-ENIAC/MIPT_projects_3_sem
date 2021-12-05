#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "animation_manager.h"
#include "view_manager.h"

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
  public:
  	SDL_Window* window;
  	SDL_Renderer* render;
  	SDL_Texture* texture;
  	SDL_Surface* screen;
  	TTF_Font* font;

  	int width_screen, height_screen;
  	View_manager* view_manager;

  	Colour screen_color;

  	App(const int par_width, const int par_height) {
  		window = NULL;
  		render = NULL;
  		texture = NULL;
  		screen = NULL;

  		screen_color = BLACK;

  		width_screen  = par_width;
  		height_screen = par_height;
  	}

  	void initialize();

	void deinitialize();

	void update();
};

#endif