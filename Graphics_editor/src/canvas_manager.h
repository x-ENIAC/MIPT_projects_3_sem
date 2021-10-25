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
    Tab* tab;


    Canvas_manager() : View_object (Widget_types::CANVAS_MANAGER) {

        view_objects = new View_object*[MAX_COUNT_OF_VIEW_OBJECTS];
        for(size_t i = 0; i < MAX_COUNT_OF_VIEW_OBJECTS; ++i)
            view_objects[i] = new View_object;
        count_of_views = 1;

        tab = new Tab;
    }    

    Canvas_manager(const Point par_point, const double par_width, const double par_height, 
    									  const Colour par_color, Pencil* par_pencil, const bool par_is_active, 
                                          Mouse_click_state* par_mouse_click_state, const size_t number_of_tab) :

      View_object (par_point, par_width, par_height, par_color, Widget_types::CANVAS_MANAGER) {

        //printf("construct---------------\n");

        view_objects = new View_object*[MAX_COUNT_OF_VIEW_OBJECTS];
        for(size_t i = 0; i < MAX_COUNT_OF_VIEW_OBJECTS; ++i)
            view_objects[i] = new View_object;
        count_of_views = 0;

        Point left_up_corner(par_point.x - par_width / 2.0, par_point.y - par_height / 2.0);
        Point center_button(par_width - WIDTH_CLOSE_BUTTON / 2.0,  HEIGHT_CLOSE_BUTTON / 2.0);

        //------------------ add canvas -----------------------------

        center_button = par_point;
        center_button += Point(0, HEIGHT_CLOSE_BUTTON / 2);

        Canvas* canvas = new Canvas(center_button, par_width, par_height - HEIGHT_CLOSE_BUTTON, par_color, par_pencil);
        view_objects[count_of_views++] = canvas;

        ++widget_types[(int)Widget_types::CANVAS];


        Point center_tab(par_point);
        center_tab -= Point(par_width / 2.0, par_height / 2.0);
        center_tab += Point(WIDTH_TABS_BUTTON / 2.0, HEIGHT_TABS_BUTTON / 2.0);
        center_tab += Point((WIDTH_TABS_BUTTON + WIDTH_CLOSE_BUTTON) * number_of_tab, 0);

        tab = new Tab(center_tab, (WIDTH_TABS_BUTTON + WIDTH_CLOSE_BUTTON), HEIGHT_TABS_BUTTON, YELLOW, 
                      number_of_tab, par_mouse_click_state, &is_visible, &is_active, &is_alive);
    }

    ~Canvas_manager() {
        printf("Destruct Canvas_manager\n");
        /*
        for(size_t i = 0; i < count_of_views; ++i)
            delete[] view_objects[i];
        delete[] view_objects;

        delete tab;*/
    }

    /*void fill_button_manager(Button_manager* button_manager, Point left_up_corner, const double par_width, const double par_height,
                                                             Mouse_click_state* par_mouse_click_state) {

        //--------------- add close button ---------------------------
        Close_delegate*  close_delegate = new Close_delegate(par_mouse_click_state, &is_alive);

        Point center_button(par_width - WIDTH_CLOSE_BUTTON / 2.0,  HEIGHT_CLOSE_BUTTON / 2.0);
        center_button += left_up_corner;

        Button* close_button = new Button(close_delegate, center_button, BLACK, WIDTH_CLOSE_BUTTON, HEIGHT_CLOSE_BUTTON, "x", WHITE);
        close_button->texture->add_new_texture(PATH_TO_PICTURE_WITH_CLOSE_BUTTON);
        button_manager->add_view_object(close_button);

        //--------------- add title button ---------------------------
        Roll_up_delegate*  roll_up_delegate = new Roll_up_delegate(par_mouse_click_state, &is_visible, &is_active);

        center_button = Point(WIDTH_CLOSE_BUTTON / 2.0, HEIGHT_CLOSE_BUTTON / 2.0);
        center_button += left_up_corner;


        Button* roll_up_button = new Button(roll_up_delegate, center_button, BLACK, WIDTH_CLOSE_BUTTON, HEIGHT_CLOSE_BUTTON, "-", WHITE);
        roll_up_button->texture->add_new_texture(PATH_TO_PICTURE_WITH_ROLL_UP_BUTTON);
        button_manager->add_view_object(roll_up_button);

        //--------------- add roll up button ---------------------------
        Title_delegate*  title_delegate = new Title_delegate;

        center_button = Point(par_width / 2.0, HEIGHT_CLOSE_BUTTON / 2.0);
        center_button += left_up_corner;


        Button* title_button = new Button(title_delegate, center_button, DARK_GREY, par_width - 2 * WIDTH_CLOSE_BUTTON, HEIGHT_CLOSE_BUTTON, "Title");
        button_manager->add_view_object(title_button);
    }*/

	void add_view_object(View_object* new_view) {
  	 	view_objects[count_of_views] = new_view;
  	 	++count_of_views;

        ++widget_types[new_view->get_yourself_type()];
  	}

    bool check_click(const double mouse_x, const double mouse_y, const Mouse_click_state* par_mouse_status) override {

        //printf("check tabs\n");
        if(tab->check_click(mouse_x, mouse_y, par_mouse_status))
            return true;

        //printf("is active %d\n", is_active);
        if(is_active) {

            if(rect->is_point_belongs_to_rectangle( Point(mouse_x, mouse_y) )) {

                for(int i = count_of_views - 1; i >= 0; --i) {

                    /*printf("\t\tcheck_click Canvas_manager, type %d\n", (int)view_objects[i]->yourself_type);
                    printf("\t - (((, mouse (%lg, %lg), center (%lg, %lg), width %lg, height %lg\n", 
                                    rect->is_point_belongs_to_rectangle( Point(mouse_x, mouse_y) ), mouse_x, mouse_y, 
                                    view_objects[i]->center.x, view_objects[i]->center.y, view_objects[i]->rect->get_width(), view_objects[i]->rect->get_height());
                    */
                    if(view_objects[i]->check_click(mouse_x, mouse_y, par_mouse_status)) {
                        //printf("return from Canvas_manager with true\n");
                        return true;
                    }
                }
            }
        }

        //printf("return from Canvas_manager with false\n");
        return false;
    }   

    virtual void draw(SDL_Renderer** render, SDL_Texture** texture, SDL_Surface** screen/*, Texture_manager* texture_manager*/) {
        //rect->draw(*render);

        //printf("is_visible %d, is_active %d\n", is_visible, is_active);
        if(is_visible && is_active) {
            for(size_t i = 0; i < count_of_views; ++i)
                view_objects[i]->draw(render, texture, screen/*, texture_manager*/);
        }
        
        if(is_active) {

            /*size_t count_of_buttons_in_tab = tab->button_manager->count_of_buttons;

            Colour* save_colors = new Colour[count_of_buttons_in_tab];

            for(size_t i = 0; i < count_of_buttons_in_tab; ++i) {
                save_colors[i] = tab->button_manager->buttons[i]->rect->get_colour();
                tab->button_manager->buttons[i]->rect->set_colour(LIGHT_GREY_4);
            }*/

            tab->button_manager->buttons[0]->texture->update_texture(PATH_TO_PICTURE_WITH_GREY_2_BUTTON);
            tab->button_manager->buttons[1]->texture->update_texture(PATH_TO_PICTURE_WITH_GREY_2_CLOSE_BUTTON);

            tab->draw(render, texture, screen);

            /*for(size_t i = 0; i < count_of_buttons_in_tab; ++i) {
                tab->button_manager->buttons[i]->rect->set_colour(save_colors[i]);
            }

            delete[] save_colors;*/

            //printf("TAAAAB (%lg, %lg)\n", tab->rect->center.x, tab->rect->center.y);
            

        } else if(is_alive) {
            tab->draw(render, texture, screen/*, texture_manager*/);
            //printf("TAAAAB (%lg, %lg)\n", tab->rect->center.x, tab->rect->center.y);
        }
    }

    void delete_all() {
        tab->delete_all();

        /*for(size_t i = 0; i < count_of_views; ++i)
            view_objects[i]->delete_all();*/

        count_of_views = 0;
    }

    void update_position(Point delta) {
        center -= delta;
        rect->set_center(delta - rect->get_center());

        //printf("tab (%lg, %lg) -> \n", tab->rect->get_center().x, tab->rect->get_center().y);
        tab->center -= delta;
        tab->rect->set_center(tab->rect->get_center() - delta);

        tab->button_manager->update_position(delta);
        //printf("(%lg, %lg)\n", tab->rect->get_center().x, tab->rect->get_center().y);

        for(size_t i = 0; i < count_of_views; ++i) {
            view_objects[i]->update_position(delta);
        }
    }

    /*inline Button_owner get_owner() const {
        return owner;
    }*/

    //inline void set_owner(const Button_owner new_owner) {
    //  owner = new_owner;
    //}
};

#endif


