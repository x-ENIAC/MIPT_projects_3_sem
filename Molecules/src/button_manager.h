#include <SDL2/SDL.h>
#include "point.h"
#include "colour.h"
#include "button.h"

#ifndef BUTTON_MANAGER_H
#define BUTTON_MANAGER_H

const size_t MAX_COUNT_OF_BUTTONS = 10;

class Button_manager {
  public:
	//Rectangle* shape_rect;
	//Button_status status;

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
  		//for(size_t i = 0; i < MAX_COUNT_OF_BUTTONS; ++i) {
  		//	delete[] buttons[i];
  		//}
  	 	//delete[] buttons;


  	 	count_buttons = 0;
  	}	

	void add_button(Button* new_button) {
  	 	buttons[count_buttons] = new_button;
  	 	++count_buttons;
  	 	printf("count %ld\n", count_buttons);
  	}

};

#endif