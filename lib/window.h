#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"
using namespace std;

//位置列舉，讓與SDL_Point相關的參數傳接更可視化
enum Position{left,right,top,bottom,middle};
//我承認是我editor可以認識rgb()然後顯示顏色我才特別弄這些函式的YA
SDL_Color rgb(Uint8 r,Uint8 g,Uint8 b);
SDL_Color rgba(Uint8 r,Uint8 g,Uint8 b,Uint8 a);

class Window
{
    //讓下方的Texture可以使用renderer
    friend class Texture;

public:
    //初始化SDL、TTF，建立視窗和renderer，參數接視窗名子，預設Window
    static void initialize(std::string title="Window");
    static void initialize_wide(std::string title="Window");
    //返回視窗訊息(位置、長寬)
    static SDL_Rect state();
    //清除視窗
    static void clear();
    //更新視窗
    static void present();
    //退出視窗
    static void quit();

private:
    static SDL_Renderer* renderer;
    static SDL_Window* window;
    static SDL_Rect box;
};

class Texture
{
public:
    //將圖片載為材質
    Texture(const string& file);
    /**
    *   將文字載為材質
    *   @param message:文字內容
    *   @param fontfile:字體ttf檔案位置
    *   @param color:RGB{0,0,0}(黑)~{255,255,255}(白)
    *   @param fontsize:字體大小
    */
    Texture(const string& message,const string& fontfile,SDL_Color color,int fontsize);
    //初始化除了tex以外所有私有成員
    void initialize();
    //清除texture
    ~Texture();
    //快速設定SDL_Point，horizan和vertical為自定義的Position enumeration，預設為垂直水平皆置中
    SDL_Point setPoint(Position horizon=middle,Position vertical=middle);
    /**
    *   設定texture要印出時所需的dstRect
    *   @param width和height設定dstRect要的寬高，為非負整數
    *   @param pivot設定矩形位置錨點，預設為左上角(0,0)
    */
    void setDstRect(unsigned int width,unsigned int height,SDL_Point pivot={0,0});
    /**
    *   設定texture要印出時所需的clipRect
    *   @param column和row設定要裁切成多少行列的小矩形，為非負整數
    *   在呼叫此函式前要先注意有沒有先setDstRect()過，因為此函式會直接變更dstRect的長寬及錨點位置(除以column和row)，以符合裁切後結果，如果一直重複呼叫此函式而未先set好dstRect，可能會讓dstRect長成非預期的樣子(dstRect用之前clip後的樣子繼續除而不是用原本的樣子只除這一次)
    */
    void setClipRect(unsigned int column,unsigned int row);
    //調整材質的色調
    void setColor(SDL_Color);
    //設定透明度
    void setAlpha(Uint8 a);
    /**
    *   讓texture render到螢幕上
    *   @param x和y設定texture要在螢幕的哪裡(座標)
    *   @param clip設定要傳入存在clipRect中的第幾個項目的裁切矩形，預設為0
    *   @param angle設定角度，會以pivot為中心旋轉
    *   @param pivot設定旋轉中心，注意在此傳入SDL_Point指針，預設為NULL=為中心點旋轉
    *   @param flip提供水平翻轉或垂直翻轉
    */
    void draw(int x,int y,unsigned int clip=0,float angle=0.0,SDL_Point* pivot=NULL,SDL_RendererFlip flip=SDL_FLIP_NONE);

    int width,height; //原材質長寬
private:
    SDL_Texture* tex;
    SDL_Rect dstRect;
    SDL_Rect* clipRect;

};

#endif
