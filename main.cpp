#include <iostream>
#include "SDL2/SDL.h"
using namespace std;

int main(int argc,char* args[])
{
    SDL_Window *win=SDL_CreateWindow("Eschatology",0,0,366,366,SDL_WINDOW_SHOWN);
    //創立視窗，參數分別是標題、x、y、長、寬，最後的參數是我設定他一執行就彈出
    SDL_Renderer *ren=SDL_CreateRenderer(win,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    //渲染器，參數-1代表讓SDL自動幫你選最適合的(後面我指定選項)的驅動
    //SDL_RENDERER_ACCELERATED，使用硬件加速的renderer=利用顯卡的力量
    // SDL_RENDERER_PRESENTVSYNC，使用SDL_RendererPresent這個函數，他會以顯示器的刷新率來更新畫面
    SDL_Surface *bmp=SDL_LoadBMP("hello.bmp");
    SDL_Texture *tex=SDL_CreateTextureFromSurface(ren,bmp);
    //SDL2是用Texture來繪製，更快

    SDL_FreeSurface(bmp); //用不到了
    SDL_RenderClear(ren); //清空螢幕
    SDL_RenderCopy(ren,tex,NULL,NULL); //把texture畫上去
    //第一個NULL是指向源矩形的指針，也就是從圖像上裁剪下的一塊矩形，這裡代表繪製整個源圖像
    //第二個NULL是指向目標矩形的指針，這裡代表把它畫在屏幕上(0,0)的位置，並拉伸這個圖像讓它填滿整個窗口
    SDL_RenderPresent(ren); //更新螢幕畫面

    SDL_Delay(2000); //不等待的話他會立刻退出

    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);

    SDL_Quit();
    return 0;
}
