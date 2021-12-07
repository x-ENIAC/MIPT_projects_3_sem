#ifndef SLIDER_H
#define SLIDER_H

class Slider: public View_object {
  public:

	long long min_limit, max_limit;
	double now_value;

	Slider (const Point par_center, const double par_width, const double par_height,
			const long long par_min_limit, const long long par_max_limit, const Widget_types par_widget_types = Widget_types::VIEW_OBJECT,
			const char par_path_to_picture[] = NON_PATH_TO_PUCTURE) :
	  View_object(par_center, par_width, par_height, BLACK, par_widget_types, par_path_to_picture) {

		min_limit = par_min_limit;
		max_limit = par_max_limit;

		now_value = (max_limit + min_limit) / 2.0;

		if(strcmp(par_path_to_picture, NON_PATH_TO_PUCTURE))
			this->texture->add_new_texture(par_path_to_picture);
	}

	void draw(SDL_Renderer** render, SDL_Texture** texture, SDL_Surface** screen) override {
		if(is_visible) {
			//rect->draw(*render);
			if(this->texture->is_using_texture) {
				SDL_Rect sdl_rect;
				sdl_rect.w = rect->get_width();
				sdl_rect.h = rect->get_height();
				sdl_rect.x = rect->get_center().x - sdl_rect.w / 2.0;
				sdl_rect.y = rect->get_center().y - sdl_rect.h / 2.0;

				this->texture->draw_texture(&sdl_rect);
			}
		}
	}

	/*bool check_click(const float mouse_x, const float mouse_y, const Mouse_click_state* par_mouse_status) override {
		if(rect->is_point_belongs_to_rectangle( Point(mouse_x, mouse_y) )) {
			if(*par_mouse_status == Mouse_click_state::MOUSE_DOWN)
				delegate->click_reaction(mouse_x, mouse_y);

			return true;
		}

		return false;
	}*/

	bool check_motion(Point old_mouse, Point now_mouse, const Mouse_click_state* par_mouse_status) override {
		if(rect->is_point_belongs_to_rectangle( Point(now_mouse.x, now_mouse.y) ) ||
			rect->is_point_belongs_to_rectangle( Point(old_mouse.x, old_mouse.y) )) {
			//printf("!!! %d\n", *par_mouse_status);
			if(*par_mouse_status == Mouse_click_state::MOUSE_DOWN_AND_MOTION)
				update_coords(now_mouse);

			return true;
		}

		return false;
	}


	void update_coords(const Point new_center) {
		rect->center.x = new_center.x;
	}

	void update_position_from_delta(const Point delta) {
		rect->center -= delta;
	}
};

#endif