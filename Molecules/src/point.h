#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "colour.h"

#ifndef POINT_H
#define POINT_H

class Point {
  public:
  	double x;
  	double y;
  	Colour color;

  	Point() {
  		x = y = 0;
  		color = BLACK;
  	}

  	Point(const Point& par_point, const Colour par_color) {
  		x = par_point.x;
  		y = par_point.y;
  		color = par_color;
  	}

  	Point(const double par_x, const double par_y, const Colour par_color) {
  		x = par_x ;
  		y = par_y ;
  		color = par_color;
  	}

  	Point(const double par_x, const double par_y) {
  		x = par_x ;
  		y = par_y ;
  		color = BLACK;
  	}  	

	inline void draw_point(SDL_Renderer* render) {
		SDL_SetRenderDrawColor(render, color.red, color.blue, color.green, color.alpha);
		SDL_RenderDrawPoint(render, x, y); 
	}


  	Point& operator=(const Point& point) {
  		x = point.x;
  		y = point.y;
  		color = point.color;

  		return *this;
  	}

  	Point& operator+=(const Point& point) {
  		x += point.x;
  		y += point.y;

  		return *this;
  	}

  	Point& operator-=(const Point& point) {
  		x -= point.x;
  		y -= point.y;

  		return *this;
  	}  

  	Point& operator*=(const double coeff) {
  		x *= coeff;
  		y *= coeff;

  		return *this;
  	}   

  	Point& operator/=(const double coeff) {
  		x /= coeff;
  		y /= coeff;

  		return *this;
  	}  

  	Point operator+(const Point& second) {
  		Point result (*this);
  		result += second;

  		return result;
  	}	  	

  	Point operator-(const Point& second) {
  		Point result (*this);
  		result -= second;

  		return result;
  	}
};


#endif