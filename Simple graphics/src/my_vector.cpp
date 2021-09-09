#include "my_vector.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void Vector::update_angle()  {
	if(angle >= THREE_HUNDRED_SIXTY || angle < ZERO)
		angle = ((long long)angle + (long long)THREE_HUNDRED_SIXTY) % (int)THREE_HUNDRED_SIXTY;
}

void Vector::calculate_angle() {
	if(x_begin == x_end)
		angle = 0;
	else
		angle = atan(((y_end - y_begin)) / (x_end - x_begin)) * ONE_HUNDRER_EIGHTY / M_PI;
}

double Vector::get_length_vector() {
	return sqrt( (x_end - x_begin) * (x_end - x_begin) + (y_end - y_begin) * (y_end - y_begin) );
}  

void Vector::draw_vector(SDL_Renderer* render, const Colour line_color, const Colour wings_color, const double  first_wings_angle,
  																				                  const double second_wings_angle)  {
  	draw_line(render, line_color);
  	draw_arrow_wing(render, wings_color,  first_wings_angle);
  	draw_arrow_wing(render, wings_color, second_wings_angle);
}

void Vector::draw_arrow_wing(SDL_Renderer* render, const Colour color, const double need_angle) {   // ------------
	double length_vector = get_length_vector();														//     / ?
																									//	  /
	Vector arrow_wing(x_end, y_end, (need_angle + angle) - 180, is_need_bold);						//   / 
	arrow_wing.update_angle();																		//  / need_angle + angle
	arrow_wing.draw_line(render, color);															// ---------
}  

void Vector::draw_line(SDL_Renderer* render, const Colour color) {
	if(!(color <= WHITE))
	    return;

	double copy_x_begin = x_begin, copy_y_begin = y_begin;
	double copy_x_end   = x_end,   copy_y_end   = y_end;

	for(int count_line = 0; count_line < VECTOR_THICKNESS; ++count_line) {
		SDL_SetRenderDrawColor(render, color.red, color.blue, color.green, color.alpha);
		SDL_RenderDrawLine(render, copy_x_begin, SCREEN_HEIGHT - copy_y_begin, copy_x_end, SCREEN_HEIGHT - copy_y_end);

		if(!is_need_bold)
			break;

		copy_y_begin += THICKNESS_DELTA;
		copy_y_end   += THICKNESS_DELTA;
	}
}  

void Vector::rotate_clockwize_vector(const double delta_angle) {
	double length_vector = get_length_vector();

	angle += delta_angle;
	update_angle();
		
	if(fabs(angle - ZERO)                < DOUBLE_SUBTRACTION_DELTA || fabs(angle - THREE_HUNDRED_SIXTY) < DOUBLE_SUBTRACTION_DELTA) {
		x_end = x_begin + length_vector;
		y_end = y_begin;
	}
	else
	if(fabs(angle - NINETY)              < DOUBLE_SUBTRACTION_DELTA) {
		x_end = x_begin;
		y_end = y_begin + length_vector;
	}
	else
	if(fabs(angle - ONE_HUNDRER_EIGHTY)  < DOUBLE_SUBTRACTION_DELTA) {
		x_end = x_begin - length_vector;
		y_end = y_begin;
	}
	else
	if(fabs(angle - TWO_HUNDRED_SEVENTY) < DOUBLE_SUBTRACTION_DELTA) {
		x_end = x_begin;
		y_end = y_begin - length_vector;
	}
	else {
		x_end = x_begin + length_vector * cos(angle  * M_PI / ONE_HUNDRER_EIGHTY);
		y_end = y_begin + length_vector * sin(angle  * M_PI / ONE_HUNDRER_EIGHTY);
	}
}

void Vector::move_vector_to_point(const double x_point, const double y_point) {
	x_end += x_point - x_begin;
	y_end += y_point - y_begin;

	x_begin = x_point;
	y_begin = y_point;
}

double Vector::get_x_begin() {
  	return x_begin;
}

double Vector::get_y_begin() {
  	return y_begin;
}

double Vector::get_x_end() {
  	return x_end;
}

double Vector::get_y_end() {
  	return y_end;
} 

double Vector::get_angle() {
	return angle;
}

void Vector::set_x_begin(const double new_x_begin) {
  	x_begin = new_x_begin;
}

void Vector::set_y_begin(const double new_y_begin) {
  	y_begin = new_y_begin;
}

void Vector::set_x_end(const double new_x_end) {
  	x_end = new_x_end;
}

void Vector::set_y_end(const double new_y_end) {
  	y_end = new_y_end;
}

void Vector::operator=(const Vector& vector) {
	x_begin = vector.x_begin;
	y_begin = vector.y_begin;

	x_end = vector.x_end;
	y_end = vector.y_end;

	calculate_angle();
}

void Vector::operator+=(const Vector& vector) {
	Vector copy_vector = vector;
	copy_vector.move_vector_to_point(x_end, y_end);

	x_end = copy_vector.x_end;
	y_end = copy_vector.y_end;

	calculate_angle();
}

void Vector::from_pixels_to_algebraic(const Canvas canvas) {
  	x_end += canvas.get_x_center_coord_system() - x_begin;
  	y_end += canvas.get_y_center_coord_system() - y_begin;

  	x_begin = canvas.get_x_center_coord_system();
  	y_begin = canvas.get_y_center_coord_system();
}