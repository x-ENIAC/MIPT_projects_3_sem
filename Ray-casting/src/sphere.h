#include "colour.h"
#include "point.h"
//#include "world.h"
#include "screen_info.h"
#include "my_vector.h"

#ifndef SPHERE_H
#define SPHERE_H

class Sphere {
  public:

  	Sphere(const Point par_center, const Colour par_color, const double par_radius) :
  		center ( par_center ),
  		color  ( par_color  ),
  		radius ( par_radius )
  	{}

  	inline Point get_center() const {
  		return center;
  	}

  	inline Colour get_color() const {
  		return color;
  	}

  	inline void set_center(const Point new_center) {
  		center = new_center;
  	}

  	inline void set_color(const Colour new_color) {
  		color = new_color;
  	}

    double calculate_diffuse_component(const Vector* vector_to_light, const Vector* normal_vector, bool* is_point_in_a_shadow);

    Colour calculate_diffuse_component(const Vector* vector_to_light, const Vector* normal_vector, Colour light_color, 
                                                                          Colour sphere_color, bool* is_point_in_a_shadow);    

    double calculate_flare_component(Vector* vector_to_light, const Vector* normal_vector, 
                                                                    const Vector* vector_to_camera, bool* is_point_in_a_shadow);

    Colour calculate_flare_component(Vector* vector_to_light, const Vector* normal_vector, const Vector* vector_to_camera, 
                                                                  Colour light_color, Colour sphere_color, bool* is_point_in_a_shadow);    

  	void calculate_intensity(const Point center, const Point light, const Point camera, const Colour light_color, Screen_info* Screen_info);

    void calculate_the_lighting_factor(const double lambert, const double flare, const Colour light_color, const Colour sphere_color,
                                                                 const double x_coord, const double y_coord, Screen_info* screen_info);
  	inline bool is_point_belongs_to_sphere(const Point point) {
  		return (point.x - center.x) * (point.x - center.x) + (point.y - center.y) * (point.y - center.y) <= radius * radius;
  	}

  	inline double get_z_coord(const double x_delta, const double y_delta) {
  		return sqrt(radius * radius - x_delta * x_delta - y_delta * y_delta);
  	}

  private:
  	Point center;
  	Colour color;
  	double radius;
};


#endif