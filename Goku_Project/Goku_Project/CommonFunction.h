#ifndef CommonFunction_H_

#define CommonFunction_H_

#include <iostream>

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <windows.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <ctime>

static Mix_Chunk *g_sound_soku[2];

const int WIDTH_BACKGROUND = 1300;
const int HEIGHT_BACKGROUND = 600;
const int BFF_BACKGROUND = 32;
const int NUMBER_THREATS = 5;


static SDL_Surface *g_screen = NULL;
static SDL_Surface *g_background = NULL;
static SDL_Surface *g_endgame = NULL;
static SDL_Surface *g_img_menu = NULL;
static SDL_Event g_even;
static SDL_Surface *g_object;

namespace SDLCommonFunc {
	SDL_Rect ApplySurface(SDL_Surface *scr, SDL_Surface *des, int x, int y);
	void ApplySurfaceClip(SDL_Surface *scr, SDL_Surface *des, SDL_Rect *clip, int x, int y);
	bool CheckCollision(const SDL_Rect & Object1, const SDL_Rect & object2);
	void CleanUp();
	SDL_Surface * LoadImage(std::string file_path);
	int ShowMenu(SDL_Surface *des, TTF_Font *font);
}

#endif // !CommonFunction_H_
