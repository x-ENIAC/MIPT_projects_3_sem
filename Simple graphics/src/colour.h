#ifndef COLOUR_H
#define COLOUR_H

class Colour {
  public:
	unsigned int red;
	unsigned int green;
	unsigned int blue;
	unsigned int alpha;

	Colour(unsigned int now_red, unsigned int now_green, unsigned int now_blue, unsigned int now_alpha) {
		red   = now_red;
		green = now_green;
		blue  = now_blue;
		alpha = now_alpha;
	}

	bool operator<=(const Colour& color) const;
};
	
const Colour BLACK = Colour(0,     0,   0, 255);
const Colour WHITE = Colour(255, 255, 255, 255);
const Colour RED   = Colour(255,   0,   0, 255);
const Colour GREEN = Colour(0,   255,   0, 255);
const Colour BLUE  = Colour(0,     0, 255, 255);

#endif