#include "view.h"
#include "animation.h"

#ifndef ANIMATION_MANAGER_H
#define ANIMATION_MANAGER_H

const int MAX_COUNT_OF_ANIMATIONS = 100;

class Animation_manager {
  private:
	static Animation_manager* animation_manager;
	
	Animation** animations;
	size_t count_of_animations;

	Animation_manager() {
		animations = new Animation*[MAX_COUNT_OF_ANIMATIONS];
		count_of_animations = 0;
	}

	Animation_manager(const Animation_manager&);  
	Animation_manager& operator=(Animation_manager&);	

	~Animation_manager() {
		for(size_t i = 0; i < count_of_animations; ++i)
			delete[] animations[i];

		count_of_animations = 0;
	}

  public:

	static Animation_manager* initialize() {
		if(!animation_manager)
			animation_manager = new Animation_manager();

		return animation_manager;
	}

	static Animation_manager* get_animation_manager();

	void operator=(const Animation_manager&) = delete;

	void add_animation(SDL_Texture* old_texture, SDL_Texture* new_texture, View_object* view, double time_alive);

	void add_animation(SDL_Renderer* render, const char path_old[], const char path_new[], View_object* view, double time_alive);

	void tick(const double time_alive);

	void slow_delete(const size_t pos);
};

#endif