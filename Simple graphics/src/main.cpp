#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
//#include "main.h"
#include "canvas.h"
#include "my_vector.h"
#include "colour.h"
#include <math.h>

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

int function(int x) {
	return x * x;
}

double function(double x) {
  	return x * x;
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
    SDL_Window*   window     = NULL;
    SDL_Renderer* render     = NULL;

    SDL_STATUSES sdl_status = initialize(window, render);
    CHECK_SDL_STATUS

    Canvas first_canvas ( FIRST_SCREEN_X_UPPER_LEFT_CORNER,
    					  FIRST_SCREEN_Y_UPPER_LEFT_CORNER,
    					  FIRST_SCREEN_WIDTH,
    					  FIRST_SCREEN_HEIGHT,
    					  1.0, 0.01);

	first_canvas.draw_coordinate_axes(render, BLACK);
    first_canvas.draw_parabola(render, BLACK);

    Canvas second_canvas ( SECOND_SCREEN_X_UPPER_LEFT_CORNER,
    					   SECOND_SCREEN_Y_UPPER_LEFT_CORNER,
    					   SECOND_SCREEN_WIDTH,
    					   SECOND_SCREEN_HEIGHT,
    					   1.0, 0.1);

	second_canvas.draw_coordinate_axes(render, BLACK);
    second_canvas.draw_parabola(render, BLACK);

	Vector vector_ (370, SCREEN_HEIGHT - 420, 470, SCREEN_HEIGHT -  320, true);
	vector_.draw_vector(render, RED, RED, ANGLE_OF_ARROW_WINGS, -ANGLE_OF_ARROW_WINGS);

	Vector vector2 = {};
	vector2 = vector_;

	/*vector2.draw_vector(render, GREEN, GREEN, ANGLE_OF_ARROW_WINGS, -ANGLE_OF_ARROW_WINGS);

	vector2.move_vector_to_point(470, SCREEN_HEIGHT - 320);
	vector2.draw_vector(render, GREEN, GREEN, ANGLE_OF_ARROW_WINGS, -ANGLE_OF_ARROW_WINGS);

	vector += vector2;
	vector.draw_vector(render, BLUE, BLUE, ANGLE_OF_ARROW_WINGS, -ANGLE_OF_ARROW_WINGS);*/

	//vector_.get_perpendicular();

	vector_.draw_vector(render, BLUE, BLUE, ANGLE_OF_ARROW_WINGS, -ANGLE_OF_ARROW_WINGS);
	SDL_RenderPresent(render);

	SDL_Event event = {};
	bool is_run = true;
	while(is_run) {
		while(SDL_PollEvent(&event)) {
			if(event.type == SDL_QUIT || 
			   event.type == SDL_KEYDOWN) {
				is_run = false;
			}
		}


		vector_.rotate_clockwize_vector(5.0);
		vector2.rotate_clockwize_vector(5.0);

		SDL_RenderPresent(render);    
	    SDL_Delay(100);

		first_canvas.draw_coordinate_axes(render, BLACK);
	    first_canvas.draw_parabola(render, BLACK);

		second_canvas.draw_coordinate_axes(render, BLACK);
	    second_canvas.draw_parabola(render, BLACK);    	

	    vector_.draw_vector(render, RED, RED, ANGLE_OF_ARROW_WINGS, -ANGLE_OF_ARROW_WINGS);
	    vector2.draw_vector(render, GREEN, GREEN, ANGLE_OF_ARROW_WINGS, -ANGLE_OF_ARROW_WINGS);
	}

    SDL_RenderPresent(render); 
    //SDL_Delay(5000); 

    quit(window, render);

  	return sdl_status;
}