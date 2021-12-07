#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "view.h"
//#include "widget_types.h"

#ifndef TEXT_H
#define TEXT_H

class Text : public View_object {
  public:
	size_t font_size;
	char* font_name;
	TTF_Font* font;
	char text[100];
	Colour color;

	Text() : View_object(Widget_types::TEXT) {

		font_size = 20;
		font_name = (char*)calloc(100, sizeof(char));
		strcpy(font_name, "courier.ttf");
		font = TTF_OpenFont(font_name, font_size);

		//text = new char[30];
		strcpy(text, "hello, world");

		color = {0, 0, 0, 0};
		
		if(font == NULL) {
			printf("error: font not found, %s\n", TTF_GetError());
			exit(EXIT_FAILURE);
		}
	}

	Text(const Point par_point, const char* par_text, const double par_width, const double par_height, const Colour par_color) : 
	  View_object(par_point, par_width, par_height, par_color, Widget_types::TEXT) {

		font_size = 20;
		font_name = (char*)calloc(100, sizeof(char));
		strcpy(font_name, "courier.ttf");
		font = TTF_OpenFont(font_name, font_size);

		//text = new char[30];
		strcpy(text, par_text);

		color = par_color;

		if(!font) {
			printf("error: font not found, %s\n", TTF_GetError());
			exit(EXIT_FAILURE);
		}
	}


	/*Text(const Point par_point, char* par_font_name, const size_t par_font_size, char* par_text, 
								const double par_width, const double par_height, const Colour par_color) : 
	  View_object(par_point, par_width, par_height, par_color, Widget_types::TEXT) {

		font_size = par_font_size;
		font_name = par_font_name;
		font 	  = TTF_OpenFont(font_name, font_size);

		//text = new char[30];
		strcpy(text, par_text);

		color     = par_color;

		if(!font) {
			printf("error: font not found, %s\n", TTF_GetError());
			exit(EXIT_FAILURE);
		}
	}*/

	~Text() {

	}

	void draw(SDL_Renderer** render, SDL_Texture** texture, SDL_Surface** screen/*, Texture_manager* texture_manager*/) {
		//printf("\t\t\tbegin draw text, text %s, pos %lg, %lg, size font %d\n", text, center.x, center.y, font_size);
		SDL_Surface* surface = {};
		SDL_Color text_color = {};

		set_color(&color, &text_color);
		SDL_Rect sdl_rect = {};

		//if(text != " ")
		//	printf("text: %s\n", text);

		surface = TTF_RenderText_Solid(font, text, text_color);
		*texture = SDL_CreateTextureFromSurface(*render, surface);
		sdl_rect.w = surface->w;
		sdl_rect.h = surface->h;
		SDL_FreeSurface(surface);	

		sdl_rect.x = rect->get_center().x - sdl_rect.w / 2.0;
		sdl_rect.y = rect->get_center().y - sdl_rect.h / 2.0;

		SDL_RenderCopy(*render, *texture, NULL, &sdl_rect);	  
		//printf("\t\t\tend draw text\n");
	}

	void draw_text(const Point pos, SDL_Renderer** render, SDL_Texture** texture) {
		SDL_Surface* surface = {};
		SDL_Color text_color = {};
		set_color(&color, &text_color);
		SDL_Rect sdl_rect = {};

		if(text && text != "") {
			surface = TTF_RenderText_Solid(font, text, text_color);
			*texture = SDL_CreateTextureFromSurface(*render, surface);
			sdl_rect.w = surface->w;
			sdl_rect.h = surface->h;
			SDL_FreeSurface(surface);	

			sdl_rect.x = pos.x - sdl_rect.w / 2.0;
			sdl_rect.y = pos.y - sdl_rect.h / 2.0;
		}

		SDL_RenderCopy(*render, *texture, NULL, &sdl_rect);	  
	}

	void set_color(const Colour* color, SDL_Color* text_color) {
		text_color->r = color->red;
		text_color->g = color->green;
		text_color->b = color->blue;
		text_color->a = color->alpha;
	}
};

#endif