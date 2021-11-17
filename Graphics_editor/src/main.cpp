#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "view_manager.h"
#include "animation_manager.h"

#include "button.h"

#include "button_delegate.h"
#include "text.h"
#include "chart.h"


SDL_Renderer* render;

extern Animation_manager* anim_manager = Animation_manager::initialize();

const int SCREEN_WIDTH  = 920;
const int SCREEN_HEIGHT = 720;
const double DELTA = 0.5;
extern const double TIME_DELTA = 0.005;

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

#define CHECK_SDL_STATUS                        							\
	if(sdl_status != SDL_OKEY) {                							\
		printf("here will be text of the error...\n");                 		\
		return sdl_status;                  								\
	}

SDL_STATUSES initialize(SDL_Window** window, SDL_Renderer** render, SDL_Texture** texture, SDL_Surface** screen, TTF_Font** font) {
	if(SDL_Init(SDL_INIT_EVERYTHING | SDL_INIT_TIMER | SDL_INIT_VIDEO) != 0) {
		printf("Could not initialize SDL: %s.\n", SDL_GetError());
		return BAD_SDL_INIT;
	}
	
	SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, window, render);


	if(!(*window))
		return WINDOW_NOT_CREATE;
	char* name_font = "courier.ttf";

	TTF_Init();

	*screen = SDL_GetWindowSurface(*window);
	
	return SDL_OKEY;
}

void quit(SDL_Window** window, SDL_Renderer** render, SDL_Texture** texture, SDL_Surface** screen) {
	SDL_FreeSurface    (*screen);
	SDL_DestroyWindow  (*window);
	SDL_DestroyRenderer(*render);
	SDL_DestroyTexture (*texture);

	TTF_Quit();
	SDL_Quit();
}

int main() {

	srand(time(NULL));
	SDL_Window*   window = NULL;
	render = NULL;
	SDL_Texture* texture = NULL;
	TTF_Font*       font = NULL;
	SDL_Surface* screen  = NULL;

	//printf("%d, %d, %d, %d\n", SDL_MOUSEWHEEL, SDL_MOUSEBUTTONUP, SDL_MOUSEBUTTONDOWN, SDL_MOUSEMOTION);
	//printf("%d, %d\n", SDL_WINDOWEVENT, SDL_SYSWMEVENT);
	//printf("%d %d %d %d %d\n", SDL_KEYDOWN, SDL_KEYUP, SDL_TEXTEDITING, SDL_TEXTINPUT, SDL_KEYMAPCHANGED);

	SDL_STATUSES sdl_status = initialize(&window, &render, &texture, &screen, &font);
	CHECK_SDL_STATUS

	Colour screen_color = BLACK;
	
	SDL_SetRenderDrawColor(render, screen_color.red, screen_color.green, screen_color.blue, screen_color.alpha);
	SDL_RenderClear(render);

	//anim_manager = Animation_manager::initialize();

	View_manager view_manager(Point(SCREEN_WIDTH / 2.0, SCREEN_HEIGHT / 2.0), SCREEN_WIDTH, SCREEN_HEIGHT, screen_color/*, &animation_manager*/);

	//View_object tmp(Point(300, 300), 100, 100, BLACK);
	//animation_manager.add_animation(render, "textures/grey_1_close.bmp", "textures/grey_2_close.bmp", TIME_DELTA * 10, &tmp);
	Point tmp(600, 620);

	SDL_Event event = {};
	bool is_run = true;
	while(is_run) {
		while(SDL_PollEvent(&event)) {
			if(event.type == SDL_QUIT)
				is_run = false;

			else {
				view_manager.check_events(&event);
			}
		}

		SDL_SetRenderDrawColor(render, screen_color.red, screen_color.green, screen_color.blue, screen_color.alpha);
		SDL_RenderClear(render);


		view_manager.draw(&render, &texture, &screen);

		view_manager.tick(TIME_DELTA);
		anim_manager->tick(TIME_DELTA);

		//tmp.draw(&render, &texture, &screen);
		//tmp.draw_big_point(render, 2);

		SDL_RenderPresent(render);
	}

	quit(&window, &render, &texture, &screen);

	return 0;
}