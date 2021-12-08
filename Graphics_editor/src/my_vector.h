#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include "colour.h"
#include "point.h"

#define _USE_MATH_DEFINES

const int    VECTOR_THICKNESS = 30;
const double THICKNESS_DELTA  = 0.1;

const double ZERO  				 =   0.0;
const double NINETY				 =  90.0;
const double ONE_HUNDRER_EIGHTY  = 180.0;
const double TWO_HUNDRED_SEVENTY = 270.0;
const double THREE_HUNDRED_SIXTY = 360.0;

const double DOUBLE_SUBTRACTION_DELTA = 0.000001;

class Vector {
  public:

	Vector() {
		point_begin = Point(0., 0.);
		point_end   = Point(0., 0.);
	}

	Vector(const Point par_point_begin, const Point par_point_end) {
		point_begin = par_point_begin ;
		point_end 	= par_point_end;
	}


	Vector& operator=(const Vector& vector);

	Vector& operator+=(const Vector& vector);

	Vector& operator-=(const Vector& vector);

	Vector& operator*=(const double coeff);

	Vector& operator/=(const double coeff);

	friend double operator*(const Vector& first_vector, const Vector& second_vector);

	double scalar_multiplication(const Vector& vector) const {

		return (point_end.x - point_begin.x) * (vector.get_point_end().x - vector.get_point_begin().x) + 
			   (point_end.y - point_begin.y) * (vector.get_point_end().y - vector.get_point_begin().y);
	}  	
	

	Vector reflect_vector(const Vector& normal_vector) {
		// this == light

		double length_this = this->get_length_vector();
		double length_normal_vector = normal_vector.get_length_vector();

		double scalar_mult = this->scalar_multiplication(normal_vector);
		double cos_angle = scalar_mult / length_this / length_normal_vector;

		if(cos_angle == 0)
		return *this;

		Vector copy_normal_vector(normal_vector);
		copy_normal_vector *= (1.0 / length_normal_vector);

		Vector copy_this(*this);
		copy_this *= (1.0 / cos_angle / length_this);

		Point change = copy_normal_vector.get_point_end();
		change -= copy_this.get_point_end();

		this->point_end = copy_normal_vector.get_point_end();
		this->point_end += change;

		return *this;
	}

	inline void draw(SDL_Renderer* render, Colour color) {
		SDL_SetRenderDrawColor(render, color.red, color.green, color.blue, 20);
		SDL_RenderDrawLine(render, point_begin.x, point_begin.y, point_end.x, point_end.y);
	}

	double get_length_vector() const;

	void rotate_clockwize_vector(const double delta_angle);

	double get_cos_of_angle_between_vectors(const Vector& vector) const;

	double get_x_begin() const;

	double get_y_begin() const;

	double get_x_end() const;

	double get_y_end() const;

	double get_angle() const;

	void set_x_begin(const double new_x_begin);

	void set_y_begin(const double new_y_begin);

	void set_x_end(const double new_x_end);

	void set_y_end(const double new_y_end);

	Point get_point_begin() const {
		return point_begin;
	}

	Point get_point_end() const {
		return point_end;
	}

	void set_point_begin(const Point new_point_begin) {
		point_begin = new_point_begin;
	}

	void set_point_end(const Point new_point_end) {
		point_end = new_point_end;
	}

	void swap_ends() {
		Point tmp = point_begin;
		point_begin = point_end;
		point_end = tmp;
	}

	int get_y_from_x(const int x) {
		if(point_end.x == point_begin.x) {
			return x - point_begin.x + point_begin.y;
		} else {
			return (point_end.y - point_begin.y) * (x - point_begin.x) / (point_end.x - point_begin.x) + point_begin.y;
		}
	}

  private:

	Point point_begin;
	Point point_end;
};


bool intersection_of_segments(Point first_begin, Point first_end, Point second_begin, Point second_end);

bool segment_into_segment(Point first_begin, Point first_end, Point second_begin, Point second_end);

double distance_from_point_to_segment(Point point, Point segment_begin, Point segment_end);

inline double get_distance_from_points(Point first, Point second);

double get_length_perpendicular(Point point, Point segment_begin, Point segment_end);

#endif