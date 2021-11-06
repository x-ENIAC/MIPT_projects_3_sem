#include "colour.h"
#include "button_delegates.h"
#include "button.h"
#include "button_manager.h"
//#include "widget_types.h"

#ifndef THICKNESS_PALETTE_H
#define THICKNESS_PALETTE_H

extern const size_t MAX_COUNT_OF_VIEW_OBJECTS;
extern const double DELTA_BETWEEN_BUTTONS;
extern const double WIDTH_CLOSE_BUTTON;
extern const double HEIGHT_CLOSE_BUTTON;

class Thickness_palette : public View_object {
  public:
	Pencil* pencil;

	Button_manager* tool_buttons;
	Button_manager* thickness_buttons;

	Thickness_palette(const double begin_width, const double begin_height, Pencil* par_pencil, Mouse_click_state* par_mouse_click_state) :
	  View_object(Widget_types::PALETTE) {
		pencil = par_pencil;

		rect->height = HEIGHT_CLOSE_BUTTON + DELTA_BETWEEN_BUTTONS * 2;
		rect->set_colour(DARK_GREY_3);

		tool_buttons = new Button_manager();

		thickness_buttons = new Button_manager();


		fill_button_manager(begin_width, begin_height, par_mouse_click_state);
	}

	void fill_button_manager(const double begin_width, const double begin_height, Mouse_click_state* par_mouse_click_state) {


		//--------------- add close button ---------------------------

		Point center_close_button(begin_width + WIDTH_CLOSE_BUTTON / 2.0 - DELTA_BETWEEN_BUTTONS,
								  begin_height - (HEIGHT_CLOSE_BUTTON + DELTA_BETWEEN_BUTTONS / 2.0));

		Button* close_button = new Button(NULL, center_close_button, BLACK, WIDTH_CLOSE_BUTTON, HEIGHT_CLOSE_BUTTON,
										  "x", BLACK);
		close_button->texture->add_new_texture(PATH_TO_PICTURE_WITH_BLACK_CLOSE_BUTTON);

		Close_delegate*  close_delegate = new Close_delegate(close_button, par_mouse_click_state, &is_alive);

		close_button->delegate = close_delegate;

		tool_buttons->add_view_object(close_button);

		//--------------- add colours button ---------------------------

		add_thickness_buttons(begin_width, begin_height, 50);
		add_thickness_buttons(begin_width, begin_height, 20);
		add_thickness_buttons(begin_width, begin_height, 10);
		add_thickness_buttons(begin_width, begin_height,  5);
		add_thickness_buttons(begin_width, begin_height,  1);

		set_parameters_of_colours_button_manager();

		//--------------- add roll up button ---------------------------

		Point center_roll_up_button = thickness_buttons->buttons[thickness_buttons->get_count_of_buttons() - 1]->rect->get_center();
		center_roll_up_button -= Point(DELTA_BETWEEN_BUTTONS, HEIGHT_CLOSE_BUTTON + DELTA_BETWEEN_BUTTONS);

		Roll_up_delegate*  roll_up_delegate = new Roll_up_delegate(par_mouse_click_state, &is_visible, &is_active);

		Button* roll_up_button = new Button(roll_up_delegate, center_roll_up_button, BLACK, WIDTH_CLOSE_BUTTON, HEIGHT_CLOSE_BUTTON,
											"-", BLACK, PATH_TO_PICTURE_WITH_ROLL_UP_BUTTON);

		roll_up_button->texture->add_new_texture(PATH_TO_PICTURE_WITH_ROLL_UP_BUTTON);
		tool_buttons->add_view_object(roll_up_button);

		//--------------- add title button ---------------------------

		Title_delegate*  title_delegate = new Title_delegate(this);

		Point center_title_button(center_close_button);
		center_title_button += center_roll_up_button;
		center_title_button /= 2.0;

		Button* title_button = new Button(title_delegate, center_title_button, DARK_GREY,
										  center_close_button.x - center_roll_up_button.x - WIDTH_CLOSE_BUTTON,
										  HEIGHT_CLOSE_BUTTON,
										  "Title", BLACK, PATH_TO_PICTURE_WITH_TITLE_BUTTON);

		title_button->texture->add_new_texture(PATH_TO_PICTURE_WITH_TITLE_BUTTON);
		tool_buttons->add_view_object(title_button);

		set_parameters_of_tools_button_manager();
	}

	void add_thickness_buttons(const double begin_width, const double begin_height, size_t added_size) {
		char text_thickness[10];
		sprintf(text_thickness, "%ld", added_size);

		size_t old_count_of_buttons = thickness_buttons->count_of_buttons;

		Change_thickness_delegate* change_thickness_delegate = new Change_thickness_delegate(pencil, added_size);
		Button* button = new Button(change_thickness_delegate, 
									Point(begin_width - (DELTA_BETWEEN_BUTTONS + WIDTH_CLOSE_BUTTON) * old_count_of_buttons, begin_height), 
									WHITE, WIDTH_CLOSE_BUTTON, HEIGHT_CLOSE_BUTTON, text_thickness);

		thickness_buttons->add_view_object(button);

		Point new_center(thickness_buttons->buttons[old_count_of_buttons]->rect->get_center());
		new_center += Point(rect->width / 2, 0);

		rect->width += WIDTH_CLOSE_BUTTON + DELTA_BETWEEN_BUTTONS;
	}

	void set_parameters_of_colours_button_manager() {
		Point center_thickness_buttons;
		size_t count_of_buttons = thickness_buttons->get_count_of_buttons();

		for(size_t i = 0; i < count_of_buttons; ++i) {
			center_thickness_buttons += thickness_buttons->buttons[i]->rect->get_center();
		}

		center_thickness_buttons /= count_of_buttons;

		thickness_buttons->rect->set_center(center_thickness_buttons);

		thickness_buttons->rect->set_height(HEIGHT_CLOSE_BUTTON + 2 * DELTA_BETWEEN_BUTTONS);
		thickness_buttons->rect->set_width(thickness_buttons->buttons[         0          ]->rect->get_center().x -
										   thickness_buttons->buttons[count_of_buttons - 1]->rect->get_center().x +
																							WIDTH_CLOSE_BUTTON + 2 * DELTA_BETWEEN_BUTTONS);

		thickness_buttons->rect->set_colour(DARK_GREY_2);
	}

	void set_parameters_of_tools_button_manager() {

		Point center_tool_buttons;
		size_t count_of_buttons = tool_buttons->get_count_of_buttons();

		for(size_t i = 0; i < count_of_buttons; ++i) {
			center_tool_buttons += tool_buttons->buttons[i]->rect->get_center();
		}

		center_tool_buttons /= count_of_buttons;		

		tool_buttons->rect->set_center(center_tool_buttons);

		tool_buttons->rect->set_height(HEIGHT_CLOSE_BUTTON);
		tool_buttons->rect->set_width(tool_buttons->buttons[         0          ]->rect->get_center().x -
									  tool_buttons->buttons[count_of_buttons - 2]->rect->get_center().x + WIDTH_CLOSE_BUTTON);
	}	

	bool check_click(const double mouse_x, const double mouse_y, const Mouse_click_state* par_mouse_status) override {
		if(thickness_buttons->rect->is_point_belongs_to_rectangle( Point(mouse_x, mouse_y) )) {
			//printf("color! Mouse (%lg, %lg); rect (%lg, %lg), w %lg, h %lg\n", mouse_x, mouse_y, thickness_buttons->rect->get_center().x,
			//								thickness_buttons->rect->get_center().y, thickness_buttons->rect->get_width(), thickness_buttons->rect->get_height());
			//printf("thickness\n");
			return thickness_buttons->check_click(mouse_x, mouse_y, par_mouse_status);
		}

		if(tool_buttons->rect->is_point_belongs_to_rectangle( Point(mouse_x, mouse_y) )) {
			//printf("tools! %d\n", *par_mouse_status);
			return tool_buttons->check_click(mouse_x, mouse_y, par_mouse_status);
		}
		
		return false;
	}  	

	void draw(SDL_Renderer** render, SDL_Texture** texture, SDL_Surface** screen) override {
		if(is_visible) {
			//rect->draw(*render);

			thickness_buttons->draw(render, texture, screen);
			tool_buttons->draw(render, texture, screen);
		}
	}

	void delete_all() {
		//delete_object()
		printf("Hello, world!\n");

		thickness_buttons->delete_all();
		delete[] thickness_buttons;
	}

	void update_view_object_position(const double mouse_x, const double mouse_y) override {
		update_palette_position(mouse_x, mouse_y);
	}

	void update_palette_position(const double mouse_x, const double mouse_y) {  	

		Point mouse(mouse_x, mouse_y);
		Point delta(tool_buttons->rect->get_center());
		delta -= mouse;

		rect->set_center(rect->get_center() - delta);

		tool_buttons->rect->set_center(mouse);
		tool_buttons->update_position_from_delta(delta);

		thickness_buttons->rect->set_center( thickness_buttons->rect->get_center() - delta );
		thickness_buttons->update_position_from_delta(delta);

		//printf("new (%lg, %lg)\n\n", tool_buttons->rect->get_center().x, tool_buttons->rect->get_center().y);
	}

	void tick(const double delta_time) override {
		tool_buttons->tick(delta_time);
		thickness_buttons->tick(delta_time);
	}
};

#endif