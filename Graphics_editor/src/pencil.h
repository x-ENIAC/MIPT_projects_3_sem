#include "colour.h"

#ifndef PENCIL_H
#define PENCIL_H

class Pencil {
  private:
	Colour color;
	size_t thickness;

  public:

	Pencil() {
		color = BLACK;
		thickness = 10;
	}

	Pencil(const Colour par_color, const size_t par_thickness) {
		color = par_color;
		thickness = par_thickness;
	}

	size_t get_thickness() const {
		return thickness;
	}

	Colour get_color() const {
		return color;
	}

	void set_color(const Colour new_color) {
		color = new_color;
	}
};

#endif