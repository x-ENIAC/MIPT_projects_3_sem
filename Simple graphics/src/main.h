
#ifndef MAIN_H
#define MAIN_H

const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;
const int MAX_VALUE_COLOUR = 255;
const int INDENT = 20;

const double DELTA = 0.005;

//-------- First screen parameters --------------
const int FIRST_SCREEN_WIDTH  = 650;
const int FIRST_SCREEN_HEIGHT = 650;

const int FIRST_SCREEN_X_UPPER_LEFT_CORNER = 10;
const int FIRST_SCREEN_Y_UPPER_LEFT_CORNER = 10;

//-------- Second screen parameters --------------
const int SECOND_SCREEN_WIDTH  = 350;
const int SECOND_SCREEN_HEIGHT = 500;

const int SECOND_SCREEN_X_UPPER_LEFT_CORNER = 700;
const int SECOND_SCREEN_Y_UPPER_LEFT_CORNER = 10;

enum SDL_STATUSES {
	SDL_OKEY		   = 0,
	BAD_SDL_INIT       = 1,
	WINDOW_NOT_CREATE  = 2,
	SURFACE_NOT_CREATE = 3,
	RENDER_NOT_CREATE  = 4,
	PICTURE_NOT_INIT   = 5,
	TEXTURE_NOT_CREATE = 6,
};

SDL_STATUSES initialize 			(SDL_Window* &window, SDL_Renderer* &render);
void 		 quit					(SDL_Window* &window, SDL_Renderer* &render);


int function(int x);
double function(double x);

#endif