#ifndef GAME_MAP_H
#define GAME_MAP_H

#include "CommonFunction.h"
#include "BaseObject.h"

//Tạo class kế thừa tính năng BaseObject

class TileMap : public BaseObject
{
public:
	TileMap() {
		;
	}
	~TileMap() { ; }

};
//Quản lý việc xây dựng map, tile toàn bộ map vào vị trí ô vuông đc lưu trong struct

class GameMap
{
public:

	GameMap() { ; }
	~GameMap() { ; }
	void LoadMap(char* name);
	void LoadTile(SDL_Renderer* screen);
	void DrawMap(SDL_Renderer* screen);
	Map getMap()const {
		return game_map_;
	};
private:
	Map game_map_;
	TileMap tile_map[20];
};
#endif