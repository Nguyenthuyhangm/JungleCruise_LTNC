#ifndef THREATS_OBJECT_H_
#define THREATS_OBJECT_H_
#define THREAT_FRAME_NUM 8
#include"CommonFunction.h"
#include"BaseObject.h"

using namespace std; 

class ThreatsObject : public BaseObject {
public: 
	ThreatsObject();
	~ThreatsObject();

	void set_x_val(const float& xVal) { x_val_ = xVal; }
	void set_y_val(const float& yVal) { y_val_ = yVal; }

	void set_x_pos(const float& xp) { x_pos_ = xp; }
	void set_y_pos(const float& yp) { y_pos_ = yp; }
	float get_x_pos()const { return x_pos_; }
	float get_y_pos()const { return y_pos_; }
	void SetMapXY(const int& mp_x, const int& mp_y) { SDL_)

private: 
	int map_x_;
	int map_y_;
	float x_val_;//2 biến tăng gtri
	float y_val_;
	float x_pos_;
	float y_pos_;
	bool on_ground_;// trên mđất hay chưa
	int come_back_time_;//tgian quay trở lại
	SDL_Rect frame_clip_[THREAT_FRAME_NUM];
	int width_frame_;
	int height_frame_;
	int frame_;
};

#endif
