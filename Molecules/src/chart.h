#include "point.h"

const int MAX_SIZE_POINTS_ARRAY = 3000;

class Amount_chart {
  public:
  	Point* points;
  	int count_drawable_points;

  	Rectangle shape;

  	size_t count_of_areas;

  	Amount_chart() :
  		shape() {
  		count_drawable_points = 0;
  		points = new Point[MAX_SIZE_POINTS_ARRAY];
  		count_of_areas = 0;
  	}  	

  	Amount_chart(const Point par_point, const Colour par_color, const int par_width, const int par_height) :
  		shape(par_point, 0.0, 0.0, 0.0, par_color, par_width, par_height, RECTANGLE, false) {
  		count_drawable_points = 0;
  		points = new Point[MAX_SIZE_POINTS_ARRAY];
  		count_of_areas = 0;
  	}

  	void add_point(Point new_point) { 
  		if(count_drawable_points + 1 >= MAX_SIZE_POINTS_ARRAY)
  			update_point_array();

  		const double width = shape.get_width();

  		points[count_drawable_points] = Point(new_point.x, shape.get_y_center() + shape.get_height() / 2.0 - new_point.y, new_point.color);
  		++count_drawable_points;
  	}

  	void update_point_array() {
  		count_drawable_points = 0;
  	}

  	void draw_chart(SDL_Renderer* render, const bool need_area) {
  		if(need_area)
  			draw_area(render);

  		for(int i = 0; i < count_drawable_points; ++i) {
  			points[i].draw_point(render);
  		}
  	}

  	void draw_area(SDL_Renderer* render) {
  		shape.draw_molecule(render);
  	}

  	~Amount_chart() {
  		delete[] points;
  	}
};