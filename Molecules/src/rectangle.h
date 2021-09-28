#include <SDL2/SDL.h>
#include "shape.h"
#include "molecule.h"

#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle : public Shape {
  public:
  	double width;
  	double height;

    Rectangle() : 
        Shape() {
        width  = 0;
        height = 0;
    }    


  	Rectangle(const Point par_point, const double par_mass,  const double par_x_speed, const double par_y_speed, 
  			  const Colour par_color, const double par_width,   const double par_height, const Type_object par_type, const bool par_is_active) : 
        Shape  ( par_point, par_mass, par_x_speed, par_y_speed, par_color, par_type, par_is_active) {
  		width  = par_width ;
  		height = par_height;
    }

    ~Rectangle() {
    	//~Shape();
    	width = height = 0;
    }

    void collision_detection() {
        printf("collision_detection rect\n");
    }

    virtual void collision_with_a_wall(const int screen_width, const int screen_height) {
        //printf("\t\tAAAAAAAAAAAAAAAAAAAAAAA begin rect\n");
        double half_width = get_width() / 2.0, half_height = get_height() / 2.0;

        if(get_x_center() + half_width >= screen_width)
            set_x_speed( -fabs(get_x_speed()) );

        if(get_x_center() - half_width <= 0)       
            set_x_speed( fabs(get_x_speed()) );     

        if(get_y_center() + half_height >= screen_height)
            set_y_speed( -fabs(get_y_speed()) ); 

        if(get_y_center() - half_height <= 0)
            set_y_speed( fabs(get_y_speed()) );
        //printf("\t\tAAAAAAAAAAAAAAAAAAAAAAA end rect\n");
    }      

  	virtual void draw_molecule(SDL_Renderer* render) {
        //printf("\t\tdraaaaaaaaw rect\n");
  		double x_center = get_x_center(), y_center = get_y_center();
  		double half_width = width / 2.0, half_height = height / 2.0;

  		for(int x_coord = x_center - half_width; x_coord <= x_center + half_width; ++x_coord) {
  			for(int y_coord = y_center - half_height; y_coord <= y_center + half_height; ++y_coord) {
                Point now_point( (double)x_coord, (double)y_coord, color );
  				now_point.draw_point(render);              
  			}
  		}
        //printf("\t\t end draaaaaaaaw rect\n");
  	}   

    virtual void make_inactive() {
        set_is_active( false );
        set_colour ( WHITE );
        set_center  ( Point(0.0, 0.0) );
        set_height ( 0.0 );
        set_width  ( 0.0 );
        set_mass   ( 0.0 );
        set_type ( WALL );
    }    

    inline double get_width() const {
        return width;
    } 

    inline double get_height() const {
        return height;
    }     

    inline void set_width(const double new_width) {
        width = new_width;
    } 

    inline void set_height(const double new_height) {
        height = new_height;
    }         
};

#endif