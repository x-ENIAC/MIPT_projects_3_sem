#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "main.h"
#include <math.h>
#include "colour.h"
#include "canvas.h"


#define _USE_MATH_DEFINES

const int    VECTOR_THICKNESS = 30;
const double THICKNESS_DELTA  = 0.1;

const double ZERO  				 =   0.0;
const double NINETY				 =  90.0;
const double ONE_HUNDRER_EIGHTY  = 180.0;
const double TWO_HUNDRED_SEVENTY = 270.0;
const double THREE_HUNDRED_SIXTY = 360.0;

const double DOUBLE_SUBTRACTION_DELTA          = 0.0001;
const int    LENGTH_COEFFICIENT_OF_ARROW_WINGS =     50;
const double ANGLE_OF_ARROW_WINGS              =     20;

class Vector {
  public:

  	Vector() :
  		x_begin 	 ( 0 ),
  		y_begin 	 ( 0 ),
  		x_end   	 ( 0 ),
  		y_end   	 ( 0 ),
  		angle        ( 0 ),
  		is_need_bold ( 0 )
  	{}

  	Vector(const double par_x_begin, const double par_y_begin, const double par_x_end, const double par_y_end, const bool par_is_need_bold) :
  		x_begin 	 ( par_x_begin ),
  		y_begin 	 ( par_y_begin ),
  		x_end   	 (  par_x_end  ),
  		y_end   	 (  par_y_end  ),
  		is_need_bold ( par_is_need_bold )
  	{
  		calculate_angle();
  		update_angle();
  	}

  	Vector(const double par_x_begin, const double par_y_begin, const double par_angle, const bool par_is_need_bold) :
  		x_begin      ( par_x_begin ),
  		y_begin      ( par_y_begin ),
  		angle        ( par_angle ),
  		x_end        (  x_begin + LENGTH_COEFFICIENT_OF_ARROW_WINGS * cos(par_angle * M_PI / ONE_HUNDRER_EIGHTY)  ),
  		y_end        (  y_begin + LENGTH_COEFFICIENT_OF_ARROW_WINGS * sin(par_angle * M_PI / ONE_HUNDRER_EIGHTY)  ),
  		is_need_bold ( par_is_need_bold )
  	{
  		update_angle();
  	}  	

  	~Vector() {
  		x_begin 	 = y_begin = 0;
  		x_end 		 = y_end   = 0;
  		angle 		 = 0;
  		is_need_bold = false;
  	}

  	Vector& operator=(const Vector& vector);

  	void operator+=(const Vector& vector);

  	void from_pixels_to_algebraic(const Canvas canvas);

  	void update_angle();

  	void calculate_angle();

    double get_length_vector();	

    void get_perpendicular();

  	void draw_vector(SDL_Renderer* render, const Colour line_color, const Colour wings_color, const double  first_wings_angle,
  																				              const double second_wings_angle);

	void draw_arrow_wing(SDL_Renderer* render, const Colour color, const double need_angle);	

	void draw_line(SDL_Renderer* render, const Colour color);	

	void rotate_clockwize_vector(const double delta_angle);

	void move_vector_to_point(const double x_point, const double y_point);

  	double get_x_begin();

  	double get_y_begin();

  	double get_x_end();

  	double get_y_end();

  	double get_angle();

  	void set_x_begin(const double new_x_begin);

  	void set_y_begin(const double new_y_begin);

  	void set_x_end(const double new_x_end);

  	void set_y_end(const double new_y_end);

  private:

  	double x_begin, y_begin;
  	double x_end,   y_end;

	double angle;
  	bool is_need_bold;
};

#endif