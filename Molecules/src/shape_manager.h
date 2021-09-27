#include "molecule.h"
#include "rectangle.h"
#include "point.h"
#include "my_vector.h"
#include "collision_detection.h"
#include "collision_response.h"

#ifndef SHAPE_MANAGER_H
#define SHAPE_MANAGER_H

extern Collision_detection_table collision_detected_table;
extern Collision_response_table collision_responsed_table;

const double DELTA_TIME = 0.05;

class Shape_manager {
  public:
  	Shape** shapes;
  	size_t count_objects;
  	size_t count_non_active_objects;

  	Shape_manager() {
  	 	shapes = new Shape*;
  	 	count_objects = 0;
  	 	count_non_active_objects = 0;
  	}

  	~Shape_manager() {
  		printf("Destruct, %ld\n", count_objects);
  		//for(size_t i = 0; i < count_objects; ++i) {
  		//	printf("Delete\n");
  		//	delete[] shapes[i];
  		//}
  	 	//delete[] shapes;


  	 	count_objects = 0;
  	}

  	void update_molecule() {
  	 	for(int i = 0; i < count_objects; ++i)
  	 		shapes[i]->move_molecule(DELTA_TIME);
  	}

  	void collision_detection(const int screen_width, const int screen_height) {
  		int now_count_object = count_objects;

  		//printf("begin collision_detection\n");
	  	for(size_t first = 0; first < now_count_object; ++first) {
	  		if(shapes[first]->get_type() != WALL && shapes[first]->get_is_active())
	  			shapes[first]->collision_with_a_wall(screen_width, screen_height);
	  	}

	  	for(size_t first = 0; first < now_count_object; ++first) {
	  	 	for(size_t second = 0; second < now_count_object; ++second) {
	  	 		if(first == second || !shapes[first]->get_is_active() || !shapes[second]->get_is_active() || shapes[first]->get_type() == WALL || shapes[second]->get_type() == WALL)
	  	 			continue;

	  	 		int first_type  = shapes[first]->get_type();
	  	 		int second_type = shapes[second]->get_type();


	  	 		bool is_collision = collision_detected_table.collide_table[first_type][second_type](shapes[first], shapes[second]);

	  	 		if(is_collision && first_type == CIRCLE && second_type == CIRCLE) {

					Rectangle* new_rect = new Rectangle;
					get_new_rectangle_after_circles_collide(new_rect, (Molecule*)shapes[first], (Molecule*)shapes[second]);

					add_object(new_rect);
					//shapes[first]->move_molecule(DELTA_TIME);
	  	 			//shapes[second]->move_molecule(DELTA_TIME);
	  	 			shapes[count_objects - 1]->move_molecule(DELTA_TIME);
	  	 			collision_responsed_table.collire_table[first_type][second_type](shapes[first], shapes[second]);
					count_non_active_objects += 2;	  	 			
	  	 		}

	  	 		else
				if(is_collision && (first_type == CIRCLE && second_type == RECTANGLE || first_type == RECTANGLE && second_type == CIRCLE)) {


	  	 			shapes[first]->move_molecule(DELTA_TIME);
	  	 			shapes[second]->move_molecule(DELTA_TIME);

	  	 			collision_responsed_table.collire_table[first_type][second_type](shapes[first], shapes[second]);
	  	 			++count_non_active_objects;	  	 			
	  	 		}

	  	 		else
	  	 		if(is_collision && first_type == RECTANGLE && second_type == RECTANGLE) {


	  	 			Point collision_point = get_rectangles_collision_point((Rectangle*)shapes[first], (Rectangle*)shapes[second]);
	  	 			double small_masses = (shapes[first]->get_mass() + shapes[second]->get_mass()) / 5.0;

	  	 			for(int i = 0; i < 7; ++i) {
	  	 				int sign_x = 1, sign_y = 1;
	  	 				if(rand() % 2)
	  	 					sign_x = -1;
	  	 				if(rand() % 2)
	  	 					sign_y = -1;	  	 

	  	 				double new_x = collision_point.x + sign_x * (rand() % 10);
	  	 				double new_y = collision_point.y + sign_y * (rand() % 10);	  	 				

	  	 				Molecule* new_molecule = new Molecule;
	  	 				set_values_to_circle_after_rectangles_collide(new_molecule, Point(new_x, new_y), 15.0, small_masses, rand() % 15 * sign_x, rand() % 15 * sign_y, 
	  	 															  Colour(255, 0, 0, 255), CIRCLE, true);


	  	 				new_molecule->move_molecule(100 * DELTA_TIME);

	  	 				add_object(new_molecule);
	  	 				collision_responsed_table.collire_table[first_type][second_type](shapes[first], shapes[second]);
	  	 			}  	

	  	 			count_non_active_objects += 2;	  	 			
	  	 		}
	  		}
	  	}

		/*printf("-------- @@@ types ---------------\n");
		for(size_t i = 0; i < count_objects; ++i) {
			printf("%d ", shapes[i]->get_type());
		}		
		printf("\n----------------------------\n\n");

		printf("-------- @@@ is_active ---------------\n");
		for(size_t i = 0; i < count_objects; ++i) {
			printf("%d ", shapes[i]->get_is_active());
		}		
		printf("\n----------------------------\n\n");			  	

	  	printf("end collision_detection\n");*/
  	}

  	void get_new_rectangle_after_circles_collide(Rectangle* &new_rect, Molecule* first, Molecule* second) {
  		Point first_center  = first->get_center();
	  	Point second_center = second->get_center();

	  	double first_mass  = first->get_mass();
	  	double second_mass = second->get_mass();  	 	

	  	double first_x_speed  = first->get_x_speed (),  first_y_speed = first->get_y_speed ();
	  	double second_x_speed = second->get_x_speed(), second_y_speed = second->get_y_speed();

	 	Vector first_speed  ( Point(0., 0.), Point(first_x_speed,   first_y_speed) );
	 	Vector second_speed ( Point(0., 0.), Point(second_x_speed, second_y_speed) ); 

	  	Vector first_impulse ( first_speed );
	  	first_impulse *= first_mass;

	  	Vector second_impulse ( second_speed );
	  	second_impulse *= second_mass;	

	  	Vector res_impulse ( first_impulse );
	  	res_impulse += second_impulse;
	  	res_impulse /= first_mass + second_mass;

	  	res_impulse.set_point_end   ( res_impulse.get_point_end() - res_impulse.get_point_begin() );
	  	res_impulse.set_point_begin ( Point(0, 0) );

  		Vector vector_to_collision_point ( Point(0., 0.), second_center - first_center );
  		vector_to_collision_point *= first->get_radius();
  		vector_to_collision_point /= first->get_radius() + second->get_radius();
  		vector_to_collision_point.set_point_end ( vector_to_collision_point.get_point_end() + first_center );
  		vector_to_collision_point.set_point_begin ( first_center );

  		//Rectangle new_rect( vector_to_collision_point.get_point_end(), first->get_mass() + second->get_mass(), 
  		//					res_impulse.get_x_end(), res_impulse.get_y_end(), Colour(0, 0, 255, 255), 40.0, 100.0, RECTANGLE, true);

  		new_rect->set_center ( vector_to_collision_point.get_point_end() );

  		new_rect->set_mass   ( first->get_mass() + second->get_mass() );
  		new_rect->set_x_speed( res_impulse.get_x_end() );
  		new_rect->set_y_speed( res_impulse.get_y_end() );
  		new_rect->set_colour ( Colour(0, 0, 255, 255) );
  		new_rect->set_width  ( 40.0 );
  		new_rect->set_height ( 100.0 );
  		new_rect->set_type   ( RECTANGLE );
  		new_rect->set_is_active(true);

  		//return new_rect;
  	}

  	Point get_rectangles_collision_point(Rectangle* first, Rectangle* second) {
  		double first_x_left_up = first->get_x_center() - first->width  / 2.0;
		double first_y_left_up = first->get_y_center() - first->height / 2.0;

		double first_x_right_down = first->get_x_center() + first->width  / 2.0;
		double first_y_right_down = first->get_y_center() + first->height / 2.0;	

		if(is_point_belongs_to_rectangle(second, Point( first_x_left_up, first_y_left_up )))
			return Point( first_x_left_up, first_y_left_up );

		if(is_point_belongs_to_rectangle(second, Point( first_x_left_up, first_y_right_down )))
			return Point( first_x_left_up, first_y_right_down );

		if(is_point_belongs_to_rectangle(second, Point( first_x_right_down, first_y_left_up )))
			return Point( first_x_right_down, first_y_left_up );

		if(is_point_belongs_to_rectangle(second, Point( first_x_right_down, first_y_right_down )))
			return Point( first_x_right_down, first_y_right_down );

		return Point(0, 0);
  	}

  	void set_values_to_circle_after_rectangles_collide(Molecule* molecule, const Point par_point, const double par_radius,  const double par_mass, 
             										   const double par_x_speed, const double par_y_speed, const Colour par_color, 
             										   const Type_object par_type, const bool par_is_active) {
  		molecule->set_center (par_point);
  		molecule->set_radius (par_radius);
  		molecule->set_mass   (par_mass);
  		molecule->set_x_speed(par_x_speed);
  		molecule->set_y_speed(par_y_speed);
  		molecule->set_colour (par_color);
  		molecule->set_type   (par_type);
  		molecule->set_is_active(par_is_active);
  	}

	void add_object(Shape* new_object) {
		shapes[count_objects] = new Shape;
  	 	shapes[count_objects] = new_object;
  	 	++count_objects;
  	}
};

#endif