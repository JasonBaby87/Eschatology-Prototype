#include <iostream>
#include <string>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
using namespace std;

const int SCREEN_WIDTH=800;
const int SCREEN_HEIGHT=480;
SDL_Window *window;
SDL_Renderer *renderer;

SDL_Texture* RenderText(string message,string fontFile,SDL_Color color,int fontSize)
{
    //color是RGB
    TTF_Font *font=nullptr;
    font=TTF_OpenFont(fontFile.c_str(),fontSize);
    if (font == nullptr)
        throw runtime_error("Failed to load font: " + fontFile + TTF_GetError());

    //TTF_RenderText用來繪製文本，其中Blended是效率最慢但效果最好的
    SDL_Surface *surf=TTF_RenderText_Blended(font,message.c_str(),color);
    SDL_Texture *texture=SDL_CreateTextureFromSurface(renderer,surf);

    SDL_FreeSurface(surf);
    TTF_CloseFont(font);

    return texture;
}

//裁切圖片的每一小塊圖片都是一樣長寬而且是有序排列的
SDL_Rect* clipRect(int iW,int iH,int row,int column) //要裁切的每一份小圖的長寬和小圖們總共幾行幾列
{
    SDL_Rect* clips=new SDL_Rect[row*column];
    for (int i=0,c=0;i<row*column;i++)
    {
        if (i!=0 && i%row== 0)
            c++;
        clips[i].x = c * iW;
        clips[i].y = i % row * iH;
        clips[i].w = iW;
        clips[i].h = iH;
    }
    return clips;
}

void ApplySurface(int x,int y,SDL_Texture *tex,SDL_Rect *clip=NULL)
{
    SDL_Rect pos; //一個長方形

    if (clip!=NULL) //如果有需要剪裁
    {
        pos.w = clip->w;
        pos.h = clip->h;
    }
    else
        SDL_QueryTexture(tex,NULL,NULL,&pos.w,&pos.h); //把texture的長寬傳出給pos，我們要1:1畫圖

    pos.x=x-pos.w/2; //以物體的中心點做定位錨
    pos.y=y-pos.h/2;

    SDL_RenderCopy(renderer,tex,clip,&pos);
    //把texture畫上去
    //第三個參數是指向源矩形的指針，也就是從圖像上裁剪下的一塊矩形，若是NULL代表繪製整個源圖像
    //第四個參數是指向目標矩形的指針，若是NULL代表把它畫在屏幕上(0,0)的位置，並拉伸這個圖像讓它填滿整個窗口
}



int main(int argc,char* args[])
{
    TTF_Init();

    window=SDL_CreateWindow("Eschatology",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
    //創立視窗，參數分別是標題、x、y、長、寬，最後的參數是我設定他一執行就彈出
    renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    //渲染器，參數-1代表讓SDL自動幫你選最適合的(後面我指定選項)的驅動
    //SDL_RENDERER_ACCELERATED，使用硬件加速的renderer=利用顯卡的力量
    // SDL_RENDERER_PRESENTVSYNC，使用SDL_RendererPresent這個函數，他會以顯示器的刷新率來更新畫面

    SDL_Texture* bg=IMG_LoadTexture(renderer,"img/bg.jpg");
    SDL_Texture* buttons=IMG_LoadTexture(renderer,"img/buttons.png");

    SDL_Color color={255,255,255};
    SDL_Texture* title=RenderText("Eschatology","font/freeWing.ttf",color,64);

    SDL_Rect* clips=clipRect(245,245,2,2);
    int useClip=0;

    SDL_Event e;
    bool quit = false;
    while (!quit)
    {
        while (SDL_PollEvent(&e))
        {

            if (e.type == SDL_QUIT) //單擊右上角的X
            {
    			quit = true;
    		}
    		if (e.type == SDL_KEYDOWN)
            {
                switch (e.key.keysym.sym)
                {
                    case SDLK_1:
                        useClip = 0;
                        break;
                    case SDLK_2:
                        useClip = 1;
                        break;
                    case SDLK_3:
                        useClip = 2;
                        break;
                    case SDLK_4:
                        useClip = 3;
                        break;
                    //For quitting, escape key
                    case SDLK_ESCAPE:
                        quit = true;
                        break;
                    default:
                        break;
                }
    		}
    		if (e.type == SDL_MOUSEBUTTONDOWN)
            {
    			quit = true;
    		}

            SDL_RenderClear(renderer); //清屏

            ApplySurface(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,bg);
            ApplySurface(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,buttons,&clips[useClip]);
            ApplySurface(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,title);

            SDL_RenderPresent(renderer); //更新螢幕畫面
        }
    }

    SDL_DestroyTexture(bg);
    SDL_DestroyTexture(buttons);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}
