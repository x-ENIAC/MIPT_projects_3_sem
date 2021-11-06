
#include "animation_manager.h"
#define PATTERN_SINGLTONE

Animation_manager* Animation_manager::animation_manager = 0;

void Animation_manager::add_animation(SDL_Texture* old_texture, SDL_Texture* new_texture, View_object* view, double time_alive) {
	Animation* new_anim = new Animation(old_texture, new_texture, view, time_alive);

	animations[count_of_animations++] = new_anim;
}

void Animation_manager::add_animation(SDL_Renderer* render, const char path_old[], const char path_new[], View_object* view, double time_alive) {
	Texture* old_t = new Texture(render);
	old_t->update_texture(path_old);

	Texture* new_t = new Texture(render);
	new_t->update_texture(path_new);

	Animation* new_anim = new Animation(old_t->texture, new_t->texture, view, time_alive);

	animations[count_of_animations++] = new_anim;
}	

void Animation_manager::tick(const double time_alive) {
	for(size_t i = 0; i < count_of_animations; ++i)
		animations[i]->tick(time_alive);

	for(size_t i = 0; i < count_of_animations; ++i)
		if(!(animations[i]->is_alive())) {
			slow_delete(i);
		}
}

void Animation_manager::slow_delete(const size_t pos) {
	for(size_t i = pos + 1; i < MAX_COUNT_OF_ANIMATIONS; ++i)
		animations[i - 1] = animations[i];

	--count_of_animations;
}
