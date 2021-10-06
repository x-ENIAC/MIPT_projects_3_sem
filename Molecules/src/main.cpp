#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "object_manager.h"
#include "circle.h"
#include "rectangle.h"

#include "button_manager.h"
#include "adding_object_button.h"
#include "button_with_text.h"

#include "text.h"
#include "chart.h"

const int SCREEN_WIDTH  = 920;
const int SCREEN_HEIGHT = 720; 

const double DELTA = 0.5;

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

SDL_STATUSES initialize(SDL_Window** window, SDL_Renderer** render, SDL_Texture** texture, TTF_Font** font) {
	if(SDL_Init(SDL_INIT_EVERYTHING | SDL_INIT_TIMER | SDL_INIT_VIDEO) != 0) {
    	printf("Could not initialize SDL: %s.\n", SDL_GetError());
    	return BAD_SDL_INIT;
  	}

  	//*window = SDL_CreateWindow("Molecules", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
    //			                           SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  	
  	SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, window, render);


  	if(!(*window))
    	return WINDOW_NOT_CREATE;
	char* name_font = "00057_1000HURT.ttf";

    TTF_Init();

  	/**render = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if(!(*render))                                         
        return RENDER_NOT_CREATE;*/

    /*surface = IMG_Load("alphabet.png");
 	if(!(surface)) {
    	printf("Can't load image\n");
    	return SURFACE_NOT_CREATE;
 	}*/
    
	return SDL_OKEY;
}

void quit(SDL_Window** window, SDL_Renderer** render, SDL_Texture** texture) {
  	SDL_DestroyWindow  (*window);
  	SDL_DestroyRenderer(*render);
  	SDL_DestroyTexture (*texture);

  	*window  = NULL;
  	*render  = NULL;
  	*texture = NULL;

  	TTF_Quit();
  	SDL_Quit();
}

void draw_line(SDL_Renderer** render, const Point begin, const int y) {
	double x_begin = begin.x, x_end = begin.y;

	for(size_t x = x_begin; x <= x_end; ++x) {
		Point now_point ( x, y, BLACK );
		now_point.draw_point(*render);
	}
}

void draw_line(SDL_Renderer** render, const int x, const Point end) {
	double y_begin = end.x, y_end = end.y;

	for(size_t y = y_begin; y <= y_end; ++y) {
		Point now_point ( x, y, BLACK );
		now_point.draw_point(*render);
	}
}

int main() {
	const int FIELD_WIDTH  = SCREEN_WIDTH - 200;
	const int FIELD_HEIGHT = SCREEN_HEIGHT - 150;

	srand(time(NULL));
    SDL_Window*   window = NULL;
    SDL_Renderer* render = NULL;
    SDL_Texture* texture = NULL;
    TTF_Font*       font = NULL;

    SDL_STATUSES sdl_status = initialize(&window, &render, &texture, &font);
    CHECK_SDL_STATUS

    SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
    SDL_RenderClear(render);


	Object_manager object_manager = {};
	Button_manager button_manager = {};

	//Circle m2( Point(70, 370), 20, 1, 7, -5, Colour(0, rand() % 255, rand() % 255, 255), CIRCLE, true );
	Circle m2( Point(rand() % FIELD_WIDTH, rand() % FIELD_HEIGHT), rand() % 20, 1, rand() % 10, rand() % 10, 
																	 Colour(0, rand() % 255, rand() % 255, 255), true, OBJECT_OWNER_USER );	
	object_manager.add_object(&m2);

	//Circle m3( Point(570, 70), 20, 1, -10, 5, Colour(0, 255, 0, 255), CIRCLE, true );
	Circle m3( Point(rand() % FIELD_WIDTH, rand() % FIELD_HEIGHT), rand() % 20, 1, rand() % 10, rand() % 10, 
																	 Colour(0, rand() % 255, rand() % 255, 255), true, OBJECT_OWNER_USER );
	object_manager.add_object(&m3);

	//Rectangle r1( Point(170, 170), 1, 0, 0, Colour(0, 0, 255, 255), 30.0, 30.0, RECTANGLE, true );
	Rectangle r1( Point(rand() % FIELD_WIDTH, rand() % FIELD_HEIGHT), 1, rand() % 30,      rand() % 30,
																			     Colour(rand() % 255, rand() % 255, rand() % 255, 255), 
																		 rand() % 20 + 10, rand() % 20 + 10, RECTANGLE, true );	
	object_manager.add_object(&r1);

	//Rectangle r2( Point(300, 500), 4, 5*3, -5*3, Colour(0, 255, 0, 255), 30.0, 30.0, RECTANGLE, true );
	Rectangle r2( Point(rand() % FIELD_WIDTH, rand() % FIELD_HEIGHT), 4, rand() % 30,      rand() % 30,
																	     Colour(rand() % 255, rand() % 255, rand() % 255, 255), 
																		 rand() % 20 + 10, rand() % 20 + 10, RECTANGLE, true );	
	object_manager.add_object(&r2);

	//Rectangle r3( Point(500, 300), 4, -4*3, 4*3, Colour(121, 255, 0, 255), 30.0, 30.0, RECTANGLE, true );
	Rectangle r3( Point(rand() % FIELD_WIDTH, rand() % FIELD_HEIGHT), 8, rand() % 30,      rand() % 30,
																	     Colour(rand() % 255, rand() % 255, rand() % 255, 255), 
																		 rand() % 20 + 10, rand() % 20 + 10, RECTANGLE, true );	
	object_manager.add_object(&r3);

	//Rectangle r4( Point(600, 300), 1, -3*3, 8*3, Colour(90, 123, 12, 255), 30.0, 30.0, RECTANGLE, true );
	Rectangle r4( Point(rand() % FIELD_WIDTH, rand() % FIELD_HEIGHT), 5, rand() % 30,      rand() % 30, 
																		 Colour(rand() % 255, rand() % 255, rand() % 255, 255), 
																		 rand() % 20 + 10, rand() % 20 + 10, RECTANGLE, true );	
	object_manager.add_object(&r4);	


    //Rectangle_button rect_b1  ( Point(820,  50), Colour(200, 192, 54, 255), 180, 80);
    Adding_object_button    circle_b1( Point(820, 50), Colour(172,  32,  5, 255), 180, 80, CIRCLE);
    Adding_object_button      rect_b1( Point(820, 150), Colour(172,  32,  5, 255), 180, 80, RECTANGLE);
    //Text_button        text_b1( &rect_b1, "text" );


    button_manager.add_button(&rect_b1);
    button_manager.add_button(&circle_b1);

    Amount_chart amount_chart_for_circle   ( Point(360, 645), Colour(200.0, 162.0, 200.0, 255.0), 720.0, 120.0);
    Amount_chart amount_chart_for_rectangle( Point(360, 645), Colour(200.0, 162.0, 200.0, 255.0), 720.0, 120.0);

    size_t count_circles = 0, count_rectangles = 0;
    amount_chart_for_circle.add_point( Point(0, count_circles) );

    double timer = 0;

    Text text;

	SDL_Event event = {};
	bool is_run = true;
	while(is_run) {
		while(SDL_PollEvent(&event)) {
			if(event.type == SDL_QUIT)
				is_run = false;			

			else if(event.type == SDL_KEYDOWN || event.type == SDL_MOUSEBUTTONUP)
				button_manager.check_events(&event, &object_manager);        
		}

		count_circles    = object_manager.get_count_of_objects(CIRCLE);
		count_rectangles = object_manager.get_count_of_objects(RECTANGLE);

		object_manager.update_circle();
		object_manager.collision_detection(FIELD_WIDTH, FIELD_HEIGHT);
    	SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
    	SDL_RenderClear(render);

    	amount_chart_for_circle.add_point   ( Point(timer, object_manager.get_count_of_objects(CIRCLE), Colour(255.0, 0.0, 0.0, 255.0)) );
    	amount_chart_for_rectangle.add_point( Point(timer, object_manager.get_count_of_objects(RECTANGLE), Colour(0.0, 255.0, 0.0, 255.0)) );

    	amount_chart_for_circle.draw_chart   (render, true);
    	amount_chart_for_rectangle.draw_chart(render, false);

   		draw_line(&render, Point(0, FIELD_WIDTH), FIELD_HEIGHT);
   		draw_line(&render, FIELD_WIDTH, Point(0, FIELD_HEIGHT));

		for(size_t i = 0; i < object_manager.count_objects; ++i)
			object_manager.objects[i]->draw_molecule(render);

		for(size_t i = 0; i < button_manager.count_buttons; ++i)
			button_manager.buttons[i]->draw_button(render);

		text.draw_text(Point(820, 50), &render, &texture);
		SDL_RenderPresent(render);

		timer += DELTA;
		if(timer > FIELD_WIDTH) {
			timer = 0;
			amount_chart_for_circle.update_point_array();
			amount_chart_for_rectangle.update_point_array();
		}
	}	


	SDL_RenderPresent(render);
	quit(&window, &render, &texture);

	return 0;
}