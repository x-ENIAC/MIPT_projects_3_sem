#include "colour.h"

#ifndef PIXELS_H
#define PIXELS_H

class Pixel {
  public:
  	int x_coord;
  	int y_coord;
  	Colour color;

  	/*Pixel() :
  	{}*/

  	Pixel(int par_x_coord, int par_y_coord, Colour par_color) :
  		x_coord ( par_x_coord ),
  		y_coord ( par_y_coord ),
  		color   (  par_color  )
  	{}

  private:

};

#endif