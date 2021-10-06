
#ifndef TEXT_BUTTON_H
#define TEXT_BUTTON_H

/*class Text_button {
  public:
	Button* button;
	char* text;
	SDL_Rect *rect;

  	Text_button(Button* new_button, char* par_text) {
  		//Button new_button(par_point, par_color, par_width, par_height, BUTTON_OWNER_OTHER_CLASS);
  		button = new_button;
        text = par_text;
        //printf("(%lg, %lg)\n", button->object_rect->get_x_center(), button->object_rect->get_y_center());
    }	

    void draw_button(SDL_Renderer* render, SDL_Texture* texture, TTF_Font* font) {
		button->object_rect->draw_molecule(render);
		draw_text(render, texture, font);
	}

	void draw_text(SDL_Renderer* render, SDL_Texture* texture, TTF_Font* font) {
    	SDL_Surface *surface;
    	SDL_Color textColor = {255, 255, 255, 0};

    	surface = TTF_RenderText_Solid(font, text, textColor);
    	*texture = SDL_CreateTextureFromSurface(render, surface);
    	//rect->x = 
	}
};*/

#endif

