#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "app.h"
#include "view_manager.h"
#include "animation_manager.h"

#include "button.h"

#include "button_delegate.h"
#include "text.h"
#include "chart.h"

SDL_Renderer* render;

const int SCREEN_WIDTH  = 920;
const int SCREEN_HEIGHT = 720;
const double DELTA = 0.5;
const double TIME_DELTA = 0.005;

Animation_manager* anim_manager = Animation_manager::initialize();

int main() {
	App::get_app()->initialize(SCREEN_WIDTH, SCREEN_HEIGHT);
	
	render = App::get_app()->get_render();

	App::get_app()->update();
	App::get_app()->deinitialize();

	return 0;
}