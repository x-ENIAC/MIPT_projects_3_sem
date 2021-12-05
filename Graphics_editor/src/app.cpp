#include "app.h"

void App::initialize() {
  	SDL_STATUSES status = SDL_OKEY;

	if(SDL_Init(SDL_INIT_EVERYTHING | SDL_INIT_TIMER | SDL_INIT_VIDEO) != 0) {
		printf("bad init\n");
		status = BAD_SDL_INIT;
		return;
	}

	if((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
		printf("bad init\n");
		status = BAD_SDL_INIT;
		return;
	}

	SDL_CreateWindowAndRenderer(width_screen, height_screen, 0, &window, &render);

	if(!(window)) {
		printf("Window not create\n");
		status = WINDOW_NOT_CREATE;
		return;
	}

	char* name_font = "courier.ttf";

	TTF_Init();

	screen = SDL_GetWindowSurface(window);
}

void App::deinitialize() {
	SDL_FreeSurface    (screen);
	SDL_DestroyWindow  (window);
	SDL_DestroyRenderer(render);
	SDL_DestroyTexture (texture);

	TTF_Quit();
	SDL_Quit();
}

void App::update() {
	SDL_SetRenderDrawColor(render, screen_color.red, screen_color.green, screen_color.blue, screen_color.alpha);
	SDL_RenderClear(render);

	view_manager = new View_manager(Point(width_screen / 2.0, height_screen / 2.0), width_screen, height_screen, screen_color/*, &animation_manager*/);

	SDL_Event event = {};
	bool is_run = true;
	while(is_run) {
		while(SDL_PollEvent(&event)) {
			if(event.type == SDL_QUIT)
				is_run = false;

			else {
				view_manager->check_events(&event);
			}
		}

		SDL_SetRenderDrawColor(render, screen_color.red, screen_color.green, screen_color.blue, screen_color.alpha);
		SDL_RenderClear(render);

		view_manager->draw(&render, &texture, &screen);

		view_manager->tick(TIME_DELTA);
		anim_manager->tick(TIME_DELTA);

		SDL_RenderPresent(render);
	}		
}