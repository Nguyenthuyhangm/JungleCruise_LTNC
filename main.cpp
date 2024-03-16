#include"CommonFunction.h"
#include"BaseObject.h"
#include"game_map.h"

BaseObject g_background3;


bool  InitData()
{
	bool success = true;
	int ret = SDL_Init(SDL_INIT_VIDEO);
	if (ret < 0)
		return false;

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	g_window = SDL_CreateWindow("Game Jungle Cruise", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (g_window == NULL)
	{
		success = false;
	}
	else
	{
		g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
		if (g_screen == NULL)
			success = false;
		else
		{
			SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) && imgFlags))
				success = false;
		}
	}
	return success;
}
// Đóng cửa sổ
void close()
{
	g_background3.Free();//Giải phóng bộ nhớ 

	SDL_DestroyRenderer(g_screen);
	g_screen = NULL;

	SDL_DestroyWindow(g_window);
	g_window = NULL;

	IMG_Quit();
	SDL_Quit();

}

bool LoadBackGround3()//Kiểm tra BackGround load lên có bị lỗi hay không
{
	bool ret = g_background3.LoadImg("background.png", g_screen);
	if (ret == false)
		return false;

	return true;
}

int main(int argc, char* argv[])
{
	if (InitData() == false)
		return -1;
	if (LoadBackGround3() == false)
		return -1;

	GameMap game_map;
	//fill ảnh đất
	//Đọc map viết bởi số 0 1 2 
	char file_path[] = "map01.dat";
	game_map.LoadMap(file_path);
	//Load các hình ảnh tương ứng vào ô 1 2 3
	game_map.LoadTile(g_screen);


	bool is_quit = false;
	while (!is_quit)
	{
		while (SDL_PollEvent(&g_event) != 0)
		{
			if (g_event.type == SDL_QUIT)
			{
				is_quit = true;
			}
		}
		SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);
		SDL_RenderClear(g_screen);

		g_background3.Render(g_screen, NULL);
		game_map.DrawMap(g_screen);

		SDL_RenderPresent(g_screen);
	}

	close();
	return 0;
}