#include "view.h"
#include "button.h"
#include "colour.h"
//#include "widget_types.h"

#ifndef BUTTON_MANAGER_H
#define BUTTON_MANAGER_H

extern const double WIDTH_TABS_BUTTON;
extern const double HEIGHT_TABS_BUTTON;

class Button_manager : public View_object {
  public:
	Button** buttons;
	size_t count_of_buttons;

	Button_manager() : View_object(Widget_types::BUTTON_MANAGER) {
		count_of_buttons = 0;

  	 	buttons = new Button*[MAX_COUNT_OF_VIEW_OBJECTS];
  	 	for(size_t i = 0; i < MAX_COUNT_OF_VIEW_OBJECTS; ++i)
  	 		buttons[i] = new Button;
	}	

	Button_manager(const Point par_center, const double par_width, const double par_height, const Colour par_color,
																							const char* par_path_to_picture = NON_PATH_TO_PUCTURE) :
	  View_object(par_center, par_width, par_height, par_color, Widget_types::BUTTON_MANAGER, par_path_to_picture) {
		count_of_buttons = 0;

  	 	buttons = new Button*[MAX_COUNT_OF_VIEW_OBJECTS];
  	 	for(size_t i = 0; i < MAX_COUNT_OF_VIEW_OBJECTS; ++i)
  	 		buttons[i] = new Button;
	}

	void add_view_object(Button* new_button) {
  	 	buttons[count_of_buttons] = new_button;
  	 	++count_of_buttons;

  	 	++widget_types[new_button->get_yourself_type()];
  	}

  	bool check_click(const double mouse_x, const double mouse_y, const Mouse_click_state* par_mouse_status) override {
        
  		//printf("Button_manager, check_click, %d. Mouse (%lg, %lg). Center (%lg, %lg), widht %lg, height %lg\n", is_active, mouse_x, mouse_y,
  		//																rect->get_center().x, rect->get_center().y, rect->get_width(), rect->get_height());

  		//if(is_active) {
	  		for(size_t i = 0; i < count_of_buttons; ++i) {
	  			/*printf("\tcenter (%lg, %lg), width %lg, height %lg. MMM %d\n", buttons[i]->rect->center.x, buttons[i]->rect->center.y, 
	  												buttons[i]->rect->get_width(), buttons[i]->rect->get_height(),
	  												buttons[i]->rect->is_point_belongs_to_rectangle( Point(mouse_x, mouse_y) ));*/

	  			if(buttons[i]->rect->is_point_belongs_to_rectangle( Point(mouse_x, mouse_y) )) {
  					if(*par_mouse_status == Mouse_click_state::MOUSE_DOWN)
  						buttons[i]->delegate->click_reaction(mouse_x, mouse_y);

	  				else
  					if(*par_mouse_status == Mouse_click_state::MOUSE_DOWN_AND_MOTION)
  						buttons[i]->delegate->motion_reaction(mouse_x, mouse_y);
	  				return true;
	  			}
	  		}
	  	//}

	  	//printf("return false Button_manager\n");

  		return false;
  	}  	

	void draw(SDL_Renderer** render, SDL_Texture** texture, SDL_Surface** screen) override {
		//if(!strcmp(NON_PATH_TO_PUCTURE, path_to_picture))
			rect->draw(*render);
		/*else {
	    	SDL_Rect sdl_rect;
	    	sdl_rect.w = rect->get_width();
		    sdl_rect.h = rect->get_height();
    		sdl_rect.x = rect->get_center().x - sdl_rect.w / 2.0;
	    	sdl_rect.y = rect->get_center().y - sdl_rect.h / 2.0;

    		texture_manager->draw_texture(path_to_picture, &sdl_rect);			
		}*/


		for(size_t i = 0; i < count_of_buttons; ++i)
			buttons[i]->draw(render, texture, screen);
	}

	void delete_all() {
		printf("begin Button_manager delete_all\n");

		for(size_t i = 0; i < count_of_buttons; ++i) {
			buttons[i]->delete_all();
			delete[] buttons[i];
		}

		delete[] buttons;
		count_of_buttons = 0;

		printf("end Button_manager delete_all\n");
	}

    void update_position(Point delta) {

        for(size_t i = 0; i < count_of_buttons; ++i) {
            buttons[i]->update_position(delta);
        }
    }	
};

#endif