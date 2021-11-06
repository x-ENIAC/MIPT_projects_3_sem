#include "view.h"

#ifndef ANIMATION_H
#define ANIMATION_H

class Animation {
  public:
	SDL_Texture* old_texture;
	SDL_Texture* new_texture;

	double time_alive;

	Texture* texture;

	size_t num_of_texture;

	Animation() {
		old_texture = new_texture = NULL;
		texture = NULL;

		time_alive = 0;
		num_of_texture = 0;
	}

	Animation(SDL_Texture* par_old_texture, SDL_Texture* par_new_texture, const double par_time_alive, Texture* par_texture) {
		old_texture = par_old_texture;
		new_texture = par_new_texture;

		time_alive = par_time_alive;

		texture = par_texture;
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

		texture->set_texture(new_texture);

		time_alive -= delta_time;

		if(time_alive <= 0) {
			texture->set_texture(old_texture);
			//printf("@@@\n");
		}
	}

	inline bool is_alive() const {
		return (time_alive >= 0);
	}
};

#endif