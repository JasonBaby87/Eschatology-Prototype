#include <iostream>
#include <string>
#include "lib/window.h"
#include "lib/timer.h"
using namespace std;

int main(int argc,char* args[])
{
    Window::init("Eschatology");

    SDL_Texture* bg=Window::loadImage("img/bg.jpg");
    SDL_Rect* bgRect=Window::setRect(bg,0,Window::state().h,'l','t'); //讓它填滿螢幕(長填滿，寬依比例縮放)，錨點設為左上
    SDL_Texture* alurens=Window::loadImage("img/alurens.png");
    SDL_Rect* alurensRect=Window::setRect(alurens,0,0,'m','m',0,0,2,2); //長寬為原材質長寬，錨點為中心，分割成2x2

    SDL_Texture* title=Window::loadText("Eschatology","font/freeWing.ttf",{255,255,255},64);
    SDL_Rect* titleRect=Window::setRect(title); //長寬為原材質長寬，錨點為中心

    SDL_Texture* alurensTimerText;
    SDL_Rect* alurensTimerTextRect;
    string alurensName[4]={"FIRE","HEAL","POISON","FROZEN"};
    Timer alurensTimer[4];

    int numberKey=-1; //用來紀錄現在的數字鍵值，-1代表按的是數字鍵以外的鍵
    float angle=0; //用來記錄角度


    SDL_Event e;
    bool quit=false;

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
                int temp=numberKey;
                switch(e.key.keysym.sym)
                {
                    case SDLK_1:
                        numberKey=1;
                        break;
                    case SDLK_2:
                        numberKey=2;
                        break;
                    case SDLK_3:
                        numberKey=3;
                        break;
                    case SDLK_4:
                        numberKey=4;
                        break;
                    //ESC退出
                    case SDLK_ESCAPE:
                        quit=true;
                        break;
                    default:
                        numberKey=-1;
                        break;
                }
                if(numberKey>0 && temp==numberKey)
                {
                    switch (alurensTimer[numberKey-1].state())
                    {
                        case -1:
                            alurensTimer[numberKey-1].start();
                            break;
                        case 0:
                            alurensTimer[numberKey-1].resume();
                            break;
                        case 1:
                            alurensTimer[numberKey-1].pause();
                            break;
                        default:
                            break;
                    }
                }
    		}
    		if(e.type==SDL_MOUSEBUTTONDOWN)
            {
                quit=true;
                break;
    		}
            if(e.type==SDL_MOUSEMOTION) //滑鼠移動
            {
    			angle++;
    		}
        }
        Window::clear();

        alurensTimerText=Window::loadText("Magic "+alurensName[numberKey-1]+" is using for "+ alurensTimer[numberKey-1].clock(),"font/freeWing.ttf",{255,255,255},16);
        alurensTimerTextRect=Window::setRect(alurensTimerText,0,0,'m','t'); //長寬為原材質長寬，錨點為中上

        Window::draw(bg,0,0,bgRect[0]);
        Window::draw(alurens,Window::state().w/2,Window::state().h/2,alurensRect[0],&alurensRect[numberKey],angle); //以錨點繪製在螢幕正中間，只繪製numberKey選取到的clipRect[]，旋轉angle度
        Window::draw(title,Window::state().w/2,Window::state().h/2,titleRect[0]);
        if(numberKey>0)
            Window::draw(alurensTimerText,Window::state().w/2,Window::state().h/2+150,alurensTimerTextRect[0]);

        Window::present();
    }

    SDL_DestroyTexture(bg);
    SDL_DestroyTexture(alurens);

    Window::quit();
    return 0;
}
