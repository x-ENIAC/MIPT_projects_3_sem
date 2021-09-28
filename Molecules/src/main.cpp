#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "molecule.h"
#include "shape_manager.h"
#include "rectangle.h"

const int SCREEN_WIDTH  = 920;
const int SCREEN_HEIGHT = 720; 

extern Collision_detection_table collision_detected_table(3);
extern Collision_response_table collision_responsed_table(3);

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

SDL_STATUSES initialize(SDL_Window* &window, SDL_Renderer* &render) {
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    	printf("Could not initialize SDL: %s.\n", SDL_GetError());
    	return BAD_SDL_INIT;
  	}

  	window = SDL_CreateWindow("Molecules", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
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
}

int main() {
	srand(time(NULL));
    SDL_Window*   window = NULL;
    SDL_Renderer* render = NULL;

    SDL_STATUSES sdl_status = initialize(window, render);
    CHECK_SDL_STATUS

    SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
    SDL_RenderClear(render);

	Shape_manager shape_manager = {};

	Molecule m1( Point(50, 50), 50, 6, rand() % 10, rand() % 10, Colour(255, 0, 0, 255), CIRCLE, true );
	//Molecule m1( Point(50, 50), 50, 6, 8, 3, Colour(255, 0, 0, 255), CIRCLE, true );
	shape_manager.add_object(&m1);

	Molecule m2( Point(70, 370), 60, 6, rand() % 50, -(rand() % 50), Colour(0, 255, 0, 255), CIRCLE, true );
	//Molecule m2( Point(70, 370), 60, 6, 21, -2, Colour(0, 255, 0, 255), CIRCLE, true );
	shape_manager.add_object(&m2);

	Molecule m3( Point(570, 70), 60, 6, rand() % 50, -(rand() % 50), Colour(0, 255, 0, 255), CIRCLE, true );
	//Molecule m3( Point(570, 70), 60, 16, 42, -36, Colour(0, 255, 0, 255), CIRCLE, true );
	//shape_manager.add_object(&m3);

	Rectangle r1( Point(170, 170), 3, rand() % 10 + 5, rand() % 10 + 5, Colour(0, 0, 255, 255), 40.0, 100.0, RECTANGLE, true );
	//Rectangle r1( Point(170, 170), 3,  5, 10, Colour(0, 0, 255, 255), 40.0, 100.0, RECTANGLE, true );
	shape_manager.add_object(&r1);

	Rectangle r2( Point(570, 470), 3, rand() % 10 + 5, rand() % 10 + 5, Colour(0, 0, 255, 255), 40.0, 100.0, RECTANGLE, true );
	//Rectangle r2( Point(570, 470), 3, 6, 13, Colour(0, 0, 255, 255), 40.0, 100.0, RECTANGLE, true );
	shape_manager.add_object(&r2);

	size_t old_count_objects = shape_manager.count_objects;
	size_t old_count_non_active_objects = shape_manager.count_non_active_objects;

	SDL_Event event = {};
	bool is_run = true;
	while(is_run) {
		while(SDL_PollEvent(&event)) {
			if(event.type == SDL_QUIT) {
				is_run = false;
			}
		}

		shape_manager.update_molecule();
		shape_manager.collision_detection(SCREEN_WIDTH, SCREEN_HEIGHT);

    	SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
    	SDL_RenderClear(render);

    	//printf("\tbegin draw\n");
		for(size_t i = 0; i < shape_manager.count_objects; ++i) {
			//printf("\t\ti = %ld (from %ld), %p, type %d\n", i, shape_manager.count_objects, shape_manager.shapes[i], shape_manager.shapes[i]->get_type());
			//if(shape_manager.shapes[i]->get_is_active())
				shape_manager.shapes[i]->draw_molecule(render);
		}
		//printf("\tend draw\n");

		SDL_RenderPresent(render);

		/*if(!(old_count_objects == shape_manager.count_objects && old_count_non_active_objects == shape_manager.count_non_active_objects)) {
				log_file = fopen("logs.txt", "a");
				fprintf(log_file, "count_objects %ld, non exist %ld\n", shape_manager.count_objects, shape_manager.count_non_active_objects);
				fprintf(log_file, "-------- types -------------\n");
				for(size_t i = 0; i < shape_manager.count_objects; ++i) {
					//if(shape_manager)
					fprintf(log_file, "%d ", shape_manager.shapes[i]->get_type());
				}		
				fprintf(log_file, "\n----------------------------\n");
				
				fprintf(log_file, "------ is active -----------\n");
				for(size_t i = 0; i < shape_manager.count_objects; ++i) {
					//if(shape_manager)
					fprintf(log_file, "%d ", shape_manager.shapes[i]->get_is_active());
				}		
				fprintf(log_file, "\n----------------------------\n\n");
				fclose(log_file);
		}*/

		old_count_objects = shape_manager.count_objects;
		old_count_non_active_objects = shape_manager.count_non_active_objects;
	}	

	printf("end of cycle\n");

	SDL_RenderPresent(render);
	printf("before quit\n");
	quit(window, render);

	printf("end main\n");
	//fclose(log_file);

	return sdl_status;
}