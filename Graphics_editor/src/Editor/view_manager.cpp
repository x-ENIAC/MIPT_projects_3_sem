//class Pencil;
#include "view_manager.h"
#include "../GUI/animation_manager.h"
#include "painter_tools_and_plugins.h"
// #include "pencil.h"
#include "../app.h"

void View_manager::add_tool_manager() {
	painter_tools_and_plugins = new Painter_tools_and_plugins(Point{200, 500}, 150, 200);

	printf("\tLoad plugin of Mark\n");

	Plugin_tool* mark_plugin_tool = new Plugin_tool(WAY_TO_LOOCHEK_BRUSH, App::get_app()->get_app_interface());
	mark_plugin_tool->texture->add_new_texture(PATH_TO_PICTURE_WITH_PENCIL_1);
	painter_tools_and_plugins->plugin_manager->add_plugin(mark_plugin_tool);



	printf("\tLoad plugin of Max\n");

	Plugin_tool* max_plugin_tool = new Plugin_tool(WAY_TO_KCTF_SHARPY, App::get_app()->get_app_interface());
	max_plugin_tool->texture->add_new_texture(PATH_TO_PICTURE_WITH_SHARPY);
	painter_tools_and_plugins->plugin_manager->add_plugin(max_plugin_tool);	



	printf("\tLoad plugin of Max\n");

	Plugin_effect* max_plugin_effect = new Plugin_effect(WAY_TO_KCTF_NEGATIVE, App::get_app()->get_app_interface());
	max_plugin_effect->texture->add_new_texture(PATH_TO_PICTURE_WITH_EFFECT_1);
	painter_tools_and_plugins->plugin_manager->add_plugin(max_plugin_effect);	


	Tool_manager::get_tool_manager()->initialize(Point(200, 500), 150, 200, DARK_GREY_2, Widget_types::TOOL_MANAGER);

	fill_tool_manager();

	painter_tools_and_plugins->set_tool_manager(Tool_manager::get_tool_manager());

	add_view_object(painter_tools_and_plugins);

	painter_tools_and_plugins->update_positions();
}

void View_manager::add_manager_of_canvas_managers() {

	printf("Start initialize the manager_of_canvas_managers\n");
	manager_of_canvas_managers = new Manager_of_canvas_managers(CENTER_MANAGER_OF_CANVAS_MANAGERS,
																WIDTH_MANAGER_OF_CANVAS_MANAGERS_WIDGET,
																HEIGHT_MANAGER_OF_CANVAS_MANAGERS_WIDGET,
																LIGHT_LIGHT_GREY,
																false,
																&mouse_click_state,
																painter_tools_and_plugins);

	Point center_of_button_manager(rect->get_width() / 2.0, HEIGHT_CLOSE_BUTTON / 2.0), left_up_corner = rect->get_left_up_corner();
	center_of_button_manager += left_up_corner;

	panel_buttons_manager = new Button_manager(center_of_button_manager, rect->get_width(), HEIGHT_CLOSE_BUTTON,
												DARK_GREY_2, PATH_TO_PICTURE_WITH_TITLE_BUTTON);
	add_view_object(panel_buttons_manager);

	fill_panel_button_manager(left_up_corner, rect->get_width(), rect->get_height());
}

void View_manager::add_palette(Point* center_button) {
	Palette* palette = new Palette(rect->get_width() - WIDTH_CLOSE_BUTTON, HEIGHT_CLOSE_BUTTON * 3, &mouse_click_state);
	add_view_object(palette);

	Open_window_delegate* open_colour_palette_delegate = new Open_window_delegate(&(palette->is_visible));

	*center_button += Point(WIDTH_FILE_PANEL_BUTTON, 0);
	Button* colour_palette_button = new Button(open_colour_palette_delegate, *center_button, DARK_GREY, WIDTH_FILE_PANEL_BUTTON,
												HEIGHT_CLOSE_BUTTON, TEXT_PALETTE_1, BLACK);

	colour_palette_button->texture->add_new_texture(PATH_TO_PICTURE_WITH_PALETTE_BUTTON);
	panel_buttons_manager->add_view_object(colour_palette_button);
}

void View_manager::add_thickness_palette(Point* center_button) {
	Thickness_palette* thickness_palette = new Thickness_palette(10 * WIDTH_CLOSE_BUTTON, HEIGHT_CLOSE_BUTTON * 3, &mouse_click_state);
	add_view_object(thickness_palette);

	Open_window_delegate* open_thickness_palette_delegate = new Open_window_delegate(&(thickness_palette->is_visible));

	*center_button += Point(WIDTH_FILE_PANEL_BUTTON, 0);
	Button* thickness_palette_button = new Button(open_thickness_palette_delegate, *center_button, DARK_GREY, WIDTH_FILE_PANEL_BUTTON,
													HEIGHT_CLOSE_BUTTON, TEXT_PALETTE_2, BLACK);

	thickness_palette_button->texture->add_new_texture(PATH_TO_PICTURE_WITH_THICKNESS_BUTTON);
	panel_buttons_manager->add_view_object(thickness_palette_button);	
}

void View_manager::add_slider() {
	Slider_manager* slider_manager = new Slider_manager(Point(300, 100), 10, 0, 100, &mouse_click_state);
	printf("maybe here??? %d\n", count_of_view_objects);
	add_view_object(slider_manager);
	printf("or here........\n");
}

void View_manager::add_spline(Point* center_button) {
	Chart* chart = new Chart(Point(600, 300), 255, 255, WHITE, manager_of_canvas_managers, false, &mouse_click_state);
	add_view_object(chart);	

	*center_button += Point(WIDTH_FILE_PANEL_BUTTON, 0);

	Open_window_delegate* open_spline_delegate = new Open_window_delegate(&(chart->is_visible));

	Button* spline_panel_button = new Button(open_spline_delegate, *center_button, DARK_GREY, WIDTH_FILE_PANEL_BUTTON,
												HEIGHT_CLOSE_BUTTON, TEXT_SPLINE, BLACK);

	spline_panel_button->texture->add_new_texture(PATH_TO_PICTURE_WITH_SPLINE_BUTTON);
	panel_buttons_manager->add_view_object(spline_panel_button);
}

void View_manager::add_canvases(Point* center_button) {
	*center_button += Point(WIDTH_FILE_PANEL_BUTTON, 0);

	Open_window_delegate* open_canvases_delegate = new Open_window_delegate(&(manager_of_canvas_managers->is_visible));

	Button* canvas_panel_button = new Button(open_canvases_delegate, *center_button, DARK_GREY, WIDTH_FILE_PANEL_BUTTON, HEIGHT_CLOSE_BUTTON,
										   TEXT_CANVASES, BLACK);
	canvas_panel_button->texture->add_new_texture(PATH_TO_PICTURE_WITH_CANVAS_BUTTON);
	panel_buttons_manager->add_view_object(canvas_panel_button);	
}



void View_manager::fill_panel_button_manager(Point left_up_corner, const double par_width, const double par_height) {
	Point center_button(WIDTH_FILE_PANEL_BUTTON / 2.0, HEIGHT_CLOSE_BUTTON / 2.0);
	center_button += left_up_corner;

	Open_panel_delegate* open_panel_delegate = new Open_panel_delegate;

	Button* file_panel_button = new Button(open_panel_delegate, center_button, DARK_GREY, WIDTH_FILE_PANEL_BUTTON, HEIGHT_CLOSE_BUTTON,
										   TEXT_FILE, BLACK);
	file_panel_button->texture->add_new_texture(PATH_TO_PICTURE_WITH_FILE_BUTTON);
	panel_buttons_manager->add_view_object(file_panel_button);



	Create_new_canvas_delegate* create_new_canvas_delegate = new Create_new_canvas_delegate(manager_of_canvas_managers);        

	center_button += Point(WIDTH_FILE_PANEL_BUTTON, 0);
	Button* edit_panel_button = new Button(create_new_canvas_delegate, center_button, DARK_GREY, WIDTH_FILE_PANEL_BUTTON, HEIGHT_CLOSE_BUTTON,
										  TEXT_NEW, BLACK);
	//printf("before add NEW %s\n", PATH_TO_PICTURE_WITH_NEW_BUTTON);
	edit_panel_button->texture->add_new_texture(PATH_TO_PICTURE_WITH_NEW_BUTTON);
	panel_buttons_manager->add_view_object(edit_panel_button);




	center_button += Point(WIDTH_FILE_PANEL_BUTTON, 0);
	Button* help_panel_button = new Button(open_panel_delegate, center_button, DARK_GREY, WIDTH_FILE_PANEL_BUTTON, HEIGHT_CLOSE_BUTTON,
										   TEXT_HELP, BLACK);
	help_panel_button->texture->add_new_texture(PATH_TO_PICTURE_WITH_HELP_BUTTON);
	panel_buttons_manager->add_view_object(help_panel_button);	
}

void View_manager::fill_tool_manager() {
	Point center = Tool_manager::get_tool_manager()->rect->get_left_up_corner();
	center += Point(30, 30);

	Pencil* pencil = new Pencil(center, Tool_manager::get_tool_manager()->get_ptr_to_pen_colour(), Widget_types::TOOL, PATH_TO_PICTURE_WITH_PENCIL);
	pencil->texture->add_new_texture(PATH_TO_PICTURE_WITH_PENCIL);
	Tool_manager::get_tool_manager()->add_tool(pencil);



	// printf("\tLoad plugin of Mark\n");

	// center += Point(0, 60);

	// Plugin_tool* mark_plugin_tool = new Plugin_tool(WAY_TO_LOOCHEK_BRUSH, App::get_app()->get_app_interface());
	// mark_plugin_tool->texture->add_new_texture(PATH_TO_PICTURE_WITH_PENCIL_1);
	// App::get_app()->get_plugin_manager()->add_plugin(mark_plugin_tool);


	// printf("\tLoad plugin of Max\n");

	// center += Point(60, -60);

	// Plugin_tool* max_plugin_tool = new Plugin_tool(WAY_TO_KCTF_SHARPY, App::get_app()->get_app_interface());
	// max_plugin_tool->texture->add_new_texture(PATH_TO_PICTURE_WITH_SHARPY);
	// App::get_app()->get_plugin_manager()->add_plugin(max_plugin_tool);	
}