#include "colour.h"
#include "button_delegates.h"
#include "button.h"

#ifndef PALETTE_H
#define PALETTE_H

extern const size_t MAX_COUNT_OF_VIEW_OBJECTS;
extern const double DELTA_BETWEEN_BUTTONS = 5;
extern const double WIDTH_CLOSE_BUTTON;
extern const double HEIGHT_CLOSE_BUTTON;

class Palette : public View_object {
  public:
	Pencil* pencil;

	Button** buttons;
	size_t count_of_buttons;

	Palette(const double begin_width, const double begin_height, Pencil* par_pencil) : View_object() {
		pencil = par_pencil;

		count_of_buttons = 0;

  	 	buttons = new Button*[MAX_COUNT_OF_VIEW_OBJECTS];
  	 	for(size_t i = 0; i < MAX_COUNT_OF_VIEW_OBJECTS; ++i)
  	 		buttons[i] = new Button;

  	 	rect->center = center = Point(begin_width - DELTA_BETWEEN_BUTTONS, begin_height, DARK_GREY);
  	 	rect->height = HEIGHT_CLOSE_BUTTON + DELTA_BETWEEN_BUTTONS * 2;
  	 	rect->set_colour(DARK_GREY);

	    add_button(begin_width, begin_height, YELLOW);
	    add_button(begin_width, begin_height, RED);
	    add_button(begin_width, begin_height, GREEN);
	    add_button(begin_width, begin_height, BLUE);
	    add_button(begin_width, begin_height, PURPLE);
	    add_button(begin_width, begin_height, LIGHT_GREEN);
	    add_button(begin_width, begin_height, PINK);
	}

	void add_button(const double begin_width, const double begin_height, Colour color) {
	    Change_colour_delegate* change_colour_to_purple_delegate = new Change_colour_delegate(pencil, color);
	    Button* set_purple = new Button(change_colour_to_purple_delegate, 
	    								Point(begin_width - (DELTA_BETWEEN_BUTTONS + WIDTH_CLOSE_BUTTON) * count_of_buttons, begin_height), 
	    								color, WIDTH_CLOSE_BUTTON, HEIGHT_CLOSE_BUTTON);
	    add_view_object(set_purple);
	}

	void add_view_object(Button* new_button) {
  	 	buttons[count_of_buttons] = new_button;
  	 	++count_of_buttons;

  	 	Point new_center(buttons[count_of_buttons-1]->center);
  	 	new_center += Point(rect->width / 2, 0);

  	 	rect->center = center = new_center;
  	 	rect->width += WIDTH_CLOSE_BUTTON + DELTA_BETWEEN_BUTTONS;
  	}

  	virtual bool check_click(const double mouse_x, const double mouse_y) {
  		for(size_t i = 0; i < count_of_buttons; ++i) {
  			if(buttons[i]->rect->is_point_belongs_to_rectangle( Point(mouse_x, mouse_y) )) {
  				buttons[i]->delegate->click_reaction();
  				return true;
  			}
  		}

  		return false;
  	}  	

	void draw(SDL_Renderer** render, SDL_Texture** texture) override {
		rect->draw(*render);

		for(size_t i = 0; i < count_of_buttons; ++i)
			buttons[i]->draw(render, texture);
	}

};

#endif