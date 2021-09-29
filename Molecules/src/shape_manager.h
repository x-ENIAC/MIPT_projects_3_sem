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
const size_t MAX_COUNT_OF_OBJECTS = 5000;

class Shape_manager {
  public:
  	Shape** shapes;
  	size_t count_objects;
  	size_t count_non_active_objects;

  	Shape_manager() {
  	 	shapes = new Shape*[MAX_COUNT_OF_OBJECTS];
  	 	for(size_t i = 0; i < MAX_COUNT_OF_OBJECTS; ++i)
  	 		shapes[i] = new Shape;

  	 	count_objects = 0;
  	 	count_non_active_objects = 0;
  	}

  	~Shape_manager() {
  		printf("Destruct, %ld\n", count_objects);
  		for(size_t i = 0; i < MAX_COUNT_OF_OBJECTS; ++i) {
  			if(shapes[i]->get_owner() == SHAPE_OWNER_SHAPE_CLASS) {
  				delete[] shapes[i];
  			}
  		}
  	 	delete[] shapes;


  	 	count_objects = 0;
  	}

  	void update_molecule() {
  	 	for(int i = 0; i < count_objects; ++i)
  	 		shapes[i]->move_molecule(DELTA_TIME);
  	}

  	void collision_detection(const int screen_width, const int screen_height) {
  		int now_count_object = count_objects;

	  	for(size_t first = 0; first < now_count_object; ++first) {
	  		if(shapes[first]->get_type() != WALL && shapes[first]->get_is_active())
	  			shapes[first]->collision_with_a_wall(screen_width, screen_height);
	  	}

	  	for(size_t first = 0; first < now_count_object; ++first) {
	  		if(!shapes[first]->get_is_active() || shapes[first]->get_type() == WALL)
	  			continue;

	  	 	for(size_t second = 0; second < now_count_object; ++second) {

	  	 		if(first == second || !shapes[second]->get_is_active() || shapes[second]->get_type() == WALL)
	  	 			continue;

	  	 		if(!shapes[first]->get_is_active() || shapes[first]->get_type() == WALL)
	  	 			break;

	  	 		//printf("%lg, %g\n", shapes[first]->get_kinetic_enegry(), shapes[second]->get_kinetic_enegry());
	  	 		//if(shapes[first]->get_kinetic_enegry() < 200 && shapes[second]->get_kinetic_enegry() < 200)
	  	 		//	physical_reaction_handler(first, second);
	  	 		//else
	  	 			chemical_reaction_handler(first, second);	  	 		
	  		}
	  	}
  	}

  	void physical_reaction_handler(const size_t first, const size_t second) {
  		bool is_collision = collision_detected_table.collide_table[shapes[first]->get_type()][shapes[second]->get_type()](shapes[first], shapes[second]);
  		if(!is_collision)
  			return;

		Point first_center  = shapes[first]->get_center();
  	 	Point second_center = shapes[second]->get_center();

  	 	double first_mass  = shapes[first]->get_mass();
  	 	double second_mass = shapes[second]->get_mass();  	 	

  	 	double first_x_speed  = shapes[first]->get_x_speed (),  first_y_speed = shapes[first]->get_y_speed ();
  	 	double second_x_speed = shapes[second]->get_x_speed(), second_y_speed = shapes[second]->get_y_speed();

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
  	 	shapes[first]->set_x_speed ( res_first_speed.get_x_end() );
  	 	shapes[first]->set_y_speed ( res_first_speed.get_y_end() );  	

  	 	res_second_speed.set_point_end   ( res_second_speed.get_point_end() - res_second_speed.get_point_begin() );
  	 	res_second_speed.set_point_begin ( Point(0, 0) );
  	 	shapes[second]->set_x_speed ( res_second_speed.get_x_end() );
  	 	shapes[second]->set_y_speed ( res_second_speed.get_y_end() );	

  	 	shapes[first]->move_molecule(10 * DELTA_TIME);
  	 	shapes[second]->move_molecule(10 * DELTA_TIME);  	 	  		
  	}

  	void chemical_reaction_handler(const size_t first, const size_t second) {
	  	int first_type  = shapes[first]->get_type();
	  	int second_type = shapes[second]->get_type();

		bool is_collision = collision_detected_table.collide_table[first_type][second_type](shapes[first], shapes[second]);

	  	if(is_collision && first_type == CIRCLE && second_type == CIRCLE) {

			Rectangle* new_rect = new Rectangle;
			get_new_rectangle_after_circles_collide(new_rect, (Molecule*)shapes[first], (Molecule*)shapes[second]);
			/*printf("(%lg, %lg), speed %lg, %lg, widht %lg, hegith %lg\n", new_rect->get_x_center(), new_rect->get_y_center(), 
																		  new_rect->get_x_speed(), new_rect->get_y_speed(),
																		  new_rect->get_width(), new_rect->get_height());*/

			add_object(new_rect);

	  	 	shapes[count_objects - 1]->move_molecule(DELTA_TIME);
	  	 	collision_responsed_table.collire_table[first_type][second_type](shapes[first], shapes[second]);
			count_non_active_objects += 2;	  	
	  	}

	  	else
		if(is_collision && (first_type == CIRCLE && second_type == RECTANGLE || first_type == RECTANGLE && second_type == CIRCLE)) {

			collision_responsed_table.collire_table[first_type][second_type](shapes[first], shapes[second]);
	  	 			
	  	 	if(first_type == RECTANGLE) {
	  	 		shapes[first]->move_molecule(DELTA_TIME); // fix shapes !!!
	  	 	}
	  	 	else {
	  	 		shapes[second]->move_molecule(DELTA_TIME);	  	 				 	 			
	  	 	}

	  	 	++count_non_active_objects;	  	 			
	  	}

	  	else
	  	if(is_collision && first_type == RECTANGLE && second_type == RECTANGLE) {

	  	 	Point collision_point = get_rectangles_collision_point((Rectangle*)shapes[first], (Rectangle*)shapes[second]);
	  	 	double small_masses = (shapes[first]->get_mass() + shapes[second]->get_mass());

	  	 	for(int i = 0; i < small_masses; ++i) {
	  	 		int sign_x = (rand() % 2 ? -1 : 1), sign_y = (rand() % 2 ? -1 : 1); 	 

	  	 		double new_x = collision_point.x + sign_x * (rand() % 30);
	  	 		double new_y = collision_point.y + sign_y * (rand() % 30);	  	 				

	  	 		Molecule* new_molecule = new Molecule;
	  	 		set_values_to_circle_after_rectangles_collide(new_molecule, Point(new_x, new_y), rand() % 7 + 8, 1.0, 
	  	 																	10 * sign_x, 10 * sign_y, 
	  	 															  		Colour(255, 0, 0, 255), CIRCLE, true, SHAPE_OWNER_SHAPE_CLASS);

	  	 		new_molecule->move_molecule(10 * DELTA_TIME);
	  	 		add_object(new_molecule);
		  	}  	

	  	 	collision_responsed_table.collire_table[first_type][second_type](shapes[first], shapes[second]);	
	  	 	count_non_active_objects += 2;	  	 			
	  	}  		
  	}

  	void get_new_rectangle_after_circles_collide(Rectangle* new_rect, Molecule* first, Molecule* second) {
  		Point first_center   = first->get_center(),  second_center  = second->get_center();

	  	double first_mass    = first->get_mass(),    second_mass    = second->get_mass();  	 	
	  	double first_x_speed = first->get_x_speed(), second_x_speed = second->get_x_speed();
	  	double first_y_speed = first->get_y_speed(), second_y_speed = second->get_y_speed();

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

  		set_values_to_rectangle_after_circles_collide(new_rect, vector_to_collision_point.get_point_end(), first->get_mass() + second->get_mass(),
  													  res_impulse.get_x_end(), res_impulse.get_y_end(), Colour(0, 0, 255, 255), 
  													  30.0, 30.0, RECTANGLE, true, SHAPE_OWNER_SHAPE_CLASS );
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

  	void set_values_to_rectangle_after_circles_collide(Rectangle* rectangle, const Point par_point, const double par_mass, 
             										   const double par_x_speed, const double par_y_speed, const Colour par_color, 
             										   const double par_width, const double par_height,
             										   const Type_object par_type, const bool par_is_active, const Shape_owner par_owner) {
  		rectangle->set_center (par_point);
  		rectangle->set_mass   (par_mass);
  		rectangle->set_x_speed(par_x_speed);
  		rectangle->set_y_speed(par_y_speed);
  		rectangle->set_width  (par_width);
  		rectangle->set_height (par_height );  		
  		rectangle->set_colour (par_color);
  		rectangle->set_type   (par_type);
  		rectangle->set_is_active(par_is_active);
  		rectangle->set_owner(par_owner);
  	}  	

  	void set_values_to_circle_after_rectangles_collide(Molecule* molecule, const Point par_point, const double par_radius,  const double par_mass, 
             										   const double par_x_speed, const double par_y_speed, const Colour par_color, 
             										   const Type_object par_type, const bool par_is_active, const Shape_owner par_owner) {
  		molecule->set_center (par_point);
  		molecule->set_radius (par_radius);
  		molecule->set_mass   (par_mass);
  		molecule->set_x_speed(par_x_speed);
  		molecule->set_y_speed(par_y_speed);
  		molecule->set_colour (par_color);
  		molecule->set_type   (par_type);
  		molecule->set_is_active(par_is_active);
  		molecule->set_owner(par_owner);  		
  	}

	void add_object(Shape* new_object) {
  	 	shapes[count_objects] = new_object;
  	 	++count_objects;
  	 	printf("count %ld\n", count_objects);

  	 	//if(MAX_COUNT_OF_OBJECTS * 2 <= count_objects * 3)
  	 	//	remove_inactive_items();
  	}

  	/*void remove_inactive_items() {
  		printf("begin remove\n");

  		size_t real_count_objects = 0;
  		for(size_t i = 0; i < count_objects; ++i)
  			if(shapes[i]->get_type())
  				++real_count_objects;

  		printf("open file\n");
  		FILE* log_file = fopen("logs.txt", "w");
  		for(size_t i = 0; i < count_objects; ++i) {
  			fprintf(log_file, "%d ", shapes[i]->get_type());
  		}
  		printf("\n");
  		fclose(log_file);
  		printf("close file\n");

  		printf("open file\n");
  		log_file = fopen("logs.txt", "a");
  		fprintf(log_file, "real_count_objects %ld\n", real_count_objects);


  		int first_free_pos = -1;
  		size_t now_pos = 0;

  		while(now_pos < count_objects) {
  			size_t now_is_active = shapes[now_pos]->get_type();

  			if(now_is_active == 0 && first_free_pos == -1) { 
  					first_free_pos = now_pos;

  			} else if(now_is_active > 0) {
                shapes[first_free_pos] = shapes[now_pos];
                ++first_free_pos;
  			}

  			++now_pos;
  		}

  		fprintf(log_file, "\n");
  		for(size_t i = 0; i < real_count_objects; ++i)
  			fprintf(log_file, "%d ", shapes[i]->get_type());
  		fprintf(log_file, "\n------------------------------------------------------\n");  		
  		fclose(log_file);
  		printf("close file\n");

  		//for(size_t i = real_count_objects; i < MAX_COUNT_OF_OBJECTS; ++i)
  		//	delete[] shapes[i];

  		count_objects = real_count_objects;
  		count_non_active_objects = 0;
  		printf("end remove\n");

  	}*/
};

#endif