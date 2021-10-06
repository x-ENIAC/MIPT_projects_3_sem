#include <SDL2/SDL.h>
#include "point.h"
#include "colour.h"
#include "button.h"

#ifndef BUTTON_MANAGER_H
#define BUTTON_MANAGER_H

const size_t MAX_COUNT_OF_BUTTONS = 10;

class Button_manager {
  public:

  	Button** buttons;
  	size_t count_buttons;

  	Button_manager() {
  	 	buttons = new Button*[MAX_COUNT_OF_BUTTONS];
  	 	for(size_t i = 0; i < MAX_COUNT_OF_BUTTONS; ++i)
  	 		buttons[i] = new Button;

  	 	count_buttons = 0;
  	}

  	~Button_manager() {
  		printf("Destruct, %ld\n", count_buttons);
  		/*for(size_t i = 0; i < MAX_COUNT_OF_BUTTONS; ++i) {
  			if(buttons[i]->get_owner() == BUTTON_OWNER_BUTTON_CLASS)
  				delete[] buttons[i];
  		}*/
  	 	//delete[] buttons;


  	 	count_buttons = 0;
  	}	

	void add_button(Button* new_button) {
  	 	buttons[count_buttons] = new_button;
  	 	++count_buttons;
  	 	//printf("count %ld\n", count_buttons);
  	}

	void check_events(SDL_Event* event, Object_manager* object_manager) {
		double x_mouse = event->button.x, y_mouse = event->button.y;

        if((event->button.button == SDL_BUTTON_LEFT) ) {
            if(buttons[0]->object_rect->is_point_belongs_to_rectangle( Point(x_mouse, y_mouse) ))
            	buttons[0]->add_new_object(object_manager); 

            else
            if(buttons[1]->object_rect->is_point_belongs_to_rectangle( Point(x_mouse, y_mouse) )) 
            	buttons[1]->add_new_object(object_manager);       		
        }	

        switch (event->key.keysym.sym) {
            case SDLK_LEFT:       
                printf("!\n");
                buttons[0]->add_new_object(object_manager);
                printf("?\n");
                break;
                    
            case SDLK_RIGHT:
				buttons[1]->add_new_object(object_manager);
                break;                    
        }        	
	}  	

};

#endif