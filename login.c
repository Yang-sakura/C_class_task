#include "login.h"
#include "public.h"

void login_bkpaint(void)//画登录页面背景
{
    setbkcolor(WHITE);
    cleardevice();

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

    back_button(PAINT);

    put_flower(105,425,5,CYAN);
    put_flower(155,425,5,GREEN);
    put_flower(515,425,10,BLUE);

}
void signup_button_recover(void)
{
    clrmous(MouseX, MouseY);
	delay(10);
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
void put_flower(int x,int y,int pix,int COLOR)
{
    // void printline(int x,int y,int len,int n,int flag,int COLOR,int wid,int gap);
    printline(x,y-pix*9,1,9,1,COLOR,pix,0);
    printline(x-2*pix,y-pix*6,1,5,0,COLOR,pix,0);
    printline(x-2*pix,y-pix*5,1,5,0,COLOR,pix,0);
    printline(x-2*pix,y-pix*10,1,4,1,COLOR,pix,0);
    printline(x-3*pix,y-pix*9,1,3,1,COLOR,pix,0);
    printline(x+2*pix,y-pix*10,1,4,1,COLOR,pix,0);
    printline(x+3*pix,y-pix*9,1,3,1,COLOR,pix,0);
    printline(x,y-pix*8,1,3,0,COLOR,pix,0);
    printline(x-4*pix,y-pix*4,1,2,1,COLOR,pix,0);
    printline(x-3*pix,y-pix*3,1,2,1,COLOR,pix,0);
    printline(x+4*pix,y-pix*4,1,2,1,COLOR,pix,0);
    printline(x+3*pix,y-pix*3,1,2,1,COLOR,pix,0);
    printline(x-2*pix,y-pix*2,1,5,0,COLOR,pix,0);
    printline(x-2*pix,y-pix*1,1,5,0,COLOR,pix,0);
    printline(x-pix,y-pix*7,1,3,1,COLOR,pix,0);
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
            return SIGNUP;
        }
        else if( mouse_press(595,5,630,40)==2 )
        {
            MouseS = 1;
            if( place==0 ) 
            {
                place=2;
                back_button(LIGHT);
            }
        }
        else if( mouse_press(595,5,630,40)==1 )//跳转welcome页面
        {
            cleardevice();
            return WELCOME;
        }
        else {
            if(place!=0)
            {
                MouseS=0;
                place=0;
                signup_button_recover();
                back_button(RECOVER);
            }
        }
    }
}
