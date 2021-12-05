#include "view_manager.h"

void View_manager::fill_panel_button_manager(Point left_up_corner, const double par_width, const double par_height) {
	Point center_button(WIDTH_FILE_PANEL_BUTTON / 2.0, HEIGHT_CLOSE_BUTTON / 2.0);
	center_button += left_up_corner;

	Open_panel_delegate* open_panel_delegate = new Open_panel_delegate;

	Button* file_panel_button = new Button(open_panel_delegate, center_button, DARK_GREY, WIDTH_FILE_PANEL_BUTTON, HEIGHT_CLOSE_BUTTON,
										   "File", BLACK);
	file_panel_button->texture->add_new_texture(PATH_TO_PICTURE_WITH_FILE_BUTTON);
	panel_buttons_manager->add_view_object(file_panel_button);

	Create_new_canvas_delegate* create_new_canvas_delegate = new Create_new_canvas_delegate(manager_of_canvas_managers);        

	center_button += Point(WIDTH_FILE_PANEL_BUTTON, 0);
	Button* edit_panel_button = new Button(create_new_canvas_delegate, center_button, DARK_GREY, WIDTH_FILE_PANEL_BUTTON, HEIGHT_CLOSE_BUTTON,
										   "New", BLACK);
	//printf("before add NEW %s\n", PATH_TO_PICTURE_WITH_NEW_BUTTON);
	edit_panel_button->texture->add_new_texture(PATH_TO_PICTURE_WITH_NEW_BUTTON);
	panel_buttons_manager->add_view_object(edit_panel_button);


	center_button += Point(WIDTH_FILE_PANEL_BUTTON, 0);
	Button* help_panel_button = new Button(open_panel_delegate, center_button, DARK_GREY, WIDTH_FILE_PANEL_BUTTON, HEIGHT_CLOSE_BUTTON,
										   "Help", BLACK);
	help_panel_button->texture->add_new_texture(PATH_TO_PICTURE_WITH_HELP_BUTTON);
	panel_buttons_manager->add_view_object(help_panel_button);	
}

void View_manager::fill_tool_manager() {
	Point left_corner = tool_manager->rect->get_left_up_corner();

	pencil = new Pencil(left_corner, 50, 50, Widget_types::TOOL, PATH_TO_PICTURE_WITH_PENCIL);
	pencil->texture->add_new_texture(PATH_TO_PICTURE_WITH_PENCIL);
	tool_manager->add_tool(pencil);
}