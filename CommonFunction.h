#ifndef COMMON_FUNCTION_H_

#define COMMON_FUNCTION_H_

#include <string>
#include<SDL.h>
#include<windows.h>
#include <SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>
#include<vector>

static SDL_Window* g_window = nullptr;
static SDL_Renderer* g_screen = nullptr;
static SDL_Event g_event;

//Define Screen
const int FRAME_PER_SECOND = 30;// chất lượng hình ảnh -> số frame trong 1s
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 32;

//Tạo màu 
const  int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

#define BLANK_TILE 0
#define TILE_SIZE 64
#define MAX_MAP_X 400
#define MAX_MAP_Y 10
#define STAFF_FRUIT 4

//cau truc du lieu di chuyen

struct Input {
	int right_;
	int up_;
	int jump_;
	int down_;
};

struct Map {
	int start_x_;
	int start_y_;

	int max_x_;
	int max_y_;

	int tile[MAX_MAP_Y][MAX_MAP_X];
	char* file_name_;
};

#endif