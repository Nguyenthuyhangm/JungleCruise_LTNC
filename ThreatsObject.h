#ifndef THREATS_OBJECT_H_
#define THREATS_OBJECT_H_
#define THREAT_FRAME_NUM 8
#define THREAT_GRAVITY 0.8
#define MAX_FALL_SPEED 10

#include"CommonFunction.h"
#include"BaseObject.h"

using namespace std;
class ThreatsObject : public BaseObject
{
public:
	ThreatsObject();
	~ThreatsObject();
	
	void set_x_val(float& xVal) { x_val = xVal; }
	void set_y_val(float& yVal) { y_val = yVal; }

	void set_x_pos(const float& xp) { x_pos = xp; }
	void set_y_pos(const float& yp) { y_pos = yp; }
	float get_x_pos()const { return x_pos; }// lay vi tri hien tai
	float get_y_pos()const { return y_pos; }
	void setmapXY(const int& mp_x, const int& mp_y) { map_x = mp_x; map_y = mp_y; }
	void setclip();
	bool LoadImg(string path, SDL_Renderer* Screen);
	void Show(SDL_Renderer* des);
	int get_width_frame() { return width_frame; }
	int get_height_frame() { return height_frame; }
	void DoPlayer(Map& gMap);// xử lý việc di chuyển của nhân v?t
	void CheckToMap(Map& gMap);

private: 
	SDL_Rect frame_clip_[THREAT_FRAME_NUM];
	int frame_;// quản lí chỉ số frame
	int height_frame;
	int width_frame;
	int come_back_time;//tgian quay lai
	bool on_ground;
	float y_pos;
	float x_pos;//.vị trí hiện tại
	float x_val;// hai biến tăng giá trị 
	float y_val;
	int map_x;// gioi han ban do 
	int map_y;

};

#endif // ! THREATS_OBJECT_H_
