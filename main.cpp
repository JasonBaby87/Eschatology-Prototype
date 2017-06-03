#include <iostream>
#include <string>
#include "lib/window.h"
using namespace std;

int main(int argc,char* args[])
{
    Window::Init("Eschatology");

    SDL_Texture* bg=Window::LoadImage("img/bg.jpg");
    SDL_Rect* bgRect=Window::setRect(bg,Window::Box().w,Window::Box().h,'l','t');
    SDL_Texture* buttons=Window::LoadImage("img/buttons.png");
    SDL_Rect* buttonsRect=Window::setRect(buttons,0,0,'m','m',0,0,2,2);

    SDL_Texture* title=Window::RenderText("Eschatology","font/freeWing.ttf",{255,255,255},64);
    SDL_Rect* titleRect=Window::setRect(title);

    int useClip=1;

    SDL_Event e;
    bool quit=false;
    float angle=0;
    while(!quit)
    {
        while(SDL_PollEvent(&e))
        {

            if(e.type==SDL_QUIT) //單擊右上角的X
            {
    			quit=true;
    		}
    		if(e.type==SDL_KEYDOWN)
            {
                switch(e.key.keysym.sym)
                {
                    case SDLK_1:
                        useClip=1;
                        break;
                    case SDLK_2:
                        useClip=2;
                        break;
                    case SDLK_3:
                        useClip=3;
                        break;
                    case SDLK_4:
                        useClip=4;
                        break;
                    //For quitting, escape key
                    case SDLK_ESCAPE:
                        quit=true;
                        break;
                    default:
                        break;
                }
    		}
    		if(e.type==SDL_MOUSEBUTTONDOWN)
            {
                quit=true;
                break;
    		}
            if(e.type==SDL_MOUSEMOTION)
            {
    			angle++;
    		}
            Window::Clear();

            Window::Draw(bg,0,0,bgRect[0]);
            Window::Draw(buttons,Window::Box().w/2,Window::Box().h/2,buttonsRect[0],&buttonsRect[useClip],angle);
            Window::Draw(title,Window::Box().w/2,Window::Box().h/2,titleRect[0],NULL,0.0,SDL_FLIP_VERTICAL);

            Window::Present(); //更新螢幕畫面
        }
    }

    SDL_DestroyTexture(bg);
    SDL_DestroyTexture(buttons);

    Window::Quit();
    return 0;
}
