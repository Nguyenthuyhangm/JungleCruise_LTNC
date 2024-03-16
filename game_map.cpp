#define _CRT_SECURE_NO_DEPRECATE
#include<iostream>
#include<fstream>
using namespace std;
#include "game_map.h"

void GameMap::LoadMap(char* name)
{
    ifstream fi("map01.dat");
    if (!fi) {
        cout << "Error!" << endl;
        return;
    }
    for (int i = 0; i < MAX_MAP_Y; i++) {
        for (int j = 0; j < MAX_MAP_X; j++) {
            fi >> game_map_.tile[i][j];
            int val = game_map_.tile[i][j];
            if (val > 0) {
                if (j > game_map_.max_x_) { game_map_.max_x_ = j; }
                if (i > game_map_.max_y_) { game_map_.max_y_ = i; }
            }
        }
    }
    game_map_.max_x_ = (game_map_.max_x_ + 1) *TILE_SIZE;
    game_map_.max_y_ = (game_map_.max_y_ + 1) * TILE_SIZE;

    game_map_.start_x_ = 0;
    game_map_.start_y_ = 0;

    game_map_.file_name_ = name;
    fi.close();
};


//LoadTile 
void GameMap::LoadTile(SDL_Renderer* screen)
{
    char file_img[30];
    FILE* fp = NULL;
    for (int i = 0; i < 20; i++)
    {
        sprintf_s(file_img, "map/%d.png", i);
        fopen_s(&fp, file_img, "rb");
        if (fp == NULL)
        {
            continue;
        }
        fclose(fp);
        tile_map[i].LoadImg(file_img, screen);
    }
}

//vẽ map
void GameMap::DrawMap(SDL_Renderer* Screen)
{
    int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;

    int map_x = 0;
    int map_y = 0;

    map_x = game_map_.start_x_ / TILE_SIZE;
    map_y = game_map_.start_y_ / TILE_SIZE;//chỉ số của ô đang lưu trữ

    x1 = (game_map_.start_x_ % TILE_SIZE) * (-1);// lấy phần nguyên
    x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);// lấy phần nguyên

    y1 = (game_map_.start_y_ % TILE_SIZE) * -1;
    y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);

    for (int i = y1; i < y2; i += TILE_SIZE)
    {
        map_x = game_map_.start_x_ / TILE_SIZE;
        for (int j = x1; j < x2; j += TILE_SIZE)
        {
            int val = game_map_.tile[map_y][map_x];// vị trí ô thứ bao nhiêu? 
            if (val > 0)
            {
                tile_map[val].SetRect(j, i);
                tile_map[val].Render(Screen);//thiết lập vị trí fill map
            }
            map_x++;//sau mỗi vòng map phải tăng ô chỉ số lên mới lấy đc trạng thái tiếp theo
        }
        map_y++;//sau mỗi vòng map phải tăng ô chỉ số lên mới lấy đc trạng thái tiếp theo
    }

}