#include "manager_of_canvas_managers.h"

void Manager_of_canvas_managers::add_canvas_manager(Canvas_manager* new_canvas_manager) {
	canvas_managers[count_of_canvas_managers] = new_canvas_manager;
	++count_of_canvas_managers;

	++widget_types[(int)Widget_types::CANVAS_MANAGER];

	for(int i = count_of_canvas_managers - 1; i >= 0; --i) {

		if(canvas_managers[i]->is_active && who_is_active != i)
			canvas_managers[i]->is_active = false;
	}
}

void Manager_of_canvas_managers::fill_button_manager(Point left_up_corner, const double par_width, const double par_height,
													 Mouse_click_state* par_mouse_click_state) {

	//--------------- add close button ---------------------------

	Point center_button(par_width - WIDTH_CLOSE_BUTTON / 2.0,  HEIGHT_CLOSE_BUTTON / 2.0);
	center_button += left_up_corner;

	Button* close_button = new Button(NULL, center_button, BLACK, WIDTH_CLOSE_BUTTON, HEIGHT_CLOSE_BUTTON,
									  "x", BLACK);
	close_button->texture->add_new_texture(PATH_TO_PICTURE_WITH_BLACK_CLOSE_BUTTON);

	Close_delegate*  close_delegate = new Close_delegate(close_button->texture, par_mouse_click_state, &is_alive);
	close_button->delegate = close_delegate;

	button_manager->add_view_object(close_button);

	//--------------- add roll up button ---------------------------
	Roll_up_delegate*  roll_up_delegate = new Roll_up_delegate(par_mouse_click_state, &is_visible, &is_active);

	center_button = Point(WIDTH_CLOSE_BUTTON / 2.0, HEIGHT_CLOSE_BUTTON / 2.0);
	center_button += left_up_corner;

	Button* roll_up_button = new Button(roll_up_delegate, center_button, BLACK, WIDTH_CLOSE_BUTTON, HEIGHT_CLOSE_BUTTON,
										"-", BLACK, PATH_TO_PICTURE_WITH_ROLL_UP_BUTTON);
	roll_up_button->texture->add_new_texture(PATH_TO_PICTURE_WITH_ROLL_UP_BUTTON);
	button_manager->add_view_object(roll_up_button);

	//--------------- add title button ---------------------------
	Title_delegate*  title_delegate = new Title_delegate(this);

	center_button = Point(par_width / 2.0, HEIGHT_CLOSE_BUTTON / 2.0);
	center_button += left_up_corner;

	Button* title_button = new Button(title_delegate, center_button, DARK_GREY, par_width - 2 * WIDTH_CLOSE_BUTTON, HEIGHT_CLOSE_BUTTON,
									  "Title", BLACK, PATH_TO_PICTURE_WITH_TITLE_BUTTON);
	title_button->texture->add_new_texture(PATH_TO_PICTURE_WITH_TITLE_BUTTON);
	button_manager->add_view_object(title_button);
}

void Manager_of_canvas_managers::add_new_canvas_manager() {

	Canvas_manager* new_canvas_manager = new Canvas_manager(any_canvas_center, any_canvas_width, any_canvas_height,
															WHITE, pencil, false, mouse_click_state, widget_types[(int)Widget_types::TABS]);

	++widget_types[(int)Widget_types::TABS];
	set_new_active_object(count_of_canvas_managers);

	add_canvas_manager(new_canvas_manager);
	/*printf("is_active\n");
	for(size_t i = 0; i < count_of_canvas_managers; ++i)
		printf("%d ", canvas_managers[i]->is_active);
	printf("\n\n");*/

	//printf("end add_canvas_manager\n");
}

void Manager_of_canvas_managers::set_new_active_object(const int new_active) {
	if(who_is_active != -1) {
		canvas_managers[who_is_active]->is_active = false;
		canvas_managers[who_is_active]->tab->button_manager->buttons[0]->texture->update_texture(PATH_TO_PICTURE_WITH_GREY_1_BUTTON);
		canvas_managers[who_is_active]->tab->button_manager->buttons[1]->texture->update_texture(PATH_TO_PICTURE_WITH_GREY_1_CLOSE_BUTTON);
	}

	who_is_active = new_active;

	if(who_is_active != -1) {
		canvas_managers[who_is_active]->is_active = true;
		canvas_managers[who_is_active]->tab->button_manager->buttons[0]->texture->update_texture(PATH_TO_PICTURE_WITH_GREY_2_BUTTON);
		canvas_managers[who_is_active]->tab->button_manager->buttons[1]->texture->update_texture(PATH_TO_PICTURE_WITH_GREY_2_CLOSE_BUTTON);
	}
}

void Manager_of_canvas_managers::draw_tabs_area(SDL_Renderer** render, SDL_Texture** texture, SDL_Surface** screen) {
	Point rect_center(button_manager->rect->get_center());
	rect_center += Point(0, HEIGHT_CLOSE_BUTTON / 2.0 + HEIGHT_TABS_BUTTON / 2.0);

	Rectangle tab_rect(rect_center, button_manager->rect->get_width(), button_manager->rect->get_height(), LIGHT_LIGHT_GREY, false);

	tab_rect.draw(*render);
}

void Manager_of_canvas_managers::find_not_alive() {
	for(size_t i = 0; i < count_of_canvas_managers; ++i) {
		if(!(canvas_managers[i]->is_alive)) {

			--widget_types[(int)Widget_types::CANVAS_MANAGER];
			--widget_types[(int)Widget_types::TABS];

			//canvas_managers[i]->is_visible = false;
			printf("i = %ld\n", i);

			update_tabs_offset(i);
			array_shift(i);

			--count_of_canvas_managers;
		}
	}
}

void Manager_of_canvas_managers::array_shift(const size_t pos) {
	for(size_t i = pos + 1; i < count_of_canvas_managers; ++i)
		canvas_managers[i - 1] = canvas_managers[i];
}

void Manager_of_canvas_managers::update_tabs_offset(const size_t pos) {
	//printf("pos %ld, count %ld. Center of deletes tab (%lg, %lg)\n", pos, count_of_canvas_managers, canvas_managers[pos]->tab->rect->get_center().x,
	//                                                                                                canvas_managers[pos]->tab->rect->get_center().y);

	for(size_t i = pos + 1; i < count_of_canvas_managers; ++i) {
		Point before_point(canvas_managers[i]->tab->rect->get_center());

		//printf("(%lg, %lg) -> ", before_point.x, before_point.y);
		before_point -= Point((WIDTH_TABS_BUTTON + WIDTH_CLOSE_BUTTON), 0);

		canvas_managers[i]->tab->update_tabs_offset(before_point);
		canvas_managers[i]->tab->update_tabs_number(i - 1);

		//printf(" %lg, %lg\n", canvas_managers[i]->tab->rect->center.x, canvas_managers[i]->tab->rect->center.y);
	}
}

void Manager_of_canvas_managers::update_canvas_manager_position(const double mouse_x, const double mouse_y) {
	Point mouse(mouse_x, mouse_y);
	Point delta(button_manager->rect->get_center());
	delta -= mouse;

	any_canvas_center -= delta;

	//center -= delta;
	rect->set_center(rect->get_center() - delta);

	button_manager->rect->set_center(mouse);
	button_manager->update_position_from_delta(delta);

	for(size_t i = 0; i < count_of_canvas_managers; ++i)
		canvas_managers[i]->update_position_from_delta(delta);
}

void Manager_of_canvas_managers::tick(const double delta_time) {
	for(size_t i = 0; i < count_of_canvas_managers; ++i) {
		if(!(canvas_managers[i]->is_alive)) {
			printf("Delete!!\n");
		}

		canvas_managers[i]->tick(delta_time);
	}
}