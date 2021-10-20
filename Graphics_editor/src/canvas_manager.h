#include <SDL2/SDL.h>
#include "point.h"
#include "colour.h"
#include "rectangle.h"
#include "view.h"
#include "button_delegates.h"
#include "canvas.h"
#include "pencil.h"
#include "button_manager.h"
#include "tab.h"
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
    Tab* tab;

    Canvas_manager(const Point par_point, const double par_width, const double par_height, 
    									  const Colour par_color, Pencil* par_pencil, const bool par_is_active, Mouse_click_state* par_mouse_click_state,
                                          const Point par_center_tab, const int number_of_tab) :
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

        fill_button_manager(button_manager, left_up_corner, par_width, par_height, par_mouse_click_state);

		who_is_active = -1;

        Point center_tab = par_center_tab;
        center_tab -= Point(WIDTH_CLOSE_BUTTON / 2.0, 0);

        tab = new Tab(center_tab, (WIDTH_TABS_BUTTON + WIDTH_CLOSE_BUTTON), HEIGHT_TABS_BUTTON, YELLOW, 
                      number_of_tab, par_mouse_click_state, &is_visible, &is_active);
    }

    void fill_button_manager(Button_manager* button_manager, Point left_up_corner, const double par_width, const double par_height,
                                                             Mouse_click_state* par_mouse_click_state) {

        //--------------- add close button ---------------------------
        Close_delegate*  close_delegate = new Close_delegate(par_mouse_click_state, &is_visible, &is_active);

        Point center_button(par_width - WIDTH_CLOSE_BUTTON / 2.0,  HEIGHT_CLOSE_BUTTON / 2.0);
        center_button += left_up_corner;

        Button* close_button = new Button(close_delegate, center_button, BLACK, WIDTH_CLOSE_BUTTON, HEIGHT_CLOSE_BUTTON, "x", WHITE);
        button_manager->add_view_object(close_button);

        //--------------- add title button ---------------------------
        Roll_up_delegate*  roll_up_delegate = new Roll_up_delegate(par_mouse_click_state, &is_visible, &is_active);

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

    bool check_click(const double mouse_x, const double mouse_y, const Mouse_click_state* par_mouse_status) override {
        //printf("click Canvas_manager\n");    

        if(tab->check_click(mouse_x, mouse_y, par_mouse_status))
            return true;

        if(is_active) {

            if(rect->is_point_belongs_to_rectangle( Point(mouse_x, mouse_y) )) {

                for(int i = count_of_views - 1; i >= 0; --i) {

                    /*printf("\t - (((, mouse (%lg, %lg), center (%lg, %lg)\n", 
                                    rect->is_point_belongs_to_rectangle( Point(mouse_x, mouse_y) ), mouse_x, mouse_y, 
                                    view_objects[i]->center.x, view_objects[i]->center.y);*/

                    if(view_objects[i]->check_click(mouse_x, mouse_y, par_mouse_status)) {
                        return true;
                    }
                }
            }
        }

        return false;
    }   

    virtual void draw(SDL_Renderer** render, SDL_Texture** texture) {
        //rect->draw(*render);

        if(is_visible) {
            for(size_t i = 0; i < count_of_views; ++i)
                view_objects[i]->draw(render, texture);
        }
        
        tab->draw(render, texture);
    }

    bool delete_object() override {
        if(is_visible && !is_active) {
            tab->delete_object();

            for(size_t i = 0; i < count_of_views; ++i)
                view_objects[i]->delete_object();

            return true;
        }

        return false;
    }

    /*inline Button_owner get_owner() const {
        return owner;
    }*/

    //inline void set_owner(const Button_owner new_owner) {
    //  owner = new_owner;
    //}
};

#endif


