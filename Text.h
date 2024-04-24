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
    bool LoadFromFile(std::string path);
    bool LoadFromRenderText(TTF_Font* font,SDL_Renderer* Screen);
    void Free();

    void SetColor(Uint8 red,Uint8 green,Uint8 blue);
    void setColor(int type);

    void RenderText(SDL_Renderer* Screen,int xp,int yp,SDL_Rect* clip=NULL,double angle=0.0, SDL_Point* center=NULL,SDL_RendererFlip flip=SDL_FLIP_NONE);
    int GetWidth()const {return width_;}
    int GetHeight()const{return height_;}

    void setText (const std::string& text){str_val_}
private:
    std::string str_val_;
    SDL_Color text_color;
    SDL_Texture* texture_;
    int width_;
    int height_;

};

#endif TEXT_H_


