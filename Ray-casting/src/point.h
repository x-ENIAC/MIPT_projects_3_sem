#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "colour.h"

#ifndef POINT_H
#define POINT_H

class Point {
  public:
  	double x;
  	double y;
  	double z;

  	Point(const Point& par_point) :
  		x ( par_point.x ),
  		y ( par_point.y ),
  		z ( par_point.z )
  	{}

  	Point(const double par_x, const double par_y, const double par_z) :
  		x ( par_x ),
  		y ( par_y ),
  		z ( par_z )
  	{}

  	Point(const double par_x, const double par_y) :
  		x ( par_x ),
  		y ( par_y ),
  		z (   0   )
  	{}

  	Point& operator=(const Point& point) {
  		x = point.x;
  		y = point.y;
  		z = point.z;

  		return *this;
  	}

  	Point& operator+=(const Point& point) {
  		x += point.x;
  		y += point.y;
  		z += point.z;

  		return *this;
  	}

  	Point& operator-=(const Point& point) {
  		x -= point.x;
  		y -= point.y;
  		z -= point.z;

  		return *this;
  	}  

  	Point& operator*=(const double coeff) {
  		x *= coeff;
  		y *= coeff;
  		z *= coeff;

  		return *this;
  	}   

  	Point& operator/=(const double coeff) {
  		x /= coeff;
  		y /= coeff;
  		z /= coeff;

  		return *this;
  	}     	 		
};

inline void draw_point(SDL_Renderer* render, const Point point, const Colour color) {
	SDL_SetRenderDrawColor(render, color.red, color.blue, color.green, color.alpha);
	SDL_RenderDrawPoint(render, point.x, point.y); 
}

#endif