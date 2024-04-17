#include"ThreatsObject.h"

ThreatsObject::ThreatsObject() {
	width_frame_ = 0;
	height_frame_ = 0;
	x_val = 0.0;
	y_val = 0.0;
	x_pos = 0.0;
	y_pos = 0.0;
	on_ground_ = 0;
	comeback_time = 0;
	frame_ = 0;

}
ThreatsObject::~ThreatsObject() {

}

bool ThreatsObject::LoadImg(string path, SDL_Renderer* Screen) {
	bool ret = BaseObject::LoadImg(path, Screen);
	if (ret) {
		width_frame_ = rect_.w / THREAT_FRAME_NUM;
		height_frame_ = rect_.h;
	}
	return false;
}

void ThreatsObject::set_clip() {
	if (width_frame_ > 0 && height_frame_ > 0) {
		for (int i = 0; i < 8; i++) {	//có 5 frame nên cho vòng lặp chạy đến 5
			frame_clip[i].x = width_frame_ * i;
			frame_clip[i].y = 0;
			frame_clip[i].w = width_frame_;
			frame_clip[i].h = height_frame_;
		}
	}
}

void ThreatsObject::Show(SDL_Renderer* des) {
	/*if (comeback_time == 0) {*/
		rect_.x = x_pos - map_x;
		rect_.y = y_pos - map_y;
		frame_++;
		/*if (frame_ >= 8) {
			frame_ = 0;
		}*/
		SDL_Rect* currentClip = &frame_clip[frame_];
		SDL_Rect rendQuad = { rect_.x,rect_.y,width_frame_,height_frame_ };
		SDL_RenderCopy(des, p_object_, currentClip, &rendQuad);

	/*}*/
}

void ThreatsObject::DoPlayer(Map& gMap) {
	if (comeback_time == 0) {
		x_val = 0;
		y_val += GRAVITY_SPEED;
		if (y_val >= 10){
			y_val = 10;
		}
		CheckToMap(gMap);
	}
	else if (comeback_time > 0) {
		comeback_time--;
		if (comeback_time == 0) {
			x_val = 0;
			y_val = 0;
			if (x_pos > 256) {
				x_pos -= 256;
			}
			else {
				x_pos = 0;
			}
			y_pos = 0;
			comeback_time = 0;
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
	int height_min = min(height_frame_, TILE_SIZE);

	x1 = (x_pos+ x_val) / TILE_SIZE;
	x2 = (x_pos + x_val + width_frame_ - 1) / TILE_SIZE;// kiểm tra đường biên 

	y1 = (y_pos) / TILE_SIZE;
	y2 = (y_pos + height_min - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
	{
		if (x_val > 0)//main object đang di chuyển sang phải
		{
			int val1 = map_data.tile[y1][x2];
			int val2 = map_data.tile[y2][x2];
				if ((map_data.tile[y1][x2] != BLANK_TILE &&val1!=STAFF_FRUIT)||( map_data.tile[y2][x2] != BLANK_TILE&&val2!=STAFF_FRUIT))
				{
					x_pos = x2 * TILE_SIZE;
					x_pos -= width_frame_ + 1;
					x_val = 0;// va chạm rồi vẫn đứng im

				}
			}
		}
		else if (x_val < 0)
		{
			int val1 = map_data.tile[y1][x1];
			int val2 = map_data.tile[y2][x1];
			if ((map_data.tile[y1][x1] != BLANK_TILE&&val1!=STAFF_FRUIT) ||( map_data.tile[y2][x1] != BLANK_TILE&&val2!=STAFF_FRUIT))
			{
				x_pos = (x1 + 1) * TILE_SIZE;
				x_val = 0;
			}
		}
	//check theo chiều dọc
	/*int width_min = width_frame_ < TILE_SIZE ? width_frame_ : TILE_SIZE*/
	int width_min = min (width_frame_, TILE_SIZE);
	x1 = (x_pos) / TILE_SIZE;
	x2 = (x_pos + width_min) / TILE_SIZE;

	y1 = (y_pos + y_val) / TILE_SIZE;
	y2 = (y_pos + y_val + height_frame_ - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
	{
		if (y_val> 0)
		{
			int val1 = map_data.tile[y2][x1];
			int val2 = map_data.tile[y2][x2];
				if ((map_data.tile[y2][x1] != BLANK_TILE&&val1!=STAFF_FRUIT )||( map_data.tile[y2][x2] != BLANK_TILE&&val2!=STAFF_FRUIT))
				{
					y_pos = y2 * TILE_SIZE;
					y_pos -= (height_frame_ + 1);
					y_val = 0;
					on_ground_ = true;//đang ở trên mặt đất
				}
		}
		else if (y_val < 0)
		{
			int val1 = map_data.tile[y1][x1];
			int val2 = map_data.tile[y1][x2];
			if ((map_data.tile[y1][x1] != 0 && val1 != STAFF_FRUIT) || (map_data.tile[y1][x2] != 0&&val2!=STAFF_FRUIT))
			{
				y_pos = (y1 + 1) * TILE_SIZE;
				y_val = 0;
			}
		}

	}
	x_pos += x_val;
	y_pos += y_val;// chạy bth
	if (x_pos < 0) {
		x_pos = 0;
	}
	if (x_pos + width_frame_ > map_data.max_x_) {
		x_pos = map_data.max_x_ - width_frame_ - 1;
	}
	if (y_pos > map_data.max_y_) {
		comeback_time = 60;
	}
}