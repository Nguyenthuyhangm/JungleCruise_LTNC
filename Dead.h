#ifndef DEAD_H_
#define DEAD_H_
#include"CommonFunction.h"
#include"BaseObject.h"
class Dead: public BaseObject{
public:
    Dead();
    ~Dead();

    void SetNum(const int& num){number_=num;}
    void AddPos(const int& xPos);
    void Show(SDL_Renderer* Screen);
    void Init(SDL_Renderer* Screen);

    void InitCrease();
    void DeCrease();
private:
    int number_;
    std::vector<int> pos_list_;

};
#endif // DEAD_H_
