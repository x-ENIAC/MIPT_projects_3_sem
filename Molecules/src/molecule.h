#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "point.h"
#include "colour.h"

#ifndef MOlecule_H
#define MOlecule_H

class Molecule {
  public:
    Molecule():
        center ( Point(0., 0., BLACK) ),
        radius ( 0 ),
        mass   ( 0 ),
        x_speed ( 0 ),
        y_speed ( 0 ),
        color ( BLACK )

    {}

  	Molecule(const Point par_point, const double par_radius, const double par_mass, const double par_x_speed, const double par_y_speed, const Colour par_color):
  		center   (par_point),
  		radius   (par_radius),
        mass     (par_mass),
  		x_speed  (par_x_speed),
  		y_speed  (par_y_speed),
  		color    (par_color)
  	{}

    inline bool is_point_belongs_to_sphere(const Point& point) const {
        return (point.x - center.x) * (point.x - center.x) + (point.y - center.y) * (point.y - center.y) <= radius * radius;
    }

    inline bool is_point_belongs_to_sphere(const double x_coord, const double y_coord) const {
        return (x_coord - center.x) * (x_coord - center.x) + (y_coord - center.y) * (y_coord - center.y) <= radius * radius;
    }    

  	void draw_molecule(SDL_Renderer* render) {
  		for(int x_coord = center.x - radius; x_coord <= center.x + radius; ++x_coord) {
  			for(int y_coord = center.y - radius; y_coord <= center.y + radius; ++y_coord) {
                if(is_point_belongs_to_sphere( (double)x_coord, (double)y_coord ) ) {
  				  Point now_point( (double)x_coord, (double)y_coord, color );
  				  now_point.draw_point(render);
                }
  			}
  		}
  	}

    inline bool is_touch_each_other(const double x_other, const double y_other, const double radius_other) const {
        return ( (center.x - x_other) * (center.x - x_other) + 
                 (center.y - y_other) * (center.y - y_other) <= (radius + radius_other) * (radius + radius_other) );
     } 

    inline bool is_touch_each_other(Molecule& other_molecule) const {
        return ( (center.x - other_molecule.center.x) * (center.x - other_molecule.center.x) + 
                 (center.y - other_molecule.center.y) * (center.y - other_molecule.center.y) <= 
                     (radius + other_molecule.radius) * (radius + other_molecule.radius) );
     }         

    void move_molecule(const double time) {
        center.x += x_speed * time;
        center.y += y_speed * time;
    }

    Molecule& operator=(const Molecule& new_molecule) {
        center  = new_molecule.get_center();
        radius  = new_molecule.get_radius();
        mass    = new_molecule.get_mass();

        x_speed = new_molecule.get_x_speed();
        y_speed = new_molecule.get_y_speed();
        
        color   = new_molecule.get_colour();

        return *this;
    }    

    inline Point get_center() const {
        return center;
    }

  	inline double get_x_center() const {
  		return center.x;
  	}

  	inline double get_y_center() const {
  		return center.y;
  	}  	

  	inline double get_x_speed() const {
  		return x_speed;
  	}

  	inline double get_y_speed() const {
  		return y_speed;
  	}

  	inline double get_radius() const {
  		return radius;
    }

    inline double get_mass() const {
        return mass;
    }    

    inline Colour get_colour() const {
        return color;
    }    

    inline void set_center(const Point par_center) {
        center = par_center;
    }

  	inline void set_x_center(const double par_center_x) {
  		center.x = par_center_x;
  	}

  	inline void set_y_center(const double par_center_y) {
  		center.y = par_center_y;
  	}  	

  	inline void set_x_speed(const double par_x_speed) {
  		x_speed = par_x_speed;
  	}

  	inline void set_y_speed(const double par_y_speed) {
  		y_speed = par_y_speed;
  	}

  	inline void set_radius(const double par_radius) {
  		radius = par_radius;
  	}  

    inline void set_mass(const double par_mass) {
        mass = par_mass;
    }      	

    inline void set_colour(const Colour new_color) {
        color = new_color;
    }        

  private:
  	Point center;
  	double radius;
    double mass;

  	double x_speed, y_speed;
  	Colour color;
};

#endif