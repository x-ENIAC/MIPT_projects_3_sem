#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "my_vector.h"
#include "colour.h"
#include "pixels.h"
#include "screen_info.h"
#include "sphere.h"

const int SCREEN_WIDTH = 920;
const int SCREEN_HEIGHT = 720; 

enum SDL_STATUSES {
	SDL_OKEY		   = 0,
	BAD_SDL_INIT       = 1,
	WINDOW_NOT_CREATE  = 2,
	SURFACE_NOT_CREATE = 3,
	RENDER_NOT_CREATE  = 4,
	PICTURE_NOT_INIT   = 5,
	TEXTURE_NOT_CREATE = 6,
};

#define CHECK_SDL_STATUS                        							\
 	if(sdl_status != SDL_OKEY) {                							\
    	printf("here will be text of the error...\n");                 		\
    	return sdl_status;                  								\
  	}

SDL_STATUSES initialize(SDL_Window** window, SDL_Renderer** render) {
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1) {
    	printf("Could not initialize SDL: %s.\n", SDL_GetError());
    	return BAD_SDL_INIT;
  	}

  	*window = SDL_CreateWindow("Textures", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
    			                          SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  	if(!window || !(*window))
    	return WINDOW_NOT_CREATE;

  	*render = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if(!render || !(*render))                                           
        return RENDER_NOT_CREATE;
    
	return SDL_OKEY;
}

void quit(SDL_Window** window, SDL_Renderer** render) {
  	SDL_DestroyWindow(*window);
  	SDL_DestroyRenderer(*render);

  	*window = NULL;
  	*render = NULL;

  	SDL_Quit();
	IMG_Quit();
}

void update_light(Point* light, double* angle_light, const double delta) {
    *angle_light += delta;

    light->x = 900 * sin(*angle_light * M_PI / 180.0);
    light->z = 500 * cos(*angle_light * M_PI / 180.0);

    while(*angle_light >= 360)
    	*angle_light -= 360;
}

int main() {
    SDL_Window*   window     = NULL;
    SDL_Renderer* render     = NULL;

    SDL_STATUSES sdl_status = initialize(&window, &render);
    CHECK_SDL_STATUS

    SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
    SDL_RenderClear(render);

    Screen_info screen_info(920, 720);

    const Point center(SCREEN_WIDTH / 2, SCREEN_HEIGHT * 2 / 3, 0), camera(900, -100, 500);
    Point light(700, 0, 300);
    const Colour light_color(255, 255, 255, 255);

    double angle_light = 0;
    
    Sphere sphere(center, {200, 0, 0, 255}, 200.0);

    SDL_Event event = {};
	bool is_run = true;
	while(is_run) {
		while(SDL_PollEvent(&event)) {
			if(event.type == SDL_QUIT) {
				is_run = false;
			}
		}

		sphere.calculate_intensity(center, light, camera, light_color, &screen_info);
		SDL_RenderPresent(render);
		screen_info.draw_screen(render);

		update_light(&light, &angle_light, 10);
	}   

	screen_info.draw_screen(render);   

    quit(&window, &render);

    return sdl_status;
}

// otl 10