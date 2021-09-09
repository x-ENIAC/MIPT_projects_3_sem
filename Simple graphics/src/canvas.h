#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "main.h"
#include "colour.h"
#include "my_vector.h"

#ifndef CANVAS_H
#define CANVAS_H

class Canvas {
  public:

	Canvas(const int par_x_upper_left_corner, const int par_y_upper_left_corner, const int par_width, const int par_height,
											  const double par_x_scale, const double par_y_scale) :
		x_upper_left_corner ( par_x_upper_left_corner ),
		y_upper_left_corner ( par_y_upper_left_corner ),

		width  ( par_width ),
		height ( par_height ),

		x_scale ( par_x_scale ),
		y_scale ( par_y_scale ),

		x_bottom_right_corner ( par_x_upper_left_corner + par_width ),
		y_bottom_right_corner ( par_y_upper_left_corner + par_height ),

		x_center_coord_system ( (x_upper_left_corner + x_bottom_right_corner) / 2 ),
		y_center_coord_system (  y_bottom_right_corner - 2 * INDENT )
	{}

	~Canvas() {
		x_upper_left_corner   = y_upper_left_corner   = 0;
		x_bottom_right_corner = y_bottom_right_corner = 0;
		width 				  = height 				  = 0;
		x_scale 			  = y_scale  			  = 0;
		x_center_coord_system = y_center_coord_system = 0;
	}

	void draw_coordinate_axes(SDL_Renderer* render, const Colour lines_color);

	void draw_rectangle(SDL_Renderer* render, const int x_upper_left,   const int y_upper_left,
                         					  const int x_bottom_right, const int y_bottom_right,
                        					  const Colour color, bool need_fill = false);

	void draw_line(SDL_Renderer* render, const int x_begin, const int y_begin,
	                    				 const int x_end,   const int y_end,
	                    				 const Colour color);

	void draw_parabola(SDL_Renderer* render, const Colour color);

  	double get_x_upper_left_corner() const;

  	double get_y_upper_left_corner() const;

  	double get_x_bottom_right_corner() const;

  	double get_y_bottom_right_corner() const;	

  	double get_height() const;

  	double get_width() const;

  	double get_x_scale() const;

  	double get_y_scale() const;

  	int get_x_center_coord_system() const;

  	int get_y_center_coord_system() const;

  	void set_x_upper_left_corner(const double new_x_upper_left_corner);

  	void set_y_upper_left_corner(const double new_y_upper_left_corner);

  	void set_x_bottom_right_corner(const double new_x_bottom_right_corner);

  	void set_y_bottom_right_corner(const double new_y_bottom_right_corner);	  	  	

  	void set_height(const double new_height) ;  	  	

  	void set_width(const double new_width); 	

  	void set_x_scale(const double new_x_scale); 	  	  	

  	void get_y_scale(const double new_y_scale);    	

  private:

	int x_upper_left_corner,   y_upper_left_corner;
	int x_bottom_right_corner, y_bottom_right_corner;
	int width, height;  	
	double x_scale, y_scale;

  	int x_center_coord_system, y_center_coord_system;

  	bool need_rectangle_is_correct(const int x_upper_left,   const int y_upper_left,
                         		   const int x_bottom_right, const int y_bottom_right);
};

#endif