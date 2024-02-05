#include "signup.h"
#include "public.h"
#include "logfunc.h"

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
    int state1=0;//用户名
    int state2=0;//密码
    INFO *user = (INFO *)malloc(sizeof(INFO));
    if(user != NULL) {
        memset(user,0,sizeof(INFO));
    }
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
        else if( mouse_press(595,5,630,40)==1 )//跳转login页面
        {
            free(user);
            cleardevice();
            return LOGIN;
        }
        else if( mouse_press(285,315,350,340)==2 )//ok未按下
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
            if( user->name[0]=='\0' || user->password[0]=='\0') continue;
            
            if( userinfo_input(user, &state1, &state2) ) 
            {
                free(user);
                user=NULL;
                return LOGIN;
            }
        }
        else if( mouse_press(255,155,560,205)==2 )//用户名输入框未按
        {
            if(place==0)
            {
                MouseS = 2;
                place = 4;//用户名输入框(255,155,560,205)
            }
        }
        else if( mouse_press(255,155,560,205)==1 )//用户名输入框按下
        {
            temp_input(user->name , 266,170);
        }
        else if( mouse_press(255,225,560,275)==2 )//密码输入框未按
        {
            if(place==0)
            {
                MouseS = 2;
                place = 5;//密码输入框(255,225,560,275)
            }
        }
        else if( mouse_press(255,225,560,275)==1 )//密码输入框按下
        {
            if( user->name[0] == '\0' ) continue;
            temp_input(user->password ,266,240);
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
