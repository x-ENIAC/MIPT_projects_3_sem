#include <SDL2/SDL.h>

#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle {
  public:
	Point center;
	double width;
	double height;
	Colour color;
	bool is_active;

	Rectangle() {
		center = Point(0, 0);
		width  = 0;
		height = 0;
		color = BLACK;
		is_active = true;
	}    


	Rectangle(const Point par_point, const double par_width, const double par_height, const Colour par_color, const bool par_is_active) {
		center = par_point;
		width  = par_width;
		height = par_height;
		color = par_color;
		is_active = par_is_active;
	}

	~Rectangle() {
		/*set_width  (0 );
		set_height ( 0 );*/
	}

	void draw(SDL_Renderer* render) {
		for(size_t x = center.x - width / 2.0; x <= center.x + width / 2.0; ++x) {
			for(size_t y = center.y - height / 2.0; y <= center.y + height / 2.0; ++y) {
				Point now_point(x, y, color);
				now_point.draw_point(render);
			}
		}
	}

	/*bool is_point_belongs_to_object(Point point) {
		return ((get_x_center() - width  / 2.0 <= point.x && point.x <= get_x_center() + width  / 2.0) &&
				(get_y_center() - height / 2.0 <= point.y && point.y <= get_y_center() + height / 2.0));
	}

	bool is_point_belongs_to_object(const double x, const double y) {
		return ((get_x_center() - width  / 2.0 <= x && x <= get_x_center() + width  / 2.0) &&
				(get_y_center() - height / 2.0 <= y && y <= get_y_center() + height / 2.0));
	}*/

	virtual void make_inactive() {
		set_is_active( false );
		set_colour ( WHITE );
		set_center  ( Point(0.0, 0.0) );
		set_height ( 0.0 );
		set_width  ( 0.0 );
		//set_type ( WALL );
	}    

	Rectangle& operator=(const Rectangle& new_object) {

		set_center( new_object.get_center() );
	   
		set_width ( new_object.get_width() );
		set_height( new_object.get_height() );
		
		set_colour (  new_object.get_colour() );
		//set_type  (  new_object.get_type() );

		set_is_active ( new_object.get_is_active() );

		return *this;
	}    

	bool is_point_belongs_to_rectangle(Point point) {
		double x_left_up = get_x_center() - width  / 2.0;
		double y_left_up = get_y_center() - height / 2.0;

		double x_right_down = get_x_center() + width  / 2.0;
		double y_right_down = get_y_center() + height / 2.0;

		double x_point = point.x, y_point = point.y;    

		//printf("well, check. %lg <= %lg <= %lg, %lg <= %lg <= %lg\n", x_left_up, x_point, x_right_down, y_left_up, y_point, y_right_down);

		return (x_left_up <= x_point && x_point <= x_right_down) &&
			   (y_left_up <= y_point && y_point <= y_right_down);
	}

	bool is_point_belongs_to_rectangle(const double x, const double y) {
		double x_left_up = get_x_center() - width  / 2.0;
		double y_left_up = get_y_center() - height / 2.0;

		double x_right_down = get_x_center() + width  / 2.0;
		double y_right_down = get_y_center() + height / 2.0;

		//printf("well, check. %lg <= %lg <= %lg, %lg <= %lg <= %lg\n", x_left_up, x_point, x_right_down, y_left_up, y_point, y_right_down);

		return (x_left_up <= x && x <= x_right_down) &&
			   (y_left_up <= y && y <= y_right_down);
	}	

	Point get_left_up_corner() const {
		return Point(center.x - width / 2, center.y - height / 2);
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

	inline double get_width() const {
		return width;
	} 

	inline double get_height() const {
		return height;
	}

	inline Colour get_colour() const {
		return color;
	}

	inline bool get_is_active() const {
		return is_active;
	}       

	inline void set_center(const Point new_center) {
		center = new_center;
	}

	inline void set_width(const double new_width) {
		width = new_width;
	} 

	inline void set_height(const double new_height) {
		height = new_height;
	}

	inline void set_colour(const Colour new_color) {
		color = new_color;
	}

	inline void set_is_active(const bool new_is_active) {
		is_active = new_is_active;
	}
};

#endif