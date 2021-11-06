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

	inline size_t get_thickness() const {
		return thickness;
	}

	inline Colour get_color() const {
		return color;
	}

	inline void set_color(const Colour new_color) {
		color = new_color;
	}

	inline void set_thickness(const size_t new_thickness) {
		thickness = new_thickness;
	}	
};

#endif