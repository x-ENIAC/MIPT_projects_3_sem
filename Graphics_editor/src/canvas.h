#include <SDL2/SDL.h>
#include "point.h"
#include "colour.h"
#include "rectangle.h"
#include "view.h"
#include "pencil.h"
#include "button_delegates.h"
//#include "widget_types.h"

#ifndef CANVAS_H
#define CANVAS_H

extern const size_t MAX_COUNT_OF_VIEW_OBJECTS;
const double WIDTH_CLOSE_BUTTON  = 20;
const double HEIGHT_CLOSE_BUTTON = 20;
const double WIDTH_TABS_BUTTON = 150;
const double HEIGHT_TABS_BUTTON = 20;

struct Cell {
    Colour color;
    size_t thickness;

    Cell() {
        color = WHITE;
        thickness = 0;
    }

    Cell(const Colour par_color, const size_t par_thickness) {
        color = par_color;
        thickness = par_thickness;
    }
};

class Canvas : public View_object {
  public:
    //Rectangle* object_rect;
    //Button_owner owner;

    //View_object** view_objects;
    //size_t count_of_views;
    Pencil* pencil;
    Cell** cells_color;

    Canvas(const Point par_point, const double par_width, const double par_height, const Colour par_button_color, Pencil* par_pencil
                                /*const Button_owner par_owner, */) :
        View_object(par_point, par_width, par_height, par_button_color, Widget_types::CANVAS) {

        cells_color = (Cell**)calloc(par_width + 1, sizeof(Cell*));

        for(size_t i = 0; i <= par_width; ++i)
            cells_color[i] = (Cell*)calloc(par_height + 1, sizeof(Cell));

        for(size_t i = 0; i <= par_width; ++i)
            for(size_t j = 0; j <= par_height; ++j) {
                cells_color[i][j].color = par_button_color;
                cells_color[i][j].thickness = 24;
            }

        pencil = par_pencil;
    }

    bool check_click(const double mouse_x, const double mouse_y, const Mouse_click_state* par_mouse_status) override {
        if(is_active) {
            if(*par_mouse_status == Mouse_click_state::MOUSE_DOWN_AND_MOTION || *par_mouse_status == Mouse_click_state::MOUSE_DOWN) {
                if(rect->is_point_belongs_to_rectangle( Point(mouse_x, mouse_y) )) {

                    Point left_up_corner(rect->get_center().x - rect->width / 2, rect->get_center().y - rect->height / 2);
                    cells_color[(int)(mouse_x - left_up_corner.x)][(int)(mouse_y - left_up_corner.y)].color     = pencil->get_color();
                    cells_color[(int)(mouse_x - left_up_corner.x)][(int)(mouse_y - left_up_corner.y)].thickness = pencil->get_thickness();
                    return true;
                }
            }
        }

        return false;
    }

    void draw(SDL_Renderer** render, SDL_Texture** texture, SDL_Surface** screen) override {
        if(is_visible) {
            rect->draw(*render);

            Point left_up_corner(rect->get_center().x - rect->width / 2, rect->get_center().y - rect->height / 2);

            for(size_t i = 0; i <= rect->width; ++i)
                for(size_t j = 0; j <= rect->height; ++j) {
                    Colour now_color = cells_color[i][j].color;
                    Point new_point(i + left_up_corner.x, j + left_up_corner.y, now_color);

                    if(now_color != color) {
                        Rectangle new_rect(new_point, cells_color[i][j].thickness / 2.0, cells_color[i][j].thickness / 2.0, now_color, false);
                        new_rect.draw(*render);
                    } else
                        new_point.draw_point(*render);
                }
        }
    }

    void delete_all() {
        double width  = rect->get_width();
        double height = rect->get_height();

        for(size_t i = 0; i < width; ++i)
            delete[] cells_color[i];
        delete[] cells_color;
    }    

    /*inline Button_owner get_owner() const {
        return owner;
    }*/

    //inline void set_owner(const Button_owner new_owner) {
    //  owner = new_owner;
    //}

    //void tick(const double delta_time) override {}
};

#endif


