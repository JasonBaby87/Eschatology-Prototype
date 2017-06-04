#include <string>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
using namespace std;

#ifndef WINDOW_H
#define WINDOW_H
class Window
{
public:
    //初始化SDL、TTF，建立視窗和renderer，參數接視窗名子，預設Window
    static void init(string title="Window");
    //返回視窗訊息(位置、長寬)
    static SDL_Rect state();
    //將圖片載為材質指標返回
    static SDL_Texture* loadImage(const string& file);
    /**
    *   將文字轉成材質指標返回
    *   @param message:文字內容
    *   @param fontfile:字體ttf檔案位置
    *   @param color:RGB{0,0,0}(黑)~{255,255,255}(白)
    *   @param fontsize:字體大小
    */
    static SDL_Texture* loadText(const string& message,const string& fontfile,SDL_Color color,int fontsize);
    /**
    *   設定texture要印出時所需的dstRect和clipRect，回傳一個SDL_Rect陣列
    *   @return 陣列第一項固定存放dstRect，提供Draw()時「要以錨點在哪畫在視窗座標中並縮放這個材質」的相關矩形物件
    *   @return 陣列第一項之後存放clipRect們，提供Draw()時「只render選取的clipRect[]的範圍(簡單來說就是裁切)」
    *   ---以下參數主要處理dstRect(rect[0])
    *   @param width和height設定dstRect要的寬高，若不設定預設為零，將會在程式實作「直接設定寬高為原材質1:1寬高」，意即不改變材質比例
    *   @param horizan和vertical用來快速設定錨點，預設為垂直水平接置中
    *   @param x或y是在分別無設定horizan或vertical，使用者自定義的錨點座標。若要使錨點在左上角，輸入參數時忽略horizan和vertical直接輸入0,0就好
    *   ---以下參數主要處理clipRect(rect[i+1])
    *   @param column和row是要對這張材質切多少行列「等份」，預設不切=1等分
    */
    static SDL_Rect* setRect(SDL_Texture* tex,int width=0,int height=0,char horizon='m',char vertical='m',int x=0,int y=0,int column=1,int row=1);
    /**
    *   讓texture render到螢幕上
    *   @param x和y設定texture要在螢幕的哪裡(座標)，會加諸到dstRect上(函式裡的暫時物件，不改原本的rect[0])
    *   @param dstRect必要輸入的參數，texture常要縮放或調整錨點，所以設為必要參數
    *   @param clip預設不裁切材質，如果傳入clipRect(rect[i+1])，則在render時會只render裁切部分
    *   @param angle設定角度，會以錨點為中心旋轉，錨點在dstRect裡就設定好了
    *   @param flip提供水平翻轉或垂直翻轉
    */
    static void draw(SDL_Texture* tex,int x,int y,SDL_Rect dstRect,SDL_Rect* clip=NULL,float angle=0.0,SDL_RendererFlip flip=SDL_FLIP_NONE);
    //清除視窗
    static void clear();
    //更新視窗
    static void present();
    //退出視窗
    static void quit();

private:
    static SDL_Window* window;
    static SDL_Renderer* renderer;
    static SDL_Rect box;
};

#endif
