#include"MainObject.h"
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
	//	frame_clip_[0].y = 0;
	//	frame_clip_[0].w = width_frame_;
	//	frame_clip_[0].h = height_frame_;

	//	frame_clip_[1].x = width_frame_;
	//	frame_clip_[1].y = 0;
	//	frame_clip_[1].w = width_frame_;
	//	frame_clip_[1].h = height_frame_;

	//	frame_clip_[2].x = width_frame_ * 2;
	//	frame_clip_[2].y = 0;
	//	frame_clip_[2].w = width_frame_;
	//	frame_clip_[2].h = height_frame_;

	//	frame_clip_[3].x = width_frame_ * 3;
	//	frame_clip_[3].y = 0;
	//	frame_clip_[3].w = width_frame_;
	//	frame_clip_[3].h = height_frame_;

	//	frame_clip_[4].x = width_frame_ * 4;
	//	frame_clip_[4].y = 0;
	//	frame_clip_[4].w = width_frame_;
	//	frame_clip_[4].h = height_frame_;

	//	frame_clip_[5].x = width_frame_ * 5;
	//	frame_clip_[5].y = 0;
	//	frame_clip_[5].w = width_frame_;
	//	frame_clip_[5].h = height_frame_;

	//	frame_clip_[6].x = width_frame_ * 6;
	//	frame_clip_[6].y = 0;
	//	frame_clip_[6].w = width_frame_;
	//	frame_clip_[6].h = height_frame_;

	//	frame_clip_[7].x = width_frame_ * 7;
	//	frame_clip_[7].y = 0;
	//	frame_clip_[7].w = width_frame_;
	//	frame_clip_[7].h = height_frame_;
		for(int i=0;i<8;i++){
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
		default:
			break;
		}
	} 
}