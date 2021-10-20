#include "view.h"
#include "button.h"
#include "canvas_manager.h"
#include "pencil.h"
#include "palette.h"
#include "tab.h"
//#include "widget_types.h"

#ifndef VIEW_MANAGER_H
#define VIEW_MANAGER_H

class Create_new_canvas_delegate;

extern const double DELTA_BETWEEN_BUTTONS;
extern const double WIDTH_CLOSE_BUTTON;
extern const double HEIGHT_CLOSE_BUTTON;
extern const double WIDTH_TABS_BUTTON;
extern const double HEIGHT_TABS_BUTTON;

const double WIDTH_FILE_PANEL_BUTTON = 60;

class View_manager : public View_object {
  public:
	View_object** view_objects;
	size_t count_of_view_objects;
	int who_is_active;

	Pencil pencil;

	Button_manager* tool_buttons_manager;
	//Tab** tabs;
	//size_t count_of_tabs;
	//Button_manager* canvases_manager;

	Mouse_click_state mouse_click_state;

  	View_manager(const Point par_point, const double par_width, const double par_height, const Colour par_color, const bool par_is_active) :
  	  View_object(par_point, par_width, par_height, LIGHT_GREY, Widget_types::VIEW_MANAGER) {

  	 	count_of_view_objects = 1;
  		printf("Construct View_manager, %ld\n", count_of_view_objects);

  	 	view_objects = new View_object*[MAX_COUNT_OF_VIEW_OBJECTS];
  	 	for(size_t i = 0; i < MAX_COUNT_OF_VIEW_OBJECTS; ++i)
  	 		view_objects[i] = new View_object;

        Point center_of_button_manager(par_width / 2.0, HEIGHT_CLOSE_BUTTON / 2.0), left_up_corner = rect->get_left_up_corner();
        center_of_button_manager += left_up_corner;

        tool_buttons_manager = new Button_manager(center_of_button_manager, par_width, HEIGHT_CLOSE_BUTTON, WHITE);
        add_view_object(tool_buttons_manager);

        fill_tools_button_manager(tool_buttons_manager, left_up_corner, par_width, par_height);

  	 	who_is_active = -1;

  	 	pencil = {};

  	 	/*tabs = new Tab*[MAX_COUNT_OF_VIEW_OBJECTS];
  	 	for(size_t i = 0; i < MAX_COUNT_OF_VIEW_OBJECTS; ++i)
  	 		tabs[i] = new Tab;*/

  	 	//count_of_tabs = 0;

  	 	mouse_click_state = Mouse_click_state::MOUSE_UP;

  	 	Palette* palette = new Palette(par_width - WIDTH_CLOSE_BUTTON, HEIGHT_CLOSE_BUTTON * 3, &pencil);
  	 	add_view_object(palette);
  	}

    void fill_tools_button_manager(Button_manager* tool_buttons_manager, Point left_up_corner, const double par_width, const double par_height);

  	~View_manager() {
  		printf("Destruct View_manager, %ld\n", count_of_view_objects);

  	 	count_of_view_objects = 0;
  	 	who_is_active = 0;
  	}

  	void add_new_canvas_manager(const Point center, const double width, const double height) {
        Point center_tab((WIDTH_TABS_BUTTON + WIDTH_CLOSE_BUTTON) * widget_types[(int)Widget_types::TABS] + WIDTH_TABS_BUTTON / 2.0 + WIDTH_CLOSE_BUTTON / 2.0,
        				 HEIGHT_CLOSE_BUTTON + HEIGHT_TABS_BUTTON / 2.0);

        center_tab += rect->get_left_up_corner();

  		Canvas_manager* new_canvas_manager = new Canvas_manager(center, width, height, WHITE, &pencil, false, &mouse_click_state, 
  																center_tab, widget_types[(int)Widget_types::TABS]);

  		++widget_types[(int)Widget_types::TABS];

  		add_view_object(new_canvas_manager);
  	}

	void add_view_object(View_object* new_view) {
  	 	view_objects[count_of_view_objects] = new_view;
  	 	++count_of_view_objects;

  	 	++widget_types[new_view->get_yourself_type()];
  	}  	

  	void draw(SDL_Renderer** render, SDL_Texture** texture) override {
  		if(is_visible) {
	  		rect->draw(*render);

	  		for(size_t i = 0; i < count_of_view_objects; ++i) {
	  			view_objects[i]->draw(render, texture);
	  		}
	  	}
  	}

	bool try_to_find_corpse() {
	  	for(size_t i = 0; i < count_of_view_objects; ++i) {
	  		if(view_objects[i]->is_visible && !view_objects[i]->is_active)
	  			view_objects[i]->delete_object();
	  	}		
	}

	bool delete_object() override {
		//delete_object()
		printf("Hello, world!\n");

        for(size_t i = 1; i < count_of_view_objects; ++i) {
        	printf("type %d\n", view_objects[i]->get_yourself_type());
            view_objects[i]->delete_object();
        }

        return false;		
	}

  	void check_events(SDL_Event* event) {
		if(event->type == SDL_MOUSEBUTTONUP) {
			mouse_click_state = Mouse_click_state::MOUSE_UP;
			//printf("up\n");
		}

		if(event->type == SDL_MOUSEBUTTONDOWN) {
			mouse_click_state = Mouse_click_state::MOUSE_DOWN;
			double x_mouse = event->button.x, y_mouse = event->button.y;
			//printf("down\n");

			bool is_solved = check_click(x_mouse, y_mouse, &mouse_click_state);
			if(!is_solved)
				printf("!!!WARNING!!!\n");
		}		

		else if(event->type == SDL_MOUSEMOTION) {
			double x_mouse = event->button.x, y_mouse = event->button.y;

			if(mouse_click_state == Mouse_click_state::MOUSE_DOWN)
				mouse_click_state = Mouse_click_state::MOUSE_DOWN_AND_MOTION;
			//printf("motion\n");

			if(mouse_click_state == Mouse_click_state::MOUSE_DOWN_AND_MOTION) {
				check_click(x_mouse, y_mouse, &mouse_click_state);		
			}
		}

		else if(event->type == SDL_KEYDOWN) {
			bool is_solved = check_tap(event);
			if(!is_solved)
				printf("!!!WARNING!!!\n");
		}
  	}

  	bool check_click(const double mouse_x, const double mouse_y, const Mouse_click_state* par_mouse_status) override {

  		if(is_active) {

  			//printf("click View_manager\n");
	  		for(int i = count_of_view_objects - 1; i >= 0; --i) {
	  			//printf("type %d\n", get_yourself_type());
	  			if(view_objects[i]->check_click(mouse_x, mouse_y, par_mouse_status)) {
	  				set_new_active_object(i);

	  				return true;
	  			}
	  		}

	  	}

  		return false;
  	}

  	bool check_tap(SDL_Event* event) {
  		//if(event->key.repeat != 0) // клавиша зажата
  		//	printf("NICE\n");

        switch (event->key.keysym.sym) {                    
            case SDLK_b:					// black
            	pencil.set_color(BLACK);
                return true;

            case SDLK_r:					// RED
            	pencil.set_color(RED);
                return true;

            case SDLK_g:					// GREEN
            	pencil.set_color(GREEN);
                return true;

            case SDLK_y:					// YELLOW
            	pencil.set_color(YELLOW);
                return true;

            case SDLK_l:					// BLUE (l)
            	pencil.set_color(BLUE);
                return true;                
        } 			

        return false;	  		
  	}

  	void set_new_active_object(const int new_active) {
  		who_is_active = new_active;
  	}
};

#endif