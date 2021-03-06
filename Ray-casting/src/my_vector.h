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

const double DOUBLE_SUBTRACTION_DELTA          = 0.000001;

class Vector {
  public:

  	Vector(const Point par_point_begin, const Point par_point_end) :
  		point_begin  ( par_point_begin ),
  		point_end 	 ( par_point_end )
  	{}


  	Vector& operator=(const Vector& vector);

  	Vector& operator+=(const Vector& vector);

  	Vector& operator-=(const Vector& vector);

  	Vector& operator*=(const double coeff);

  	Vector& operator/=(const double coeff);

  	double scalar_multiplication(const Vector* vector) const {

  		return (point_end.x - point_begin.x) * (vector->get_point_end().x - vector->get_point_begin().x) + 
  			   (point_end.y - point_begin.y) * (vector->get_point_end().y - vector->get_point_begin().y) + 
  			   (point_end.z - point_begin.z) * (vector->get_point_end().z - vector->get_point_begin().z);
  	}  	
	

	Vector reflect_vector(const Vector* normal_vector) {
		// this == light

		double length_this = this->get_length_vector();
		double length_normal_vector = normal_vector->get_length_vector();

		double scalar_mult = this->scalar_multiplication(normal_vector);
		double cos_angle = scalar_mult / length_this / length_normal_vector;

		if(cos_angle == 0)
		return *this;

		Vector copy_normal_vector(*normal_vector);
		copy_normal_vector *= (1.0 / length_normal_vector);

		Vector copy_this(*this);
		copy_this *= (1.0 / cos_angle / length_this);

		Point change = copy_normal_vector.get_point_end();
		change -= copy_this.get_point_end();

		this->point_end = copy_normal_vector.get_point_end();
		this->point_end += change;

		return *this;
	}
	
	/*Vector reflect_vector(Vector& normal_vector) {
		// this == light

		double length_this          = this->get_length_vector();
		double length_normal_vector = normal_vector.get_length_vector();

		double scalar_mult = this->scalar_multiplication(normal_vector);
		double cos_angle = scalar_mult / length_this / length_normal_vector;

		if(cos_angle == 0)
			return *this;

		Vector copy_normal_vector(normal_vector);
		copy_normal_vector *= (cos_angle / fabs(cos_angle) / length_normal_vector);

		Vector copy_this(*this);
		copy_this *= (1.0 / cos_angle / length_this);

		Vector change(copy_normal_vector);
		change -= copy_this;

		Point copy_change_begin = change.get_point_begin();
		Point copy_change_end   = change.get_point_end();

		copy_change_end  -= copy_change_begin;

		Vector copy_(Point(0, 0), copy_change_end);
		copy_ *= 2;	

		copy_.point_end += copy_change_begin;
		copy_.point_begin = copy_change_begin;

		return copy_;
  	}*/

  	/*friend double operator*(const Vector& first_vector, const Vector& second_vector);

  	void operator*=(const double coeff);*/

    double get_length_vector() const;	

	void rotate_clockwize_vector(const double delta_angle);

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

  private:

  	Point point_begin;
  	Point point_end;

  	double length_vector;
};

#endif