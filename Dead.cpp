
#include"Dead.h"

Dead::Dead(){
    number_=0;
}
Dead::~Dead(){

}

void Dead::AddPos(const int& xp){
    pos_list_.push_back(xp);
}
void Dead::Init(SDL_Renderer* Screen){
    LoadImg("Base//mang.png",Screen);
    number_=3;
    if(pos_list_.size()>0){
        pos_list_.clear();
    }
    AddPos(20);
    AddPos(60);
    AddPos(100);
}
void Dead::Show(SDL_Renderer* Screen){
    for(int i=0;i<(int)pos_list_.size();i++){ //nhiệm vụ show ảnh
        rect_.x=pos_list_.at(i);
        rect_.y=0;
        Render(Screen);
    }
}

void Dead::DeCrease(){
    number_--;
    pos_list_.pop_back();
}
void Dead::InitCrease(){
    number_++;
    int last_pos=pos_list_.back();
    last_pos+=40;
    pos_list_.push_back(last_pos);
}

PlayerMoney:: PlayerMoney(){
    x_pos_ = 0;
    y_pos_ = 0;
}

PlayerMoney:: ~PlayerMoney(){

}

void PlayerMoney:: Init(SDL_Renderer* screen){
    LoadImg("Base//apple.png", screen);
}

void PlayerMoney :: Show (SDL_Renderer* screen){
    rect_.x = x_pos_;
    rect_.y = y_pos_;
    Render(screen);
}
