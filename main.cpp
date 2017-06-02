#include <iostream>
#include <string>
#include "SDL2/SDL.h"
using namespace std;

const int SCREEN_WIDTH=960;
const int SCREEN_HEIGHT=600;
SDL_Window *window;
SDL_Renderer *renderer;

SDL_Texture* LoadImage(string file)
{
    SDL_Surface *loadedImage=SDL_LoadBMP(file.c_str());
    SDL_Texture *texture=SDL_CreateTextureFromSurface(renderer, loadedImage);
    //SDL2是用Texture來繪製，更快，所以我們把SDL_Surface轉成SDL_Texture
    SDL_FreeSurface(loadedImage); //用不到了
    return texture;
}

void ApplySurface(int x,int y,SDL_Texture *tex)
{
    SDL_Rect pos; //一個長方形
    pos.x=x;
    pos.y=y;
    SDL_QueryTexture(tex,NULL,NULL,&pos.w,&pos.h); //把texture的長寬傳出給pos，我們要1:1畫圖

    SDL_RenderCopy(renderer,tex,NULL,&pos);
    //把texture畫上去
    //第三個參數是指向源矩形的指針，也就是從圖像上裁剪下的一塊矩形，這裡代表繪製整個源圖像
    //第四個參數是指向目標矩形的指針，這裡代表把它畫在屏幕上(0,0)的位置，並拉伸這個圖像讓它填滿整個窗口
}

int main(int argc,char* args[])
{
    window=SDL_CreateWindow("Eschatology",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
    //創立視窗，參數分別是標題、x、y、長、寬，最後的參數是我設定他一執行就彈出
    renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    //渲染器，參數-1代表讓SDL自動幫你選最適合的(後面我指定選項)的驅動
    //SDL_RENDERER_ACCELERATED，使用硬件加速的renderer=利用顯卡的力量
    // SDL_RENDERER_PRESENTVSYNC，使用SDL_RendererPresent這個函數，他會以顯示器的刷新率來更新畫面

    SDL_Texture* bg=LoadImage("img/bg.bmp");
    SDL_Texture* yellowDot=LoadImage("img/yellowDot.bmp");

    SDL_RenderClear(renderer); //清屏

    int iW, iH;
    SDL_QueryTexture(yellowDot, NULL, NULL, &iW, &iH);
    ApplySurface(SCREEN_WIDTH/2-iW/2,SCREEN_HEIGHT/2-iH/2,yellowDot);
    //因為SDL會pin在圖片的左上角，所以要讓圖片放在正中央需要計算一下
    ApplySurface(0,0,bg);

    SDL_RenderPresent(renderer); //更新螢幕畫面
    SDL_Delay(2000); //不等待的話他會立刻退出


    SDL_DestroyTexture(bg);
    SDL_DestroyTexture(yellowDot);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}
