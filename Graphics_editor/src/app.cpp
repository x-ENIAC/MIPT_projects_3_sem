#include "app.h"

App* App::app = 0;

void App::initialize(const int width_screen, const int height_screen) {

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

	fill_app_interface();

	return;
}

PRGBA from_prgba_to_colour(Colour color) {
	return PRGBA(color.red, color.green, color.blue, color.alpha);
}

Colour from_prgba_to_colour(PRGBA color) {
	return Colour(color.r, color.g, color.b, color.a);
}

// ----------- General ---------------------- 

double get_absolute_time() {
	return time(NULL) - App::get_app()->get_begin_era();
}

void log(const char *fmt, ...) {
	va_list args;
	va_start(args, fmt);

	FILE* log_file = fopen("log.txt", "w");
	fprintf(log_file, fmt, args);
	fclose(log_file);

	va_end(args);
}

void release_pixels(PRGBA *pixels) {
	Canvas* active_canvas = (Canvas*)(App::get_app()->get_view_manager()->manager_of_canvas_managers->active_canvas->view_objects[0]);

	int width  = active_canvas->rect->get_width();
	int height = active_canvas->rect->get_height();	

	for(int i = 0; i < height; ++i) {
		for(int j = 0; j < width; ++j) {
			Colour now = {pixels[i * width + j].r, pixels[i * width + j].g, pixels[i * width + j].b, pixels[i * width + j].a};
			active_canvas->cells_color[i][j].color_after_correction	= now;
			active_canvas->cells_color[i][j].begin_color			= now;
		}
	}

	delete[] pixels;
}

PRGBA get_color() {
	Colour color = Tool_manager::get_tool_manager()->get_pen_colour();
	PRGBA new_color = {(unsigned char)color.red, (unsigned char)color.green, (unsigned char)color.blue, (unsigned char)color.alpha};
	return new_color;
}

float get_size() {
	return Tool_manager::get_tool_manager()->get_pen_size();
}

// ----------- Target ---------------------- 

PRGBA* get_pixels() {
	Canvas* active_canvas = (Canvas*)(App::get_app()->get_view_manager()->manager_of_canvas_managers->active_canvas->view_objects[0]);

	int width  = active_canvas->rect->get_width();
	int height = active_canvas->rect->get_height();

	PRGBA* pixels = new PRGBA[width * height];

	for(int i = 0; i < height; ++i) {
		for(int j = 0; j < width; ++j) {
			Colour now = (active_canvas->cells_color[i][j].color_after_correction);
			if(now != WHITE)
				now.print();
			pixels[i * width + j] = {(unsigned char)now.red, (unsigned char)now.green, (unsigned char)now.blue, (unsigned char)now.alpha};
		}
	}

	return pixels;
}

void get_size(size_t *width, size_t *height) {
	Canvas* active_canvas = App::get_app()->get_active_canvas();

	*width  = active_canvas->rect->get_width();
	*height = active_canvas->rect->get_height();
}

// ----------- Render ---------------------- 

void circle(PVec2f position, float radius, PRGBA color, const PRenderMode *render_mode) {
	// printf("draw circle\n");
	Canvas* active_canvas = App::get_app()->get_active_canvas();

	Point left_up_corner = active_canvas->rect->get_left_up_corner();

	int x_begin = position.x - radius / 2, x_end = position.x + radius / 2;
	int y_begin = position.y - radius / 2, y_end = position.y + radius / 2;

	radius /= 2;

	SDL_SetRenderDrawColor(render, color.r, color.g, color.b, color.a);

	for(int x = x_begin; x <= x_end; ++x) {
		for(int y = y_begin; y <= y_end; ++y) {
			if((x - position.x) * (x - position.x) + (y - position.y) * (y - position.y) <= radius * radius) {

				active_canvas->cells_color[(int)(x - left_up_corner.x)][(int)(y - left_up_corner.y)].begin_color 			= from_prgba_to_colour(color);
				active_canvas->cells_color[(int)(x - left_up_corner.x)][(int)(y - left_up_corner.y)].color_after_correction = from_prgba_to_colour(color);
				active_canvas->cells_color[(int)(x - left_up_corner.x)][(int)(y - left_up_corner.y)].thickness			  	= 1;

				SDL_RenderDrawPoint(render, x, y);
			}
		}
	}
}

void line(PVec2f start, PVec2f end, PRGBA color, const PRenderMode *render_mode) {
	// printf("draw line!\n");
	Vector line({start.x, start.y}, {end.x, end.y});

	if(start.x > end.x)
		line.swap_ends();

	line.draw(App::get_app()->get_render(), from_prgba_to_colour(color));

	Canvas* active_canvas = App::get_app()->get_active_canvas();

	Point left_up_corner = active_canvas->rect->get_left_up_corner();

	for(int x = start.x; x <= end.x; ++x) {
		int y = line.get_y_from_x(x);

		active_canvas->cells_color[(int)(x - left_up_corner.x)][(int)(y - left_up_corner.y)].begin_color 			= from_prgba_to_colour(color);
		active_canvas->cells_color[(int)(x - left_up_corner.x)][(int)(y - left_up_corner.y)].color_after_correction = from_prgba_to_colour(color);
		active_canvas->cells_color[(int)(x - left_up_corner.x)][(int)(y - left_up_corner.y)].thickness			  	= 1;

		SDL_RenderDrawPoint(render, x, y);		
	}
}

void triangle(PVec2f p1, PVec2f p2, PVec2f p3, PRGBA color, const PRenderMode *render_mode) {
	// printf("triangle!\n");

	Vector line1({p1.x, p1.y}, {p2.x, p2.y});
	Vector line2({p2.x, p2.y}, {p3.x, p3.y});
	Vector line3({p3.x, p3.y}, {p1.x, p1.y});

	line({(float)line1.get_point_begin().x, (float)line1.get_point_begin().y},
		{(float)line2.get_point_end().x, (float)line2.get_point_end().y}, color, render_mode);

	line({(float)line2.get_point_begin().x, (float)line2.get_point_begin().y},
		{(float)line3.get_point_end().x, (float)line3.get_point_end().y}, color, render_mode);

	line({(float)line3.get_point_begin().x, (float)line3.get_point_begin().y},
		{(float)line1.get_point_end().x, (float)line1.get_point_end().y}, color, render_mode);
}

void rectangle(PVec2f p1, PVec2f p2, PRGBA color, const PRenderMode *render_mode) {
	// Point center = {p1.x, p1.y};
	// center += {p2.x, p2.y};
	// center /= 2.0;

	Vector line1({p1.x, p1.y}, {p1.x, p2.y});
	Vector line2({p1.x, p2.y}, {p2.x, p2.y});
	Vector line3({p2.x, p2.y}, {p2.x, p1.y});
	Vector line4({p2.x, p1.y}, {p1.x, p1.y});

	line({(float)line1.get_point_begin().x, (float)line1.get_point_begin().y},
		{(float)line2.get_point_end().x, (float)line2.get_point_end().y}, color, render_mode);

	line({(float)line2.get_point_begin().x, (float)line2.get_point_begin().y},
		{(float)line3.get_point_end().x, (float)line3.get_point_end().y}, color, render_mode);	

	line({(float)line3.get_point_begin().x, (float)line3.get_point_begin().y},
		{(float)line4.get_point_end().x, (float)line4.get_point_end().y}, color, render_mode);	

	line({(float)line4.get_point_begin().x, (float)line4.get_point_begin().y},
		{(float)line1.get_point_end().x, (float)line1.get_point_end().y}, color, render_mode);	

	// double rwidth = fabs(p2.x - p1.x), rheight = fabs(p2.y - p1.y);
	// Rectangle rect(center, rwidth, rheight, from_prgba_to_colour(color), true);
	// rect.draw(render);
}

void pixels(PVec2f position, const PRGBA *data, size_t width, size_t height, const PRenderMode *render_mode) {
	Canvas* active_canvas = App::get_app()->get_active_canvas();

	for(int i = 0; i < width; ++i) {
		for(int j = 0; j < height; ++j) {
			Point now_point({position.x, position.y});
			now_point += Point(i, j);

			SDL_SetRenderDrawColor(render, data[i * height + j].r, data[i * height + j].g, data[i * height + j].b, 1);
			SDL_RenderDrawPoint(render, now_point.x, now_point.y);

			int now_index = i * height + j;

			active_canvas->cells_color[i][j].begin_color			= {data[now_index].r, data[now_index].g,
																		data[now_index].b, data[now_index].a};
			active_canvas->cells_color[i][j].color_after_correction = {data[now_index].r, data[now_index].g,
																		data[now_index].b, data[now_index].a};
			active_canvas->cells_color[i][j].thickness = 1;
		}
	}
}


void App::fill_app_interface() {
	printf("Start fill app interface\n");
	
	app_interface = new PAppInterface;

	app_interface->std_version = 1;
	app_interface->reserved = NULL;

	app_interface->general.feature_level = 0;
	app_interface->general.log = &log;
	app_interface->general.get_absolute_time = &get_absolute_time;
	app_interface->general.release_pixels = &release_pixels;
	app_interface->general.get_color = &get_color;
	app_interface->general.get_size = &get_size;

	app_interface->target.get_pixels = &get_pixels;
	app_interface->target.get_size = &get_size;

	app_interface->render.circle = &circle;
	app_interface->render.line = &line;
	app_interface->render.triangle = &triangle;
	app_interface->render.rectangle = &rectangle;
	app_interface->render.pixels = &pixels;

	app_interface->settings.create_surface = NULL;
	app_interface->settings.destroy_surface = NULL;
	app_interface->settings.add = NULL;
	app_interface->settings.get = NULL;

	app_interface->shader.apply = NULL;
	app_interface->shader.compile = NULL;
	app_interface->shader.release = NULL;
	app_interface->shader.set_uniform_int = NULL;
	app_interface->shader.set_uniform_int_arr = NULL;
	app_interface->shader.set_uniform_float = NULL;
	app_interface->shader.set_uniform_float_arr = NULL;
}

void App::deinitialize() {
	SDL_FreeSurface    (app->screen);
	SDL_DestroyWindow  (app->window);
	SDL_DestroyRenderer(app->render);
	SDL_DestroyTexture (app->texture);

	TTF_Quit();
	SDL_Quit();
}

void App::update() {
	begin_era = time(NULL);

	SDL_SetRenderDrawColor(render, screen_color.red, screen_color.green, screen_color.blue, screen_color.alpha);
	SDL_RenderClear(app->render);

	printf("Start initialize the view manager\n");
	// app->plugin_manager = new Plugin_manager();

	app->view_manager = new View_manager(Point(width_screen / 2.0, height_screen / 2.0), width_screen, height_screen, screen_color/*, &animation_manager*/);

	printf("\n\nBEGIN EVENTS CYCLE\n");
	SDL_Event event = {};
	bool is_run = true;
	while(is_run) {
		while(SDL_PollEvent(&event)) {
			if(event.type == SDL_QUIT)
				is_run = false;

			else {
				app->view_manager->check_events(&event);
			}
		}

		SDL_SetRenderDrawColor(render, screen_color.red, screen_color.green, screen_color.blue, screen_color.alpha);
		SDL_RenderClear(app->render);

		app->view_manager->draw(&app->render, &app->texture, &app->screen);

		app->view_manager->tick(TIME_DELTA);
		Animation_manager::get_animation_manager()->tick(TIME_DELTA);

		SDL_RenderPresent(app->render);
	}
}

Canvas* App::get_active_canvas() {
	return (Canvas*)(App::get_app()->get_view_manager()->manager_of_canvas_managers->active_canvas->view_objects[0]);
}

SDL_Renderer* App::get_render() {
	return app->render;
}

App* App::get_app() {
	if(!app)
		app = new App();
	return app;
}

Painter_tools_and_plugins* App::get_painter_tools_and_plugins() {
	if(!view_manager)
		return NULL;

	return view_manager->painter_tools_and_plugins;
}

long long App::get_begin_era() {
	return begin_era;
}

long long App::get_width_screen() {
	return width_screen;
}

long long App::get_height_screen() {
	return height_screen;
}

View_manager* App::get_view_manager() {
	return view_manager;
}

PAppInterface* App::get_app_interface() {
	return app_interface;
}