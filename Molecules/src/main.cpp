#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "shape_manager.h"
#include "molecule.h"
#include "rectangle.h"

#include "button_manager.h"
#include "rectangle_button.h"
#include "circle_button.h"

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

void draw_line(SDL_Renderer* &render, const Point begin, const int y) {
	double x_begin = begin.x, x_end = begin.y;

	for(size_t x = x_begin; x <= x_end; ++x) {
		Point now_point ( x, y, BLACK );
		now_point.draw_point(render);
	}
}

void draw_line(SDL_Renderer* &render, const int x, const Point end) {
	double y_begin = end.x, y_end = end.y;

	for(size_t y = y_begin; y <= y_end; ++y) {
		Point now_point ( x, y, BLACK );
		now_point.draw_point(render);
	}
}

int main() {
	srand(time(NULL));
    SDL_Window*   window = NULL;
    SDL_Renderer* render = NULL;

    SDL_STATUSES sdl_status = initialize(window, render);
    CHECK_SDL_STATUS

    SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
    SDL_RenderClear(render);

    Rectangle screen_rect( Point(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), 0, 0, 0, Colour(0, 0, 0, 0), SCREEN_WIDTH - 100, SCREEN_HEIGHT - 100.0, RECTANGLE, true );

	Shape_manager  shape_manager  = {};
	Button_manager button_manager = {};

	Molecule m2( Point(70, 370), 20, 1, 7, -5, Colour(0, rand() % 255, rand() % 255, 255), CIRCLE, true );
	shape_manager.add_object(&m2);

	Molecule m3( Point(570, 70), 20, 1, -10, 5, Colour(0, 255, 0, 255), CIRCLE, true );
	shape_manager.add_object(&m3);

	Rectangle r1( Point(170, 170), 1, 0, 0, Colour(0, 0, 255, 255), 30.0, 30.0, RECTANGLE, true );
	shape_manager.add_object(&r1);

	Rectangle r2( Point(570, 470), 1, -5, -12, Colour(0, 255, 0, 255), 30.0, 30.0, RECTANGLE, true );
	shape_manager.add_object(&r2);

	Rectangle r3( Point(0, 400), 1, -1, -1, Colour(121, 255, 0, 255), 30.0, 30.0, RECTANGLE, true );
	shape_manager.add_object(&r3);

	Rectangle r4( Point(600, 300), 1, -3, 8, Colour(90, 123, 12, 255), 30.0, 30.0, RECTANGLE, true );
	shape_manager.add_object(&r4);	

    Rectangle r( Point(500, 10), 1, 1, 0, Colour(90, 123, 12, 255), 30.0, 30.0, RECTANGLE, true );	

    Rectangle_button rect_b1  ( Point(820, 50), Colour(200, 192, 54, 255), 180, 80);
    Circle_button    circle_b1( Point(820, 150), Colour(172, 32, 5, 255), 180, 80);

    button_manager.add_button(&rect_b1);
    button_manager.add_button(&circle_b1);

	SDL_Event event = {};
	bool is_run = true;
	while(is_run) {
		while(SDL_PollEvent(&event)) {
			if(event.type == SDL_QUIT) {
				is_run = false;
			}

			else if(event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_LEFT:       
                    	rect_b1.add_new_object(&shape_manager);
                    	break;
                    
                    case SDLK_RIGHT:
						circle_b1.add_new_object(&shape_manager);
                    	break;                    
                }
            }

            else if(event.type == SDL_MOUSEBUTTONUP) {
            	double x_mouse = event.button.x, y_mouse = event.button.y;
        		if((event.button.button == SDL_BUTTON_LEFT) ) {
            		if(rect_b1.shape_rect->is_point_belongs_to_rectangle( Point(x_mouse, y_mouse) ))
            			button_manager.buttons[0]->add_new_object(&shape_manager);        		
        		}

            	else
        		if(event.button.button == SDL_BUTTON_RIGHT) {
            		if(circle_b1.shape_rect->is_point_belongs_to_rectangle( Point(x_mouse, y_mouse) )) 
            			button_manager.buttons[1]->add_new_object(&shape_manager);            		            		        		            		            
        		}
            }
		}

		shape_manager.update_molecule();
		shape_manager.collision_detection(SCREEN_WIDTH - 200, SCREEN_HEIGHT - 150);

    	SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
    	SDL_RenderClear(render);

   		draw_line(render, Point(0, SCREEN_WIDTH - 200.0), SCREEN_HEIGHT - 150.0);
   		draw_line(render, SCREEN_WIDTH - 200.0, Point(0, SCREEN_HEIGHT - 150.0));

		for(size_t i = 0; i < shape_manager.count_objects; ++i) {
			shape_manager.shapes[i]->draw_molecule(render);
		}

		for(size_t i = 0; i < button_manager.count_buttons; ++i) {
			button_manager.buttons[i]->draw_button(render);
		}		

		SDL_RenderPresent(render);
	}	


	SDL_RenderPresent(render);
	quit(window, render);

	return sdl_status;
}