#include <SDL2/SDL.h>
#include "point.h"
#include "colour.h"
#include "rectangle.h"
#include "text.h"
#include "button_delegate.h"
#include "view.h"

#ifndef BUTTON_H
#define BUTTON_H

const size_t MAX_COUNT_OF_VIEW_OBJECTS_FOR_BUTTON = 5;
//extern const char NON_PATH_TO_PUCTURE[];

/*enum Button_status {
	IS_PUSH 	= 1,
	IS_NOT_PUSH = 2,
};*/

/*enum Button_owner {
    BUTTON_OWNER_BUTTON_CLASS = 0,
    BUTTON_OWNER_USER         = 1,
    BUTTON_OWNER_OTHER_CLASS  = 2,
};*/

class Button : public View_object {
  public:
	Button_delegate* delegate;

	//Button_status status;
	//Button_owner owner;

	View_object** view_objects;
	size_t count_of_views;

	Button() : View_object(Widget_types::BUTTON) {

  	 	view_objects = new View_object*[MAX_COUNT_OF_VIEW_OBJECTS_FOR_BUTTON];

  	 	for(size_t i = 0; i < MAX_COUNT_OF_VIEW_OBJECTS_FOR_BUTTON; ++i)
  	 		view_objects[i] = new View_object;
  	 	count_of_views = 0;
	}	

	Button(Button_delegate* par_delegate, const Point par_point, const Colour par_button_color, const double par_width, const double par_height, 
								/*const Button_owner par_owner, */char text_on_button[] = " ", const Colour par_text_color = BLACK,
																  const char* par_path_to_picture = NON_PATH_TO_PUCTURE) :
	  View_object (par_point, par_width, par_height, par_button_color, Widget_types::BUTTON, par_path_to_picture) {

	  	//printf("%s\n", NON_PATH_TO_PUCTURE);
	  	delegate = par_delegate;

	  	//status = IS_NOT_PUSH;

  	 	view_objects = new View_object*[MAX_COUNT_OF_VIEW_OBJECTS_FOR_BUTTON];
  	 	for(size_t i = 0; i < MAX_COUNT_OF_VIEW_OBJECTS_FOR_BUTTON; ++i)
  	 		view_objects[i] = new View_object;
  	 	count_of_views = 0;

	  	Point text_center = par_point;

	  	Text* text = new Text(text_center, text_on_button, par_width, par_height, par_text_color);
	  	view_objects[count_of_views++] = text;
	}

	~Button() {
		printf("~Button\n");
		delete delegate;

		for(size_t i = 0; i < count_of_views; ++i)
			delete[] view_objects[i];

		delete[] view_objects;

		count_of_views = 0;
	}

  	bool check_click(const double mouse_x, const double mouse_y, const Mouse_click_state* par_mouse_status) override {
  		if(rect->is_point_belongs_to_rectangle( Point(mouse_x, mouse_y) )) {
  			delegate->click_reaction();
  			return true;
  		}

  		return false;
  	}

	void draw(SDL_Renderer** render, SDL_Texture** texture, SDL_Surface** screen/*, Texture_manager* texture_manager*/) override {
		if(is_visible) {
			rect->draw(*render);

			if(this->texture->is_using_texture) {
				SDL_Rect sdl_rect;
	    		sdl_rect.w = rect->get_width();
			    sdl_rect.h = rect->get_height();
	    		sdl_rect.x = rect->get_center().x - sdl_rect.w / 2.0;
	    		sdl_rect.y = rect->get_center().y - sdl_rect.h / 2.0;

	    		//printf("(%d, %d), %d, %d\n", sdl_rect.x, sdl_rect.y, sdl_rect.w, sdl_rect.h);

    			this->texture->draw_texture(&sdl_rect);				
			}

			/*if(strcmp(NON_PATH_TO_PUCTURE, path_to_picture)) {
				//printf("%s\n", path_to_picture);
	    		SDL_Rect sdl_rect;
	    		sdl_rect.w = rect->get_width();
			    sdl_rect.h = rect->get_height();
	    		sdl_rect.x = rect->get_center().x - sdl_rect.w / 2.0;
	    		sdl_rect.y = rect->get_center().y - sdl_rect.h / 2.0;

	    		//printf("(%d, %d), %d, %d\n", sdl_rect.x, sdl_rect.y, sdl_rect.w, sdl_rect.h);

    			texture_manager->draw_texture(path_to_picture, &sdl_rect);

    			
			}*/

			else
				for(size_t i = 0; i < count_of_views; ++i)
					view_objects[i]->draw(render, texture, screen/*, texture_manager*/);
		}
	}

	void update_position(const Point new_center) {
		Point old_center(rect->get_center());

		rect->set_center(new_center);
		center = new_center;

		for(size_t i = 0; i < count_of_views; ++i) {
			Point new_view_center(view_objects[i]->rect->get_center());

			new_view_center += new_center;
			new_view_center -= old_center;

			view_objects[i]->rect->set_center(new_view_center);
			view_objects[i]->center = new_view_center;
		}
	}

	void delete_all() {
		printf("begin button delete_all\n");

		for(size_t i = 0; i < count_of_views; ++i) {
			//view_objects[i]->delete_all();
			delete[] view_objects[i];
		}

		printf("middle button delete_all\n");

		// delete[] view_objects;
		count_of_views = 0;

		//delete delegate;
		printf("end button delete_all\n");
	}

	/*inline Button_owner get_owner() const {
		return owner;
	}*/

	//inline void set_owner(const Button_owner new_owner) {
	//	owner = new_owner;
	//}
};

#endif


