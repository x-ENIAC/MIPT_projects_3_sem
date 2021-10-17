#include "view.h"
#include "button.h"
#include "canvas_manager.h"
#include "pencil.h"

#ifndef VIEW_MANAGER_H
#define VIEW_MANAGER_H

extern const size_t MAX_COUNT_OF_VIEW_OBJECTS = 10000;

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

  	 	/*Close_delegate*  close_delegate = new Close_delegate;

        Point center_button = Point(par_width - WIDTH_CLOSE_BUTTON / 2.0 + par_point.x - par_width / 2.0,  HEIGHT_CLOSE_BUTTON / 2.0 + par_point.y - par_height / 2.0);

        Button* close_button = new Button(close_delegate, center_button, BLACK, WIDTH_CLOSE_BUTTON, HEIGHT_CLOSE_BUTTON, "x", WHITE);
        view_objects[count_of_view_objects++] = close_button;*/

  	 	//Canvas_manager* canvas_manager = new Canvas_manager(/*NULL,*/ par_point, par_width, par_height, par_color, par_is_active);
  	 	//add_view_object(canvas_manager);

  	 	who_is_active = -1;

  	 	pencil = {};

  	 	mouse_click_state = MOUSE_UP;
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

  	/*bool check_click(const double mouse_x, const double mouse_y) {
  		for(int i = count_of_view_objects - 1; i >= 0; --i) {
  			if(view_objects[i]->check_click(mouse_x, mouse_y)) {
  				set_new_active_object(i);

  				//Point new_point(mouse_x, mouse_y, pencil.get_color());
  				//new_point.draw_point(render);

  				return true;
  			}
  		}

  		return false;
  	}*/

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
                return true;

            case SDLK_r:					// RED
            	pencil.set_color(RED);
                return true;

            case SDLK_g:					// GREEN
            	pencil.set_color(GREEN);
                return true;
        } 			

        return false;	  		
  	}

  	void set_new_active_object(const int new_active) {
  		who_is_active = new_active;
  		printf("new active %d\n", who_is_active);
  	}
};

#endif