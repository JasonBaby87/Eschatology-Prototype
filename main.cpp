#define __USE_MINGW_ANSI_STDIO 0
#include <iostream>
#include <cstdlib>
#include <cctype> //用來判斷字元是否為英文或數字
#include <math.h> //簡協運動的三角函數
#include <sstream>
#include "lib/window.h"
#include "lib/timer.h"

const int FPS=60;

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
    Texture* black = new Texture("img/black.png"); //國防布

    bg.setDstRect(0,Window::state().h); //讓它填滿螢幕(長填滿，寬依比例縮放)，錨點設為左上
    Texture alurens("img/alurens.png");
    alurens.setDstRect(0,0,alurens.setPoint()); //長寬為原材質長寬，錨點為中心
    alurens.setClipRect(2,2);   //分割成2x2

    Texture title("Eschatology","font/freeWing.ttf",rgb(255, 255, 255),64);
    Texture title2("pre-demo","font/freeWing.ttf",rgb(255, 255, 255),32);
    title.setDstRect(0,0,title.setPoint()); //長寬為原材質長寬，錨點為中心
    title2.setDstRect(0,0,title2.setPoint());

    SDL_Color alurensColor[4]={rgb(255, 128, 128),rgb(255, 255, 128),rgb(211, 128, 255),rgb(176, 255, 255)};

    Mix_Music* mainBGM=Mix_LoadMUS("sounds/main.ogg");
    Mix_Chunk *rain_drop=Mix_LoadWAV("sounds/rain_drop.wav");

    Timer fps;

    int numKey=-1; //用來紀錄現在的數字鍵值，-1代表按的是數字鍵以外的鍵
    float theta1=0,theta2=0,theta3=0; //用來記錄角度
    //theta1用來

    SDL_Event e;
    SDL_Event trash_e;
    bool quit=false;

    bool slide = false;
	int slide_down = 0;
    int fade_out = 0;
    Mix_PlayMusic( mainBGM, -1 ); //-1是loop次數，在此是loop到halt(stop)為止
    ////////////////////////////////////////////////////////////////////迴圈開始
    while (!quit)
    {
        fps.start();
		if (slide_down < 180)
			slide_down++;
        if (slide_down == 179)
            numKey = 2;

        while(SDL_PollEvent(&e) && !slide)
        {
            if(e.type==SDL_QUIT) //單擊右上角的X
            {
    			quit=true;
    		}
    		if(e.type==SDL_KEYDOWN && slide_down==180)
            {
                switch(e.key.keysym.sym)
                {
                    //ESC退出
                    case SDLK_ESCAPE:
                        quit=true;
                        break;
                }
    		}
    		if(e.type==SDL_MOUSEBUTTONUP && slide_down==180 )
            {
                Mix_FadeOutMusic(1200);
                slide = true;
            }
            if(e.type==SDL_MOUSEMOTION && slide_down==180 ) //滑鼠移動
                theta1+=e.motion.xrel+e.motion.yrel;
    	}

        Window::clear();

        bg.draw(-120,-360+slide_down);
        alurensColor[numKey-1].b=rhs(theta3,128,240,0.1);
        alurens.setColor(alurensColor[numKey-1]);
        if (slide_down == 180)
            alurens.draw(Window::state().w/2,Window::state().h/2+80,numKey-1,theta1); //繪製在螢幕正中間，切換到相對應的子圖，旋轉theta1度
        title.setAlpha(rhs(theta2,0,255,0.01)); //透明度的簡諧運動
        title2.setAlpha(rhs(theta2,0,255,0.01));
        alurens.setAlpha(rhs(theta2,80,255,0.01));
        title.draw(Window::state().w/2,180);
        title2.draw(Window::state().w/2,244);

        if(fps.ticks()*FPS<1000)
            SDL_Delay((1000/FPS)- fps.ticks());

        if (slide)
        {
            fade_out++;
            black->setAlpha(fade_out*3);
            black->draw(0,0);
            if (fade_out == 1)
                Mix_PlayChannel(-1,rain_drop,0);
            else if (fade_out == 85)
            {
                fade_out = 0;
				SDL_Delay(3000);
                break;
            }
        }

        Window::present();
    }
    Window::quit();
	delete black;
    if (quit)
        exit(0);
    ///////////////////////////////////////////////切換橫視窗
    slide = false;
    Window::initialize_wide("Eschatology");

    Texture bg1("img/bg1.png");
    Texture bg2("img/bg2.png");
    Texture bg3("img/bg3.png");
    Texture* black_w = new Texture("img/black_w.png");
    Texture* chat = new Texture("img/chat.png");
    Texture face1("img/face1.png");
    Texture face1_2("img/face1_2.png");
    Texture face2("img/face2.png");
    Texture bg_flare("img/bg_flare.png");

    mainBGM = Mix_LoadMUS("sounds/starting.ogg");
	Mix_Chunk *blow = Mix_LoadWAV("sounds/blow.wav");
	Mix_Chunk *transition = Mix_LoadWAV("sounds/transition.wav");
    Mix_PlayMusic(mainBGM,-1);
	
	string talking[39];
	talking[0] = "報告，已經確認黑盒子反應";
	talking[1] = "目標，奪取黑盒子並消滅目擊相關人士";
	talking[2] = "進行最後確認";
	talking[3] = "北方";
	talking[4] = "無異狀";
	talking[5] = "南方";
	talking[6] = "無異狀";
	talking[7] = "東方";
	talking[8] = "無異狀";
	talking[9] = "西方";
	talking[10] = "無異狀";
	talking[11] = "確認完畢，倒數10秒";
	talking[12] = "10！";
	talking[13] = "！！！";
	talking[14] = "居然不知不覺睡著了......";
	talking[15] = "已經很晚了啊，不知道爸睡了沒？";
	talking[16] = "去樓下看看好了";
	talking[17] = "......！";
	talking[18] = "周圍魔力的流動很詭異，發生了什麼事？";
	talking[19] = "爸！你還醒著嗎？";
	talking[20] = "羅雷，快趴下！";
	talking[21] = "３！";
	talking[22] = "２！";
	talking[23] = "１！";
	talking[24] = "發動，地獄業火！";
	talking[25] = "";
	talking[26] = "這種程度的攻擊性魔法...敵人究竟有多少人？";
	talking[27] = "沒時間管那麼多了，羅雷，帶著黑盒子快跑！";
	talking[28] = "跑？去哪裡？那你呢？";
	talking[29] = "往南邊跑！米亞姊會去接應你的。我留下來拖延他們的腳步";
	talking[30] = "別開玩笑了！我怎麼可能眼睜睜看著你...";
	talking[31] = "我們沒有選擇！";
	talking[32] = "敵人的目標是黑盒子，這是我們的使命";
	talking[33] = "我......";
	talking[34] = "動作快！";
	talking[35] = "......";
	talking[36] = "可惡！";
	talking[37] = "我打開藏著黑盒子的暗門，帶著黑盒子從後門跑出去，身後敵人源源不絕的湧上來";
	talking[38] = "黑盒子在那個少年身上，別讓他跑了！";
	int word_count[39] = {12,17,6,2,3,2,3,2,3,2,3,9,2,3,11,15,7,3,18,8,7,2,2,2,8,0,20,20,10,26,18,7,17,3,4,2,3,36,17};

	int talk = 0;
	int display = 0;
	bool display_end = false;
	int shake = 0;
	int direction = -1;
	int shake_times = 0;
	int alpha = 0;
	int cls_pos = 0;
    while (!quit)
    {
        fps.start();
		
		if (talk < 39)
		{
			display_end = false;
			display++;
			if (display > word_count[talk] * 3)
			{
				display = word_count[talk] * 3;
				display_end = true;
			}
		}
        while(SDL_PollEvent(&e))
        {
            if(e.type==SDL_QUIT) //單擊右上角的X
            {
    			quit=true;
    		}
    		if(e.type==SDL_KEYDOWN)
            {
                switch(e.key.keysym.sym)
                {
                    //ESC退出
                    case SDLK_ESCAPE:
                        quit=true;
                        break;
                }
    		}
    		if(e.type==SDL_MOUSEBUTTONUP && talk != 25)
			{
				if (!display_end)
				{
					display = word_count[talk] * 3;
					display_end = true;
				}
				else
				{
					if (talk < 39)
						talk++;
					if (talk == 25)
						Mix_PlayChannel(-1,blow,0);
					else if (talk == 13)
						alpha = 255;
					else if (talk == 14)
						black_w->setAlpha(255);
					else if (talk == 39 && cls_pos == 0)
					{
						Mix_PlayChannel(-1,transition,0);
						Mix_FadeOutMusic(600);
					}
					display = 0;
				}
			}
    	}
        Window::clear();
		if (talk >= 13 && talk <= 20)
		{
			bg1.draw(0,0);
			if (talk == 13)
			{
				black_w->setAlpha(alpha);
				black_w->draw(0,0);
				if (alpha > 0)
					alpha -= 51;
			}
		}
		else if (talk == 25)
		{
			shake += direction * 15;
			shake_times++;
			if (shake == -30)
				direction = 1;
			if (shake == 30)
				direction = -1;
			if (shake_times == 28)
			{
				talk = 26;
				bg2.draw(0,0);
				Window::present();
				SDL_Delay(3000);
				while (SDL_PollEvent(&trash_e));
				continue;
			}
			bg_flare.draw(shake,0);
		}
		else if (talk >= 26 && talk <= 36)
			bg2.draw(0,0);
		else if (talk >= 37)
			bg3.draw(0,0);
		
		if (talk >= 13 && talk != 21 && talk != 22 && talk != 23 && talk != 24)
			chat->draw(0,320);
		////////////////////////////////////////表情
		if ((talk >= 13 && talk <= 16) || talk == 26 || talk == 28 || talk == 33 || talk == 35)
			face1.draw(0,320);
		else if (talk == 17 || talk == 18 || talk == 19 || talk == 30 || talk == 36)
			face1_2.draw(0,320);
		else if (talk == 20 || talk == 27 || talk == 29 || talk == 31 || talk == 32 || talk == 34)
			face2.draw(0,320);
		////////////////////////////////////////表情
		if (talk < 39)
		{
			if (display <= 54)
			{
				Texture* temp = new Texture(talking[talk].substr(0,(display/3)*3),"font/freeWing.ttf",rgb(255, 255, 255),24);
				temp->setDstRect(0,0,temp->setPoint());
				if (talk < 13 || talk == 21 || talk == 22 || talk == 23 || talk == 24 || talk == 37)
					temp->draw(400,400);
				else
					temp->draw(460,400);
				delete temp;
			}
			else
			{
				Texture* temp = new Texture(talking[talk].substr(0,54),"font/freeWing.ttf",rgb(255, 255, 255),24);
				temp->setDstRect(0,0,temp->setPoint());
				if (talk < 13 || talk == 21 || talk == 22 || talk == 23 || talk == 24 || talk == 37)
					temp->draw(400,376);
				else
					temp->draw(460,376);
				Texture* temp2 = new Texture(talking[talk].substr(54,(display/3)*3-54),"font/freeWing.ttf",rgb(255, 255, 255),24);
				temp2->setDstRect(0,0,temp2->setPoint());
				if (talk < 13 || talk == 21 || talk == 22 || talk == 23 || talk == 24 || talk == 37)
					temp2->draw(400,424);
				else
					temp2->draw(460,424);
				delete temp;
				delete temp2;
			}
		}
		else if (talk == 39)
		{
			cls_pos += 20;
			black_w->draw(-800+cls_pos,0);
			if (cls_pos == 820)
			{
				SDL_Delay(200);
				cls_pos = 0;
				break;
			}
		}
		
        if (fps.ticks()*FPS<1000)
            SDL_Delay((1000/FPS)- fps.ticks());
        Window::present();
    }
    Window::quit();
	delete black_w;
	if (quit)
		exit(0);
	///////////////////////////////////////////////切換戰鬥畫面
	Window::initialize("Eschatology");
	
    Texture bg4("img/bg4.png");
    Texture bg5("img/bg5.png");
	black = new Texture("img/black.png");
    Texture minion("img/minion.png");
    Texture character1("img/character1.png");
    Texture hp_ground("img/hp_ground.png");
    Texture hp_layer("img/hp_layer.png");
    Texture hp2_ground("img/hp2_ground.png");
    Texture hp2_layer("img/hp2_layer.png");
	Texture aluren("img/aluren.png");
    Texture boss("img/boss.png");
    Texture flash1("img/flash1.png");
    Texture flash2("img/flash2.png");
    Texture flash3("img/flash3.png");
	Texture full_hp("100/100","font/freeWing.ttf",rgb(255, 255, 255),16);
	Texture full_hp2("100/100","font/freeWing.ttf",rgb(255, 255, 255),16);
	
	Mix_Chunk *transition_r = Mix_LoadWAV("sounds/transition_r.wav");
	Mix_Chunk *battle_pre = Mix_LoadWAV("sounds/battle_pre.ogg");
	mainBGM = Mix_LoadMUS("sounds/battle1.ogg");
	SDL_Delay(500);
	Mix_PlayChannel(-1,transition_r,0);
	
	display = 0;
	cls_pos = 0;
	string battle_text = "一些士兵擋住了去路";
	string battle_text2 = "抓準魔力的流動";
	string battle_text3 = "組成各種元素進行攻擊";
	int hp1 = 100;
	int hp2 = 100;
	while (!quit)
	{
		fps.start();
		
		while(SDL_PollEvent(&e))
        {
            if(e.type==SDL_QUIT) //單擊右上角的X
            {
    			quit=true;
    		}
    		if(e.type==SDL_KEYDOWN)
            {
                switch(e.key.keysym.sym)
                {
                    //ESC退出
                    case SDLK_ESCAPE:
                        quit=true;
                        break;
					/*case SDLK_f:
					case SDLK_e:
					case SDLK_j:
					case SDLK_i:*/
                }
    		}
    	}
        Window::clear();
		minion.draw(0,0);
		character1.draw(0,0);
		if (display <= 27)
		{
			Texture* temp = new Texture(battle_text.substr(0,(display/3)*3),"font/freeWing.ttf",rgb(255, 255, 255),24);
			temp->setDstRect(0,0,temp->setPoint());
			temp->draw(240,300);
			delete temp;
		}
		else if (display <= 48)
		{
			Texture* temp = new Texture(battle_text,"font/freeWing.ttf",rgb(255, 255, 255),24);
			Texture* temp2 = new Texture(battle_text2.substr(0,((display-27)/3)*3),"font/freeWing.ttf",rgb(255, 255, 255),24);
			temp->setDstRect(0,0,temp->setPoint());
			temp2->setDstRect(0,0,temp2->setPoint());
			temp->draw(240,300);
			temp2->draw(240,336);
			delete temp;
			delete temp2;
		}
		else if (display <= 78)
		{
			Texture* temp = new Texture(battle_text,"font/freeWing.ttf",rgb(255, 255, 255),24);
			Texture* temp2 = new Texture(battle_text2,"font/freeWing.ttf",rgb(255, 255, 255),24);
			Texture* temp3 = new Texture(battle_text3.substr(0,((display-48)/3)*3),"font/freeWing.ttf",rgb(255, 255, 255),24);
			temp->setDstRect(0,0,temp->setPoint());
			temp2->setDstRect(0,0,temp2->setPoint());
			temp3->setDstRect(0,0,temp3->setPoint());
			temp->draw(240,300);
			temp2->draw(240,336);
			temp3->draw(240,372);
			delete temp;
			delete temp2;
			delete temp3;
		}
		else if (display > 78 && display < 510)
		{
			Texture* temp = new Texture(battle_text,"font/freeWing.ttf",rgb(255, 255, 255),24);
			Texture* temp2 = new Texture(battle_text2,"font/freeWing.ttf",rgb(255, 255, 255),24);
			Texture* temp3 = new Texture(battle_text3,"font/freeWing.ttf",rgb(255, 255, 255),24);
			temp->setDstRect(0,0,temp->setPoint());
			temp2->setDstRect(0,0,temp2->setPoint());
			temp3->setDstRect(0,0,temp3->setPoint());
			if (display > 660)
			{
				temp->setAlpha(240-(display-480)*8);
				temp2->setAlpha(240-(display-480)*8);
				temp3->setAlpha(240-(display-480)*8);
			}
			temp->draw(240,300);
			temp2->draw(240,336);
			temp3->draw(240,372);
			delete temp;
			delete temp2;
			delete temp3;
		}
		
		if (display < 540 && cls_pos == 800)
		{
			display++;
			if (display == 343)
				Mix_PlayMusic(mainBGM,-1);
			else if (display > 480 && display <= 510)
			{
				hp_layer.draw((display-480)*8-240,180);
				hp2_layer.draw(480-(display-480)*8,180);
				full_hp.setAlpha((display-480)*8+15);
				full_hp2.setAlpha((display-480)*8+15);
				full_hp.draw(30,210);
				full_hp2.draw(450-full_hp2.getWidth(),210);
			}
			else if (display > 510)
			{
				hp_layer.draw(0,180);
				hp2_layer.draw(240,180);
				full_hp.draw(30,210);
				full_hp2.draw(450-full_hp2.getWidth(),210);
				aluren.setAlpha((display-510)*8+15);
				aluren.draw(90,270);
			}
		}
		if (display == 540)
		{
			hp_ground.draw(0,180);
			hp2_ground.draw(240,180);
			hp_layer.draw(hp1*240/100-240,180);
			hp2_layer.draw(480-hp2*240/100,180);
			stringstream ss;
			string temp_hp;
			ss << hp1;
			ss >> temp_hp;
			Texture* hp1_t = new Texture(temp_hp+"/100","font/freeWing.ttf",rgb(255, 255, 255),16);
			ss << hp2;
			ss >> temp_hp;
			Texture* hp2_t = new Texture(temp_hp+"/100","font/freeWing.ttf",rgb(255, 255, 255),16);
			hp1_t->draw(30,210);
			hp2_t->draw(450-hp2_t->getWidth(),210);
			aluren.draw(90,270);
		}
		
		
		
		if (cls_pos < 800)
		{
			black->draw(0,cls_pos);
			cls_pos += 20;
			if (cls_pos == 800)
				Mix_PlayChannel(-1,battle_pre,0);
		}
		
		Window::present();
	}
    return 0;
}
