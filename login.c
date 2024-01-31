#include "login.h"
#include "public.h"

void login_bkpaint(void)//画登录页面背景
{
    // 设置背景色
    setbkcolor(WHITE);
    cleardevice();

    // 设置字体样式、方向和大小
    setcolor(BLUE);
    settextstyle(DEFAULT_FONT   , HORIZ_DIR,3);
    outtextxy(70, 100, "Please log in here...");
    settextstyle(DEFAULT_FONT   , HORIZ_DIR,2);
    outtextxy(250, 410, "-sign up-");

    setcolor(DARKGRAY);
    settextstyle(DEFAULT_FONT   , HORIZ_DIR,2);
    outtextxy(80, 170, "user     :");
    outtextxy(80, 240, "password :");


    printbox(255,155,560,205,DARKGRAY,2,5,5);
    printbox(255,225,560,275,DARKGRAY,2,5,5);

    printbox(595,5,630,40,DARKGRAY,1,5,4);//右上角退出
    setcolor(DARKGRAY);
    settextstyle(DEFAULT_FONT   , HORIZ_DIR,3);
    outtextxy(602,10, "x");

}
void back_button_light(void)
{
    setfillstyle(SOLID_FILL, WHITE);
    bar(590,0,635,45);
    printbox(595,5,630,40,BLUE,1,5,4);
    setcolor(BLUE);
    settextstyle(DEFAULT_FONT   , HORIZ_DIR,3);
    outtextxy(602,10, "x");
}
void buttons_recover(void)
{
    clrmous(MouseX, MouseY);
	delay(10);

    setfillstyle(SOLID_FILL, WHITE);
    bar(590,0,635,45);
    bar(240,400,400,435);

    printbox(595,5,630,40,DARKGRAY,1,5,4);
    setcolor(DARKGRAY);
    settextstyle(DEFAULT_FONT   , HORIZ_DIR,3);
    outtextxy(602,10, "x");

    setcolor(BLUE);
    settextstyle(DEFAULT_FONT   , HORIZ_DIR,2);
    outtextxy(250, 410, "-sign up-");
}
void signup_button_light(void)
{
    setfillstyle(SOLID_FILL, WHITE);
    bar(240,400,400,435);
    setcolor(CYAN);
    settextstyle(DEFAULT_FONT   , HORIZ_DIR,2);
    outtextxy(250, 410, "-sign up-");
}
int login_page(void)
{
    int place=0;

    login_bkpaint();
    mouseinit();

    while(1)
    {
        newmouse(&MouseX, &MouseY, &press);

        if( mouse_press(265,405,375,425)==2 )//注册按钮未按
        {
            if(place == 0)
            {
                MouseS = 1;
                place = 1;
                signup_button_light();
            }
        }
        else if( mouse_press(265,405,375,425)==1 )//跳转注册页面(2)
        {
            cleardevice();
            return 2;
        }
        else if( mouse_press(595,5,630,40)==2 )
        {
            MouseS = 1;
            if( place==0 ) 
            {
                place=2;
                back_button_light();
            }
        }
        else if( mouse_press(595,5,630,40)==1 )//跳转welcome页面
        {
            cleardevice();
            return 0;
        }
        else {
            if(place!=0)
            {
                MouseS=0;
                place=0;
                buttons_recover();
            }
        }
    }
}
