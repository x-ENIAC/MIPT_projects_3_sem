#include "tool_manager.h"

Tool_manager* Tool_manager::tool_manager = 0;

void Tool_manager::initialize(const Point par_center, const double par_width, const double par_height,
								const Colour par_color, const Widget_types par_widget_types, const char par_path_to_picture[]) {

	printf("Start initialize the tool manager\n");

	rect->set_center(par_center);

	rect->set_width(par_width);
	rect->set_height(par_height);

	rect->set_colour(par_color);
	yourself_type = par_widget_types;
	strcpy(texture->path_to_picture, par_path_to_picture);
}

Tool_manager* Tool_manager::get_tool_manager() {
	if(!tool_manager)
		tool_manager = new Tool_manager();
	return tool_manager;
}

Tool* Tool_manager::get_active_tool() {
	return active_tool;
}

Colour Tool_manager::get_pen_colour() {
	return pen_colour;
}

void Tool_manager::set_pen_colour(const Colour new_color) {
	pen_colour = new_color;
}

Colour* Tool_manager::get_ptr_to_pen_colour() {
	return &pen_colour;
}

float Tool_manager::get_pen_size() {
	return pen_size;
}

void Tool_manager::set_pen_size(float new_size) {
	pen_size = new_size;
}
