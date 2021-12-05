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

Animation_manager* anim_manager = Animation_manager::initialize();

const int SCREEN_WIDTH  = 920;
const int SCREEN_HEIGHT = 720;
const double DELTA = 0.5;
extern const double TIME_DELTA = 0.005;

int main() {

	App* app = new App(SCREEN_WIDTH, SCREEN_HEIGHT);

	app->initialize();
	
	render = app->render;

	app->update();
	app->deinitialize();

	return 0;
}