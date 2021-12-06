#include "view.h"
#include "manager_of_canvas_managers.h"
#include "pencil.h"
#include "button_manager.h"
#include "spline_canvas.h"

#ifndef CHART_H
#define CHART_H

// extern const double WIDTH_TABS_BUTTON;
// extern const double HEIGHT_TABS_BUTTON;
// extern const double WIDTH_CLOSE_BUTTON;
// extern const double HEIGHT_CLOSE_BUTTON;

class Chart : public View_object {
  public:
	Spline_canvas** spline_canvas;
    size_t count_spline_canvases;
	Button_manager* tools;

	Chart(const Point par_point, const double par_width, const double par_height, 
		  const Colour par_color, Pencil* par_pencil, Manager_of_canvas_managers* par_manager_of_canvas_managers,
          const bool par_is_active, Mouse_click_state* par_mouse_click_state) :

	  View_object (par_point, par_width, par_height, par_color, Widget_types::CHART) {

	  	Point tools_center(par_width / 2.0, HEIGHT_CLOSE_BUTTON / 2.0);
	  	tools_center += rect->get_left_up_corner();

	  	tools = new Button_manager(tools_center, par_width, HEIGHT_CLOSE_BUTTON, DARK_GREY_2);

        fill_tools(par_mouse_click_state);

	  	Point canvas_center(par_point);
	  	canvas_center.y += HEIGHT_CLOSE_BUTTON / 2;

        spline_canvas = new Spline_canvas*[5];

	  	spline_canvas[0] = new Spline_canvas(canvas_center, par_width, par_height - HEIGHT_CLOSE_BUTTON, WHITE, par_pencil,
                                            par_manager_of_canvas_managers, Color_management::MAN_RED, par_mouse_click_state);
        spline_canvas[1] = new Spline_canvas(/*Point(300, 600)*/ canvas_center, par_width, par_height - HEIGHT_CLOSE_BUTTON, WHITE, par_pencil,
                                            par_manager_of_canvas_managers, Color_management::MAN_GREEN, par_mouse_click_state);
        spline_canvas[2] = new Spline_canvas(/*Point(300, 300)*/ canvas_center, par_width, par_height - HEIGHT_CLOSE_BUTTON, WHITE, par_pencil,
                                            par_manager_of_canvas_managers, Color_management::MAN_BLUE, par_mouse_click_state);        
        count_spline_canvases = 3;
        //spline_canvas = new Spline_canvas(canvas_center, par_width, par_height - HEIGHT_CLOSE_BUTTON, WHITE, par_pencil,
        //                                    par_manager_of_canvas_managers, Color_management::MAN_BLUE, par_mouse_click_state);
	}

    void fill_tools(Mouse_click_state* par_mouse_click_state) {
        //--------------- add close button ---------------------------

        Point center_button(rect->get_width() - WIDTH_CLOSE_BUTTON / 2.0,  HEIGHT_CLOSE_BUTTON / 2.0);
        center_button += rect->get_left_up_corner();

        Button* close_button = new Button(NULL, center_button, BLACK, WIDTH_CLOSE_BUTTON, HEIGHT_CLOSE_BUTTON,
                                          "x", BLACK);
        close_button->texture->add_new_texture(PATH_TO_PICTURE_WITH_BLACK_CLOSE_BUTTON);

        Close_delegate*  close_delegate = new Close_delegate(close_button, par_mouse_click_state, &is_alive);
        close_button->delegate = close_delegate;

        tools->add_view_object(close_button);

        //--------------- add roll up button ---------------------------
        Roll_up_delegate*  roll_up_delegate = new Roll_up_delegate(par_mouse_click_state, &is_visible, &is_active);

        center_button = Point(WIDTH_CLOSE_BUTTON / 2.0, HEIGHT_CLOSE_BUTTON / 2.0);
        center_button += rect->get_left_up_corner();

        Button* roll_up_button = new Button(roll_up_delegate, center_button, BLACK, WIDTH_CLOSE_BUTTON, HEIGHT_CLOSE_BUTTON,
                                            "-", BLACK, PATH_TO_PICTURE_WITH_ROLL_UP_BUTTON);
        roll_up_button->texture->add_new_texture(PATH_TO_PICTURE_WITH_ROLL_UP_BUTTON);
        tools->add_view_object(roll_up_button);

        //--------------- add title button ---------------------------
        Title_delegate*  title_delegate = new Title_delegate(this);

        center_button = Point(rect->get_width() / 2.0, HEIGHT_CLOSE_BUTTON / 2.0);
        center_button += rect->get_left_up_corner();

        Button* title_button = new Button(title_delegate, center_button, DARK_GREY, rect->get_width() - 2 * WIDTH_CLOSE_BUTTON, HEIGHT_CLOSE_BUTTON,
                                          "Title", BLACK, PATH_TO_PICTURE_WITH_TITLE_BUTTON);
        title_button->texture->add_new_texture(PATH_TO_PICTURE_WITH_TITLE_BUTTON);
        tools->add_view_object(title_button);
    }

    bool check_click(const double mouse_x, const double mouse_y, const Mouse_click_state* par_mouse_status) override {
        for(int i = 0; i < count_spline_canvases; ++i)
            if(spline_canvas[i]->rect->is_point_belongs_to_rectangle( Point(mouse_x, mouse_y))) {
                //printf("click chart spline_canvas[i]!\n");
                if(spline_canvas[i]->check_click(mouse_x, mouse_y, par_mouse_status))
                    return true;
            }

        if(tools->rect->is_point_belongs_to_rectangle( Point(mouse_x, mouse_y))) {
            //printf("chart tools\n");
            return tools->check_click(mouse_x, mouse_y, par_mouse_status);
        }

        return false;
    }


    bool check_motion(Point old_mouse, Point now_mouse, const Mouse_click_state* par_mouse_status) override {
        for(int i = 0; i < count_spline_canvases; ++i)
            if(spline_canvas[i]->rect->is_point_belongs_to_rectangle( Point(now_mouse.x, now_mouse.y)) ||
                spline_canvas[i]->rect->is_point_belongs_to_rectangle( Point(old_mouse.x, old_mouse.y))) {
                //printf("motion chart spline_canvas!\n");
                if(spline_canvas[i]->check_motion(old_mouse, now_mouse, par_mouse_status))
                    return true;
            }

        if(tools->rect->is_point_belongs_to_rectangle( Point(now_mouse.x, now_mouse.y)) ||
           tools->rect->is_point_belongs_to_rectangle( Point(old_mouse.x, old_mouse.y))) {
            //printf("chart tools\n");
            return tools->check_motion(old_mouse, now_mouse, par_mouse_status);
        }

        return false;
    }


    void draw(SDL_Renderer** render, SDL_Texture** texture, SDL_Surface** screen) override {
        if(is_visible) {
            rect->draw(*render);

            tools->draw(render, texture, screen);

            for(int i = 0; i < count_spline_canvases; ++i)
                spline_canvas[i]->draw(render, texture, screen);
        }
    }

    void update_view_object_position(const double mouse_x, const double mouse_y) override {
        Point mouse(mouse_x, mouse_y);
        Point delta(tools->rect->get_center());
        delta -= mouse;

        rect->set_center(rect->get_center() - delta);

        tools->rect->set_center(mouse);
        tools->update_position_from_delta(delta);

        for(int i = 0; i < count_spline_canvases; ++i)
            spline_canvas[i]->update_position_from_delta(delta);
    }
};

#endif