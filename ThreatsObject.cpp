#include "ThreatsObject.h"
#include<windows.h>
#include<iostream>
ThreatsObject::ThreatsObject() {
    width_frame_ = 0;
    height_frame_ = 0;
    x_val_ = 0.0;
    y_val_ = 2.0;
    x_pos_ = 0.0;
    y_pos_ = 0.0;
    on_ground_ = false;
    come_back_time_ = 0;
    frame_ = 0;

    animation_a_ = 0;
    animation_b_ = 0;
    //Khởi đầu là quay trái
    input_type_.left_ = 1;
    type_move_ = STATIC_THREAT;

}

ThreatsObject::~ThreatsObject() {

}

SDL_Rect ThreatsObject :: GetRectFrame(){
    SDL_Rect rect;
    rect.x = rect_.x;
    rect.y = rect_.y;
    rect.w = rect_.x/8;
    rect.h = rect_.h;
    return rect;
}


bool ThreatsObject::LoadImg(std::string path, SDL_Renderer* screen) {
    bool ret = BaseObject::LoadImg(path, screen);
    if (ret) {
        width_frame_ = rect_.w / THREAT_FRAME_NUM;
        height_frame_ = rect_.h;
    }
    return ret;
}

void ThreatsObject::set_clips() {
    if (width_frame_ > 0 && height_frame_ > 0) {
        for (int i = 0; i < 8; i++) {	//có 8 frame nên cho vòng lặp chạy đến 8
            frame_clip_[i].x = width_frame_ * i;
            frame_clip_[i].y = 0;
            frame_clip_[i].w = width_frame_;
            frame_clip_[i].h = height_frame_;
        }
    }
}
void ThreatsObject::Show(SDL_Renderer* des) {
        rect_.x = x_pos_ - map_x_;
        rect_.y = y_pos_ - map_y_;
        frame_++;
        if (frame_ >= 8) {
            frame_ = 0;
        }
        SDL_Rect* currentClip = &frame_clip_[frame_%8];
        SDL_Rect rendQuad = { rect_.x, rect_.y, width_frame_, height_frame_ };
        SDL_RenderCopy(des, p_object_, currentClip, &rendQuad);
}

void ThreatsObject::DoPlayer(Map& gMap) {
    if(come_back_time_  == 0)
    {
        y_val_ += THREAT_GRAVITY_SPEED;
        if(y_val_ >= THREAT_MAX_FALL_SPEED)
        {
            y_val_ = THREAT_MAX_FALL_SPEED;
        }
        //x_val_ cứ tăng x_pos_ được cộng x_val_ ở cuối hàm CheckToMap cho đến khi ở hàm ImpMoveType thì chặn 2 đầu a b, đến a thì quay phải, đến b thì trái
        if(input_type_.left_ == 1)
        {
           x_val_ = 3;
        }
        if(input_type_.right_ == 1)
        {
           x_val_ = -3;
           // x_val_ += THREAT_SPEED;
        }
        CheckToMap(gMap);
    }
    else if(come_back_time_ > 0)
    {
        come_back_time_ --;
        if( come_back_time_ == 0)
        {
            InitThreats();
        }
    }
}
void ThreatsObject::InitThreats() {
    x_val_ = -2;
    y_val_ = 2;
    if (x_pos_ > 256) {
        x_pos_ -= 256;
        //Trừ cả khoảng luôn
        animation_a_ -= 256;
        animation_b_ -= 256;
    }
    else {
        x_pos_ = 0;
    }
    y_pos_ = 0;
    come_back_time_ = 0;
    input_type_.left_ = ~input_type_.left_;
}
void ThreatsObject::CheckToMap(Map& map_data) {
    //Định vị trí đầu cuối
    int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;

    //KIỂM TRA THEO CHIỀU NGANG
    int height_min = height_frame_ < TILE_SIZE ? height_frame_ : TILE_SIZE;
    //Xác định Ô BẮT ĐẦU mà nhân vật đang đứng
    x1 = (x_pos_ + x_val_) / TILE_SIZE;
    //Xác định Ô KẾT THÚC mà nhân vật đứng
    x2 = (x_pos_ + x_val_ + width_frame_ - 1) / TILE_SIZE;


    //Xác định ô đầu cuối mà nhân vật đang đứng
    y1 = (y_pos_) / TILE_SIZE;
    y2 = (y_pos_ + height_min - 1) / TILE_SIZE;

    /*
        x1,y1********x2,y1
        *               *
        *               *
        *               *
        x1,y2********x2,y2
    */
    //Kiểm tra xem có đang nằm trong bản đồ không
    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {
        if (x_val_ > 0) //Di chuyển sang phải
        {
            int val1 = map_data.tile[y1][x2];
            int val2 = map_data.tile[y2][x2];
            //Kiểm tra xem ô bên phải có phải là ô trống hay không
            if (((val1 >= 1 && val1 <= 18) && val1 != STAFF_FRUIT) || ((val2 >= 1 && val2 <= 18) && val2 != STAFF_FRUIT)) {
                x_pos_ = x2 * TILE_SIZE; // Ra vị trí biên của frame nhân vật
                //Nếu mà chạm tường thì x_pos_ chỉ dừng ở đó
                //x_val_ = 0
                x_pos_ -= width_frame_ + 1;
                //x_val_ = 0;
                input_type_.left_ = 1;
                input_type_.right_ = 0;
            }
        }
        //di chuyển sang trái
        else if (x_val_ < 0) {
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y2][x1];
            //Nếu ăn phải quả thì ô quả biến mất
            if (((val1 >= 1 && val1 <= 18) && val1 != STAFF_FRUIT||LACAY) || ((val2 >= 1 && val2 <= 18) && val2 != STAFF_FRUIT||LACAY)) {
                //Lùi chạm đá thì giữ vị trí, x_val_ = 0 luôn
                x_pos_ = (x1 + 1) * TILE_SIZE;
               // x_val_ = 0;
                input_type_.right_ = 1;
                input_type_.left_ = 0;
            }
        }
    }

    //KIỂM TRA THEO CHIỀU DỌC
    int width_min = width_frame_ < TILE_SIZE ? width_frame_ : TILE_SIZE;
    x1 = (x_pos_) / TILE_SIZE;
    x2 = (x_pos_ + width_min) / TILE_SIZE;

    y1 = (y_pos_ + y_val_) / TILE_SIZE;
    y2 = (y_pos_ + y_val_ + height_frame_ - 1) / TILE_SIZE;

    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {
        //Rơi tự do
        if (y_val_ > 0) {
            int val1 = map_data.tile[y2][x1];
            int val2 = map_data.tile[y2][x2];
            if (((val1 >= 1 && val1 <= 18) && val1 != STAFF_FRUIT||LACAY) || ((val2 >= 1 && val2 <= 18) && val2 != STAFF_FRUIT||LACAY)) {
                y_pos_ = y2 * TILE_SIZE;
                //y_pos_ -= (height_frame_ + 1);
                y_val_ = 0;
                on_ground_ = true;
            }
        }
        else if (y_val_ < 0) {
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y1][x2];
            if (((val1 >= 1 && val1 <= 18) && val1 != STAFF_FRUIT||LACAY) || ((val2 >= 1 && val2 <= 18) && val2 != STAFF_FRUIT||LACAY)) {
                y_pos_ = (y1 + 1) * TILE_SIZE;
                y_val_ = 0;
            }
        }
    }
    //XPOS CỨ TĂNG DẦN
    x_pos_ += x_val_;
    y_pos_ += y_val_;
    //Lùi quá mép bản đồ
    if (x_pos_ < 0) {
        //Cho nó dừng lại luôn
        x_pos_ = 0;
    }
    else if (x_pos_ + width_frame_ > map_data.max_x_) {
        x_pos_ = map_data.max_x_ - width_frame_ - 1;
    }

    if (y_pos_ > map_data.max_y_) {
        come_back_time_ = 60;
    }
}

void ThreatsObject::ImpMoveType(SDL_Renderer* screen) {
    //Đứng im 1 chỗ
    if (type_move_ == STATIC_THREAT) {
            ;
    }

    //Nếu không thì di chuyển
    if (type_move_==MOVE_IN_SPACE_THREAT){

        //Đứng trên mặt đất mới di chuyển
//        if(on_ground_==true){
            if (x_pos_ < animation_b_) {

                input_type_.left_ = 1;
                input_type_.right_ = 0;
                LoadImg("Base//Thanlan.png", screen);

            }
            else if (x_pos_ > animation_a_) {
                input_type_.right_ = 1;
                input_type_.left_ = 0;
                LoadImg("Base//Thanlan.png", screen);

            }
        }
    }
void ThreatsObject::InitBullet(BulletObject* p_bullet,SDL_Renderer* Screen){
    if(p_bullet!=NULL){
        p_bullet->set_bullet_type(BulletObject::COMMON_BULLET);
        p_bullet->LoadImgBullet(Screen);
        p_bullet->set_is_move(true);
        p_bullet->set_bullet_dir(BulletObject::DIR_LEFT);
        p_bullet->SetRect(rect_.x+5,y_pos_+10);
        p_bullet-> Set_x_val(15);
        bullet_list_.push_back(p_bullet);
    }
}
void ThreatsObject::InitBullet1(BulletObject* p_bullet,SDL_Renderer* Screen){
    if(p_bullet!=NULL){
        p_bullet->set_bullet_type(BulletObject::TRUNK_BULLET);
        p_bullet->LoadImgBullet(Screen);
        p_bullet->set_is_move(true);
        p_bullet->set_bullet_dir(BulletObject::DIR_LEFT);
        p_bullet->SetRect(rect_.x+5,y_pos_+10);
        p_bullet-> Set_x_val(15);
        bullet_list_.push_back(p_bullet);
    }
}
void ThreatsObject::InitBullet2(BulletObject* p_bullet,SDL_Renderer* Screen){
    if(p_bullet!=NULL){
        p_bullet->set_bullet_type(BulletObject::BEE_BULLET);
        p_bullet->LoadImgBullet(Screen);
        p_bullet->set_is_move(true);
        p_bullet->set_bullet_dir(BulletObject::DIR_DOWN);
        p_bullet->SetRect(rect_.x+5,y_pos_+10);
        p_bullet-> Set_y_val(15);
        bullet_list_.push_back(p_bullet);
    }
}
void ThreatsObject::MakeBullet(SDL_Renderer* Screen,const int& x_limit,const int&y_limit){
    for(int i=0;i<bullet_list_.size();i++){
        BulletObject* p_bullet=bullet_list_.at(i);
        if(p_bullet!=NULL){
            if(p_bullet->get_is_move()){
                int bullet_distance=rect_.x+width_frame_-p_bullet->GetRect().x;//trừ có thể ra 10 -> ktra thêm trường hợp
                if(bullet_distance<300&&bullet_distance>0){
                    p_bullet->HandleMove(x_limit,y_limit);
                    p_bullet->Render(Screen);
                }
                else{
                    p_bullet->set_is_move(false);
                }
            }
            else{
                p_bullet->set_is_move(true);
                p_bullet-> SetRect(rect_.x+5,y_pos_+10);
            }
        }
    }
}
//x_pos là chỉ số ứng với toàn bộ bản đồ
//rect là vị trí của threat trong màn hình
void ThreatsObject::RemoveBullet(const int& idx){
    int size = bullet_list_.size();
    if(size>0&&idx<size){
        BulletObject* p_bullet=bullet_list_.at(idx);
        bullet_list_.erase(bullet_list_.begin()+idx);
        if(p_bullet){
            delete p_bullet;
            p_bullet = NULL;
        }
    }
}

