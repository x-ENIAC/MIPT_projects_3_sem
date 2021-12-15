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
		SDL_SetRenderDrawColor(render, color.red, color.green, color.blue, 20);
		SDL_RenderDrawPoint(render, x, y); 
	}

	inline void draw_big_point(SDL_Renderer* render, const int radius) {
		int radius_2 = radius * radius;

		SDL_SetRenderDrawColor(render, color.red, color.green, color.blue, 20);

		int max_x = x + radius;
		for(int i = x - radius; i <= max_x; ++i) {

			int max_y = y + radius;
			for(int j = y - radius; j <= max_y; ++j) {

				if((i - x) * (i - x) + (j - y) * (j - y) <= radius_2)
					SDL_RenderDrawPoint(render, i, j);
			}
		}
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

	Point operator*(const double scale) {
		Point result (*this);
		result *= scale;

		return result;
	}

	bool operator==(const Point& second) {
		return (this->x == second.x && this->y == second.y);
	}

	double scalar_mult(const Point& other) {
		return x * other.x + y * other.y;
	}

	void set_center(const Point new_center) {
		x = new_center.x;
		y = new_center.y;
	}
};

int compare(const void* p1, const void* p2);

#endif