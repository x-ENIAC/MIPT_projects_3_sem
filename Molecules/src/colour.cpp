#include "colour.h"

bool Colour::operator<=(const Colour& color) const {
	return (red <= color.red && blue <= color.blue && green <= color.green && alpha <= color.alpha);
}

Colour& Colour::operator*=(const Colour& color) {
	red   *= color.red;
	green *= color.green;
	blue  *= color.blue;

	return *this;
}

Colour&  Colour::operator*=(const double coeff) {
	red   *= coeff;
	blue  *= coeff;
	green *= coeff;
	alpha *= coeff;

	return *this;
}

Colour&  Colour::operator/=(const double coeff) {
	red   /= coeff;
	blue  /= coeff;
	green /= coeff;
	alpha /= coeff;

	return *this;
}

Colour&  Colour::operator+=(const Colour& color) {
	red   += color.red;
	blue  += color.blue;
	green += color.green;
	alpha += color.alpha;

	return *this;
}

/*Colour operator*(const Colour& first_colour, const Colour& second_colour) {
	return Colour((first_colour.red   * second_colour.red) > 256 ? 255 : (first_colour.red   * second_colour.red),
		   		  (first_colour.blue  * second_colour.blue) > 256 ? 255 : (first_colour.blue  * second_colour.blue),
		   		  (first_colour.green * second_colour.green) > 256 ? 255 : (first_colour.green * second_colour.green),
		   		  (first_colour.alpha * second_colour.alpha) > 256 ? 255 : (first_colour.alpha * second_colour.alpha));
}*/