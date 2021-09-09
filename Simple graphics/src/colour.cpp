#include "colour.h"

bool Colour::operator<=(const Colour& color) const {
	return (red <= color.red && blue <= color.blue && green <= color.green && alpha <= color.alpha);
}