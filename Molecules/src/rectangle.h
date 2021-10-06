#include <SDL2/SDL.h>
#include "object.h"

#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle : public Object {
  public:
  	double width;
  	double height;

    Rectangle() : 
        Object() {
        set_width  ( 0 );
        set_height ( 0 );
        set_type ( RECTANGLE );
        set_is_active ( true );
    }    


  	Rectangle(const Point par_point, const double par_mass,  const double par_x_speed, const double par_y_speed, 
  			  const Colour par_color, const double par_width,   const double par_height, const Type_object par_type, const bool par_is_active) : 
        Object  ( par_point, par_mass, par_x_speed, par_y_speed, par_color, par_type, par_is_active) {
  		width  = par_width ;
  		height = par_height;
    }

    ~Rectangle() {
    	set_width  (0 );
        set_height ( 0 );
    }

    void collision_detection() {
        printf("collision_detection rect\n");
    }

    virtual void collision_with_a_wall(const int screen_width, const int screen_height) {
        double half_width = get_width() / 2.0, half_height = get_height() / 2.0;

        if(get_x_center() + half_width >= screen_width)
            set_x_speed( -fabs(get_x_speed()) );

        if(get_x_center() - half_width <= 0)       
            set_x_speed( fabs(get_x_speed()) );     

        if(get_y_center() + half_height >= screen_height)
            set_y_speed( -fabs(get_y_speed()) ); 

        if(get_y_center() - half_height <= 0)
            set_y_speed( fabs(get_y_speed()) );
    }      

  	virtual void draw_molecule(SDL_Renderer* render) {
  		double x_center = get_x_center(), y_center = get_y_center();
  		double half_width = width / 2.0, half_height = height / 2.0;
        Colour now_color = get_colour();

  		for(int x_coord = x_center - half_width; x_coord <= x_center + half_width; ++x_coord) {
  			for(int y_coord = y_center - half_height; y_coord <= y_center + half_height; ++y_coord) {
                Point now_point( (double)x_coord, (double)y_coord, now_color);
  				now_point.draw_point(render);              
  			}
  		}
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

    Rectangle& operator=(const Rectangle& new_object) {

        set_center( new_object.get_center() );
        set_mass ( new_object.get_mass() );

        set_x_speed ( new_object.get_x_speed() );
        set_y_speed ( new_object.get_y_speed() );

        set_width ( new_object.get_width() );
        set_height( new_object.get_height() );
        
        set_colour (  new_object.get_colour() );
        set_type  (  new_object.get_type() );

        set_is_active ( new_object.get_is_active() );

        return *this;
    }    

    bool is_point_belongs_to_rectangle(Point point) {
        double x_left_up = get_x_center() - width  / 2.0;
        double y_left_up = get_y_center() - height / 2.0;

        double x_right_down = get_x_center() + width  / 2.0;
        double y_right_down = get_y_center() + height / 2.0;

        double x_point = point.x, y_point = point.y;    

        return (x_left_up <= x_point && x_point <= x_right_down) &&
               (y_left_up <= y_point && y_point <= y_right_down);
    }   

    //void update_size(const size_t screen_width, const size_t screen_height) {
    //    if()
    //} 


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