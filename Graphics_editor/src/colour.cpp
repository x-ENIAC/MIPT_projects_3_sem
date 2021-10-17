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
	green *= coeff;
	blue  *= coeff;
	alpha *= coeff;

	return *this;
}

Colour&  Colour::operator/=(const double coeff) {
	red   /= coeff;
	green /= coeff;
	blue  /= coeff;
	alpha /= coeff;

	return *this;
}

Colour&  Colour::operator+=(const Colour& color) {
	red   += color.red;
	green += color.green;
	blue  += color.blue;
	alpha += color.alpha;

	return *this;
}
