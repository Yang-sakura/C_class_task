#include "signup.h"
#include "public.h"

void signup_bkpaint(void)
{
    setbkcolor(WHITE);
    cleardevice();
    clrmous(MouseX,MouseY);

    setcolor(BLUE);
    settextstyle(DEFAULT_FONT   , HORIZ_DIR,3);
    outtextxy(70, 100, "Please sign up here...");

    setcolor(DARKGRAY);
    settextstyle(DEFAULT_FONT   , HORIZ_DIR,2);
    outtextxy(80, 170, "user     :");
    outtextxy(80, 240, "password :");

    printbox(255,155,560,205,DARKGRAY,2,5,5);
    printbox(255,225,560,275,DARKGRAY,2,5,5);

    printbox(320-40,300,320+40,300+40,DARKGRAY,2,5,5);
    setcolor(DARKGRAY);
    settextstyle(DEFAULT_FONT   , HORIZ_DIR,2);
    outtextxy(306, 312, "OK");

    back_button(PAINT);

}

int signup_page(void)
{
    int place=0;

    signup_bkpaint();
    mouseinit();

    while(1)
    {
        newmouse(&MouseX, &MouseY, &press);

        if( mouse_press(595,5,630,40)==2 )
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
            return LOGIN;
        }
        else if( mouse_press(285,315,350,340)==2 )
        {
            if(place == 0)
            {
                MouseS = 1;
                place = 2;
                ok_button_light();
            }
        }
        else if( mouse_press(285,315,350,340)==1 )//ok按下
        {

        }
        else {
            if(place!=0)
            {
                MouseS=0;
                place=0;
                ok_button_recover();
                back_button(RECOVER);
            }
        }
    }
}
