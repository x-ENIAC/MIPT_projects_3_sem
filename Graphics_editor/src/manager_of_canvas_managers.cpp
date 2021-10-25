#include "manager_of_canvas_managers.h"

    void Manager_of_canvas_managers::fill_button_manager(Point left_up_corner, const double par_width, const double par_height,
    													 Mouse_click_state* par_mouse_click_state) {

        //--------------- add close button ---------------------------
        Close_delegate*  close_delegate = new Close_delegate(par_mouse_click_state, &is_alive);

        Point center_button(par_width - WIDTH_CLOSE_BUTTON / 2.0,  HEIGHT_CLOSE_BUTTON / 2.0);
        center_button += left_up_corner;

        Button* close_button = new Button(close_delegate, center_button, BLACK, WIDTH_CLOSE_BUTTON, HEIGHT_CLOSE_BUTTON,
                                          "x", BLACK);
        close_button->texture->add_new_texture(PATH_TO_PICTURE_WITH_BLACK_CLOSE_BUTTON);
        button_manager->add_view_object(close_button);

        //--------------- add roll up button ---------------------------
        Roll_up_delegate*  roll_up_delegate = new Roll_up_delegate(par_mouse_click_state, &is_visible, &is_active);

        center_button = Point(WIDTH_CLOSE_BUTTON / 2.0, HEIGHT_CLOSE_BUTTON / 2.0);
        center_button += left_up_corner;


        Button* roll_up_button = new Button(roll_up_delegate, center_button, BLACK, WIDTH_CLOSE_BUTTON, HEIGHT_CLOSE_BUTTON,
                                            "-", BLACK, PATH_TO_PICTURE_WITH_ROLL_UP_BUTTON);
        roll_up_button->texture->add_new_texture(PATH_TO_PICTURE_WITH_ROLL_UP_BUTTON);
        button_manager->add_view_object(roll_up_button);

        //--------------- add title button ---------------------------
        Title_delegate*  title_delegate = new Title_delegate(this);

        center_button = Point(par_width / 2.0, HEIGHT_CLOSE_BUTTON / 2.0);
        center_button += left_up_corner;


        Button* title_button = new Button(title_delegate, center_button, DARK_GREY, par_width - 2 * WIDTH_CLOSE_BUTTON, HEIGHT_CLOSE_BUTTON,
                                          "Title", BLACK, PATH_TO_PICTURE_WITH_TITLE_BUTTON);
        title_button->texture->add_new_texture(PATH_TO_PICTURE_WITH_TITLE_BUTTON);
        button_manager->add_view_object(title_button);
    }

  	void Manager_of_canvas_managers::add_new_canvas_manager() {
  		//printf("begin add_canvas_manager %d, %p\n", (int)Widget_types::TABS, widget_types);
  		//printf("count of types %d\n", COUNT_OF_TYPES);

  		//for(int i = 0; i < COUNT_OF_TYPES; ++i)
  		//	printf("[%d] = %d\n", i, widget_types[i]);

        //Point center_tab((WIDTH_TABS_BUTTON + WIDTH_CLOSE_BUTTON) * widget_types[(int)Widget_types::TABS] + WIDTH_TABS_BUTTON / 2.0 + WIDTH_CLOSE_BUTTON / 2.0,
        //				 HEIGHT_CLOSE_BUTTON + HEIGHT_TABS_BUTTON / 2.0);

        //printf("!!! canvas size: width %lg, height %lg\n", any_canvas_width, any_canvas_height);

  		Canvas_manager* new_canvas_manager = new Canvas_manager(any_canvas_center, any_canvas_width, any_canvas_height,
  																WHITE, pencil, false, mouse_click_state, widget_types[(int)Widget_types::TABS]);


  		++widget_types[(int)Widget_types::TABS];
  		set_new_active_object(count_of_canvas_managers);

        add_canvas_manager(new_canvas_manager);
        /*printf("is_active\n");
        for(size_t i = 0; i < count_of_canvas_managers; ++i)
            printf("%d ", canvas_managers[i]->is_active);
        printf("\n\n");*/


  		//printf("end add_canvas_manager\n");
  	}    