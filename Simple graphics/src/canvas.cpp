#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "canvas.h"

void Canvas::draw_coordinate_axes(SDL_Renderer* render, const Colour lines_color) {
	draw_rectangle(render, x_upper_left_corner,         y_upper_left_corner, 
                 		   x_upper_left_corner + width, y_upper_left_corner + height, WHITE, true);

	Vector horizontal_line(x_upper_left_corner + INDENT,         SCREEN_HEIGHT - (y_upper_left_corner + height - 2 * INDENT), 
	    				   x_upper_left_corner + width - INDENT, SCREEN_HEIGHT - (y_upper_left_corner + height - 2 * INDENT), false);
 
	horizontal_line.draw_vector(render, lines_color, lines_color, -10, 10);	  

	Vector vertical_line(x_upper_left_corner + width / 2, SCREEN_HEIGHT - (y_upper_left_corner + height - INDENT),
	              	     x_upper_left_corner + width / 2, SCREEN_HEIGHT - (y_upper_left_corner + INDENT * 2), false);

	vertical_line.draw_vector(render, lines_color, lines_color, NINETY - 10, NINETY + 10);	  
}

void Canvas::draw_rectangle(SDL_Renderer* render, const int x_upper_left,   const int y_upper_left,
                         					      const int x_bottom_right, const int y_bottom_right,
                        					      const Colour color, bool need_fill) {

	if(!(need_rectangle_is_correct(x_upper_left, y_upper_left, x_bottom_right, y_bottom_right) && color <= WHITE))
	    return;

	SDL_SetRenderDrawColor(render, color.red, color.blue, color.green, color.alpha);

	SDL_Rect rectangle = {x_upper_left, y_upper_left, x_bottom_right - x_upper_left, y_bottom_right - y_upper_left};

	if(!need_fill)
	    SDL_RenderDrawRect(render, &rectangle);
	else
		SDL_RenderFillRect(render, &rectangle);
}

void Canvas::draw_line(SDL_Renderer* render, const int x_begin, const int y_begin,
    	                    				 const int x_end,   const int y_end,
	                        				 const Colour color) {

	if(!(color <= WHITE))
		return;

	SDL_SetRenderDrawColor(render, color.red, color.blue, color.green, color.alpha);
	SDL_RenderDrawLine(render, x_begin, y_begin, x_end, y_end);
}

void Canvas::draw_parabola(SDL_Renderer* render, const Colour color) {
	SDL_SetRenderDrawColor(render, color.red, color.blue, color.green, color.alpha);

	int real_x_right_corner = x_bottom_right_corner - INDENT;
	for(double draw_x = x_upper_left_corner + INDENT; draw_x <= real_x_right_corner; draw_x += DELTA) {
		double draw_y = y_center_coord_system - function((draw_x - x_center_coord_system) * x_scale) * y_scale;

		if(draw_y + INDENT > y_bottom_right_corner || draw_y - INDENT < y_upper_left_corner)
			continue;

	    SDL_RenderDrawPoint(render, draw_x, draw_y);    
	}
}

double Canvas::get_x_upper_left_corner() const {
  	return x_upper_left_corner;
}

double Canvas::get_y_upper_left_corner() const {
  	return y_upper_left_corner;
}

double Canvas::get_x_bottom_right_corner() const {
  	return x_bottom_right_corner;
}

double Canvas::get_y_bottom_right_corner() const {
  	return y_bottom_right_corner;
}  	  	  	

double Canvas::get_height() const {
  	return height;
}  	  	  	

double Canvas::get_width() const {
  	return width;
}

double Canvas::get_x_scale() const {
  	return x_scale;
}  	  	  	

double Canvas::get_y_scale() const {
  	return y_scale;
}  	

int Canvas::get_x_center_coord_system() const {
	return x_center_coord_system;
}

int Canvas::get_y_center_coord_system() const {
	return y_center_coord_system;
}

void Canvas::set_x_upper_left_corner(const double new_x_upper_left_corner) {
  	x_upper_left_corner = new_x_upper_left_corner;
}

void Canvas::set_y_upper_left_corner(const double new_y_upper_left_corner) {
  	y_upper_left_corner = new_y_upper_left_corner;
}

void Canvas::set_x_bottom_right_corner(const double new_x_bottom_right_corner) {
	x_bottom_right_corner = new_x_bottom_right_corner;
}

void Canvas::set_y_bottom_right_corner(const double new_y_bottom_right_corner) {
  	y_bottom_right_corner = new_y_bottom_right_corner;
}  	  	  	

void Canvas::set_height(const double new_height) {
  	height = new_height;
}  	  	  	

void Canvas::set_width(const double new_width) {
  	width = new_width;
}  	

void Canvas::set_x_scale(const double new_x_scale) {
  	x_scale = new_x_scale;
}  	  	  	

void Canvas::get_y_scale(const double new_y_scale) {
  	y_scale = new_y_scale;
}    	

bool Canvas::need_rectangle_is_correct(const int x_upper_left,   const int y_upper_left,
                         			   const int x_bottom_right, const int y_bottom_right) {
	if(x_upper_left <= x_bottom_right && x_bottom_right - x_upper_left <= width  &&
	   y_upper_left <= y_bottom_right && y_bottom_right - y_upper_left <= height)
		return true;
	return false;
}