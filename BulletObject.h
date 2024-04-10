#ifndef BULLET_OBJECT_H_
#define BULLET_OBJECT_H_

#include "BaseObject.h"
#include "CommonFunction.h"

class BulletObject : public BaseObject {

public:
	BulletObject();
	~BulletObject();
	
	void Set_x_val(const int& xVal) {
		x_val_= xVal;
	}
	void Set_y_val(const int& yVal) {
		y_val_ = yVal;
	}
	int get_x_val() const { return x_val_; }
	int get_y_val() const { return y_val_; }

	void set_is_move(const bool& isMove) {
		is_move = isMove;
	}
	bool get_is_move()const { return is_move; }
	void HandleMove(const int& x_border, const int& y_border);// giới hạn hiển thị 

private:
	int x_val_;
	int y_val_;
	bool is_move;

};
#endif