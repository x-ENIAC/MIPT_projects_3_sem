#include "colour.h"
#include "point.h"

#ifndef SHAPE_H
#define SHAPE_H


enum Type_object {
    WALL      = 0,
    CIRCLE    = 1,
    RECTANGLE = 2,
    BUTTON    = 3,
    AAAAAAAAA = 66,
};

class Shape {
  public:
    Shape():
        center ( Point(0., 0., BLACK) ),
        mass   ( 0 ),
        x_speed ( 0 ),
        y_speed ( 0 ),
        color ( BLACK ),
        type ( WALL ),
        is_active ( false )

    {}

  	Shape(const Point par_point, const double par_mass, const double par_x_speed, const double par_y_speed, const Colour par_color, 
                                                                                  const Type_object par_type, const bool par_is_active):
  		center   (par_point),
        mass     (par_mass),
  		x_speed  (par_x_speed),
  		y_speed  (par_y_speed),
  		color    (par_color),
        type     (par_type),
        is_active(par_is_active)
  	{}

    Shape& operator=(const Shape& new_shape) {

        center  = new_shape.get_center();
        mass    = new_shape.get_mass();

        set_x_speed ( new_shape.get_x_speed() );
        set_y_speed ( new_shape.get_y_speed() );
        
        color   = new_shape.get_colour();
        type    = new_shape.get_type();

        is_active = new_shape.get_is_active();

        return *this;
    }    

    void collision_detection() {
        printf("collision_detection shape\n");
    } 

    virtual void draw_molecule(SDL_Renderer* render) {printf("\t\tdraaaaaaaaw shape\n");};    

    virtual void collision_with_a_wall(const int screen_width, const int screen_height) {printf("!!!\n");};  

    virtual void make_inactive() {};      

    void move_molecule(const double time) {
        set_x_center( get_x_center() + get_x_speed() * time);
        set_y_center( get_y_center() + get_y_speed() * time);
    }    

    inline double get_kinetic_enegry() {
        return mass * (x_speed + y_speed);
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

  	inline double get_mass() const {
        return mass;
    }    

    inline Colour get_colour() const {
        return color;
    }    

    inline Type_object get_type() const {
        return type;
    }  

    inline bool get_is_active() const {
        return is_active;
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

  	inline void set_mass(const double par_mass) {
        mass = par_mass;
    }      	

    inline void set_colour(const Colour new_color) {
        color = new_color;
    }	

    inline void set_type(const Type_object new_type) {
        type = new_type;
    }     

    inline void set_is_active(const bool new_is_active) {
        is_active = new_is_active;
    }

  	Point center;
    double mass;

  	double x_speed, y_speed;
  	Colour color;	

    Type_object type;
    bool is_active;
};

#endif