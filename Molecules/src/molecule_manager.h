#include "molecule.h"
#include "point.h"
#include "my_vector.h"

#ifndef MOlecule_MANAGER_H
#define MOlecule_MANAGER_H

enum Type_object {
	CIRCLE = 0,
};

const double DELTA_TIME = 0.05;

class Molecule_manager {
  public:
  	 Molecule* molecule;
  	 size_t count_objects;

  	 Molecule_manager() {
  	 	molecule = new Molecule[0];
  	 	count_objects = 0;
  	 }

  	 ~Molecule_manager() {
  	 	delete[] molecule;
  	 	count_objects = 0;
  	 }

  	 void update_molecule() {
  	 	for(int i = 0; i < count_objects; ++i)
  	 		molecule[i].move_molecule(DELTA_TIME);
  	 }

  	 void collision_detection(const int screen_width, const int screen_height) {
  	 	for(size_t first = 0; first < count_objects; ++first) {
  	 		if(molecule[first].get_x_center() + molecule[first].get_radius() >= screen_width)
  	 			molecule[first].set_x_speed( -fabs(molecule[first].get_x_speed()) );

  	 		if(molecule[first].get_x_center() - molecule[first].get_radius() <= 0)  	 
  	 			molecule[first].set_x_speed( fabs(molecule[first].get_x_speed()) );		

  	 		if(molecule[first].get_y_center() + molecule[first].get_radius() >= screen_height)
  	 			molecule[first].set_y_speed( -fabs(molecule[first].get_y_speed()) ); 

  	 		if(molecule[first].get_y_center() - molecule[first].get_radius() <= 0)
  	 			molecule[first].set_y_speed( fabs(molecule[first].get_y_speed()) );
  	 	}

  	 	for(size_t first = 0; first < count_objects; ++first) {
  	 		for(size_t second = 0; second < count_objects; ++second) {
  	 			if(first == second)
  	 				continue;

  	 			if(molecule[first].is_touch_each_other(molecule[second])) {
  	 				collision_responce(first, second);
  	 				molecule[first].move_molecule(DELTA_TIME);
  	 				molecule[second].move_molecule(DELTA_TIME);
  	 			}
  	 		}
  	 	}
  	 }

  	 void collision_responce(const int first, const int second) {
  	 	Point first_center  = molecule[first].get_center();
  	 	Point second_center = molecule[second].get_center();

  	 	double first_mass  = molecule[first].get_mass();
  	 	double second_mass = molecule[second].get_mass();  	 	

  	 	double first_x_speed  = molecule[first].get_x_speed (),  first_y_speed = molecule[first].get_y_speed ();
  	 	double second_x_speed = molecule[second].get_x_speed(), second_y_speed = molecule[second].get_y_speed();

 		Vector first_speed  ( Point(0., 0.), Point(first_x_speed,   first_y_speed) );
 		Vector second_speed ( Point(0., 0.), Point(second_x_speed, second_y_speed) );

  	 	Vector vector_between_centers ( Point(0., 0.), second_center - first_center );
  	 	double length_vector_between_centers = vector_between_centers.get_length_vector();

  	 	Vector pr_on_n_first_vector  ( vector_between_centers );
  	 	pr_on_n_first_vector  *= (first_speed * vector_between_centers) / length_vector_between_centers / length_vector_between_centers;

  	 	Vector pr_on_n_second_vector ( vector_between_centers );
  	 	pr_on_n_second_vector *= (second_speed * vector_between_centers) / length_vector_between_centers / length_vector_between_centers;  	 

  	 	Vector first_impulse ( pr_on_n_first_vector );
  	 	first_impulse *= first_mass;

  	 	Vector second_impulse ( pr_on_n_second_vector );
  	 	second_impulse *= second_mass;

  	 	Vector res_first_speed  ( first_speed );
  	 	res_first_speed  -= pr_on_n_first_vector;

  	 	Vector res_second_speed  ( second_speed );
  	 	res_second_speed  -= pr_on_n_second_vector;

  	 	Vector new_pr_on_n_first_vector ( first_impulse );
  	 	new_pr_on_n_first_vector += second_impulse;
  	 	new_pr_on_n_first_vector *= 2;
  	 	new_pr_on_n_first_vector /= ( first_mass + second_mass );
  	 	new_pr_on_n_first_vector -= pr_on_n_first_vector;

  	 	Vector new_pr_on_n_second_vector ( second_impulse );
  	 	new_pr_on_n_second_vector += first_impulse;
  	 	new_pr_on_n_second_vector *= 2;
  	 	new_pr_on_n_second_vector /= ( first_mass + second_mass );
  	 	new_pr_on_n_second_vector -= pr_on_n_second_vector;  	

  	 	res_first_speed  += new_pr_on_n_first_vector;
  	 	res_second_speed += new_pr_on_n_second_vector;

  	 	res_first_speed.set_point_end   ( res_first_speed.get_point_end() - res_first_speed.get_point_begin() );
  	 	res_first_speed.set_point_begin ( Point(0, 0) );
  	 	molecule[first].set_x_speed ( res_first_speed.get_x_end() );
  	 	molecule[first].set_y_speed ( res_first_speed.get_y_end() );  	
  	 	
  	 	res_second_speed.set_point_end   ( res_second_speed.get_point_end() - res_second_speed.get_point_begin() );
  	 	res_second_speed.set_point_begin ( Point(0, 0) );
  	 	molecule[second].set_x_speed ( res_second_speed.get_x_end() );
  	 	molecule[second].set_y_speed ( res_second_speed.get_y_end() );	  	 	 	 	

  	 }

  	 void add_object(const Type_object type_object, const Point new_center, const double new_radius, const double new_mass, const double new_x_speed, const double new_y_speed) {
  	 	Molecule* resize_molecule = new Molecule[count_objects + 1];
  	 	for(size_t i = 0; i < count_objects; ++i)
  	 		resize_molecule[i] = molecule[i];

  	 	resize_molecule[count_objects].set_center (new_center);
  	 	resize_molecule[count_objects].set_colour (new_center.color);
  	 	resize_molecule[count_objects].set_radius (new_radius);
  	 	resize_molecule[count_objects].set_mass   (new_mass);
  	 	resize_molecule[count_objects].set_x_speed(new_x_speed);
  	 	resize_molecule[count_objects].set_y_speed(new_y_speed);

  	 	++count_objects;

  	 	delete[] molecule;
  	 	molecule = new Molecule[count_objects];
  	 	for(int i = 0; i < count_objects; ++i) {
  	 		molecule[i] = resize_molecule[i];
 	 	}  	 	
  	 }
};

#endif