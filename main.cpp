#include <iostream>
#include <cctype> //用來判斷字元是否為英文或數字
#include <math.h> //簡協運動的三角函數
#include "lib/window.h"
#include "lib/timer.h"

/**
*   簡諧運動
*   @return cos(傳入theta2後成長一個omega的角度)作為比例，回傳上下限中的該比例對應的值
*   @param &theta2用來記錄現在在虛擬圓的哪個角度，並會直接以omega遞增/減該值
*   @param low簡諧運動下限
*   @param up簡諧運動上限
*   @param omega虛擬圓角速度
*/
float rhs(float& theta2,float low,float up,float omega)
{
    if(theta2>6.28)
        theta2=0;
    theta2+=omega;
    return (up+low)/2+(up-low)/2*cos(theta2);
}

int main(int argc,char* args[])
{
    Window::initialize("Eschatology");

    Texture bg("img/bg.jpg");

    bg.setDstRect(0,Window::state().h); //讓它填滿螢幕(長填滿，寬依比例縮放)，錨點設為左上
    Texture alurens("img/alurens.png");
    alurens.setDstRect(0,0,alurens.setPoint()); //長寬為原材質長寬，錨點為中心
    alurens.setClipRect(2,2);   //分割成2x2

    Texture title("Eschatology","font/freeWing.ttf",rgb(255, 255, 255),64);
    title.setDstRect(0,0,title.setPoint()); //長寬為原材質長寬，錨點為中心

    string alurensName[4]={"FIRE","LIGHT","DARK","ICE"};
    SDL_Color alurensColor[4]={rgb(255, 128, 128),rgb(255, 255, 128),rgb(211, 128, 255),rgb(176, 255, 255)};
    int alurensColorTransLow[4]={128,128,164,176};
    int alurensColorTransUp[4]={160,240,211,240};
    Timer alurensTimer[4];

    int numKey=-1; //用來紀錄現在的數字鍵值，-1代表按的是數字鍵以外的鍵
    float theta1=0,theta2=0,theta3=0; //用來記錄角度
    //theta1用來

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
                theta1+=e.motion.xrel+e.motion.yrel;
    		}
        }
        Window::clear();

        bg.draw(0,0);

        if(numKey>0)
        {
            Texture alurensTimerText("Magic "+alurensName[numKey-1]+" is using for "+ alurensTimer[numKey-1].clock(),"font/freeWing.ttf",rgb(255,255,255),16);
            alurensTimerText.setDstRect(0,0,alurensTimerText.setPoint(middle,top)); //長寬為原材質長寬，錨點為中上
            alurensTimerText.draw(Window::state().w/2,Window::state().h/2+150);

            switch(numKey)
            {
                case 1:
                    alurensColor[numKey-1].g=rhs(theta3,alurensColorTransLow[numKey-1],alurensColorTransUp[numKey-1],0.05);
                    alurensColor[numKey-1].b=rhs(theta3,alurensColorTransLow[numKey-1],255-alurensColorTransUp[numKey-1],0.05);
                    break;
                case 2:
                    alurensColor[numKey-1].b=rhs(theta3,alurensColorTransLow[numKey-1],alurensColorTransUp[numKey-1],0.1);
                    break;
                case 3:
                    alurensColor[numKey-1].r=rhs(theta3,alurensColorTransLow[numKey-1],alurensColorTransUp[numKey-1],0.1);
                    break;
                case 4:
                    alurensColor[numKey-1].r=rhs(theta3,alurensColorTransLow[numKey-1],alurensColorTransUp[numKey-1],0.1);
                    break;
            }
            alurens.setColor(alurensColor[numKey-1]);
            alurens.draw(Window::state().w/2,Window::state().h/2,numKey-1,theta1); //繪製在螢幕正中間，切換到相對應的子圖，旋轉theta1度
        }
        title.setAlpha(rhs(theta2,0,255,0.02)); //透明度的簡諧運動
        title.draw(Window::state().w/2,100);

        Window::present();
    }

    Window::quit();
    return 0;
}
