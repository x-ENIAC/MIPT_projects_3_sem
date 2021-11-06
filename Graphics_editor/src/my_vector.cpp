#include "my_vector.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

double Vector::get_length_vector() const {
	return sqrt( (point_end.x - point_begin.x) * (point_end.x - point_begin.x) + 
				 (point_end.y - point_begin.y) * (point_end.y - point_begin.y) );
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

double Vector::get_cos_of_angle_between_vectors(const Vector& vector) const {
	double length_this = get_length_vector(), length_vector = vector.get_length_vector();

	if(fabs(length_vector) < DOUBLE_SUBTRACTION_DELTA || fabs(length_this) < DOUBLE_SUBTRACTION_DELTA)
		return 0.;

	return (*this * vector) / length_vector / length_this;

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

inline double min(const double first, const double second) {
	return (first < second ? first : second);
}

double operator*(const Vector& first_vector, const Vector& second_vector) {
	return (first_vector.get_x_end() - first_vector.get_x_begin()) * (second_vector.get_x_end() - second_vector.get_x_begin()) + 
		   (first_vector.get_y_end() - first_vector.get_y_begin()) * (second_vector.get_y_end() - second_vector.get_y_begin());
}

double distance_from_point_to_segment(Point point, Point segment_begin, Point segment_end) {
	Vector to_point_from_begin(segment_begin, point), segment_1(segment_begin, segment_end);
	Vector to_point_from_end  (segment_end,   point), segment_2(segment_end, segment_begin);

	double first_scalar  = to_point_from_begin.scalar_multiplication(segment_1);
	double second_scalar = to_point_from_end.scalar_multiplication(segment_2);

	if(first_scalar < 0 || second_scalar < 0) {
		return min(sqrt(get_distance_from_points(point, segment_begin)),
				   sqrt(get_distance_from_points(point, segment_end)));
	}

	return get_length_perpendicular(point, segment_begin, segment_end);
}

inline double get_distance_from_points(Point first, Point second) {
	return (first.x - second.x) * (first.x - second.x) + (first.y - second.y) * (first.y - second.y);
}

double get_length_perpendicular(Point point, Point segment_begin, Point segment_end) {
	return fabs( ((segment_end.x - segment_begin.x) * (point.y - segment_begin.y) -
				  (segment_end.y - segment_begin.y) * (point.x - segment_begin.x)) /
				   sqrt(get_distance_from_points(segment_begin, segment_end)) );
}