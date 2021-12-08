#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "rectangle.h"

#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

const size_t MAX_SIZE_OF_TEXTURES_ARRAY = 50;
const char NON_PATH_TO_PUCTURE[] = "non_picture";

const char PATH_TO_PICTURE_WITH_BLACK_CLOSE_BUTTON[]   = "textures/black_close.bmp";
const char PATH_TO_PICTURE_WITH_GREY_1_CLOSE_BUTTON[]  = "textures/grey_1_close.bmp";
const char PATH_TO_PICTURE_WITH_GREY_2_CLOSE_BUTTON[]  = "textures/grey_2_close.bmp";

const char PATH_TO_PICTURE_WITH_ROLL_UP_BUTTON[] = "textures/roll_up.bmp";
const char PATH_TO_PICTURE_WITH_TITLE_BUTTON[]	 = "textures/title.bmp";

const char PATH_TO_PICTURE_WITH_FILE_BUTTON[] 	 = "textures/file.bmp";
const char PATH_TO_PICTURE_WITH_NEW_BUTTON[]	 = "textures/new.bmp";
const char PATH_TO_PICTURE_WITH_HELP_BUTTON[]	 = "textures/help.bmp";

const char PATH_TO_PICTURE_WITH_GREY_1_BUTTON[]	 = "textures/grey_1.bmp";
const char PATH_TO_PICTURE_WITH_GREY_2_BUTTON[]	 = "textures/grey_2.bmp";
const char PATH_TO_PICTURE_WITH_GREY_3_BUTTON[]	 = "textures/grey_3.bmp";
const char PATH_TO_PICTURE_WITH_GREY_4_BUTTON[]	 = "textures/grey_4.bmp";

const char PATH_TO_PICTURE_WITH_PALETTE_BUTTON[]  	   = "textures/black_palette.bmp";
const char PATH_TO_PICTURE_WITH_THICKNESS_BUTTON[] 	   = "textures/black_thickness.bmp";
const char PATH_TO_PICTURE_WITH_SPLINE_BUTTON[]		   = "textures/black_spline.bmp";
const char PATH_TO_PICTURE_WITH_CANVAS_BUTTON[]	 	   = "textures/black_canvas.bmp";

const char PATH_TO_PICTURE_WITH_PENCIL[]	= "textures/pencil.bmp";
const char PATH_TO_PICTURE_WITH_PENCIL_1[]	= "textures/pencil_1.bmp";
const char PATH_TO_PICTURE_WITH_SHARPY[]	= "textures/sharpy.bmp";

struct Texture {
	SDL_Texture* texture;
	SDL_Renderer* render;
	char path_to_picture[MAX_SIZE_OF_TEXTURES_ARRAY];
	bool is_using_texture;

	Texture(SDL_Renderer* par_render) {
		render = par_render;
		is_using_texture = false;
	}

	~Texture() {}

	void add_new_texture(const char par_path_to_picture[]) { 
		texture = IMG_LoadTexture(render, par_path_to_picture);
		if(!texture) {
			printf("%s\n", IMG_GetError()); // Можно заменить на SDL_GetError()
			return;
		}

		if(strcmp(par_path_to_picture, path_to_picture)) {
			strcpy(path_to_picture, par_path_to_picture);
		}

		is_using_texture = true;
	}

	void update_texture(const char par_path_to_picture[]) {
		add_new_texture(par_path_to_picture);
	}

	void set_texture(SDL_Texture* par_texture) {
		texture = par_texture;
	}

	void draw_texture(SDL_Rect* rectangle) {
		SDL_RenderCopy(render, texture, NULL, rectangle);
	}
};

#endif