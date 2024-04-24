#ifndef TEXT_H_
#define TEXT_H_
#include"CommonFunction.h"
class TextObject{
public:
    TextObject();
    ~TextObject();

    enum TextColor{
        RED_TEXT=0,
        WHITE_TEXT=1,
        BLACK_TEXT=2,

    };
private:
    std::string str_val_;
    SDL_Color text_color;
    SDL_Texture* texture_;
    int width_;
    int height_;

};

#endif TEXT_H_


