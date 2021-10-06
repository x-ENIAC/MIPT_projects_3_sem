#include "circle.h"
#include "rectangle.h"
#include "point.h"
#include "my_vector.h"
#include "collision_detection.h"
#include "collision_response.h"

#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H

extern Collision_detection_table collision_detected_table;
extern Collision_response_table collision_responsed_table;

const double DELTA_TIME = 0.05;
const size_t MAX_COUNT_OF_OBJECTS = 5000;

class Object_manager {
  public:
  	Object** objects;
  	size_t count_objects;
  	size_t count_non_active_objects;

  	Object_manager() {
  	 	objects = new Object*[MAX_COUNT_OF_OBJECTS];
  	 	for(size_t i = 0; i < MAX_COUNT_OF_OBJECTS; ++i)
  	 		objects[i] = new Object;

  	 	count_objects = 0;
  	 	count_non_active_objects = 0;
  	}

  	~Object_manager() {
  		printf("Destruct, %ld\n", count_objects);
  		for(size_t i = 0; i < MAX_COUNT_OF_OBJECTS; ++i) {
  			if(objects[i]->get_owner() == OBJECT_OWNER_OBJECT_CLASS) {
  				delete[] objects[i];
  			}
  		}
  	 	delete[] objects;


  	 	count_objects = 0;
  	}

  	void update_circle() {
  	 	for(int i = 0; i < count_objects; ++i)
  	 		objects[i]->move_circle(DELTA_TIME);
  	}

  	void collision_detection(const int screen_width, const int screen_height) {
  		int now_count_object = count_objects;

	  	for(size_t first = 0; first < now_count_object; ++first) {
	  		if(objects[first]->get_type() != WALL && objects[first]->get_is_active())
	  			objects[first]->collision_with_a_wall(screen_width, screen_height);
	  	}

	  	for(size_t first = 0; first < now_count_object; ++first) {
	  		if(!objects[first]->get_is_active() || objects[first]->get_type() == WALL)
	  			continue;

	  	 	for(size_t second = 0; second < now_count_object; ++second) {

	  	 		if(first == second || !objects[second]->get_is_active() || objects[second]->get_type() == WALL)
	  	 			continue;

	  	 		if(!objects[first]->get_is_active() || objects[first]->get_type() == WALL)
	  	 			break;

	  	 		if(objects[first]->get_kinetic_enegry() < 100 && objects[second]->get_kinetic_enegry() < 100)
	  	 			physical_reaction_handler(first, second);
	  	 		else
	  	 			chemical_reaction_handler(first, second);	  	 		
	  		}
	  	}
  	}

  	void physical_reaction_handler(const size_t first, const size_t second) {
  		bool is_collision = collision_detected_table.collide_table[objects[first]->get_type()][objects[second]->get_type()](objects[first], objects[second]);
  		if(!is_collision)
  			return;

		Point first_center  = objects[first]->get_center();
  	 	Point second_center = objects[second]->get_center();

  	 	double first_mass  = objects[first]->get_mass();
  	 	double second_mass = objects[second]->get_mass();  	 	

  	 	double first_x_speed  = objects[first]->get_x_speed (),  first_y_speed = objects[first]->get_y_speed ();
  	 	double second_x_speed = objects[second]->get_x_speed(), second_y_speed = objects[second]->get_y_speed();

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
  	 	objects[first]->set_x_speed ( res_first_speed.get_x_end() );
  	 	objects[first]->set_y_speed ( res_first_speed.get_y_end() );  	

  	 	res_second_speed.set_point_end   ( res_second_speed.get_point_end() - res_second_speed.get_point_begin() );
  	 	res_second_speed.set_point_begin ( Point(0, 0) );
  	 	objects[second]->set_x_speed ( res_second_speed.get_x_end() );
  	 	objects[second]->set_y_speed ( res_second_speed.get_y_end() );	

  	 	objects[first]->move_circle(1 * DELTA_TIME);
  	 	objects[second]->move_circle(1 * DELTA_TIME);  	 	  		
  	}

  	void chemical_reaction_handler(const size_t first, const size_t second) {
	  	int first_type  = objects[first]->get_type();
	  	int second_type = objects[second]->get_type();

		bool is_collision = collision_detected_table.collide_table[first_type][second_type](objects[first], objects[second]);

	  	if(is_collision && first_type == CIRCLE && second_type == CIRCLE) {

			Rectangle* new_rect = new Rectangle;
			get_new_rectangle_after_circles_collide(new_rect, (Circle*)objects[first], (Circle*)objects[second]);

			add_object(new_rect);

	  	 	objects[count_objects - 1]->move_circle(DELTA_TIME);
	  	 	collision_responsed_table.collire_table[first_type][second_type](objects[first], objects[second]);
			count_non_active_objects += 2;	  	
	  	}

	  	else
		if(is_collision && (first_type == CIRCLE && second_type == RECTANGLE || first_type == RECTANGLE && second_type == CIRCLE)) {

			collision_responsed_table.collire_table[first_type][second_type](objects[first], objects[second]);
	  	 			
	  	 	if(first_type == RECTANGLE) {
	  	 		objects[first]->move_circle(DELTA_TIME); // fix objects !!!
	  	 	}
	  	 	else {
	  	 		objects[second]->move_circle(DELTA_TIME);	  	 				 	 			
	  	 	}

	  	 	++count_non_active_objects;	  	 			
	  	}

	  	else
	  	if(is_collision && first_type == RECTANGLE && second_type == RECTANGLE) {

	  	 	Point collision_point = get_rectangles_collision_point((Rectangle*)objects[first], (Rectangle*)objects[second]);
	  	 	double small_masses = (objects[first]->get_mass() + objects[second]->get_mass());
	  	 	double delta_angle = 360.0 / small_masses, angle = 0;

	  	 	Vector vector_to_new_circle(collision_point, Point(collision_point.x + 20.0, collision_point.y));
	  	 	double length_vector_to_new_circle = vector_to_new_circle.get_length_vector();
	  	 	//vector_to_new_circle.rotate_clockwize_vector(delta_angle);

	  	 	for(int i = 0; i < small_masses; ++i) {
	  	 		Circle* new_circle = new Circle;

	  	 		/*printf("angle %lg, speed_x %lg, speed_y %lg; (%lg, %lg) -> (%lg, %lg), length %lg\n", 
	  	 				angle, 2.0 * cos(angle * M_PI / 180.0), 2.0 * sin(angle * M_PI / 180.0), collision_point.x, collision_point.y,
	  	 				vector_to_new_circle.get_x_end(), vector_to_new_circle.get_y_end(), vector_to_new_circle.get_length_vector());*/

	  	 		set_values_to_circle_after_rectangles_collide(new_circle, vector_to_new_circle.get_point_end(), 4.0, 1.0, 
	  	 																	5 * cos(angle * M_PI / 180.0), 5 * sin(angle * M_PI / 180.0), 
	  	 															  		Colour(rand() % 255, rand() % 255, rand() % 255, 255), 
	  	 															  		CIRCLE, true, OBJECT_OWNER_OBJECT_CLASS);

	  	 		//if(i < small_masses)
	  	 		//	new_circle->move_circle(1000.0 * DELTA_TIME);
	  	 		add_object(new_circle);

	  	 		vector_to_new_circle.rotate_clockwize_vector(delta_angle);
	  	 		angle += delta_angle;
		  	}  	

	  	 	collision_responsed_table.collire_table[first_type][second_type](objects[first], objects[second]);	
	  	 	count_non_active_objects += 2;	  	 			
	  	}  		
  	}

  	void get_new_rectangle_after_circles_collide(Rectangle* new_rect, Circle* first, Circle* second) {
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
  													  res_impulse.get_x_end(), res_impulse.get_y_end(), 
  													  Colour(rand() % 255, rand() % 255, rand() % 255, 255), 
  													  20.0, 20.0, RECTANGLE, true, OBJECT_OWNER_OBJECT_CLASS );
  	}

  	Point get_rectangles_collision_point(Rectangle* first, Rectangle* second) {
  		double first_x_left_up = first->get_x_center() - first->width  / 2.0;
		double first_y_left_up = first->get_y_center() - first->height / 2.0;

		double first_x_right_down = first->get_x_center() + first->width  / 2.0;
		double first_y_right_down = first->get_y_center() + first->height / 2.0;	

  		double second_x_left_up = second->get_x_center() - second->width  / 2.0;
		double second_y_left_up = second->get_y_center() - second->height / 2.0;

		double second_x_right_down = second->get_x_center() + second->width  / 2.0;
		double second_y_right_down = second->get_y_center() + second->height / 2.0;			

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
             										   const Type_object par_type, const bool par_is_active, const Object_owner par_owner) {
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

  	void set_values_to_circle_after_rectangles_collide(Circle* circle, const Point par_point, const double par_radius,  const double par_mass, 
             										   const double par_x_speed, const double par_y_speed, const Colour par_color, 
             										   const Type_object par_type, const bool par_is_active, const Object_owner par_owner) {
  		circle->set_center (par_point);
  		circle->set_radius (par_radius);
  		circle->set_mass   (par_mass);
  		circle->set_x_speed(par_x_speed);
  		circle->set_y_speed(par_y_speed);
  		circle->set_colour (par_color);
  		circle->set_type   (par_type);
  		circle->set_is_active(par_is_active);
  		circle->set_owner(par_owner);  		
  	}

  	size_t get_count_of_objects(const Type_object type_object) {
  		size_t count = 0;

  		for(int i = 0; i < count_objects; ++i)
  			if(type_object == objects[i]->get_type() && objects[i]->get_is_active())
  				++count;

  		return count;
  	}

	void add_object(Object* new_object) {
  	 	objects[count_objects] = new_object;
  	 	++count_objects;
  	 	//printf("count %ld\n", count_objects);

  	 	//if(MAX_COUNT_OF_OBJECTS * 2 <= count_objects * 3)
  	 	//	remove_inactive_items();
  	}

  	/*void remove_inactive_items() {
  		printf("begin remove\n");

  		size_t real_count_objects = 0;
  		for(size_t i = 0; i < count_objects; ++i)
  			if(objects[i]->get_type())
  				++real_count_objects;

  		printf("open file\n");
  		FILE* log_file = fopen("logs.txt", "w");
  		for(size_t i = 0; i < count_objects; ++i) {
  			fprintf(log_file, "%d ", objects[i]->get_type());
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
  			size_t now_is_active = objects[now_pos]->get_type();

  			if(now_is_active == 0 && first_free_pos == -1) { 
  					first_free_pos = now_pos;

  			} else if(now_is_active > 0) {
                objects[first_free_pos] = objects[now_pos];
                ++first_free_pos;
  			}

  			++now_pos;
  		}

  		fprintf(log_file, "\n");
  		for(size_t i = 0; i < real_count_objects; ++i)
  			fprintf(log_file, "%d ", objects[i]->get_type());
  		fprintf(log_file, "\n------------------------------------------------------\n");  		
  		fclose(log_file);
  		printf("close file\n");

  		//for(size_t i = real_count_objects; i < MAX_COUNT_OF_OBJECTS; ++i)
  		//	delete[] objects[i];

  		count_objects = real_count_objects;
  		count_non_active_objects = 0;
  		printf("end remove\n");

  	}*/
};

#endif