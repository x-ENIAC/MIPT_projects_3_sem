#include <SDL2/SDL.h>
#include "point.h"
#include "colour.h"
#include "rectangle.h"
#include "view.h"
#include "button_delegates.h"
#include "canvas_manager.h"
#include "pencil.h"
#include "button_manager.h"
#include "tab.h"

#ifndef MANAGER_OF_CANVAS_MANAGERS_H
#define MANAGER_OF_CANVAS_MANAGERS_H

extern const size_t MAX_COUNT_OF_VIEW_OBJECTS;
//const double WIDTH_CLOSE_BUTTON  = 20;
//const double HEIGHT_CLOSE_BUTTON = 20;
extern const double WIDTH_TABS_BUTTON;
extern const double HEIGHT_TABS_BUTTON;

class Manager_of_canvas_managers : public View_object {
  public:

    Canvas_manager** canvas_managers;
    size_t count_of_canvas_managers;

    Button_manager* button_manager;
    Point any_canvas_center;
    double any_canvas_width;
    double any_canvas_height;

	Pencil* pencil;
	Mouse_click_state* mouse_click_state;

	int who_is_active;

    Manager_of_canvas_managers(const Point par_point, const double par_width, const double par_height, 
    						   const Colour par_color, Pencil* par_pencil, const bool par_is_active, Mouse_click_state* par_mouse_click_state) :

      View_object (par_point, par_width, par_height, par_color, Widget_types::CANVAS_MANAGER_MANAGER) {

        canvas_managers = new Canvas_manager*[MAX_COUNT_OF_VIEW_OBJECTS];
        for(size_t i = 0; i < MAX_COUNT_OF_VIEW_OBJECTS; ++i)
            canvas_managers[i] = new Canvas_manager;
        count_of_canvas_managers = 0;


        Point center_of_button_manager(par_width / 2.0, HEIGHT_CLOSE_BUTTON / 2.0);
        center_of_button_manager += rect->get_left_up_corner();

        button_manager = new Button_manager(center_of_button_manager, par_width, HEIGHT_CLOSE_BUTTON, WHITE);
        ++widget_types[(int)Widget_types::BUTTON_MANAGER];

        fill_button_manager(rect->get_left_up_corner(), par_width, par_height, par_mouse_click_state);

        center_of_button_manager += Point(0.0, HEIGHT_TABS_BUTTON);
        any_canvas_center = par_point;
        any_canvas_center += Point(0, HEIGHT_TABS_BUTTON / 2.0);

        any_canvas_width = par_width;
        any_canvas_height = par_height - HEIGHT_CLOSE_BUTTON;

        pencil = par_pencil;
        mouse_click_state = par_mouse_click_state;

  		/*for(int i = 0; i < COUNT_OF_TYPES; ++i)
  			printf("[%d] = %d\n", i, widget_types[i]);*/

  		who_is_active = -1;
    }

	void add_canvas_manager(Canvas_manager* new_canvas_manager) {
  	 	canvas_managers[count_of_canvas_managers] = new_canvas_manager;
  	 	++count_of_canvas_managers;

        ++widget_types[(int)Widget_types::CANVAS_MANAGER];

        for(int i = count_of_canvas_managers - 1; i >= 0; --i) {

            if(canvas_managers[i]->is_active && who_is_active != i)
                canvas_managers[i]->is_active = false;
        }        
  	} 	

    void fill_button_manager(Point left_up_corner, const double par_width, const double par_height, Mouse_click_state* par_mouse_click_state) {

        //--------------- add close button ---------------------------
        Close_delegate*  close_delegate = new Close_delegate(par_mouse_click_state, &is_alive);

        Point center_button(par_width - WIDTH_CLOSE_BUTTON / 2.0,  HEIGHT_CLOSE_BUTTON / 2.0);
        center_button += left_up_corner;

        Button* close_button = new Button(close_delegate, center_button, BLACK, WIDTH_CLOSE_BUTTON, HEIGHT_CLOSE_BUTTON, "x", WHITE);
        button_manager->add_view_object(close_button);

        //--------------- add roll up button ---------------------------
        Roll_up_delegate*  roll_up_delegate = new Roll_up_delegate(par_mouse_click_state, &is_visible, &is_active);

        center_button = Point(WIDTH_CLOSE_BUTTON / 2.0, HEIGHT_CLOSE_BUTTON / 2.0);
        center_button += left_up_corner;


        Button* roll_up_button = new Button(roll_up_delegate, center_button, BLACK, WIDTH_CLOSE_BUTTON, HEIGHT_CLOSE_BUTTON, "-", WHITE);
        button_manager->add_view_object(roll_up_button);

        //--------------- add title button ---------------------------
        Title_delegate*  title_delegate = new Title_delegate;

        center_button = Point(par_width / 2.0, HEIGHT_CLOSE_BUTTON / 2.0);
        center_button += left_up_corner;


        Button* title_button = new Button(title_delegate, center_button, DARK_GREY, par_width - 2 * WIDTH_CLOSE_BUTTON, HEIGHT_CLOSE_BUTTON, "Title");
        button_manager->add_view_object(title_button);
    }

  	void add_new_canvas_manager() {
  		//printf("begin add_canvas_manager %d, %p\n", (int)Widget_types::TABS, widget_types);
  		//printf("count of types %d\n", COUNT_OF_TYPES);

  		//for(int i = 0; i < COUNT_OF_TYPES; ++i)
  		//	printf("[%d] = %d\n", i, widget_types[i]);

        //Point center_tab((WIDTH_TABS_BUTTON + WIDTH_CLOSE_BUTTON) * widget_types[(int)Widget_types::TABS] + WIDTH_TABS_BUTTON / 2.0 + WIDTH_CLOSE_BUTTON / 2.0,
        //				 HEIGHT_CLOSE_BUTTON + HEIGHT_TABS_BUTTON / 2.0);

        //printf("!!! canvas size: width %lg, height %lg\n", any_canvas_width, any_canvas_height);

  		Canvas_manager* new_canvas_manager = new Canvas_manager(any_canvas_center, any_canvas_width, any_canvas_height,
  																WHITE, pencil, false, mouse_click_state, widget_types[(int)Widget_types::TABS]);

  		//printf("adding\n");

  		++widget_types[(int)Widget_types::TABS];
  		set_new_active_object(count_of_canvas_managers);

        add_canvas_manager(new_canvas_manager);
        /*printf("is_active\n");
        for(size_t i = 0; i < count_of_canvas_managers; ++i)
            printf("%d ", canvas_managers[i]->is_active);
        printf("\n\n");*/


  		//printf("end add_canvas_manager\n");
  	}


    bool check_click(const double mouse_x, const double mouse_y, const Mouse_click_state* par_mouse_status) override {
		printf("view_manager check_click, now active %d\n", who_is_active);

        if(is_active) {

            if(rect->is_point_belongs_to_rectangle( Point(mouse_x, mouse_y) )) {

            	if(button_manager->check_click(mouse_x, mouse_y, par_mouse_status))
            		return true;

            	//printf("%d\n", count_of_canvas_managers);
                //for(int i = count_of_canvas_managers - 1; i >= 0; --i) {
                //    printf("%d ", canvas_managers[i])

                for(int i = count_of_canvas_managers - 1; i >= 0; --i) {

                    /*printf("\tcall canvas_manager number %d - (is belong %d) (((, mouse (%lg, %lg), center (%lg, %lg)\n", i,
                                    rect->is_point_belongs_to_rectangle( Point(mouse_x, mouse_y) ), mouse_x, mouse_y, 
                                    canvas_managers[i]->center.x, canvas_managers[i]->center.y);*/

                    if(canvas_managers[i]->check_click(mouse_x, mouse_y, par_mouse_status)) {

                    	set_new_active_object(i);

                        /*printf("is_active\n");
                        for(size_t i = 0; i < count_of_canvas_managers; ++i)
                            printf("%d ", canvas_managers[i]->is_active);
                        printf("\n\n");*/

                        return true;
                    }
                }
                printf("\n");
            }
        }

        return false;
    }

  	void set_new_active_object(const int new_active) {
        printf("old_active %d, new %d\n", who_is_active, new_active);
        if(who_is_active != -1)
            canvas_managers[who_is_active]->is_active = false;

        who_is_active = new_active;

        if(who_is_active != -1)
            canvas_managers[who_is_active]->is_active = true;
  	}

    virtual void draw(SDL_Renderer** render, SDL_Texture** texture) {
        rect->draw(*render);

        button_manager->draw(render, texture);

        draw_tabs_area(render, texture);

        if(is_visible) {
        	for(size_t i = 0; i < count_of_canvas_managers; ++i)
        		canvas_managers[i]->draw(render, texture);
        }
    }

    void draw_tabs_area(SDL_Renderer** render, SDL_Texture** texture) {
        Point rect_center(button_manager->rect->get_center());
        rect_center += Point(0, HEIGHT_CLOSE_BUTTON / 2.0 + HEIGHT_TABS_BUTTON / 2.0);

        Rectangle tab_rect(rect_center, button_manager->rect->get_width(), button_manager->rect->get_height(), LIGHT_LIGHT_GREY, false);

        tab_rect.draw(*render);
    }

    void find_not_alive() {
        for(size_t i = 0; i < count_of_canvas_managers; ++i) {
            if(!(canvas_managers[i]->is_alive)) {

                --widget_types[(int)Widget_types::CANVAS_MANAGER];
                --widget_types[(int)Widget_types::TABS];

                canvas_managers[i]->is_visible = false;

                update_tabs_offset(i);
                array_shift(i);

                --count_of_canvas_managers;
            }
        }
    }

    void array_shift(const size_t pos) {
        for(size_t i = pos + 1; i < count_of_canvas_managers; ++i)
            canvas_managers[i - 1] = canvas_managers[i];
    }

    void update_tabs_offset(const size_t pos) {
        //size_t count = 1;
        Point before_point(canvas_managers[pos]->tab->center);

        for(size_t i = pos + 1; i < count_of_canvas_managers; ++i) {
            //printf("(%lg, %lg) -> ", before_point.x, before_point.y);
            before_point = Point(canvas_managers[i]->tab->center);
            before_point -= Point((WIDTH_TABS_BUTTON + WIDTH_CLOSE_BUTTON), 0);
            //before_point = Point(300, 0);
            canvas_managers[i]->tab->update_tabs_offset(before_point);
            canvas_managers[i]->tab->update_tabs_number(i - 1);

            //printf("before (%lg, %lg);   %lg, %lg\n", before_point.x, before_point.y, canvas_managers[i]->tab->rect->center.x, canvas_managers[i]->tab->rect->center.y);
            //++count;
        }
    }
};

#endif