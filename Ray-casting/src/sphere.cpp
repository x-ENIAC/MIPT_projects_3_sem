#include <stdio.h>
#include <stdlib.h>
#include "sphere.h"

void Sphere::calculate_intensity(const Point center_sphere, const Point light_point, const Point camera_point, const Colour light_color, Screen_info* screen_info) {
	int screen_width  = screen_info->get_screen_width();
	int screen_height = screen_info->get_screen_height();

	Colour copy_light_color(light_color);
	Colour copy_sphere_color(color);
	Colour copy_ambient(AMBIENT);

	copy_light_color  /= 255.0;
	copy_sphere_color /= 255.0;	
	copy_ambient      /= 255.0;

	for(int x_coord = 0; x_coord < screen_width; ++x_coord) {
		for(int y_coord = 0; y_coord < screen_height; ++y_coord) {

			if(is_point_belongs_to_sphere(Point(x_coord, y_coord))) {

				Point now_point(x_coord, y_coord, get_z_coord((double)x_coord - center_sphere.x, (double)y_coord - center_sphere.y));

				Vector vector_to_camera(now_point, camera_point);
				Vector vector_to_light(now_point, light_point);

				Vector normal_vector(center_sphere, now_point);
				normal_vector *= 2.0;
				normal_vector.set_point_begin(now_point);

				double length_normal_vector    = normal_vector.get_length_vector();
				double length_vector_to_light  = vector_to_light.get_length_vector();				
				double length_vector_to_camera = vector_to_camera.get_length_vector();
				

				bool is_point_in_a_shadow = false;
				Colour intensity_coefficient = calculate_diffuse_component(&vector_to_light,  &normal_vector, 
																		   copy_light_color, copy_sphere_color,
																		   &is_point_in_a_shadow);
				if(is_point_in_a_shadow) {
					screen_info->set_pixel_colour(x_coord, y_coord, AMBIENT);
					continue;					
				}

			   
				Colour flare_component = calculate_flare_component(&vector_to_light,  &normal_vector,    &vector_to_camera, 
																    copy_light_color, copy_sphere_color, &is_point_in_a_shadow);
				if(is_point_in_a_shadow) {
					screen_info->set_pixel_colour(x_coord, y_coord, AMBIENT);
					continue;					
				}

				Colour result_color(flare_component);
				result_color += intensity_coefficient;
				result_color += copy_ambient;

				result_color.red   = (result_color.red   > 1.0 ? 1.0 : result_color.red);
				result_color.green = (result_color.green > 1.0 ? 1.0 : result_color.green);
				result_color.blue  = (result_color.blue  > 1.0 ? 1.0 : result_color.blue);
				result_color.alpha = (result_color.alpha > 1.0 ? 1.0 : result_color.alpha);

				result_color *= 255.0;

				screen_info->set_pixel_colour(x_coord, y_coord, result_color);				

			} else {
				screen_info->set_pixel_colour(x_coord, y_coord, Colour(0, 0, 0, 255));
			}

		}
	}
}

double Sphere::calculate_diffuse_component(const Vector* vector_to_light, const Vector* normal_vector, bool* is_point_in_a_shadow) {

	double scalar_mult = normal_vector->scalar_multiplication(vector_to_light);

	double length_normal_vector    = normal_vector->get_length_vector();
	double length_vector_to_light  = vector_to_light->get_length_vector();

	if(length_normal_vector == 0 || length_vector_to_light == 0 || scalar_mult < 0) {
		*is_point_in_a_shadow = true;
		return 0;
	}

	double intensity_coefficient = scalar_mult / length_normal_vector / length_vector_to_light;
	if(intensity_coefficient < 0)
		intensity_coefficient = 0;

	return intensity_coefficient;
}

Colour Sphere::calculate_diffuse_component(const Vector* vector_to_light, const Vector* normal_vector, Colour light_color, 
						 												  Colour sphere_color, bool* is_point_in_a_shadow) {

	double scalar_mult = normal_vector->scalar_multiplication(vector_to_light);

	double length_normal_vector    = normal_vector->get_length_vector();
	double length_vector_to_light  = vector_to_light->get_length_vector();

	if(length_normal_vector == 0 || length_vector_to_light == 0 || scalar_mult < 0) {
		*is_point_in_a_shadow = true;
		return BLACK;
	}

	double intensity_coefficient = scalar_mult / length_normal_vector / length_vector_to_light;
	if(intensity_coefficient < 0)
		intensity_coefficient = 0;

	Colour result_color(light_color);
	result_color *= sphere_color;
	result_color *= intensity_coefficient;

	return result_color;
}

double Sphere::calculate_flare_component(Vector* vector_to_light, const Vector* normal_vector, 
																  const Vector* vector_to_camera, bool* is_point_in_a_shadow) {

	double length_normal_vector    = normal_vector->get_length_vector();
	double length_vector_to_light  = vector_to_light->get_length_vector();
	double length_vector_to_camera = vector_to_camera->get_length_vector();

	Vector reflected(vector_to_light->reflect_vector(normal_vector));
	double length_reflected = reflected.get_length_vector();

	if(length_reflected == 0) {
		*is_point_in_a_shadow = true;
		return 0;
	}

	double flare_coefficient = reflected.scalar_multiplication(vector_to_camera) / length_reflected / length_vector_to_camera;
	if(flare_coefficient < 0)
		flare_coefficient = 0;

	flare_coefficient = pow(flare_coefficient, 30);

	return flare_coefficient;
}

Colour Sphere::calculate_flare_component(Vector* vector_to_light, const Vector* normal_vector, const Vector* vector_to_camera, 
																  Colour light_color, Colour sphere_color, bool* is_point_in_a_shadow) {

	double length_normal_vector    = normal_vector->get_length_vector();
	double length_vector_to_light  = vector_to_light->get_length_vector();
	double length_vector_to_camera = vector_to_camera->get_length_vector();

	Vector reflected(vector_to_light->reflect_vector(normal_vector));
	double length_reflected = reflected.get_length_vector();

	if(length_reflected == 0) {
		*is_point_in_a_shadow = true;
		return BLACK;
	}

	double flare_coefficient = reflected.scalar_multiplication(vector_to_camera) / length_reflected / length_vector_to_camera;
	if(flare_coefficient < 0)
		flare_coefficient = 0;

	flare_coefficient = pow(flare_coefficient, 30);

	Colour result_color(light_color);
	result_color *= flare_coefficient;

	return result_color;
}

void Sphere::calculate_the_lighting_factor(const double lambert, const double flare, const Colour light_color, const Colour sphere_color,
															     const double x_coord, const double y_coord, Screen_info* screen_info) {

	Colour copy_light_color = light_color, copy_sphere_color = sphere_color;

	Colour result_color = copy_sphere_color;
	result_color *= copy_light_color;
	result_color *= lambert;

	Colour copy_ambient = AMBIENT;
	copy_ambient /= 255.0;
	result_color += copy_ambient;

	Colour tmp = copy_light_color;
	tmp *= flare;

	result_color += tmp;

	result_color.red   = (result_color.red   > 1.0 ? 1.0 : result_color.red);
	result_color.green = (result_color.green > 1.0 ? 1.0 : result_color.green);
	result_color.blue  = (result_color.blue  > 1.0 ? 1.0 : result_color.blue);
	result_color.alpha = (result_color.alpha > 1.0 ? 1.0 : result_color.alpha);


	result_color *= 255.0;

	screen_info->set_pixel_colour(x_coord, y_coord, result_color);
}