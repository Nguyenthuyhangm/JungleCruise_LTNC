#include"MainObject.h"
#include"CommonFunction.h"
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
	bool on_ground = false;
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
	if (status_ == WALK_RIGTH)//ktra trạng thái
	{
		LoadImg("Base//Run.png", des);
	}
	if (input_type_.jump_ ==1)//ktra trạng thái
	{
		LoadImg("Base//Jump.png", des);
	}
	if (input_type_.right_ == 1) {
		frame_++;//di chuyển
	}
	else {
		frame_ = 0;// đứng im 
	}
	if (frame_ >= 8) {
		frame_ = 0;//set dd
	}
	rect_.x = x_pos_;
	rect_.y = y_pos_;

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
		case SDLK_UP:
		{
			input_type_.jump_ = 1;
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
		case SDLK_UP:
		{
			input_type_.jump_ = 0;
		}
		break;
		default:
			break;
		}
	} 
	/*if (events.type == SDL_MOUSEBUTTONDOWN)
	{
		if (events.button.button == SDL_BUTTON_RIGHT)
		{
			input_type_.jump_ = 1;
		}
	}*/
}

void MainObject::DoPlayer(Map& map_data)
{
	x_val_ = 0;
	y_val_ += 0.8;//rơi từ từ xuống 

	//giới hạn tốc độ rơi 
	if (y_val_ >= 10) {
		y_val_ = 10;
	}
	if (input_type_.right_ == 1) {
		x_val_ += PLAYER_SPEED;
	}
	if (input_type_.jump_ == 1) {
		if (on_ground == true) {

			y_val_ = JUMP_SPEED;
		}

			input_type_.jump_ = 0;
	}
	Checkmap(map_data);
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
			//kiểm tra xem map data có phải ô trống không
			if (map_data.tile[y1][x2] != 0 || map_data.tile[y2][x2] != 0)
			{
				x_pos_ = x2 * TILE_SIZE;
				x_pos_ -= width_frame_ + 1;
				x_val_ = 0;// va chạm rồi vẫn đứng im 

			}
		}
		else if (x_val_ < 0)
		{
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
			if (map_data.tile[y2][x1] != 0 || map_data.tile[y2][x2] != 0)
			{
				y_pos_ = y2 * TILE_SIZE;
				y_pos_ -= (height_frame_ + 1);
				y_val_ = 0;
				on_ground = true;//đang ở trên mặt đất
			}
		}
		else if (y_val_ < 0)
		{
			if (map_data.tile[y1][x1] != 0 || map_data.tile[y1][x2] != 0)
			{
				y_pos_ = (y1 + 1) * TILE_SIZE;
				y_val_ = 0;
			}
		}
	}
	x_pos_ += x_val_;
	y_pos_ += y_val_;// chạy bth

	if (x_pos_ + width_frame_ > map_data.max_x_) {
		x_pos_ = map_data.max_x_ - width_frame_-1;
	}

}
