#ifndef COMMON_FUNCTION_H_

#define COMMON_FUNCTION_H_

#include <string>
#include<SDL.h>
#include<windows.h>
#include <SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>

static SDL_Window* g_window = nullptr;
static SDL_Renderer* g_screen = nullptr;
static SDL_Event g_event;

//Screen
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 674;
const int SCREEN_BPP = 32;

const  int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

#endif
