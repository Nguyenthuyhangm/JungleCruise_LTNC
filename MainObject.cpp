#include"MainObject.h"
#include"CommonFunction.h"
#include <time.h>
#include<iostream>
using namespace std;


MainObject::MainObject()
{
	frame_ = 0;
	x_pos_ = 0;
	y_pos_ = 0;
	x_val_ = 0;
	y_val_ = 0;
	width_frame_ = 0;
	height_frame_ = 0;
	status_ = -1;
	input_type_.jump_ = 0;
	input_type_.down_ = 0;
	input_type_.up_ = 0;
	input_type_.left_ = 0;

	bool on_ground = false;
	map_x_ = 0;
	map_y_ = 0;
	fruit_count = 0;
	come_back_time = 0;
}
MainObject::~MainObject()
{

}
bool MainObject::LoadImg(string path, SDL_Renderer* Screen)
{
	bool ret = BaseObject::LoadImg(path, Screen);
	if (ret == true)
	{
		width_frame_ = rect_.w / 8;
		height_frame_ = rect_.h;
	}
	return ret;
}
void MainObject::Animation()
{
	if (width_frame_ > 0 && height_frame_ > 0)//tọa độ của frame ->set clip
	{
		for(int i=0;i<8;i++){	//có 8 frame nên cho vòng lặp chạy đến 8
			frame_clip_[i].x = width_frame_ * i;
			frame_clip_[i].y = 0;
			frame_clip_[i].w = width_frame_;
			frame_clip_[i].h = height_frame_;
		}
	}
}

void MainObject::Show(SDL_Renderer* des)
{
	UpdateImagePlayer(des);
	if (input_type_.right_ == 1||input_type_.left_==1||input_type_.jump_) {
		frame_++;//di chuyển
	}
	else {
		frame_ = 0;// đứng im
	}
	if (frame_ >= 8) {
		frame_ = 0;//set dd
	}
	rect_.x = x_pos_- map_x_;// tính từ điểm mốc ban đầu đến điểm map hiện tại
	rect_.y = y_pos_- map_y_;

	SDL_Rect* current_clip = &frame_clip_[frame_];//lấy frame hiện tại

	SDL_Rect renderQuad = { rect_.x,rect_.y,width_frame_,height_frame_ };//kích thước chuẩn nhất

	SDL_RenderCopy(des, p_object_, current_clip, &renderQuad);//đẩy lên màn hình hiện tại
}

void MainObject::HandleInputAction(SDL_Event events, SDL_Renderer* Screen)
{
	if (events.type == SDL_KEYDOWN)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_RIGHT:
		{
			status_ = WALK_RIGTH;
			input_type_.right_ = 1;
		}
		break;
		case SDLK_LEFT:
		{
			status_ = WALK_LEFT;
			input_type_.left_ = 1;
		}
		break;
		case SDLK_UP:
		{
			input_type_.jump_ = 1;
			UpdateImagePlayer(Screen);

		}
		break;
		default:
			break;
		}
	}
	else if (events.type == SDL_KEYUP)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_RIGHT:
		{
			input_type_.right_ = 0;
		}
		break;
		case SDLK_LEFT:
		{
			input_type_.left_ = 0;
		}
		break;
		case SDLK_UP:
		{
			input_type_.jump_ = 0;
		}
		break;
		default:
			break;
		}
	}
	if (events.type == SDL_MOUSEBUTTONDOWN)
	{
		 if (events.button.button ==SDL_BUTTON_RIGHT)
		{
			//tạo viên đạn mới
			BulletObject* p_bullet = new BulletObject();
			p_bullet->set_bullet_type(BulletObject::SOFIA_BULLET);
			p_bullet->LoadImgBullet(Screen);
            if(status_==WALK_LEFT){
                p_bullet->set_bullet_dir(BulletObject::DIR_LEFT);
                p_bullet-> SetRect(this->rect_.x,rect_.y+height_frame_*0.3);

            }
            else{
                p_bullet->set_bullet_dir(BulletObject::DIR_RIGHT);
                p_bullet-> SetRect(this->rect_.x+width_frame_-20,rect_.y+height_frame_*0.3);
            }

			//set vị trí phù hợp
			p_bullet->SetRect(this->rect_.x + width_frame_ - 20, rect_.y + height_frame_ * 0.3);
			p_bullet->Set_x_val(20);// tốc độ di chuyển của viên đạn
			p_bullet->Set_y_val(20);
			p_bullet->set_is_move(true);

			p_bullet_list.push_back(p_bullet);

		}
		else if (events.button.button ==SDL_BUTTON_LEFT)
		{
			//tạo viên đạn mới
			BulletObject* p_bullet = new BulletObject();
			p_bullet->set_bullet_type(BulletObject::LASER_BULLET);
			p_bullet->LoadImgBullet(Screen);
            if(status_==WALK_LEFT){
                p_bullet->set_bullet_dir(BulletObject::DIR_UP_LEFT);
                p_bullet-> SetRect(this->rect_.x,rect_.y+height_frame_*0.3);

            }
            else{
                p_bullet->set_bullet_dir(BulletObject::DIR_UP_RIGHT);
                p_bullet-> SetRect(this->rect_.x+width_frame_-20,rect_.y+height_frame_*0.3);
            }

			//set vị trí phù hợp
			p_bullet->SetRect(this->rect_.x + width_frame_ - 20, rect_.y + height_frame_ * 0.3);
			p_bullet->Set_x_val(20);// tốc độ di chuyển của viên đạn
			p_bullet->Set_y_val(20);
			p_bullet->set_is_move(true);

			p_bullet_list.push_back(p_bullet);

		}
    }
}
void MainObject::HandleBullet(SDL_Renderer* des) {// gọi liên tục dderr bắn
	for (int i = 0; i < p_bullet_list.size(); i++) {
		BulletObject* p_bullet = p_bullet_list.at(i);
		if (p_bullet != NULL) {
			if (p_bullet->get_is_move() == true) {
				p_bullet->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
				p_bullet->Render(des);//show lên màn hình
			}
			else {
				p_bullet_list.erase(p_bullet_list.begin() + i);
				if (p_bullet != NULL) {
					delete p_bullet;
					p_bullet = NULL;
				}
			}
		}
	}
}

void MainObject::DoPlayer(Map& map_data)
{
	if (come_back_time == 0) {
		x_val_ = 0;
		y_val_ += GRAVITY;//rơi từ từ xuống

		//giới hạn tốc độ rơi
		if (y_val_ >= 12) {
			y_val_ = 12;
		}
		if (input_type_.right_ == 1) {
			x_val_ += PLAYER_SPEED;
		}
		if (input_type_.left_ == 1) {
			x_val_ -= PLAYER_SPEED;
		}
		if (input_type_.jump_ == 1) {
			if (on_ground == true) {
				on_ground = false;
				y_val_ = -JUMP_SPEED;
				input_type_.jump_ = 0;
			}
		}
		Checkmap(map_data);
		CenterEntityOnMap(map_data);// tính toán ra thông số của bản đồ
	}
	if (come_back_time > 0) {
		come_back_time--;
		if (come_back_time == 0) {
			if (x_pos_ > 256) {
				x_pos_ -= 256;
				map_x_ = -256;
			}
			else {
				x_pos_ = 0;
			}
			y_pos_ = 0;
			x_val_ = 0;
			y_val_ = 0;
		}
	}
}

void MainObject::CenterEntityOnMap(Map& map_data)
{
	map_data.start_x_ = x_pos_ - (SCREEN_WIDTH / 2);//lượng mà nhân vật di chuyển và bản đồ đc cuốn theo
	if (map_data.start_x_ < 0){// khi lùi dần thì k cho phép bản đồ lùi thêm nữa
		map_data.start_x_ = 0;
	}
	else if (map_data.start_x_ + SCREEN_WIDTH >= map_data.max_x_)//bằng đúng chiều dài tối đa của bản đồ -> k cho bản đồ di chuyển thêm
	{
		map_data.start_x_ = map_data.max_x_ - SCREEN_WIDTH;
	}

	map_data.start_y_ = y_pos_ - (SCREEN_HEIGHT/ 2);
	if (map_data.start_y_ < 0)
	{
		map_data.start_y_ = 0;
	}
	else if (map_data.start_y_ + SCREEN_HEIGHT >= map_data.max_y_)
	{
		map_data.start_y_ = map_data.max_y_ - SCREEN_HEIGHT;
	}
}

// kiểm tra xem map và nhân vật có va chạm hay không ?
void MainObject::Checkmap(Map& map_data)
{
	int x1 = 0;
	int x2 = 0;

	int y1 = 0;
	int y2 = 0;
	//check theo chiều ngang
	/*int height_min = height_frame_ < TILE_SIZE ? height_frame_ : TILE_SIZE;*/
	int height_min = min(height_frame_, TILE_SIZE);

	x1 = (x_pos_ + x_val_) / TILE_SIZE;
	x2 = (x_pos_ + x_val_ + width_frame_-1) / TILE_SIZE;// kiểm tra đường biên

	y1 = (y_pos_) / TILE_SIZE;
	y2 = (y_pos_ + height_min - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
	{
		if (x_val_ > 0)//main object đang di chuyển sang phải
		{
			int val1 = map_data.tile[y1][x2];
			int val2 = map_data.tile[y2][x2];
			if (val1 == STAFF_FRUIT || val2 == STAFF_FRUIT) {
				map_data.tile[y1][x2] = 0;// cho chạm vào xong biến mất
				map_data.tile[y2][x2] = 0;
				IncreaseFruit();
			}
			if (val1 == LACAY || val2 == LACAY) {
				map_data.tile[y1][x2] = 0;// cho chạm vào xong biến mất
				map_data.tile[y2][x2] = 0;
			}
			if (val1 == MELON || val2 == MELON) {
				map_data.tile[y1][x2] = 0;// cho chạm vào xong biến mất
				map_data.tile[y2][x2] = 0;
			}
			if (val1 == LACAY || val2 == KIWI) {
				map_data.tile[y1][x2] = 0;// cho chạm vào xong biến mất
				map_data.tile[y2][x2] = 0;
			}



			//kiểm tra xem map data có phải ô trống không
			else{
				if (map_data.tile[y1][x2] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE)
				{
					x_pos_ = x2 * TILE_SIZE;
					x_pos_ -= width_frame_ + 1;
					x_val_ = 0;// va chạm rồi vẫn đứng im

				}
			}
		}
		else if (x_val_ < 0)
		{
			int val1 = map_data.tile[y1][x1];
			int val2 = map_data.tile[y2][x1];
			if (val1 == STAFF_FRUIT || val2 == STAFF_FRUIT) {
				map_data.tile[y1][x1] = 0;// cho chạm vào xong biến mất
				map_data.tile[y2][x1] = 0;
				IncreaseFruit();
			}
			if (val1 == LACAY || val2 == LACAY) {
                map_data.tile[y1][x1] = 0;// cho chạm vào xong biến mất
				map_data.tile[y2][x1] = 0;
			}
			if (val1 == LACAY || val2 == KIWI) {
                map_data.tile[y1][x1] = 0;// cho chạm vào xong biến mất
				map_data.tile[y2][x1] = 0;
			}
			if (val1 == LACAY || val2 == MELON) {
                map_data.tile[y1][x1] = 0;// cho chạm vào xong biến mất
				map_data.tile[y2][x1] = 0;
			}
			if (map_data.tile[y1][x1] != 0 || map_data.tile[y2][x1] != 0)
			{
				x_pos_ = (x1 + 1) * TILE_SIZE;
				x_val_ = 0;
			}
		}
	}
	//check theo chiều dọc
	/*int width_min = width_frame_ < TILE_SIZE ? width_frame_ : TILE_SIZE*/
	int width_min = min(width_frame_, TILE_SIZE);
	x1 = (x_pos_) / TILE_SIZE;
	x2 = (x_pos_ + width_min) / TILE_SIZE;

	y1 = (y_pos_ + y_val_) / TILE_SIZE;
	y2 = (y_pos_ + y_val_ + height_frame_ - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
	{
		if (y_val_ > 0)
		{
			int val1 = map_data.tile[y2][x1];
			int val2 = map_data.tile[y2][x2];
			if (val1 == STAFF_FRUIT || val2 == STAFF_FRUIT) {
				map_data.tile[y2][x1] = 0;
				map_data.tile[y2][x2] = 0;
				IncreaseFruit();
			}
			if (val1 == LACAY || val2 == LACAY) {
				map_data.tile[y2][x1] = 0;
				map_data.tile[y2][x2] = 0;
			}
			else {
				if (map_data.tile[y2][x1] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE)
				{
					y_pos_ = y2 * TILE_SIZE;
					y_pos_ -= (height_frame_ + 1);
					y_val_ = 0;
					on_ground = true;//đang ở trên mặt đất
				}
			}
		}
		else if (y_val_ < 0)
		{
			int val1 = map_data.tile[y1][x1];
			int val2 = map_data.tile[y1][x2];
			if (val1 == STAFF_FRUIT || val2 == STAFF_FRUIT) {
				map_data.tile[y1][x1] = 0;
				map_data.tile[y1][x2] = 0;
				IncreaseFruit();
			}
			if (val1 == LACAY || val2 == LACAY) {
				map_data.tile[y1][x1] = 0;
				map_data.tile[y1][x2] = 0;
			}
			if (val1 == KIWI || val2 == KIWI) {
				map_data.tile[y1][x1] = 0;
				map_data.tile[y1][x2] = 0;
			}
			if (val1 == KIWI || val2 == KIWI) {
				map_data.tile[y1][x1] = 0;
				map_data.tile[y1][x2] = 0;
			}
			else{
				if (map_data.tile[y1][x1] != 0 || map_data.tile[y1][x2] != 0)
				{
					y_pos_ = (y1 + 1) * TILE_SIZE;
					y_val_ = 0;
				}
			}

		}
	}
	x_pos_ += x_val_;
	y_pos_ += y_val_;// chạy bth

	if (x_pos_ < 0) {
		x_pos_ = 0;
	}
	if (x_pos_ + width_frame_ > map_data.max_x_) {
		x_pos_ = map_data.max_x_ - width_frame_-1;
	}
	if (y_pos_ > map_data.max_y_) {
		come_back_time = 60;
	}
}
void MainObject::RemoveBullet(const int& idx){
    int size = p_bullet_list.size();
    if(size>0&&idx<size){
        BulletObject* p_bullet=p_bullet_list.at(idx);
        p_bullet_list.erase(p_bullet_list.begin()+idx);
        if(p_bullet){
            delete p_bullet;
            p_bullet = NULL;
        }
    }
}
void MainObject::IncreaseFruit() {
	fruit_count++;
}

void MainObject::UpdateImagePlayer(SDL_Renderer* des) {
	if (on_ground == true) {
		if(status_==WALK_RIGTH)
		LoadImg("Base//Run.png",des);
		if (status_ == WALK_LEFT) {
			LoadImg("Base//Run1.png", des);
		}
	}

}
