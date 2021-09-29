#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include "screen_info.h"

Screen_info::Screen_info(const int par_width, const int par_height) {
	screen_width  = par_width;
	screen_height = par_height;

	pixel_colours = new Colour*[screen_width];
	for(int i = 0; i < screen_width; ++i)
		pixel_colours[i] = new Colour[screen_height];
}

Screen_info::~Screen_info() {
	for(int i = 0; i < screen_width; ++i)
		delete[] pixel_colours[i];
	delete[] pixel_colours;
}
