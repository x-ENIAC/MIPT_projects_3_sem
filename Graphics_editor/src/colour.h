#include "stdio.h"

#ifndef COLOUR_H
#define COLOUR_H

class Colour {
  public:
	double red;
	double green;
	double blue;
	double alpha;

	Colour() {
		red   = 0;
		green = 0;
		blue  = 0;
		alpha = 0;
	}

	Colour(double now_red, double now_green, double now_blue, double now_alpha) {
		red   = now_red;
		green = now_green;
		blue  = now_blue;
		alpha = now_alpha;
	}

	void print() const {
		printf("(%lg, %lg, %lg, %lg)", red, green, blue, alpha);
	}

	bool operator<=(const Colour& color) const;

	bool operator!=(const Colour& color) const;

	Colour& operator*=(const Colour& color);

	Colour& operator*=(const double coeff);

	Colour& operator/=(const double coeff);

	Colour& operator+=(const Colour& color);
};
	
const Colour BLACK = Colour(0,     0,   0,   0);
const Colour WHITE = Colour(255, 255, 255, 255);
const Colour RED   = Colour(255,   0,   0, 255);
const Colour GREEN = Colour(0,     0, 255, 255);
const Colour BLUE  = Colour(0,   255,   0, 255);
const Colour YELLOW = Colour(255, 0, 255, 255);
const Colour PURPLE = Colour(161, 161, 98, 256);
const Colour LIGHT_GREEN = Colour(153, 153, 255, 256);
const Colour PINK = Colour(255, 203, 192, 256);

const Colour MIDDLE_GREY = Colour(230, 230, 230, 256);
const Colour LIGHT_GREY = Colour(170, 170, 170, 256);
const Colour DARK_GREY = Colour(128, 128, 128, 256);

const Colour AMBIENT = Colour(20, 0, 0, 255);

#endif