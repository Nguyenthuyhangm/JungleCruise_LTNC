#ifndef MAIN_OBJECT_H
#define MAIN_OBJECT_H
#define GRAVITY 0.8;
#define MAX_FALL_SPEED 10;
#define PLAYER_SPEED 1;
#define JUMP_SPEED -10;

#include "CommonFunction.h"
#include "BaseObject.h"

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
	void Animation1();

	void DoPlayer(Map& map_data);
	void Checkmap(Map& map_data);

private:
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

};
#endif
