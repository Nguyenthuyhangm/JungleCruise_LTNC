#include"ThreatsObject.h"
using namespace std;
ThreatsObject::ThreatsObject() {
	width_frame = 0;
	height_frame = 0;
	x_val = 0.0;
	y_val = 0.0;
	x_pos = 0.0;
	y_pos = 0.0;
	on_ground = false;
	come_back_time = 0;
	frame_ = 0;
}

ThreatsObject::~ThreatsObject() {

}

bool ThreatsObject::LoadImg(string path, SDL_Renderer* Screen) {
	bool ret = BaseObject::LoadImg(path, Screen);
	if (ret==true) {
		width_frame = rect_.w / THREAT_FRAME_NUM;
		height_frame = rect_.h;
	}
	return ret;
}

void ThreatsObject::setclip() {
	if (width_frame > 0 && height_frame > 0) {
		frame_clip_[0].x = 0;
		frame_clip_[0].y = 0;
		frame_clip_[0].w = width_frame;
		frame_clip_[0].h = height_frame;

		frame_clip_[1].x = width_frame;
		frame_clip_[1].y = 0;
		frame_clip_[1].w = width_frame;
		frame_clip_[1].h = height_frame;

		frame_clip_[2].x = 2 * width_frame;
		frame_clip_[2].y = 0;
		frame_clip_[2].w = width_frame;
		frame_clip_[2].h = height_frame;

		frame_clip_[3].x = 3 * width_frame;
		frame_clip_[3].y = 0;
		frame_clip_[3].w = width_frame;
		frame_clip_[3].h = height_frame;

		frame_clip_[4].x = 4 * width_frame;
		frame_clip_[4].y = 0;
		frame_clip_[4].w = width_frame;
		frame_clip_[4].h = height_frame;

		frame_clip_[5].x = 5 * width_frame;
		frame_clip_[5].y = 0;
		frame_clip_[5].w = width_frame;
		frame_clip_[5].h = height_frame;

		frame_clip_[6].x = 6 * width_frame;
		frame_clip_[6].y = 0;
		frame_clip_[6].w = width_frame;
		frame_clip_[6].h = height_frame;

		frame_clip_[7].x = 7 * width_frame;
		frame_clip_[7].y = 0;
		frame_clip_[7].w = width_frame;
		frame_clip_[7].h = height_frame;

	}
}

void ThreatsObject::Show(SDL_Renderer* des)
{
	if (come_back_time == 0) {
		rect_.x = x_pos - map_x;
		rect_.y = y_pos - map_y;
		frame_++;
		/*if (frame_ >= 8) {
			frame_ = 0;
		}*/
		SDL_Rect* currentClip = &frame_clip_[frame_];
		SDL_Rect renderQuad = { rect_.x,rect_.y, width_frame,height_frame };
		SDL_RenderCopy(des, p_object_, currentClip, &renderQuad);
	}
}
void ThreatsObject::DoPlayer(Map& gMap) {
	if (come_back_time == 0) {
		x_val = 0;
		y_val +=THREAT_GRAVITY;
		if (y_val >= 10) {
			y_val = 10;
		}
		CheckToMap(gMap);
	}
	else if (come_back_time > 0) {
		come_back_time--;
		if (come_back_time == 0)
		{
			x_val = 0;
			y_val = 0;
			if (x_pos > 256) {
				x_pos -= 256;
			}
			else {
				x_pos = 0;
			}
			y_pos = 0;
			come_back_time = 0;
		}
	}
}
void ThreatsObject::CheckToMap(Map& map_data) {
	int x1 = 0;
	int x2 = 0;

	int y1 = 0;
	int y2 = 0;
	//check theo chiều ngang 
	/*int height_min = height_frame_ < TILE_SIZE ? height_frame_ : TILE_SIZE;*/
	int height_min = min(height_frame, TILE_SIZE);

	x1 = (x_pos + x_val) / TILE_SIZE;
	x2 = (x_pos + x_val + width_frame - 1) / TILE_SIZE;// kiểm tra đường biên 

	y1 = (y_pos) / TILE_SIZE;
	y2 = (y_pos + height_min - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
	{
		if (x_val > 0)//main object đang di chuyển sang phải
		{
			int val1 = map_data.tile[y1][x2];
			int val2 = map_data.tile[y2][x2];

				if (map_data.tile[y1][x2] != BLANK_TILE&&val1!=STAFF_FRUIT || map_data.tile[y2][x2] != BLANK_TILE&&val2!=STAFF_FRUIT)
				{
					x_pos = x2 * TILE_SIZE;
					x_pos -= width_frame + 1;
					x_val = 0;// va chạm rồi vẫn đứng im

				}
			}
		}
		else if (x_val < 0)
		{
			int val1 = map_data.tile[y1][x1];
			int val2 = map_data.tile[y2][x1];
			
			if (map_data.tile[y1][x1] != 0&&val1!=STAFF_FRUIT || map_data.tile[y2][x1] != 0&&val2!=STAFF_FRUIT)
			{
				x_pos = (x1 + 1) * TILE_SIZE;
				x_val = 0;
			}
		}
	//check theo chiều dọc
	/*int width_min = width_frame_ < TILE_SIZE ? width_frame_ : TILE_SIZE*/
	int width_min = min(width_frame, TILE_SIZE);
	x1 = (x_pos) / TILE_SIZE;
	x2 = (x_pos + width_min) / TILE_SIZE;

	y1 = (y_pos + y_val) / TILE_SIZE;
	y2 = (y_pos + y_val+ height_frame - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
	{
		if (y_val > 0)
		{
			int val1 = map_data.tile[y2][x1];
			int val2 = map_data.tile[y2][x2];
			if (val1 == STAFF_FRUIT || val2 == STAFF_FRUIT) {
				map_data.tile[y2][x1] = 0;
				map_data.tile[y2][x2] = 0;
			}
			else {
				if (map_data.tile[y2][x1] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE)
				{
					y_pos = y2 * TILE_SIZE;
					y_pos -= (height_frame + 1);
					y_val = 0;
					on_ground = true;//đang ở trên mặt đất
				}
			}
		}
		else if (y_val < 0)
		{
			int val1 = map_data.tile[y1][x1];
			int val2 = map_data.tile[y1][x2];
			if (val1 == STAFF_FRUIT || val2 == STAFF_FRUIT) {
				map_data.tile[y1][x1] = 0;
				map_data.tile[y1][x2] = 0;
			}
			else {
				if (map_data.tile[y1][x1] != 0 || map_data.tile[y1][x2] != 0)
				{
					y_pos = (y1 + 1) * TILE_SIZE;
					y_val = 0;
				}
			}

		}
	}
	x_pos += x_val;
	y_pos += y_val;// chạy bth
	if (x_pos < 0) {
		x_pos = 0;
	}
	if (x_pos +  width_frame > map_data.max_x_) {
		x_pos = map_data.max_x_ - width_frame - 1;
	}
	if (y_pos > map_data.max_y_) {
		come_back_time = 60;
	}

}