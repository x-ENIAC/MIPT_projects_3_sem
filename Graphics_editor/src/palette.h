#include "colour.h"
#include "button_delegates.h"
#include "button.h"
#include "button_manager.h"
//#include "widget_types.h"

#ifndef PALETTE_H
#define PALETTE_H

extern const size_t MAX_COUNT_OF_VIEW_OBJECTS;
const double DELTA_BETWEEN_BUTTONS = 5;
extern const double WIDTH_CLOSE_BUTTON;
extern const double HEIGHT_CLOSE_BUTTON;

class Palette : public View_object {
  public:
	Pencil* pencil;

	Button_manager* button_manager;

	Palette(const double begin_width, const double begin_height, Pencil* par_pencil) : View_object(Widget_types::PALETTE) {
		pencil = par_pencil;

  	 	button_manager = new Button_manager[MAX_COUNT_OF_VIEW_OBJECTS];
	 	

  	 	rect->center = center = Point(begin_width - DELTA_BETWEEN_BUTTONS, begin_height, DARK_GREY);
  	 	rect->height = HEIGHT_CLOSE_BUTTON + DELTA_BETWEEN_BUTTONS * 2;
  	 	rect->set_colour(DARK_GREY);

  	 	fill_button_manager(begin_width, begin_height);
	}

	void fill_button_manager(const double begin_width, const double begin_height) {
	    add_button(begin_width, begin_height, YELLOW);
	    add_button(begin_width, begin_height, RED);
	    add_button(begin_width, begin_height, GREEN);
	    add_button(begin_width, begin_height, BLUE);
	    add_button(begin_width, begin_height, PURPLE);
	    add_button(begin_width, begin_height, LIGHT_GREEN);
	    add_button(begin_width, begin_height, PINK);
	}

	void add_button(const double begin_width, const double begin_height, Colour color) {
		size_t old_count_of_buttons = button_manager->count_of_buttons;

	    Change_colour_delegate* change_colour_to_purple_delegate = new Change_colour_delegate(pencil, color);
	    Button* set_purple = new Button(change_colour_to_purple_delegate, 
	    								Point(begin_width - (DELTA_BETWEEN_BUTTONS + WIDTH_CLOSE_BUTTON) * old_count_of_buttons, begin_height), 
	    								color, WIDTH_CLOSE_BUTTON, HEIGHT_CLOSE_BUTTON);

	    button_manager->add_view_object(set_purple);

  	 	Point new_center(button_manager->buttons[old_count_of_buttons]->center);
  	 	new_center += Point(rect->width / 2, 0);

  	 	rect->center = center = new_center;
  	 	rect->width += WIDTH_CLOSE_BUTTON + DELTA_BETWEEN_BUTTONS;	    
	}

  	virtual bool check_click(const double mouse_x, const double mouse_y) {

  		return button_manager->check_click(mouse_x, mouse_y);
  	}  	

	void draw(SDL_Renderer** render, SDL_Texture** texture) override {
		rect->draw(*render);

		button_manager->draw(render, texture);
	}

};

#endif