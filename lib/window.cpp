#include "window.h"

SDL_Window* Window::window;
SDL_Renderer* Window::renderer;
SDL_Rect Window::box;

void Window::initialize(std::string title)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048 );

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

void Window::initialize_wide(std::string title)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048 );

    box.x=SDL_WINDOWPOS_CENTERED;
    box.y=SDL_WINDOWPOS_CENTERED;
    box.w=800;
    box.h=480;

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
    IMG_Quit();
    SDL_Quit();
    Mix_CloseAudio();
}

Texture::Texture(const string& file)
{
    tex=IMG_LoadTexture(Window::renderer,file.c_str());
    initialize();
}

Texture::Texture(const string& message,const string& fontFile,SDL_Color color,int fontSize)
{
    /**
    *   SDL_CreateTextureFromSurface:把surface轉成Texture
    *   @param  renderer*
    *   @param  surface*:TTF_RenderText_Blended(,,)會回傳

    *   TTF_RenderText:用來繪製文本(其中Blended是效率最慢但效果最好的)
    *   @return surface*
    *   @param TTF_Font*:TTF_OpenFont(,)會回傳
    *   @param char[]
    *   @param SDL_Color

    *   TTF_OpenFont
    *   @return TTF_Font*
    *   @param char[]:字體包檔案路徑
    *   @param int:字體大小
    */
    TTF_Font* font=TTF_OpenFont(fontFile.c_str(),fontSize);
    SDL_Surface* surf=TTF_RenderUTF8_Solid(font,message.c_str(),color);
    tex=SDL_CreateTextureFromSurface(Window::renderer,surf);
    SDL_FreeSurface(surf); //不做清除到時候重複建立超多文本材質時會爆掉
    TTF_CloseFont(font);

    initialize();
}

Texture::~Texture()
{
    SDL_DestroyTexture(tex);
}

void Texture::initialize()
{
    SDL_QueryTexture(tex,NULL,NULL,&width,&height); //獲取材質原本長寬並寫入到width和height裡面
    dstRect.x=0;
    dstRect.y=0;
    dstRect.w=width;
    dstRect.h=height;
    clipRect=NULL;
}

SDL_Point Texture::setPoint(Position horizon,Position vertical)
{
    int x=0,y=0; //x、y用來回傳point
    switch (horizon)
    {
        case Position::left:
            x=0;
            break;
        case Position::middle:
            x=width/2;
            break;
        case Position::right:
            x=width;
            break;
        default:
            x=0;
            break;
    }
    switch (vertical)
    {
        case Position::top:
            y=0;
            break;
        case Position::middle:
            y=height/2;
            break;
        case Position::bottom:
            y=height;
            break;
        default:
            y=0;
            break;
    }
    return {x,y};
}

void Texture::setDstRect(unsigned  int width,unsigned int height,SDL_Point pivot)
{
    if(width!=0 && height!=0) //如果都是零，代表要將dstRect長寬設為材質原長寬
    {
        if(width==0) //如果寬是0，長有被設定數字
        {
            width=this->width*height/this->height; //依配置的高等比例縮放寬(不讓照片變形)
        }
        else if(height==0)
        {
            height=this->height*width/this->width;
        }

        dstRect.w=width;
        dstRect.h=height;
    }
    dstRect.x=pivot.x; //設定錨點
    dstRect.y=pivot.y;
}
void Texture::setClipRect(unsigned int column,unsigned int row)
{
    if(column>0 && row>0) //以防coder亂設
    {
        clipRect=new SDL_Rect[row*column];

        for(unsigned int i=0,c=0;i<row*column;i++) //計算clipRect的每項之矩形訊息
        {
            if(i!=0 && i%row==0)
                c++;
            clipRect[i].x=c*this->width/column;
            clipRect[i].y=i%row*this->height/row;
            clipRect[i].w=this->width/column; //記得每個小裁切矩形都是原本寬的1/column倍
            clipRect[i].h=this->height/row;
        }

        dstRect.w/=column; //如果他有裁切，則使用者預期的dstRect錨點位置和長寬應該也被裁切成小小塊
        dstRect.h/=row;
        dstRect.x/=column; //比如使用者指定「中心」為錨點，這裡的中心不是原大圖的中心，是每個裁切子圖的中心
        dstRect.y/=row;
    }
}

void Texture::setColor(SDL_Color color)
{
    SDL_SetTextureColorMod(tex,color.r,color.g,color.b);
}

void Texture::setAlpha(Uint8 a)
{
    SDL_SetTextureAlphaMod(tex,a);
}

void Texture::draw(int x,int y,unsigned int clip,float angle,SDL_Point* pivot,SDL_RendererFlip flip)
{
    SDL_Rect tempRect=dstRect; //建立一個為了修正顯示位置和dstRect錨點的暫時矩形
    tempRect.x=x-dstRect.x; //修正其顯示位置和錨點
    tempRect.y=y-dstRect.y;

    SDL_RenderCopyEx(Window::renderer,tex,&clipRect[clip],&tempRect,angle,pivot,flip);
}

SDL_Color rgb(Uint8 r,Uint8 g,Uint8 b)
{
    return SDL_Color{r,g,b};
}

SDL_Color rgba(Uint8 r,Uint8 g,Uint8 b,Uint8 a)
{
    return SDL_Color{r,g,b,a};
}
