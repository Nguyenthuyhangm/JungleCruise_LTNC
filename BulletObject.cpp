#include"BulletObject.h"


BulletObject::BulletObject()
{
	x_val_ = 0;
	y_val_ = 0;
	is_move = false;
}

BulletObject::~BulletObject()
{

}

void BulletObject::HandleMove(const int& x_border, const int& y_border) {
	if(bullet_dir==DIR_RIGHT){
      rect_.x += x_val_;// sang bên phải thì cộng lên dần
		if (rect_.x > x_border) {// nếu vượt quá giới hạn
			is_move = false;// k cho phép di chuyển nữa
		}
	}
	else if(bullet_dir==DIR_LEFT){
       rect_.x -= x_val_;// sang bên phải thì cộng lên dần
		if (rect_.x <0) {// nếu vượt quá giới hạn
			is_move = false;// k cho phép di chuyển nữa
		}
	}
	else if(bullet_dir==DIR_UP){
        rect_.y-=y_val_;
        if(rect_.y<0){
            is_move=false;
        }
	}
	else if(bullet_dir==DIR_UP_LEFT){
        rect_.x-=x_val_;
        if(rect_.x<0){
            is_move=false;
        }
        rect_.y-=y_val_;
        if(rect_.y<0){
            is_move=false;
        }
	}
	else if(bullet_dir==DIR_UP_RIGHT){
        rect_.x+=x_val_;
        if(rect_.x>x_border){
            is_move=false;
        }
        rect_.y-=y_val_;
        if(rect_.y<0){
            is_move=false;
        }
	}
}
