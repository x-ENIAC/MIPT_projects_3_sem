#include "view.h"

#ifndef VIEW_MANAGER_H
#define VIEW_MANAGER_H

const size_t MAX_COUNT_OF_VIEW_OBJECTS = 100;

class View_manager {
  public:
	View_object** view_objects;
	size_t count_of_view_objects;

  	View_manager() {
  	 	count_of_view_objects = 0;
  		printf("Construct View_manager, %ld\n", count_of_view_objects);
  	 	view_objects = new View_object*[MAX_COUNT_OF_VIEW_OBJECTS];
  	 	for(size_t i = 0; i < MAX_COUNT_OF_VIEW_OBJECTS; ++i)
  	 		view_objects[i] = new View_object;

  	}

  	~View_manager() {
  		printf("Destruct View_manager, %ld\n", count_of_view_objects);

  	 	count_of_view_objects = 0;
  	}			

	void add_view_object(View_object* new_view) {
  	 	view_objects[count_of_view_objects] = new_view;
  	 	//printf("(%lg, %lg) ? (%lg, %lg)\n", new_view->center.x, new_view->center.y, view_objects[count_of_view_objects]->center.x, view_objects[count_of_view_objects]->center.y);
  	 	++count_of_view_objects;
  	 	//printf("add_view_object, count_of_view_objects %ld\n", count_of_view_objects);
  	}  	

  	void draw(SDL_Renderer** render, SDL_Texture** texture) {
  		for(size_t i = 0; i < count_of_view_objects; ++i) {
  			view_objects[i]->draw(render, texture);
  		}
  	}

  	bool check_click(const double mouse_x, const double mouse_y) {
  		for(size_t i = 0; i < count_of_view_objects; ++i) {
  			printf("z, type %d\n", view_objects[i]->type);
  			if(view_objects[i]->check_click(mouse_x, mouse_y))
  				return true;
  		}

  		return false;
  	}
};

#endif