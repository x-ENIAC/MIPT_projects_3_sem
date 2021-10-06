#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "object.h"
#include "point.h"
#include "colour.h"

#ifndef CIRCLE_H
#define CIRCLE_H

class Object;
class Circle : public Object {
  public:
    Circle() : Object() {
        radius = 0;
    }

  	Circle(const Point par_point, const double par_radius,  const double par_mass, 
             const double par_x_speed, const double par_y_speed, const Colour par_color, const bool par_is_active, const Object_owner par_owner) :
      Object (par_point, par_mass, par_x_speed, par_y_speed, par_color, CIRCLE, par_is_active, par_owner) {
        
        radius = par_radius;
    }

    bool is_touch_each_other(const Circle* other_object) const {
        return ( (get_x_center() - other_object->get_x_center()) * (get_x_center() - other_object->get_x_center()) + 
                 (get_y_center() - other_object->get_y_center()) * (get_y_center() - other_object->get_y_center()) <= 
                   (get_radius() +   other_object->get_radius()) * (get_radius()   + other_object->get_radius()) );
    }  

    inline bool is_point_belongs_to_sphere(const Point point) const {
        return (point.x - get_x_center()) * (point.x - get_x_center()) + (point.y - get_y_center()) * (point.y - get_y_center()) <= radius * radius;
    }

    inline bool is_point_belongs_to_sphere(const double x_coord, const double y_coord) const {
        return (x_coord - get_x_center()) * (x_coord - get_x_center()) + (y_coord - get_y_center()) * (y_coord - get_y_center()) <= radius * radius;
    }    

  	virtual void draw_molecule(SDL_Renderer* render) {
  		for(int x_coord = get_x_center() - get_radius(); x_coord <= get_x_center() + get_radius(); ++x_coord) {
  			for(int y_coord = get_y_center() - get_radius(); y_coord <= get_y_center() + get_radius(); ++y_coord) {

                if(is_point_belongs_to_sphere( (double)x_coord, (double)y_coord ) ) {
  				  Point now_point( (double)x_coord, (double)y_coord, get_colour() );
  				  now_point.draw_point(render);
                }
  			}
  		}
  	}

    virtual void collision_with_a_wall(const int screen_width, const int screen_height) {
        if(get_x_center() + get_radius() >= screen_width)
            set_x_speed( -fabs(get_x_speed()) );
        
        if(get_x_center() - get_radius() <= 0)       
            set_x_speed( fabs(get_x_speed()) );     

        if(get_y_center() + get_radius() >= screen_height)
            set_y_speed( -fabs(get_y_speed()) ); 

        if(get_y_center() - get_radius() <= 0)
            set_y_speed( fabs(get_y_speed()) );
    }     

    virtual void make_inactive() {
        set_is_active( false );
        set_colour ( WHITE );
        set_center  ( Point(0.0, 0.0) );
        set_radius ( 0.0 );
        set_type ( WALL );
    }

    Circle& operator=(const Circle& dnew_circle) {
        set_center( dnew_circle.get_center() );
        set_radius( dnew_circle.get_radius() );
        set_mass  ( dnew_circle.get_mass() );

        set_x_speed ( dnew_circle.get_x_speed() );
        set_y_speed ( dnew_circle.get_y_speed() );
        
        set_colour   ( dnew_circle.get_colour() );

        set_is_active ( dnew_circle.get_is_active() );

        return *this;
    }

  	inline double get_radius() const {
  		return radius;
    }

  	inline void set_radius(const double par_radius) {
  		radius = par_radius;
  	}    

  private:
  	double radius;
};

#endif