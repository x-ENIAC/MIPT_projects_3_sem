#include "my_vector.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

double Vector::get_length_vector() const {
	return sqrt( (point_end.x - point_begin.x) * (point_end.x - point_begin.x) + 
				 (point_end.y - point_begin.y) * (point_end.y - point_begin.y) +
				 (point_end.z - point_begin.z) * (point_end.z - point_begin.z) );
}  

void Vector::rotate_clockwize_vector(const double delta_angle) {
	point_end.x -= point_begin.x;
	point_end.y -= point_begin.y;

	double copy_x_end = point_end.x, copy_y_end = point_end.y;

	copy_x_end = point_end.x * cos(delta_angle  * M_PI / ONE_HUNDRER_EIGHTY) - point_end.y * sin(delta_angle  * M_PI / ONE_HUNDRER_EIGHTY);
	copy_y_end = point_end.x * sin(delta_angle  * M_PI / ONE_HUNDRER_EIGHTY) + point_end.y * cos(delta_angle  * M_PI / ONE_HUNDRER_EIGHTY);

	point_end.x = copy_x_end;
	point_end.y = copy_y_end;

	point_end.x += point_begin.x;
	point_end.y += point_begin.y;
}

double Vector::get_x_begin() const {
  	return point_begin.x;
}

double Vector::get_y_begin() const {
  	return point_begin.y;
}

double Vector::get_x_end() const {
  	return point_end.x;
}

double Vector::get_y_end() const {
  	return point_end.y;
} 

void Vector::set_x_begin(const double new_x_begin) {
  	point_begin.x = new_x_begin;
}

void Vector::set_y_begin(const double new_y_begin) {
  	point_begin.y = new_y_begin;
}

void Vector::set_x_end(const double new_x_end) {
  	point_end.x = new_x_end;
}

void Vector::set_y_end(const double new_y_end) {
  	point_end.y = new_y_end;
}

Vector& Vector::operator=(const Vector& vector) {
	point_begin = vector.get_point_begin();
	point_end   = vector.get_point_end();

	return *this;
}

Vector& Vector::operator+=(const Vector& vector) {
	point_begin += vector.get_point_begin();
	point_end   += vector.get_point_end();

	return *this;
}

Vector& Vector::operator-=(const Vector& vector) {
	point_begin -= vector.get_point_begin();
	point_end   -= vector.get_point_end();

	return *this;
}

Vector& Vector::operator*=(const double coeff) {
	Point copy_end_point = point_end;
	copy_end_point -= point_begin;

	copy_end_point *= coeff;

	point_end = point_begin;
	point_end += copy_end_point;

	return *this;
}

Vector& Vector::operator/=(const double coeff) {
	Point copy_end_point = point_end;
	copy_end_point -= point_begin;

	copy_end_point /= coeff;

	point_end = point_begin;
	point_end += copy_end_point;

	return *this;
}


/*double operator*(const Vector& first_vector, const Vector& second_vector) {
	return (first_vector.get_x_end() - first_vector.get_x_begin()) * (second_vector.get_x_end() - second_vector.get_x_begin()) + 
		   (first_vector.get_y_end() - first_vector.get_y_begin()) * (second_vector.get_y_end() - second_vector.get_y_begin());
}
*/