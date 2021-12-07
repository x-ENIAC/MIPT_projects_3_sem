#include <SDL2/SDL.h>
#include "point.h"
#include "colour.h"
#include "rectangle.h"
#include "view.h"
#include "button_delegates.h"
#include "button_manager.h"
#include "tab.h"
//#include "widget_types.h"

#include "canvas.h"
class Canvas;

#ifndef CANVAS_MANAGER_H
#define CANVAS_MANAGER_H

//extern const size_t MAX_COUNT_OF_VIEW_OBJECTS;
//const double WIDTH_CLOSE_BUTTON  = 20;
//const double HEIGHT_CLOSE_BUTTON = 20;
//extern const double WIDTH_TABS_BUTTON;
//extern const double HEIGHT_TABS_BUTTON;

class Canvas_manager : public View_object {
  public:

  	// Canvas* canvas;

	View_object** view_objects;
	size_t count_of_views;

	//Pencil* pencil;
	Tab* tab;

	Canvas_manager() : View_object (Widget_types::CANVAS_MANAGER) {

		// canvas = new Canvas;

		view_objects = new View_object*[MAX_COUNT_OF_VIEW_OBJECTS];
		for(size_t i = 0; i < MAX_COUNT_OF_VIEW_OBJECTS; ++i)
			view_objects[i] = new View_object;
		count_of_views = 1;

		tab = new Tab;
	}

	Canvas_manager(const Point par_point, const double par_width, const double par_height, 
										  const Colour par_color, const bool par_is_active, 
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

		Canvas* canvas = new Canvas(center_button, par_width, par_height - HEIGHT_CLOSE_BUTTON, WHITE);
		view_objects[count_of_views++] = canvas;

		++widget_types[(int)Widget_types::CANVAS];


		Point center_tab(par_point);
		center_tab -= Point(par_width / 2.0, par_height / 2.0);
		center_tab += Point(WIDTH_TABS_BUTTON / 2.0, HEIGHT_TABS_BUTTON / 2.0);
		center_tab += Point((WIDTH_TABS_BUTTON + WIDTH_CLOSE_BUTTON) * number_of_tab, 0);

		//printf("center_tab (%lg, %lg), %lg, %lg\n", center_tab.x, center_tab.y, WIDTH_CLOSE_BUTTON + WIDTH_TABS_BUTTON, HEIGHT_TABS_BUTTON);
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

	void add_view_object(View_object* new_view) {
		view_objects[count_of_views] = new_view;
		++count_of_views;

		++widget_types[(int)new_view->get_yourself_type()];
	}

	bool check_click(const float mouse_x, const float mouse_y, const Mouse_click_state* par_mouse_status) override {

		//printf("check click Canvas_manager? Tab (%lg, %lg)\n", tab->rect->center.x, tab->rect->center.y);
		if(tab->check_click(mouse_x, mouse_y, par_mouse_status))
			return true;

		//printf("not tab((( %d\n", is_active);
		if(is_active) {
			//printf("rect? (%lg, %lg), %lg, %lg\n\n", rect->center.x, rect->center.y, rect->get_width(), rect->get_height());
			if(rect->is_point_belongs_to_rectangle( Point(mouse_x, mouse_y) )) {

				// if(canvas->check_click(mouse_x, mouse_y, par_mouse_status)) {
				// 	return true;

				for(int i = count_of_views - 1; i >= 0; --i) {
					//printf("\t\tcheck.\n");
					if(view_objects[i]->check_click(mouse_x, mouse_y, par_mouse_status)) {
						return true;
					}
				}
			}
		}

		return false;
	}

	bool check_motion(Point old_mouse, Point now_mouse, const Mouse_click_state* par_mouse_status) override {
		//printf("\n\nview_manager check_click\n");
		//printf("canvas check_motion\n");

		if(tab->check_motion(old_mouse, now_mouse, par_mouse_status)) {
			//printf("tab...\n");
			for(int i = count_of_views - 1; i >= 0; --i) {
				view_objects[i]->check_motion(old_mouse, now_mouse, par_mouse_status);
			}
			return true;
		}

		//printf("NOT TAB %d\n", is_active);
		if(is_active) {

			if(rect->is_point_belongs_to_rectangle( Point(now_mouse.x, now_mouse.y) ) ||
			   rect->is_point_belongs_to_rectangle( Point(old_mouse.x, old_mouse.y) )) {

				// if(canvas->check_motion(old_mouse, now_mouse, par_mouse_status)) {
				// 	return true;

				for(int i = count_of_views - 1; i >= 0; --i) {

					if(view_objects[i]->check_motion(old_mouse, now_mouse, par_mouse_status)) {
						return true;
					}
				}
			}
		}

		return false;
	}		

	virtual void draw(SDL_Renderer** render, SDL_Texture** texture, SDL_Surface** screen) {
		//rect->draw(*render);

		if(is_visible && is_active) {
			// canvas->draw(render, texture, screen);

			for(size_t i = 0; i < count_of_views; ++i)
				view_objects[i]->draw(render, texture, screen);
		}
		
		if(is_active) {

			tab->button_manager->buttons[0]->texture->update_texture(PATH_TO_PICTURE_WITH_GREY_2_BUTTON);
			tab->button_manager->buttons[1]->texture->update_texture(PATH_TO_PICTURE_WITH_GREY_2_CLOSE_BUTTON);

			tab->draw(render, texture, screen);            

		} else if(is_alive) {
			tab->draw(render, texture, screen);
		}
	}

	void delete_all() {
		tab->delete_all();

		count_of_views = 0;
	}

	void update_position_from_delta(Point delta) {
		rect->set_center(rect->get_center() - delta);
		//printf("CANVAS_MANAGER CENTER (%lg, %lg)\n", rect->get_center().x, rect->get_center().y);

		tab->update_position_from_delta(delta);
		//tab->rect->set_center();
		//tab->button_manager->rect->set_center(tab->rect->get_center() - delta);
		//tab->button_manager->update_position_from_delta(delta);

		// canvas->update_position_from_delta(delta);

		for(size_t i = 0; i < count_of_views; ++i) {
			view_objects[i]->update_position_from_delta(delta);
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


