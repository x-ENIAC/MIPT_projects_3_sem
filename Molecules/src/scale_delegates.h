//#include "object_manager.h"
#include "button_delegate.h"
#include "chart.h"

#ifndef SCALE_DELEGATES_H
#define SCALE_DELEGATES_H

/*class Scale_x_delegate : public Button_delegate {
  public:

  	View_manager* view_manager;

  	Scale_x_delegate(View_manager* par_view_manager) {
  		view_manager = new View_manager;
  		view_manager = par_view_manager;
  	}

  	void click_reaction() override {
		for(size_t i = 0; i < view_manager->count_of_view_objects; ++i)
			if(view_manager->view_objects[i]->type == CHART_VIEW_TYPE) {
				Amount_chart* chart = (Amount_chart*)(view_manager->view_objects[i]);
				chart->x_scale += 0.01;
			}
	}
};*/

class Scale_y_delegate : public Button_delegate {
  public:

  	View_manager* view_manager;

  	Scale_y_delegate(View_manager* par_view_manager) {
  		view_manager = new View_manager;
  		view_manager = par_view_manager;
  	}

  	void click_reaction() override {
  		FILE* log = fopen("log.txt", "w");

  		fprintf(log, "into click react chart!\n count %lu\n", view_manager->count_of_view_objects);

		for(size_t i = 0; i < view_manager->count_of_view_objects; ++i) {
			//printf("\ttype %d\n", view_manager->view_objects[i]->type);

			if(view_manager->view_objects[i]->type == CHART_VIEW_TYPE) {
				Amount_chart* chart = (Amount_chart*)(view_manager->view_objects[i]);
				size_t count_of_points = chart->count_drawable_points;

				fprintf(log, "\t\tcount %lu\n", count_of_points);

				chart->y_scale += 0.01;

	        	Point coord_center(-chart->shape.width / 2.0, chart->shape.height / 2.0);
			    coord_center += chart->center;
        		
        		for(size_t j = 0; j < count_of_points; ++j) {
        			if(chart->points[j].x == 300)
	            		fprintf(log, "(%lg, %lg) -> (%lg, %lg)\n", coord_center.x, coord_center.y, chart->points[j].x, chart->points[j].y);        			
		            chart->points[j] -= coord_center;

	            	chart->points[j].y *= chart->y_scale;
	            	if(chart->points[j].x == 300)
	            		fprintf(log, "scale %lg\n", chart->y_scale);

	            	chart->points[j] += coord_center;
	            	if(chart->points[j].x == 300)
	            		fprintf(log, "(%lg, %lg) -> (%lg, %lg)\n\n", coord_center.x, coord_center.y, chart->points[j].x, chart->points[j].y);

	            	((Amount_chart*)(view_manager->view_objects[i]))->points[j] = chart->points[j];
	            }

			}
		}

		fclose(log);
	}
};

#endif