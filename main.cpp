#include"CommonFunction.h"
#include"BaseObject.h"
#include"game_map.h"
#include"MainObject.h"
#include"ImpTimer.h"
#include"ThreatsObject.h"

using namespace std;

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

vector<ThreatsObject*>MakeThreadsList()
{
	vector<ThreatsObject*>list_threats;
	ThreatsObject* threats_objs = new ThreatsObject[20];
	for (int i = 0; i < 20; i++) {
		ThreatsObject* p_threat = (threats_objs + i);
		if (p_threat != NULL) {
			p_threat->LoadImg("Quai/dung1.png", g_screen);
			p_threat->setclip();
			p_threat->set_x_pos(500 + i * 1200);
			p_threat->set_y_pos(250);

			list_threats.push_back(p_threat);

		}
	}
	return list_threats;
}

int main(int argc, char* argv[])
{
	ImpTimer fps_timer;

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

	MainObject p_player;
	p_player.LoadImg("Base//Run.png",g_screen);
	p_player.Animation();
	


	bool is_quit = false;
	while (!is_quit)
	{
		fps_timer.Start();//// khi bắt đầu vòng while chạy bắt đầu start để tính tgian chạy 
		while (SDL_PollEvent(&g_event) != 0)
		{
			if (g_event.type == SDL_QUIT)
			{
				is_quit = true;
			}

			p_player.HandleInputAction(g_event, g_screen);
		}
		SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);
		SDL_RenderClear(g_screen);

		g_background3.Render(g_screen, NULL);
	
		Map map_data = game_map.getMap();

		p_player.SetMapXY(map_data.start_x_, map_data.start_y_);
		p_player.DoPlayer(map_data);
		p_player.Show(g_screen);
		p_player.HandleBullet(g_screen);
		p_player.Animation();

		vector<ThreatsObject*>threats_list = MakeThreadsList();

		game_map.Setmap(map_data);
		game_map.DrawMap(g_screen);

		for (int i = 0; i < threats_list.size(); i++) {
			ThreatsObject* p_threat = threats_list.at(i);
			if (p_threat != NULL) {
				p_threat->setmapXY(map_data.start_x_, map_data.start_y_);
				p_threat->DoPlayer(map_data);
				p_threat->Show(g_screen);
			}
		}

		SDL_RenderPresent(g_screen);

		int real_imp_time = fps_timer.get_ticks();// tgian thực sự đã trôi qua
		int time_one_frame = 1000 / FRAME_PER_SECOND;//tgian trôi trên lý thuyết

		if (real_imp_time < time_one_frame) {// nếu tgian thực sự nhỏ hơn lý thuyết -> 0 có độ trễ
			int delay_time = time_one_frame - real_imp_time;
			if(delay_time>0)// phải có độ trễ để đảm bảo cân bằng cho các frame
			SDL_Delay(delay_time);
		}
	}

	close();
	return 0;
}