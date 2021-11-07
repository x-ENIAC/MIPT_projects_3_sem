#include "view.h"

#ifndef ANIMATION_H
#define ANIMATION_H

class Animation {
  public:
	SDL_Texture* old_texture;
	SDL_Texture* new_texture;

	double time_alive;

	View_object* view;

	size_t num_of_texture;

	Animation() {
		old_texture = new_texture = NULL;
		view = NULL;

		time_alive = 0;
		num_of_texture = 0;
	}

	Animation(SDL_Texture* par_old_texture, SDL_Texture* par_new_texture, View_object* par_view, const double par_time_alive) {
		old_texture = par_old_texture;
		new_texture = par_new_texture;

		time_alive = par_time_alive;

		view = par_view;
	}

	void tick(const double delta_time) {
		/*if(num_of_texture == 0) {
			texture->set_texture(old_texture);
			num_of_texture = 1;
			printf("1\n");
		}
		else {
			texture->set_texture(new_texture);
			num_of_texture = 0;
			printf("0\n");
		}*/

		view->texture->set_texture(new_texture);

		time_alive -= delta_time;

		//if(time_alive <= 0) {
		//	view->texture->set_texture(old_texture);
			//printf("@@@\n");
		//}
	}

	inline bool is_alive() const {
		return (time_alive >= 0);
	}
};

#endif