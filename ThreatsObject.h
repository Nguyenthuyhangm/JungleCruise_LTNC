#ifndef THREATS_OBJECT_H_
#define THREATS_OBJECT_H_ 
#include"CommonFunction.h"
#include"BaseObject.h"
#define THREAT_FRAME_NUM 8;
#define  GRAVITY_SPEED 0.8;
#define MAX_FALL_SPEED 10;
using namespace std;

class ThreatsObject : public BaseObject {
public:
	ThreatsObject();
	~ThreatsObject();

	enum TypeMove {
		STATIC_THREAT = 0,
		MOVE_IN_SPACE_THREAT = 1,

	};

	void set_x_val(float &xVal) { x_val = xVal; }
	void set_y_val(float& yVal) { y_val = yVal; }

	void set_x_pos(const float& xp) { x_pos = xp; }
	void set_y_pos(const float& yp) { y_pos = yp; }
	float get_x_pos()const { return x_pos; }
	float get_y_pos()const { return y_pos; }
	void setmap(const int& mp_x, const int& mp_y) { map_x = mp_x; map_y = mp_y; }
	void set_clip();
	bool LoadImg(string path, SDL_Renderer* Screen);
	void Show(SDL_Renderer* des);
	int get_width_frame()const { return width_frame_; }
	int get_height_frame()const { return height_frame_; }
	void DoPlayer(Map& gMap);
	void CheckToMap(Map& gMap);
	
	void set_type_move(const int& typeMove) {
		type_move_ = typeMove;
	}
	void SetAnimationPos(const int& pos_a, const int& pos_b) { animation_a_ = pos_a, animation_b_ = pos_b; }
	void set_input_left(const int& ipLeft) { input_type.left_ = ipLeft; };
	void ImpMoveType(SDL_Renderer* Screen);

private: 
	int map_x;
	int map_y;
	float x_pos;
	float y_pos;
	float x_val;
	float y_val; 
	bool on_ground_;
	int comeback_time;
	SDL_Rect frame_clip [8];
	int frame_;
	int width_frame_;
	int height_frame_;

	int type_move_;
	int animation_b_;
	int animation_a_;
	Input input_type_;

};




#endif