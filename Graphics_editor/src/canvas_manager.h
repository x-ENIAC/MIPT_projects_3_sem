#include <SDL2/SDL.h>
#include "point.h"
#include "colour.h"
#include "rectangle.h"
#include "view.h"
#include "button_delegates.h"
#include "canvas.h"
#include "pencil.h"
#include "button_manager.h"
//#include "widget_types.h"

#ifndef CANVAS_MANAGER_H
#define CANVAS_MANAGER_H

extern const size_t MAX_COUNT_OF_VIEW_OBJECTS;
//const double WIDTH_CLOSE_BUTTON  = 20;
//const double HEIGHT_CLOSE_BUTTON = 20;
extern const double WIDTH_TABS_BUTTON;
extern const double HEIGHT_TABS_BUTTON;

class Canvas_manager : public View_object {
  public:

    View_object** view_objects;
    size_t count_of_views;

	//Pencil* pencil;
	int who_is_active;

    Canvas_manager(const Point par_point, const double par_width, const double par_height, 
    									  const Colour par_color, Pencil* par_pencil, const bool par_is_active) :
      View_object (par_point, par_width, par_height, par_color, Widget_types::CANVAS_MANAGER) {

      	//pencil = par_pencil;

        view_objects = new View_object*[MAX_COUNT_OF_VIEW_OBJECTS];
        for(size_t i = 0; i < MAX_COUNT_OF_VIEW_OBJECTS; ++i)
            view_objects[i] = new View_object;
        count_of_views = 1;

        Point left_up_corner(par_point.x - par_width / 2.0, par_point.y - par_height / 2.0);
        Point center_button(par_width - WIDTH_CLOSE_BUTTON / 2.0,  HEIGHT_CLOSE_BUTTON / 2.0);

        //------------------ add canvas -----------------------------

        center_button = par_point;
        center_button += Point(0, HEIGHT_CLOSE_BUTTON / 2);

        Canvas* canvas = new Canvas(center_button, par_width, par_height - HEIGHT_CLOSE_BUTTON, par_color, par_pencil);
        view_objects[count_of_views++] = canvas;


        Point center_of_button_manager(par_width / 2.0, HEIGHT_CLOSE_BUTTON / 2.0);
        center_of_button_manager += left_up_corner;

        Button_manager* button_manager = new Button_manager(center_of_button_manager, par_width, HEIGHT_CLOSE_BUTTON, WHITE);
        add_view_object(button_manager);

        fill_button_manager(button_manager, left_up_corner, par_width, par_height);

		who_is_active = -1;

        //tab = new Button_manager();
    }

    void fill_button_manager(Button_manager* button_manager, Point left_up_corner, const double par_width, const double par_height) {

        //--------------- add close button ---------------------------
        Close_delegate*  close_delegate = new Close_delegate;

        Point center_button(par_width - WIDTH_CLOSE_BUTTON / 2.0,  HEIGHT_CLOSE_BUTTON / 2.0);
        center_button += left_up_corner;

        Button* close_button = new Button(close_delegate, center_button, BLACK, WIDTH_CLOSE_BUTTON, HEIGHT_CLOSE_BUTTON, "x", WHITE);
        button_manager->add_view_object(close_button);

        //--------------- add title button ---------------------------
        Roll_up_delegate*  roll_up_delegate = new Roll_up_delegate;

        center_button = Point(WIDTH_CLOSE_BUTTON / 2.0, HEIGHT_CLOSE_BUTTON / 2.0);
        center_button += left_up_corner;


        Button* roll_up_button = new Button(roll_up_delegate, center_button, BLACK, WIDTH_CLOSE_BUTTON, HEIGHT_CLOSE_BUTTON, "-", WHITE);
        button_manager->add_view_object(roll_up_button);

        //--------------- add roll up button ---------------------------
        Title_delegate*  title_delegate = new Title_delegate;

        center_button = Point(par_width / 2.0, HEIGHT_CLOSE_BUTTON / 2.0);
        center_button += left_up_corner;


        Button* title_button = new Button(title_delegate, center_button, DARK_GREY, par_width - 2 * WIDTH_CLOSE_BUTTON, HEIGHT_CLOSE_BUTTON, "Title");
        button_manager->add_view_object(title_button);
    }

	void add_view_object(View_object* new_view) {
  	 	view_objects[count_of_views] = new_view;
  	 	++count_of_views;

        ++widget_types[new_view->get_yourself_type()];
  	}  	


    virtual bool check_click(const double mouse_x, const double mouse_y) {
        if(rect->is_point_belongs_to_rectangle( Point(mouse_x, mouse_y) )) {
            for(int i = count_of_views - 1; i >= 0; --i) {
                if(view_objects[i]->check_click(mouse_x, mouse_y)) {
  					
                    return true;
                }
            }
        }

        return false;
    }   

    virtual void draw(SDL_Renderer** render, SDL_Texture** texture) {
        //rect->draw(*render);

        for(size_t i = 0; i < count_of_views; ++i)
            view_objects[i]->draw(render, texture);

    }

    /*inline Button_owner get_owner() const {
        return owner;
    }*/

    //inline void set_owner(const Button_owner new_owner) {
    //  owner = new_owner;
    //}
};

#endif


