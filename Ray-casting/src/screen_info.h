#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "colour.h"

#ifndef SCREEN_INFO_H
#define SCREEN_INFO_H

class Screen_info {
  public:

    Screen_info(const int par_screen_width, const int par_screen_height);
  	~Screen_info();

    void draw_screen(SDL_Renderer* render) {
        for(int x_coord = 0; x_coord < screen_width; ++x_coord) {
            for(int y_coord = 0; y_coord < screen_height; ++y_coord) {
                SDL_SetRenderDrawColor(render, pixel_colours[x_coord][y_coord].red,   pixel_colours[x_coord][y_coord].blue, 
                                               pixel_colours[x_coord][y_coord].green, pixel_colours[x_coord][y_coord].alpha);
                SDL_RenderDrawPoint(render, x_coord, y_coord); 
            }
        }
    }

    inline int get_screen_height() const {
        return screen_height;
    }

    inline int get_screen_width() const {
        return screen_width;
    }

    inline Colour get_pixel_colour(const int x_coord, const int y_coord) const {
        return pixel_colours[x_coord][y_coord];
    }     

    inline void set_screen_height(const int new_screen_height) {
        screen_height = new_screen_height;
    }

    inline void set_screen_width(const int new_screen_width) {
        screen_width = new_screen_width;
    }


    inline void set_pixel_colour(const int x_coord, const int y_coord, const Colour new_color) {
        if(x_coord >= 0 && x_coord < screen_width && 
           y_coord >= 0 && y_coord < screen_height)
            pixel_colours[x_coord][y_coord] = new_color;
    }    

  private:
  	Colour** pixel_colours;
  	int screen_height;
  	int screen_width;

};

#endif