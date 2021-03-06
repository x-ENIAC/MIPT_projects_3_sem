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

	bool operator<=(const Colour& color) const;

	Colour& operator*=(const Colour& color);

	Colour& operator*=(const double coeff);

	Colour& operator/=(const double coeff);

	Colour& operator+=(const Colour& color);
};
	
const Colour BLACK = Colour(0,     0,   0,   0);
const Colour WHITE = Colour(0, 0, 0, 255);
const Colour RED   = Colour(255,   0,   0, 255);
const Colour GREEN = Colour(0,   255,   0, 255);
const Colour BLUE  = Colour(0,     0, 255, 255);
const Colour YELLOW = Colour(255, 255,  0, 255);

const Colour AMBIENT = Colour(20, 0, 0, 255);

#endif