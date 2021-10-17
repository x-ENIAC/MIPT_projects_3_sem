#include "view.h"
#include "button.h"
#include "canvas_manager.h"
#include "pencil.h"
#include "palette.h"

#ifndef VIEW_MANAGER_H
#define VIEW_MANAGER_H

extern const size_t MAX_COUNT_OF_VIEW_OBJECTS = 100;
extern const double WIDTH_CLOSE_BUTTON;
extern const double HEIGHT_CLOSE_BUTTON;

const double WIDTH_FILE_PANEL_BUTTON = 60;

enum Mouse_click_state {
	MOUSE_UP   = 1,
	MOUSE_DOWN = 2
};

class View_manager : public View_object {
  public:
	View_object** view_objects;
	size_t count_of_view_objects;
	int who_is_active;

	Pencil pencil;

	Mouse_click_state mouse_click_state;

  	View_manager(const Point par_point, const double par_width, const double par_height, const Colour par_color, const bool par_is_active) :
  	  View_object(par_point, par_width, par_height, LIGHT_GREY) {

  	 	count_of_view_objects = 1;
  		printf("Construct View_manager, %ld\n", count_of_view_objects);

  	 	view_objects = new View_object*[MAX_COUNT_OF_VIEW_OBJECTS];
  	 	for(size_t i = 0; i < MAX_COUNT_OF_VIEW_OBJECTS; ++i)
  	 		view_objects[i] = new View_object;

  	 	Open_panel_delegate* open_panel_delegate = new Open_panel_delegate;

        Point center_button = Point(par_point.x - par_width / 2.0 + WIDTH_FILE_PANEL_BUTTON / 2.0, par_point.y - par_height / 2.0 + HEIGHT_CLOSE_BUTTON / 2.0);

        Button* file_panel_button = new Button(open_panel_delegate, center_button, DARK_GREY, WIDTH_FILE_PANEL_BUTTON, HEIGHT_CLOSE_BUTTON, "File", WHITE);
        view_objects[count_of_view_objects++] = file_panel_button;


  	 	who_is_active = -1;

  	 	pencil = {};

  	 	mouse_click_state = MOUSE_UP;

  	 	Palette* palette = new Palette(par_width - WIDTH_CLOSE_BUTTON, HEIGHT_CLOSE_BUTTON * 2, &pencil);
  	 	add_view_object(palette);
  	}

  	~View_manager() {
  		printf("Destruct View_manager, %ld\n", count_of_view_objects);

  	 	count_of_view_objects = 0;
  	 	who_is_active = 0;
  	}			

	void add_view_object(View_object* new_view) {
		//printf("new object!\n");
  	 	view_objects[count_of_view_objects] = new_view;
  	 	++count_of_view_objects;
  	 	printf("%ld\n", count_of_view_objects);
  	}  	

  	void draw(SDL_Renderer** render, SDL_Texture** texture) {
  		rect->draw(*render);

  		for(size_t i = 0; i < count_of_view_objects; ++i) {
  			view_objects[i]->draw(render, texture);
  		}
  	}

  	void check_events(SDL_Event* event) {
		if(event->type == SDL_MOUSEBUTTONUP) {
			mouse_click_state = MOUSE_UP;
		}

		if(event->type == SDL_MOUSEBUTTONDOWN) {
			mouse_click_state = MOUSE_DOWN;
			double x_mouse = event->button.x, y_mouse = event->button.y;

			bool is_solved = check_click(x_mouse, y_mouse);
			if(!is_solved)
				printf("!!!WARNING!!!\n");
		}		

		else if(event->type == SDL_MOUSEMOTION) {
			double x_mouse = event->button.x, y_mouse = event->button.y;

			if(mouse_click_state == MOUSE_DOWN) {
				check_click(x_mouse, y_mouse);		
			}
		}

		else if(event->type == SDL_KEYDOWN) {
			bool is_solved = check_tap(event);
			if(!is_solved)
				printf("!!!WARNING!!!\n");
		}
  	}

  	bool check_click(const double mouse_x, const double mouse_y) {
  		for(int i = count_of_view_objects - 1; i >= 0; --i) {
  			if(view_objects[i]->check_click(mouse_x, mouse_y)) {
  				set_new_active_object(i);

  				return true;
  			}
  		}

  		return false;
  	}

  	bool check_tap(SDL_Event* event) {
  		//if(event->key.repeat != 0) // клавиша зажата
  		//	printf("NICE\n");

        switch (event->key.keysym.sym) {                    
            case SDLK_b:					// black
            	pencil.set_color(BLACK);
            	printf("black\n");
                return true;

            case SDLK_r:					// RED
            	pencil.set_color(RED);
            	printf("red\n");
                return true;

            case SDLK_g:					// GREEN
            	pencil.set_color(GREEN);
                return true;

            case SDLK_y:					// YELLOW
            	pencil.set_color(YELLOW);
                return true;

            case SDLK_l:					// BLUE (l)
            	pencil.set_color(BLUE);
                return true;                
        } 			

        return false;	  		
  	}

  	void set_new_active_object(const int new_active) {
  		who_is_active = new_active;
  		//printf("new active %d\n", who_is_active);
  	}
};

#endif