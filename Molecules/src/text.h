#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#ifndef TEXT_H
#define TEXT_H

class Text {
  public:
	size_t font_size;
	char* font_name;
  	TTF_Font* font;
	char* text;
	Colour color;

	Text() {
		font_size = 24;
		font_name = "00057_1000HURT.ttf";
		font = TTF_OpenFont(font_name, font_size);
		text = "hello, world";
		color = {0, 0, 0, 0};
	    
	    if(font == NULL) {
	        printf("error: font not found, %s\n", TTF_GetError());
	        exit(EXIT_FAILURE);
	    }			
	}

	Text(char* par_font_name, const size_t par_font_size, char* par_text, const Colour par_color) {
		font_size = par_font_size;
		font_name = par_font_name;
		font = TTF_OpenFont(font_name, font_size);
		text      = par_text;
		color     = par_color;

	    if(!font) {
	        printf("error: font not found, %s\n", TTF_GetError());
	        exit(EXIT_FAILURE);
	    }		
	}

	~Text() {

	}

	void draw_text(const Point pos, SDL_Renderer** render, SDL_Texture** texture) {
	    SDL_Surface* surface = {};
	    SDL_Color text_color = {};
	    set_color(&color, &text_color);
	    SDL_Rect rect = {};

	    surface = TTF_RenderText_Solid(font, text, text_color);
	    *texture = SDL_CreateTextureFromSurface(*render, surface);
	    rect.w = surface->w;
	    rect.h = surface->h;
	    SDL_FreeSurface(surface);	

	    rect.x = pos.x - rect.w / 2.0;
	    rect.y = pos.y - rect.h / 2.0;

	    SDL_RenderCopy(*render, *texture, NULL, &rect);	  
	}

	void set_color(const Colour* color, SDL_Color* text_color) {
		text_color->r = color->red;
		text_color->g = color->green;
		text_color->b = color->blue;
		text_color->a = color->alpha;
	}
};

#endif