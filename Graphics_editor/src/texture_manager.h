#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "rectangle.h"

#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

const size_t MAX_SIZE_OF_TEXTURES_ARRAY = 30;
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

struct Texture {
	SDL_Texture* texture;
	SDL_Renderer* render;
	char path_to_picture[MAX_SIZE_OF_TEXTURES_ARRAY];
	bool is_using_texture;

	Texture(SDL_Renderer* par_render) {
		render = par_render;
		is_using_texture = false;
	}

	void add_new_texture(const char par_path_to_picture[]) {
		SDL_Surface *bmp = SDL_LoadBMP(par_path_to_picture);

		if(!bmp) {
			printf("add> %s (%s)\n", SDL_GetError(), par_path_to_picture);
		}

		texture = SDL_CreateTextureFromSurface(render, bmp);
		strcpy(path_to_picture, par_path_to_picture);

		is_using_texture = true;
	}

	void update_texture(const char par_path_to_picture[]) {
		add_new_texture(par_path_to_picture);
	}

	void draw_texture(SDL_Rect* rectangle) {
		//printf("path_to_picture %s\n", path_to_picture);
		SDL_RenderCopy(render, texture, NULL, rectangle);
	}	
};

/*
class Texture_manager {
  public:
  	SDL_Renderer* render;
	SDL_Surface* screen;
	Texture* textures_array;
	size_t count_of_textures;

	Texture_manager(SDL_Renderer* par_render, SDL_Surface* par_screen) {
		render = par_render;
		screen = par_screen;

		textures_array = new Texture[MAX_SIZE_OF_TEXTURES_ARRAY];
		count_of_textures = 0;

		initialize();
	}

	void initialize() {
		add_new_texture(PATH_TO_PICTURE_WITH_CLOSE_BUTTON);
		add_new_texture(PATH_TO_PICTURE_WITH_ROLL_UP_BUTTON);
		add_new_texture(PATH_TO_PICTURE_WITH_FILE_BUTTON);
		add_new_texture(PATH_TO_PICTURE_WITH_NEW_BUTTON);
		add_new_texture(PATH_TO_PICTURE_WITH_HELP_BUTTON);
		add_new_texture(PATH_TO_PICTURE_WITH_TITLE_BUTTON);
	}

	void add_new_texture(const char* path_to_picture) {
		SDL_Surface *bmp = SDL_LoadBMP(path_to_picture);

		if(!bmp) {
			printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! %s\n", SDL_GetError());
		}

		//bmp = SDL_ConvertSurface(bmp, (screen)->format, NULL)	

		textures_array[count_of_textures].texture = SDL_CreateTextureFromSurface(render, bmp);
		strcpy(textures_array[count_of_textures++].path_to_picture, path_to_picture);
	}

	void draw_texture(const char* path_to_picture, SDL_Rect* rectangle) {
		int number = get_texture_number(path_to_picture);

		if(-1 == number) {
			//printf("bad\n");
			return;
		}

		SDL_RenderCopy(render, textures_array[number].texture, NULL, rectangle);
	}

	int get_texture_number(const char* path_to_picture) {
		if(!strcmp(path_to_picture, NON_PATH_TO_PUCTURE))
			return -1;

		for(size_t i = 0; i < count_of_textures; ++i)
			if(!strcmp(textures_array[i].path_to_picture, path_to_picture))
				return i;

		return -1;
	}
};*/

#endif