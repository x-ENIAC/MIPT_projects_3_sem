#include "colour.h"
#include "button_delegates.h"
#include "button.h"
#include "button_manager.h"
//#include "widget_types.h"

#ifndef PALETTE_H
#define PALETTE_H

// extern const size_t MAX_COUNT_OF_VIEW_OBJECTS;
// extern const double DELTA_BETWEEN_BUTTONS;
// extern const double WIDTH_CLOSE_BUTTON;
// extern const double HEIGHT_CLOSE_BUTTON;

class Palette : public View_object {
  public:
	Pencil* pencil;

	Button_manager* tool_buttons;
	Button_manager* colour_buttons;

	Palette(const double begin_width, const double begin_height, Pencil* par_pencil, Mouse_click_state* par_mouse_click_state) :
	  View_object(Widget_types::PALETTE) {
		pencil = par_pencil;

		rect->height = HEIGHT_CLOSE_BUTTON + DELTA_BETWEEN_BUTTONS * 2;
		rect->set_colour(DARK_GREY_3);

		tool_buttons   = new Button_manager();
		colour_buttons = new Button_manager();


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

		add_colour_button(begin_width, begin_height, YELLOW);
		add_colour_button(begin_width, begin_height, RED);
		add_colour_button(begin_width, begin_height, GREEN);
		add_colour_button(begin_width, begin_height, BLUE);
		add_colour_button(begin_width, begin_height, PURPLE);
		add_colour_button(begin_width, begin_height, LIGHT_GREEN);
		add_colour_button(begin_width, begin_height, PINK);
		add_colour_button(begin_width, begin_height, LIGHT_CARROT);
		add_colour_button(begin_width, begin_height, WHITE);
		add_colour_button(begin_width, begin_height, BLACK);

		set_parameters_of_colours_button_manager();

		//--------------- add roll up button ---------------------------

		Point center_roll_up_button = colour_buttons->buttons[colour_buttons->get_count_of_buttons() - 1]->rect->get_center();
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
		//printf("PALETTE tool_buttons CENTER: (%lg, %lg)\n", tool_buttons->rect->get_center().x, tool_buttons->rect->get_center().y);
	}

	void add_colour_button(const double begin_width, const double begin_height, Colour color) {
		size_t old_count_of_buttons = colour_buttons->count_of_buttons;

		Change_colour_delegate* change_colour_to_purple_delegate = new Change_colour_delegate(pencil, color);
		Button* set_purple = new Button(change_colour_to_purple_delegate, 
										Point(begin_width - (DELTA_BETWEEN_BUTTONS + WIDTH_CLOSE_BUTTON) * old_count_of_buttons, begin_height), 
										color, WIDTH_CLOSE_BUTTON, HEIGHT_CLOSE_BUTTON);

		colour_buttons->add_view_object(set_purple);

		Point new_center(colour_buttons->buttons[old_count_of_buttons]->rect->get_center());
		new_center += Point(rect->width / 2, 0);

		//rect->center = center = new_center;
		rect->width += WIDTH_CLOSE_BUTTON + DELTA_BETWEEN_BUTTONS;
	}

	void set_parameters_of_colours_button_manager() {
		Point center_colour_buttons;
		size_t count_of_buttons = colour_buttons->get_count_of_buttons();

		for(size_t i = 0; i < count_of_buttons; ++i) {
			center_colour_buttons += colour_buttons->buttons[i]->rect->get_center();
		}

		center_colour_buttons /= count_of_buttons;

		colour_buttons->rect->set_center(center_colour_buttons);

		colour_buttons->rect->set_height(HEIGHT_CLOSE_BUTTON + 2 * DELTA_BETWEEN_BUTTONS);
		colour_buttons->rect->set_width(colour_buttons->buttons[         0          ]->rect->get_center().x -
										colour_buttons->buttons[count_of_buttons - 1]->rect->get_center().x + WIDTH_CLOSE_BUTTON + 2 * DELTA_BETWEEN_BUTTONS);

		colour_buttons->rect->set_colour(DARK_GREY_2);
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
		//printf("check_click palette, active %d\n", is_active);
		if(colour_buttons->rect->is_point_belongs_to_rectangle( Point(mouse_x, mouse_y) )) {
			//printf("color! Mouse (%lg, %lg); rect (%lg, %lg), w %lg, h %lg\n", mouse_x, mouse_y, colour_buttons->rect->get_center().x,
			//								colour_buttons->rect->get_center().y, colour_buttons->rect->get_width(), colour_buttons->rect->get_height());
			return colour_buttons->check_click(mouse_x, mouse_y, par_mouse_status);
		}

		if(tool_buttons->rect->is_point_belongs_to_rectangle( Point(mouse_x, mouse_y) )) {
			//printf("tools!\n");
			return tool_buttons->check_click(mouse_x, mouse_y, par_mouse_status);
		}
		return false;
	}

	bool check_motion(Point old_mouse, Point now_mouse, const Mouse_click_state* par_mouse_status) override {

		if(colour_buttons->rect->is_point_belongs_to_rectangle( Point(now_mouse.x, now_mouse.y) ) ||
		   colour_buttons->rect->is_point_belongs_to_rectangle( Point(old_mouse.x, old_mouse.y) )	) {

			return colour_buttons->check_motion(old_mouse, now_mouse, par_mouse_status);
		}

		if(tool_buttons->rect->is_point_belongs_to_rectangle( Point(now_mouse.x, now_mouse.y) ) ||
		   tool_buttons->rect->is_point_belongs_to_rectangle( Point(old_mouse.x, old_mouse.y) )) {

			return tool_buttons->check_motion(old_mouse, now_mouse, par_mouse_status);
		}

		return false;
	}	

	void draw(SDL_Renderer** render, SDL_Texture** texture, SDL_Surface** screen) override {
		if(is_visible) {
			//rect->draw(*render);

			colour_buttons->draw(render, texture, screen);
			tool_buttons->draw(render, texture, screen);
		}
	}

	void delete_all() {
		//delete_object()
		printf("Hello, world!\n");

		colour_buttons->delete_all();
		delete[] colour_buttons;
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

		colour_buttons->rect->set_center( colour_buttons->rect->get_center() - delta );
		colour_buttons->update_position_from_delta(delta);
	}

	void tick(const double delta_time) override {
		tool_buttons->tick(delta_time);
		colour_buttons->tick(delta_time);
	}
};

#endif