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
	rect_.x += x_val_;// sang bên phải thì cộng lên dần
		if (rect_.x > x_border) {// nếu vượt quá giới hạn 
			is_move = false;// k cho phép di chuyển nữa
		}
}