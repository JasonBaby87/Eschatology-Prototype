#include <iostream>
#include <string>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "window.h"
using namespace std;

SDL_Window* Window::window;
SDL_Renderer* Window::renderer;
SDL_Rect Window::box;

void Window::init(string title)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();

    box.x=SDL_WINDOWPOS_CENTERED;
    box.y=SDL_WINDOWPOS_CENTERED;
    box.w=480;
    box.h=800;

    window=SDL_CreateWindow(title.c_str(),box.x,box.y,box.w,box.h,SDL_WINDOW_SHOWN);
    //創立視窗，參數分別是標題、x、y、長、寬，最後的參數是我設定他一執行就彈出
    renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    //渲染器，參數-1代表讓SDL自動幫你選最適合的(後面我指定選項)的驅動
    //SDL_RENDERER_ACCELERATED，使用硬件加速的renderer=利用顯卡的力量
    // SDL_RENDERER_PRESENTVSYNC，使用SDL_RendererPresent這個函數，他會以顯示器的刷新率來更新畫面
}

SDL_Rect Window::state()
{
    //更新box讓他隨時是視窗長寬
    SDL_GetWindowSize(window,&box.w,&box.h);
    return box;
}

SDL_Texture* Window::loadImage(const string& file)
{
    return IMG_LoadTexture(renderer,file.c_str());
}

SDL_Texture* Window::loadText(const string& message,const string& fontFile,SDL_Color color,int fontSize)
{
    TTF_Font* font=TTF_OpenFont(fontFile.c_str(),fontSize);

    //TTF_RenderText用來繪製文本，其中Blended是效率最慢但效果最好的
    SDL_Surface* surf=TTF_RenderText_Blended(font,message.c_str(),color);
    SDL_Texture* texture=SDL_CreateTextureFromSurface(renderer,surf);

    SDL_FreeSurface(surf);
    TTF_CloseFont(font);

    return texture;
}

SDL_Rect* Window::setRect(SDL_Texture* tex,int width,int height,char horizon,char vertical,int x,int y,int column,int row)
{
    SDL_Rect* rect=new SDL_Rect[row*column+1]; //第零項目存放dstRect，剩下的存放clipRect[]

    int oriW=0,oriH=0; //獲取材質原本長寬
    SDL_QueryTexture(tex,NULL,NULL,&oriW,&oriH);

    for(int i=0,c=0;i<row*column;i++) //計算clipRect的每項之矩形訊息
    {
        if(i!=0 && i%row==0)
            c++;
        rect[i+1].x=c*oriW/column; //因為第零項是dstRect，所以都要加一
        rect[i+1].y=i%row*oriH/row;
        rect[i+1].w=oriW/column; //記得每個小裁切矩形都是原本寬的1/column倍
        rect[i+1].h=oriH/row;
    }

    if(width==0 && height==0) //預設都是零，代表要將dstRect長寬設為材質原長寬，意即1:1不更改比例印出
    {
        width=oriW/column;
        height=oriH/row;
    }
    else if(width==0) //如果只有寬是零，長有被設定數字
    {
        width=oriW*height/oriH; //依配置的高等比例縮放寬
    }
    else if(height==0)
    {
        height=oriH*width/oriW;
    }

    rect[0].w=width;
    rect[0].h=height;

    if(x!=0)
        rect[0].x=x;
    else
    {
        switch(horizon) //針對char horizon做快速dstRect錨點配置
        {
            case 'l': //left
                rect[0].x=0;
                break;
            case 'm': //middle
                rect[0].x=width/2;
                break;
            case 'r': //right
                rect[0].x=width;
                break;
            default: //若輸入其他指令則預設使用，所以若要自定錨點座標，傳入的char參數可以是空白字元
                rect[0].x=x;
                break;
        }
    }
    switch(vertical)
    {
        case 't':
            rect[0].y=0;
            break;
        case 'm':
            rect[0].y=height/2;
            break;
        case 'b':
            rect[0].y=height;
            break;
        default:
            rect[0].y=y;
            break;
    }
    return rect;
}

void Window::draw(SDL_Texture* tex,int x,int y,SDL_Rect dstRect,SDL_Rect* clip,float angle,SDL_RendererFlip flip)
{
    SDL_Point pivot; //SDL_RenderCopyEx要用的點物件，指出旋轉中心
    pivot.x=dstRect.x; //旋轉中心同錨點
    pivot.y=dstRect.y;
    dstRect.x=x-dstRect.x; //修正其顯示位置和錨點
    dstRect.y=y-dstRect.y;

    SDL_RenderCopyEx(renderer,tex,clip,&dstRect,angle,&pivot,flip);
}

void Window::clear()
{
    SDL_RenderClear(renderer);
}

void Window::present()
{
    SDL_RenderPresent(renderer);
}

void Window::quit()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}
