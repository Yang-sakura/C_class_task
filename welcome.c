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

void drone(void)
{
    int i;
    int x0 = 320,y0 = 220;
    setcolor(WHITE);
    setfillstyle(SOLID_FILL,WHITE);
    bar(270,170,370,180);
    bar(270,170,280,270);
    bar(280,260,370,270);
    bar(360,170,370,270);
    settextstyle( DEFAULT_FONT , HORIZ_DIR , 5);
    outtextxy( 303 , 200 , "C");

    for(i=45;i<=80;i+=5)
    {
        bar(x0-i,y0-i,x0-(i-10),y0-(i-10));
        bar(x0+(i-10),y0-i,x0+i,y0-(i-10));
        bar(x0-i,y0+(i-10),x0-(i-10),y0+i);
        bar(x0+(i-10),y0+(i-10),x0+i,y0+i);
    }
    line(0,340,640,340);
    line(0,100,640,100);
}

void drone_wing(int* drone_flag,int x,int y)
{      
    if((*drone_flag)==0)
    {
        printline(x-25,y-5,1,10,0,LIGHTGRAY,5,0);
        printline(x-30,y,1,5,0,LIGHTGRAY,5,0);
        printline(x-35,y+5,1,3,0,LIGHTGRAY,5,0);
        printline(x-40,y+10,1,3,0,LIGHTGRAY,5,0);
        printline(x-40,y+15,1,2,0,LIGHTGRAY,5,0);
        printline(x-40,y+20,1,1,0,LIGHTGRAY,5,0);
        printline(x+5,y-10,1,5,0,LIGHTGRAY,5,0);
        printline(x+15,y-15,1,3,0,LIGHTGRAY,5,0);
        printline(x+20,y-20,1,2,0,LIGHTGRAY,5,0);
        printline(x+25,y-25,1,1,0,LIGHTGRAY,5,0);
        (*drone_flag)=1;
        return;
    }
    else if((*drone_flag)==1)
    {
        printline(x-15,y-5,1,3,0,LIGHTGRAY,5,0);
        printline(x-20,y,1,4,0,LIGHTGRAY,5,0);
        printline(x-20,y+5,1,3,0,LIGHTGRAY,5,0);
        printline(x-25,y+10,1,3,0,LIGHTGRAY,5,0);
        printline(x-25,y+15,1,2,0,LIGHTGRAY,5,0);
        printline(x-30,y+20,1,2,0,LIGHTGRAY,5,0);
        printline(x-30,y+20,1,1,0,LIGHTGRAY,5,0);
        printline(x,y-10,1,3,0,LIGHTGRAY,5,0);
        printline(x+5,y-15,1,4,0,LIGHTGRAY,5,0);
        printline(x+10,y-20,1,3,0,LIGHTGRAY,5,0);
        printline(x+15,y-25,1,2,0,LIGHTGRAY,5,0);
        printline(x+20,y-30,1,1,0,LIGHTGRAY,5,0);
        (*drone_flag)=2;
        return;       
    }
    else if((*drone_flag)==2)
    {
        printline(x-5,y-5,1,1,0,LIGHTGRAY,5,0);
        printline(x-10,y-10,1,3,0,LIGHTGRAY,5,0);
        printline(x-15,y-15,1,4,0,LIGHTGRAY,5,0);
        printline(x-20,y-20,1,4,0,LIGHTGRAY,5,0);
        printline(x-30,y-25,1,5,0,LIGHTGRAY,5,0);
        printline(x,y,1,2,0,LIGHTGRAY,5,0);
        printline(x,y+5,1,3,0,LIGHTGRAY,5,0);
        printline(x+5,y+10,1,3,0,LIGHTGRAY,5,0);
        printline(x+10,y+15,1,4,0,LIGHTGRAY,5,0);
        printline(x+15,y+20,1,5,0,LIGHTGRAY,5,0);
        (*drone_flag)=0;
        return;
    }
}

int welcome_page(void)
{   
    int colorset = 1;
    int flag = 0;
    int num1 = 0;
    int num2 = 0;
    int drone_flag = 2;
    int time = 0;
    mouseinit();
    setbkcolor(BLACK);
    welcome_screen();
    drone();
    while(1)
    {   
        if(time%250==0)
        {
            setfillstyle(SOLID_FILL,BLACK);
            bar(0,100,640,340);
            drone();
            drone_wing(&drone_flag,240,140);
            drone_wing(&drone_flag,400,140);
            drone_wing(&drone_flag,240,300);
            drone_wing(&drone_flag,400,300);
            newmouse(&MouseX,&MouseY,&press);
        }

        time++;
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
