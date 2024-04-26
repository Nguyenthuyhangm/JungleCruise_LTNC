#include"CommonFunction.h"
#include"BaseObject.h"
#include"game_map.h"
#include"MainObject.h"
#include"ImpTimer.h"
#include"ThreatsObject.h"
#include<windows.h>
#include"Text.h"
#include"Dead.h"
#include"Button.h"

using namespace std;

BaseObject g_background3;
BaseObject g_ground;
BaseObject g_help;
TTF_Font* font_time=NULL;
TTF_Font* font_big=NULL;


int gameState;
enum gameState
{
    QUIT = 0,
    MENU = 1,
    PLAY = 2,
    HELP = 3,
    LOSE = 4,
};

// Buttons
const int NUM_BUTTONS = 3;
const int BUTTON_WIDTH = 150;
const int BUTTON_HEIGHT = 75;

// COLORS
const SDL_Color WHITE = {255, 255, 255, 255};
const SDL_Color BLACK = {0, 0, 0, 255};
const SDL_Color YELLOW = {255, 215, 0, 255};
const SDL_Color RED = {255, 0, 0, 255};
const SDL_Color GREEN = {0, 84, 139, 84};
const SDL_Color BLUE = {0, 0, 255, 255};
const SDL_Color PINK = {255, 192, 203, 255};
const SDL_Color BROWN = {132, 78, 51, 255};
const SDL_Color SAND = {216, 164, 100, 255};

bool  InitData()
{
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if (ret < 0)
        return false;

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    g_window = SDL_CreateWindow("Game Jungle Cruise", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (g_window == NULL)
    {
        success = false;
    }
    else
    {
        g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
        if (g_screen == NULL)
            success = false;
        else
        {
            SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) && imgFlags))
                success = false;
        }
        if(TTF_Init()==-1)
        {
            success=false;
        }
        font_time = TTF_OpenFont("Font//04B_30__.ttf",18);
        font_big=TTF_OpenFont("Font//04B_30__.ttf",30);
        if(font_time==NULL)
        {
            return success=false;
        }
         if(font_big==NULL)
        {
            return success=false;
        }
        if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
        {
            success = false;;
        }

        g_sound_bullet[0] = Mix_LoadWAV("Sound//Boss hit 1.wav");
    }
    return success;
}
// Đóng cửa sổ
void close()
{
    g_background3.Free();//Giải phóng bộ nhớ

    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;

    SDL_DestroyWindow(g_window);
    g_window = NULL;

    IMG_Quit();
    SDL_Quit();

}

bool LoadBackGround3()//Kiểm tra BackGround load lên có bị lỗi hay không
{
    bool ret = g_background3.LoadImg("background1.png", g_screen);
    if (ret == false)
        return false;

    return true;
}
bool LoadImg()//Kiểm tra BackGround load lên có bị lỗi hay không
{
    bool res = g_ground.LoadImg("Base//menu//menu.png", g_screen);
    if (res == false)
        return false;

    return true;
}
bool Help(){
    bool chekk=g_help.LoadImg("Base//menu//menu1.png", g_screen);
    if (chekk== false)
        return false;

    return true;
}

vector<ThreatsObject*>MakeThreadsList()
{
    vector<ThreatsObject*>list_threats;

    ThreatsObject* trunk_objs = new ThreatsObject[30];
    for (int i = 0; i < 10; i++)
    {
        ThreatsObject* p_threat = (trunk_objs + i);
        if (p_threat != NULL)
        {
            p_threat->LoadImg("Base//Trunk.png", g_screen);
            p_threat->set_clips();
            p_threat->set_x_pos(4000+ i*500);
            p_threat->set_y_pos(450);
            p_threat->set_type_move(ThreatsObject::STATIC_THREAT);
            p_threat->set_input_left(0);
            list_threats.push_back(p_threat);

            BulletObject* p_bullet=new BulletObject();
            p_threat->InitBullet1(p_bullet,g_screen);
            list_threats.push_back(p_threat);
        }
    }


    ThreatsObject* plant_objs = new ThreatsObject[40];
    for (int i = 0; i < 10; i++)
    {
        ThreatsObject* p_threat = (plant_objs + i);
        if (p_threat != NULL)
        {
            p_threat->LoadImg("Base//plant.png", g_screen);
            p_threat->set_clips();
            p_threat->set_x_pos(800+ i*500);
            p_threat->set_y_pos(375);
            p_threat->set_type_move(ThreatsObject::STATIC_THREAT);
            p_threat->set_input_left(0);
            list_threats.push_back(p_threat);
            BulletObject* p_bullet=new BulletObject();
            p_threat->InitBullet(p_bullet,g_screen);
            list_threats.push_back(p_threat);
        }
    }
    ThreatsObject* threats_objs = new ThreatsObject[40];
    for (int i = 0; i < 10; i++)
    {
        ThreatsObject* p_threat = (threats_objs + i);
        if (p_threat != NULL)
        {
            p_threat->LoadImg("Base//Bird.png", g_screen);
            p_threat->set_clips();
            p_threat->set_x_pos(500+ i*500);
            p_threat->set_y_pos(100);
            p_threat->set_type_move(ThreatsObject::STATIC_THREAT);
            p_threat->set_input_left(1);
            list_threats.push_back(p_threat);

        }
    }
    ThreatsObject* shoot_objs = new ThreatsObject[20];
    for (int i = 0; i < 10; i++)
    {
        ThreatsObject* p_threat = (shoot_objs + i);
        if (p_threat != NULL)
        {
            p_threat->LoadImg("Base//ocsen.png", g_screen);
            p_threat->set_clips();
            p_threat->set_x_pos(1200+ i*500);
            p_threat->set_y_pos(350);
            p_threat->set_type_move(ThreatsObject::STATIC_THREAT);
            p_threat->set_input_left(0);
            list_threats.push_back(p_threat);

        }
    }
    ThreatsObject* roll_objs = new ThreatsObject[40];
    for (int i = 0; i < 10; i++)
    {
        ThreatsObject* p_threat = (roll_objs + i);
        if (p_threat != NULL)
        {
            p_threat->LoadImg("Base//Bee.png", g_screen);
            p_threat->set_clips();
            p_threat->set_x_pos(3000+ i*500);
            p_threat->set_y_pos(200);
            p_threat->set_type_move(ThreatsObject::STATIC_THREAT);
            p_threat->set_input_left(0);

            list_threats.push_back(p_threat);

            BulletObject* p_bullet=new BulletObject();
            p_threat->InitBullet2(p_bullet,g_screen);
            list_threats.push_back(p_threat);

        }
    }
    return list_threats;
}
void help(){
     SDL_RenderClear(g_screen);

            // Render
    g_help.Render(g_screen, NULL);
    SDL_RenderPresent(g_screen);

}
void play()
{
    ImpTimer fps_timer;

    GameMap game_map;
    //fill ảnh đất
    //Đọc map viết bởi số 0 1 2
    char file_path[] = "map01.dat";
    game_map.LoadMap(file_path);
    //Load các hình ảnh tương ứng vào ô 1 2 3
    game_map.LoadTile(g_screen);

    MainObject p_player;
    p_player.LoadImg("Base//Run.png",g_screen);
    p_player.Animation();

    Dead player_power;
    player_power.Init(g_screen);

    PlayerMoney player_money;
    player_money.Init(g_screen);
    player_money.SetPos(SCREEN_WIDTH*0.5 - 300, -6);


    vector<ThreatsObject*>threats_list = MakeThreadsList();
    int solanchet=0;

    TextObject time_game;
    time_game.setColor(TextObject::WHITE_TEXT);

    TextObject mark_game;
    mark_game.setColor(TextObject::WHITE_TEXT);
    UINT mark_value =0;

    TextObject fruit_game;
    fruit_game.setColor(TextObject::WHITE_TEXT);

    bool is_quit = false;
    while (!is_quit)
    {
        fps_timer.Start();//// khi bắt đầu vòng while chạy bắt đầu start để tính tgian chạy
        while (SDL_PollEvent(&g_event) != 0)
        {
            if (g_event.type == SDL_QUIT)
            {
                is_quit = true;
            }

            p_player.HandleInputAction(g_event, g_screen,g_sound_bullet);
        }
        SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);
        SDL_RenderClear(g_screen);

        g_background3.Render(g_screen, NULL);

        Map map_data = game_map.getMap();

        p_player.SetMapXY(map_data.start_x_, map_data.start_y_);
        p_player.DoPlayer(map_data);
        p_player.Show(g_screen);
        p_player.HandleBullet(g_screen);
        p_player.Animation();

        game_map.Setmap(map_data);
        game_map.DrawMap(g_screen);

        player_power.Show(g_screen);
        player_money.Show(g_screen);

        for (int i = 0; i < threats_list.size(); i++)
        {
            ThreatsObject* p_threat = threats_list.at(i);
            if (p_threat != NULL)
            {
                p_threat->SetMapXY(map_data.start_x_, map_data.start_y_);
                p_threat->ImpMoveType(g_screen);
                p_threat->DoPlayer(map_data);
                p_threat->MakeBullet(g_screen,SCREEN_WIDTH,SCREEN_HEIGHT);
                p_threat->Show(g_screen);

                SDL_Rect rect_player= p_player.GetRectFrame();
                bool bCol1=false;
                std::vector<BulletObject*>tBullet_list=p_threat->get_bullet_list();
                for(int jj=0; jj<tBullet_list.size(); jj++)
                {
                    BulletObject* Pt_bullet=tBullet_list.at(jj);
                    if(Pt_bullet!=NULL)
                    {
                        bCol1=SDLCommonFunction::CheckCollision(Pt_bullet->GetRect(),rect_player);
                        if(bCol1==true)
                        {
                            Mix_PlayChannel(-1, Mix_LoadWAV("Sound//Suck 1V2.wav"), 0);
                            p_threat->RemoveBullet(jj);
                            break;
                        }
                    }
                }
                SDL_Rect rect_threat=p_threat->GetRectFrame();
                bool bCol2=SDLCommonFunction::CheckCollision(rect_player,rect_threat);
                if(bCol1==true||bCol2==true)
                {
                    solanchet++;
                    if(solanchet<=3)
                    {
                        p_player.SetRect(0,0);
                        p_player.set_comeback_time(30);
                        SDL_Delay(500);
                        player_power.DeCrease();
                        player_power.Render(g_screen);
                        continue;
                    }
                    else
                    {
                        if(MessageBox(NULL,"GAME OVER","Info", MB_OK|MB_ICONSTOP)==IDOK)
                        {
                            p_threat->Free();
                            close();
                            SDL_Quit();
                            return;
                        }
                    }
                }
            }
        }
        //lấy danh sách các viên đạn của threats
        std::vector<BulletObject*>bullet_arr=p_player.get_bullet_list();
        for(int r=0; r<bullet_arr.size(); r++)
        {
            BulletObject* p_bullet=bullet_arr.at(r);
            if(p_bullet!=NULL)
            {
                for(int t=0; t<threats_list.size(); t++)
                {
                    ThreatsObject*obj_threat=threats_list.at(t);
                    if(obj_threat!=NULL)
                    {
                        SDL_Rect tRect;
                        tRect.x=obj_threat->GetRect().x;
                        tRect.y=obj_threat->GetRect().y;
                        tRect.w=obj_threat->get_width_frame();// không lấy full ảnh của frame
                        tRect.h=obj_threat->get_height_frame();

                        SDL_Rect bRect = p_bullet->GetRect();

                        bool bCol = SDLCommonFunction::CheckCollision(bRect,tRect);
                        if(bCol==true)
                        {
                            Mix_PlayChannel(-1, Mix_LoadWAV("Sound//Die.wav"), 0);

                            mark_value++;
                            p_player.RemoveBullet(r);
                            obj_threat-> Free();
                            threats_list.erase(threats_list.begin()+t);
                        }
                    }
                }
            }
        }

        //xử lý thời gian
        std::string str_time="Time: ";
        Uint32 time_val=SDL_GetTicks()/1000;//thời gian hiện tại chia cho 1000
        Uint32 val_time=300-time_val;
        if(val_time<=0)
        {
            if(MessageBox(NULL,"GAME OVER","Info", MB_OK|MB_ICONSTOP)==IDOK)
            {
                is_quit=true;
                break;
            }
        }
        else
        {
            std::string str_val=std::to_string(val_time);
            str_time+=str_val;

            time_game.setText(str_time);
            time_game.LoadFromRenderText(font_time,g_screen);
            time_game.RenderText(g_screen,SCREEN_WIDTH-200,15);
        }
        std::string val_str_mark=std::to_string(mark_value);


        std::string strMark("Score: ");
        strMark+=val_str_mark;

        mark_game.setText(strMark);
        mark_game.LoadFromRenderText(font_time,g_screen);
        mark_game.RenderText(g_screen,SCREEN_WIDTH* 0.5 -50,15);
        int totalmark=mark_value;


        int fruit_count = p_player.GetFruitCount();
        std::string fruit_str=std::to_string(fruit_count);
        fruit_game.setText(fruit_str);
        fruit_game.LoadFromRenderText(font_time, g_screen);
        fruit_game.RenderText(g_screen,SCREEN_WIDTH*0.5 - 250,15);
        SDL_RenderPresent(g_screen);

        int real_imp_time = fps_timer.get_ticks();// tgian thực sự đã trôi qua
        int time_one_frame = 1000 / FRAME_PER_SECOND;//tgian trôi trên lý thuyết

        if (real_imp_time < time_one_frame)  // nếu tgian thực sự nhỏ hơn lý thuyết -> 0 có độ trễ
        {
            int delay_time = time_one_frame - real_imp_time;
            if(delay_time>0)// phải có độ trễ để đảm bảo cân bằng cho các frame
                SDL_Delay(delay_time);
        }
    }

    for(int i=0; i<threats_list.size(); i++)
    {
        ThreatsObject* p_threat=threats_list.at(i);
        if(p_threat)
        {
            p_threat->Free();
            p_threat=NULL;
        }
    }
    threats_list.clear();
    close();
}

void menu()
{
    const char *menuText[NUM_BUTTONS] = {"PLAY", "HELP", "QUIT"}; // Menu text
    std::vector<Button> buttons;

    // Load buttons
    for (int i = 0; i < NUM_BUTTONS; i++)
    {
        SDL_Rect rect = {SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, SCREEN_HEIGHT / 2 - BUTTON_HEIGHT / 2 + i * (BUTTON_HEIGHT + 50), BUTTON_WIDTH, BUTTON_HEIGHT};
        Button button(rect, WHITE , font_big, WHITE);
        button.loadTexture(g_screen, menuText[i]);

        buttons.push_back(button);
    }

    ImpTimer fps_timer;

    bool quit = false;
    while (!quit)
    {
        while (SDL_PollEvent(&g_event))
        {
            switch (g_event.type)
            {
            case SDL_QUIT:
                gameState = QUIT;
                break;

            case SDL_MOUSEMOTION:
                for (int i = 0; i < NUM_BUTTONS; i++)
                {
                    if (buttons[i].isMouseInside(g_event.motion.x, g_event.motion.y))
                    {
                        buttons[i].changeColor(SAND);



                    }
                    else
                    {
                        buttons[i].changeColor(YELLOW);
                    }
                }
                break;

            case SDL_MOUSEBUTTONDOWN:
                for (int i = 0; i < NUM_BUTTONS; i++)
                {
                    if (buttons[i].isMouseInside(g_event.motion.x, g_event.motion.y))
                    {
                        buttons[i].changeColor(SAND);
                        Mix_PlayChannel(-1, Mix_LoadWAV("Sound//Select 1.wav"), 0);

                    }
                }


                break;

            case SDL_MOUSEBUTTONUP:
                for (int i = 0; i < NUM_BUTTONS; i++)
                {
                    if (buttons[i].isMouseInside(g_event.motion.x, g_event.motion.y))
                    {
                        buttons[i].changeColor(SAND);

                        switch (i)
                        {
                        case 0:
                            gameState = PLAY;
                            break;
                        case 1:
                            gameState = HELP;
                            break;
                        case 2:
                            gameState = QUIT;
                            break;
                        }
                    }
                    else
                    {
                        buttons[i].changeColor(YELLOW);
                    }
                }
                break;
            }

            // Clear screen
            SDL_RenderClear(g_screen);

            // Render
            g_ground.Render(g_screen, NULL);


            for (int i = 0; i < NUM_BUTTONS; i++)
            {
                buttons[i].render(g_screen);
            }

            // Update screen
            SDL_RenderPresent(g_screen);


            int real_imp_time = fps_timer.get_ticks();// tgian thực sự đã trôi qua
            int time_one_frame = 1000 / FRAME_PER_SECOND;//tgian trôi trên lý thuyết

            if (real_imp_time < time_one_frame)  // nếu tgian thực sự nhỏ hơn lý thuyết -> 0 có độ trễ
            {
                int delay_time = time_one_frame - real_imp_time;
                if(delay_time>0)// phải có độ trễ để đảm bảo cân bằng cho các frame
                    SDL_Delay(delay_time);
            }

            // Quit
            if (gameState != MENU)
                quit = true;
        }
    }
}

int main(int argc, char* argv[])
{
    if (InitData() == false)
        return -1;
    if (LoadBackGround3() == false)
        return -1;

    if (LoadImg() == false)
        return -1;

    if (Help() == false)
        return -1;
    bool loop = true;
    gameState = MENU;
    while (loop)
    {
        switch (gameState)
        {
        case MENU:
            menu();
            break;

        case HELP:
            help();
            break;
        case PLAY:
            Mix_PlayChannel(-1, Mix_LoadWAV("Sound//Final Quest - World Map.wav"), 0);

            play();


            break;
//        case LOSE:
//            lose();
//            break;
        case QUIT:
            loop = false;
            break;
        }
    }
    return 0;
}
