#include "stdio.h"

#ifndef COLOUR_H
#define COLOUR_H

class Colour {
  public:
	int red;
	int green;
	int blue;
	int alpha;

	Colour() {
		red   = 0;
		green = 0;
		blue  = 0;
		alpha = 0;
	}

	Colour(int now_red, int now_green, int now_blue, int now_alpha) {
		red   = now_red;
		green = now_green;
		blue  = now_blue;
		alpha = now_alpha;
	}

	inline void print() const {
		printf("(%d, %d, %d, %d)", red, green, blue, alpha);
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
const Colour GREEN = Colour(0, 255, 0, 255);
const Colour BLUE  = Colour(0,   0, 255, 255);
const Colour YELLOW = Colour(255, 255, 0, 255);
const Colour PURPLE = Colour(161, 98, 161, 255);
const Colour LIGHT_GREEN = Colour(153, 255, 153, 255);
const Colour PINK = Colour(255, 192, 203, 255);
const Colour LIGHT_CARROT = Colour(237, 145, 33, 255);


//const Colour LIGHT_GREY_5 = Colour(245, 245, 245, 255);
const Colour LIGHT_GREY_4 = Colour(245, 245, 245, 255);
const Colour LIGHT_LIGHT_GREY = Colour(230, 230, 230, 255);
const Colour LIGHT_GREY_2 = Colour(200, 200, 200, 255);
const Colour LIGHT_GREY = Colour(170, 170, 170, 255);
//const Colour MIDDLE_GREY = Colour(135, 135, 135, 255);
const Colour DARK_GREY = Colour(128, 128, 128, 255);
const Colour DARK_GREY_3 = Colour(75, 75, 75, 255);
const Colour DARK_GREY_2 = Colour(50, 50, 50, 255);

const Colour AMBIENT = Colour(20, 0, 0, 255);

#endif