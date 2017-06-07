#include <iostream>
#include <cctype> //用來判斷字元是否為英文或數字
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

    int numKey=-1; //用來紀錄現在的數字鍵值，-1代表按的是數字鍵以外的鍵
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
                int preNumKey=numKey;

                //智慧判斷讀進來的KeyName不須再寫一個一個case再判斷和紀錄
                //SDL_GetKeyName()讀進來的會是char[]
                if(isdigit(SDL_GetKeyName(e.key.keysym.sym)[0])) //判斷按的鍵回傳的key值第一個字元是不是數字
                    numKey=atoi(SDL_GetKeyName(e.key.keysym.sym)); //確定按的是數字再進行轉換
                else //我已經確認過SDL的所有keyName，除了數字以外，其他所有鍵的key值開頭一定是英文
                    numKey=-1;

                switch(e.key.keysym.sym)
                {
                    //ESC退出
                    case SDLK_ESCAPE:
                        quit=true;
                        break;
                }
                if(numKey>0 && preNumKey==numKey)
                {
                    switch(alurensTimer[numKey-1].state())
                    {
                        case initial:
                            alurensTimer[numKey-1].start();
                            break;
                        case pausing:
                            alurensTimer[numKey-1].resume();
                            break;
                        case timing:
                            alurensTimer[numKey-1].pause();
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
                angle+=e.motion.xrel+e.motion.yrel;
    		}
        }
        Window::clear();


        Window::draw(bg,0,0,bgRect[0]);
        Window::draw(alurens,Window::state().w/2,Window::state().h/2,alurensRect[0],&alurensRect[numKey],angle); //以錨點繪製在螢幕正中間，只繪製numKey選取到的clipRect[]，旋轉angle度
        Window::draw(title,Window::state().w/2,Window::state().h/2,titleRect[0]);
        if(numKey>0)
        {
            alurensTimerText=Window::loadText("Magic "+alurensName[numKey-1]+" is using for "+ alurensTimer[numKey-1].clock(),"font/freeWing.ttf",{255,255,255},16);
            alurensTimerTextRect=Window::setRect(alurensTimerText,0,0,'m','t'); //長寬為原材質長寬，錨點為中上
            Window::draw(alurensTimerText,Window::state().w/2,Window::state().h/2+150,alurensTimerTextRect[0]);
        }

        Window::present();
    }

    SDL_DestroyTexture(bg);
    SDL_DestroyTexture(alurens);

    Window::quit();
    return 0;
}
