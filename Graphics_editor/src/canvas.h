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

class Canvas : public View_object {
  public:
    //Rectangle* object_rect;
    //Button_owner owner;

    //View_object** view_objects;
    //size_t count_of_views;
    Pencil* pencil;
    Colour** cells_color;

    Canvas(const Point par_point, const double par_width, const double par_height, const Colour par_button_color, Pencil* par_pencil
                                /*const Button_owner par_owner, */) :
        View_object(par_point, par_width, par_height, par_button_color, Widget_types::CANVAS)
    {
        cells_color = (Colour**)calloc(par_width + 1, sizeof(Colour*));

        for(size_t i = 0; i <= par_width; ++i)
            cells_color[i] = (Colour*)calloc(par_height + 1, sizeof(Colour));

        for(size_t i = 0; i <= par_width; ++i)
            for(size_t j = 0; j <= par_height; ++j)
                cells_color[i][j] = par_button_color;

        pencil = par_pencil;
    }

    bool check_click(const double mouse_x, const double mouse_y) {
        if(rect->is_point_belongs_to_rectangle( Point(mouse_x, mouse_y) )) {
            Point left_up_corner(center.x - rect->width / 2, center.y - rect->height / 2);
            cells_color[(int)(mouse_x - left_up_corner.x)][(int)(mouse_y - left_up_corner.y)] = pencil->get_color();
            return true;
        }

        return false;
    }

    virtual void draw(SDL_Renderer** render, SDL_Texture** texture) {
        rect->draw(*render);

        Point left_up_corner(center.x - rect->width / 2, center.y - rect->height / 2);

        for(size_t i = 0; i <= rect->width; ++i)
            for(size_t j = 0; j <= rect->height; ++j) {
                Point new_point(i + left_up_corner.x, j + left_up_corner.y, cells_color[i][j]);

                if(cells_color[i][j] != color) {
                    Rectangle new_rect(new_point, pencil->get_thickness() / 2.0, pencil->get_thickness() / 2.0, cells_color[i][j], false);
                    new_rect.draw(*render);
                } else
                    new_point.draw_point(*render);
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


