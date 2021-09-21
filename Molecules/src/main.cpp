#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "molecule.h"
#include "molecule_manager.h"

const int SCREEN_WIDTH  = 920;
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

SDL_STATUSES initialize(SDL_Window* &window, SDL_Renderer* &render) {
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1) {
    	printf("Could not initialize SDL: %s.\n", SDL_GetError());
    	return BAD_SDL_INIT;
  	}

  	window = SDL_CreateWindow("Textures", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
    			                          SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  	if(!window)
    	return WINDOW_NOT_CREATE;

  	render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!render)                                           
        return RENDER_NOT_CREATE;
    
	return SDL_OKEY;
}

void quit(SDL_Window* &window, SDL_Renderer* &render) {
  	SDL_DestroyWindow(window);
  	SDL_DestroyRenderer(render);

  	window = NULL;
  	render = NULL;

  	SDL_Quit();
	IMG_Quit();
}

int main() {
	srand(time(NULL));
    SDL_Window*   window     = NULL;
    SDL_Renderer* render     = NULL;

    SDL_STATUSES sdl_status = initialize(window, render);
    CHECK_SDL_STATUS

    SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
    SDL_RenderClear(render);

	Molecule_manager molecule_manager = {};
	for(int i = 0; i < 500; ++i) {
		molecule_manager.add_object(CIRCLE, Point(rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT, Colour(255 - 5 * i, rand() % 256, rand() % 256, 255)), 
											5, 5, rand() % 100, rand() % 100);
	}

	molecule_manager.add_object(CIRCLE, Point(rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT, Colour(255 - rand() % 256, rand() % 256, rand() % 256, 255)), 
										70, 5000, 0, 0);	

	int count = 0;

	SDL_Event event = {};
	bool is_run = true;
	while(is_run) {
		while(SDL_PollEvent(&event)) {
			if(event.type == SDL_QUIT) {
				is_run = false;
			}
		}

		molecule_manager.update_molecule();
		molecule_manager.collision_detection(SCREEN_WIDTH, SCREEN_HEIGHT);
    	SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
    	SDL_RenderClear(render);

		for(size_t i = 0; i < molecule_manager.count_objects; ++i) {
			molecule_manager.molecule[i].draw_molecule(render);
		}

		SDL_RenderPresent(render);
	}	



	SDL_RenderPresent(render);
	quit(window, render);

	return sdl_status;
}