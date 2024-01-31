#include "welcome.h"
#include "public.h"

void welcome_screen(void)
{
    printbox(30,360,290,460,WHITE,1,5,5);
    printbox(350,360,610,460,WHITE,1,5,5);
    setcolor(DARKGRAY);
    settextstyle( DEFAULT_FONT , HORIZ_DIR , 2);
    outtextxy( 113 , 405 , "LOG_IN" );
    outtextxy( 450 , 405 , "QUIT" );

}

void put_title(int *color)
{   
    setcolor(*color);
    settextstyle( DEFAULT_FONT , HORIZ_DIR , 3);
    outtextxy( 10 , 50 , "DRONE AGRICULTURE DETECTOR");
    (*color)++;
    if((*color)==16)
    {
        *color = 1;
    }
}



int welcome_page(void)
{   
    int colorset = 1;
    int flag = 0;
    int num1 = 0;
    int num2 = 0;
    mouseinit();
    welcome_screen();
    while(1)
    {   
        newmouse(&MouseX,&MouseY,&press);
        put_title(&colorset);
        if(mouse_press(30,360,290,460)==2)
        {   
            MouseS = 1;
            flag = 1;
            num1 = 1;
            welcome_buttons_light(flag);
        }
        else if(mouse_press(350,360,610,460)==2)
        {
            MouseS = 1;
            flag = 2;
            num2 = 2;
            welcome_buttons_light(flag);
        }
        else
        {
            MouseS = 0;
            flag = 0;
        }
        

        if(mouse_press(30,360,290,460)==1)
        {
            return 1;
        }
        else if(mouse_press(350,360,610,460)==1)
        {
            return 8;
        }

        if(flag!=1&&num1==1)
        {
            welcome_buttons_recovery(num1);
            num1 = 0;
        }
        else if(flag!=2&&num2==2)
        {
            welcome_buttons_recovery(num2);
            num2 = 0;
        }
    }
}

void welcome_buttons_light(int flag)
{
    if(flag==1)
    {
        printbox(30,360,290,460,YELLOW,1,5,5);
        setcolor(WHITE);
        settextstyle( DEFAULT_FONT , HORIZ_DIR , 2);
        outtextxy( 113 , 405 , "LOG_IN" );
    }
    else if(flag==2)
    {
        printbox(350,360,610,460,YELLOW,1,5,5);
        setcolor(WHITE);
        settextstyle( DEFAULT_FONT , HORIZ_DIR , 2);
        outtextxy( 450 , 405 , "QUIT" );
    }
}

void welcome_buttons_recovery(int num)
{
    if(num == 1)
    {
        printbox(30,360,290,460,WHITE,1,5,5);
        setcolor(DARKGRAY);
        settextstyle( DEFAULT_FONT , HORIZ_DIR , 2);
        outtextxy( 113 , 405 , "LOG_IN" );
    }
    else if(num == 2)
    {
        printbox(350,360,610,460,WHITE,1,5,5);
        setcolor(DARKGRAY);
        settextstyle( DEFAULT_FONT , HORIZ_DIR , 2);
        outtextxy( 450 , 405 , "QUIT" );
    }
}
