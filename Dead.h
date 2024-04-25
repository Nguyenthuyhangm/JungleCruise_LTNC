#ifndef DEAD_H_
#define DEAD_H_
#include"CommonFunction.h"
#include"BaseObject.h"
class Dead: public BaseObject{
public:
    Dead();
    ~Dead();

    void SetNum(const int& num){number_=num; }
    void AddPos(const int& xPos);
    void Show(SDL_Renderer* Screen);
    void Init(SDL_Renderer* Screen);

    void InitCrease();
    void DeCrease();
private:
    int number_;
    std::vector<int> pos_list_;

};
class PlayerMoney : public BaseObject
{
public:
    PlayerMoney();
    ~PlayerMoney();
    void Init(SDL_Renderer* screen);
    void Show(SDL_Renderer* screen);
    void SetPos(const int& x, const int& y) {x_pos_ = x; y_pos_ = y;}
private:
    int x_pos_;
    int y_pos_;
};
#endif // DEAD_H_
