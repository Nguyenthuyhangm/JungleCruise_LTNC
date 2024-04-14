#ifndef MAIN_OBJECT_H
#define MAIN_OBJECT_H
#define GRAVITY 1.5;
#define MAX_FALL_SPEED 12;
#define PLAYER_SPEED 10;
#define JUMP_SPEED 20;

#include "CommonFunction.h"
#include "BaseObject.h"
#include"BulletObject.h"
#include<vector>
using namespace std;

class MainObject : public BaseObject
{
public:
	MainObject();
	~MainObject();

	enum WalkType
	{
		WALK_RIGTH = 0,
		WALK_LEFT = 1,
	};

	bool LoadImg(std::string path, SDL_Renderer* Screen);
	void Show(SDL_Renderer* des);//Show Frame; 
	void HandleInputAction(SDL_Event events, SDL_Renderer* Screen);
	void Animation();//chuyên xử lý hiệu ứng, animation

	void DoPlayer(Map& map_data);
	void Checkmap(Map& map_data);
	void SetMapXY(const int map_x, const int map_y) {
		map_x_ = map_x; map_y_ = map_y;}
	void CenterEntityOnMap(Map& map_data);
	void UpdateImagePlayer(SDL_Renderer* des);
	void set_bullet_list(vector<BulletObject*>bullet_list)
	{
		p_bullet_list = bullet_list;
	}
	vector<BulletObject*>get_bullet_list()const { return p_bullet_list; }
	void HandleBullet(SDL_Renderer* des);
	void IncreaseFruit();

private:
	int fruit_count;// số lượng tiền ăn được ban đầu
	vector<BulletObject*> p_bullet_list;// băng đạn 
	float x_val_;
	float y_val_;

	float x_pos_;
	float y_pos_;

	int width_frame_;
	int height_frame_;

	SDL_Rect frame_clip_[8];
	Input input_type_;//bien chuyen luu trang thai
	int frame_;//bien luu frame dang o frame nao
	int status_;//trang thai 
	bool on_ground;

	int map_x_;
	int map_y_;
};
#endif
