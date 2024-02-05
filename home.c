#include "home.h"
#include "public.h"
#include "main.h"

void home_screen(void)
{   
    printbox(100,90,310,190,DARKGRAY,1,5,4);
    printbox(330,90,540,190,DARKGRAY,1,5,4);
    printbox(100,230,310,330,DARKGRAY,1,5,4);
    printbox(330,230,540,330,DARKGRAY,1,5,4);
    printbox(100,370,310,470,DARKGRAY,1,5,4);
    printbox(330,370,540,470,DARKGRAY,1,5,4);

    setcolor(BLUE);
    settextstyle(DEFAULT_FONT , HORIZ_DIR,3);
    outtextxy(145,130, "FIELD");
    outtextxy(375,130, "DRONE");
    outtextxy(160,270, "PEST");
    outtextxy(365,270, "DETECT");
    outtextxy(135,410, "README");
    outtextxy(390,410, "QUIT");

    setcolor(DARKGRAY);
    settextstyle(DEFAULT_FONT,HORIZ_DIR,6);
    outtextxy(120,10,"HOMEPAGE");

    printbox(595,5,630,40,DARKGRAY,1,5,4);//右上角退出
    setcolor(DARKGRAY);
    settextstyle(DEFAULT_FONT , HORIZ_DIR,3);
    outtextxy(602,10, "x");
}


int home_page()
{
    int flag = 0;
    int num[8] = {0,0,0,0,0,0,0,0};
    cleardevice();
    setbkcolor(WHITE);
    mouseinit();
    home_screen();
    while(1)
    {   
        newmouse(&MouseX,&MouseY,&press);
        if(mouse_press(100,90,310,190)==2)
        {   
            if(flag!=1)
            {
                MouseS = 1;
                flag = 1;
                num[1] = 1;
                home_button_light(flag);
            }
        }
        else if(mouse_press(330,90,540,190)==2)
        {   
            if(flag!=2)
            {
                MouseS = 1;
                flag = 2;
                num[2] = 2;
                home_button_light(flag);
            }
        }
        else if(mouse_press(100,230,310,330)==2)
        {   
            if(flag!=3)
            {
                MouseS = 1;
                flag = 3;
                num[3] = 3;
                home_button_light(flag);
            }
        }
        else if(mouse_press(330,230,540,330)==2)
        {   
            if(flag!=4)
            {
                MouseS = 1;
                flag = 4;
                num[4] = 4;
                home_button_light(flag);
            }
        }
        else if(mouse_press(100,370,310,470)==2)
        {   
            if(flag!=5)
            {
            MouseS = 1;
            flag = 5;
            num[5] = 5;
            home_button_light(flag);
            }
        }
        else if(mouse_press(330,370,540,470)==2)
        {   
            if(flag!=6)
            {
                MouseS = 1;
                flag = 6;
                num[6] = 6;
                home_button_light(flag);
            }
        }
        else if(mouse_press(595,5,630,40)==2)
        {
            if(flag!=7)
            {
                MouseS = 1;
                flag = 7;
                num[7] = 7;
                back_button(LIGHT);
            }
        }
        else
        {
            MouseS = 0;
            flag = 0;
        }

        if(mouse_press(100,90,310,190)==1)
        {   
            cleardevice();
            return 4;
        }
        else if(mouse_press(330,90,540,190)==1)
        {   
            cleardevice();
            return 5;
        }
        else if(mouse_press(100,230,310,330)==1)
        {   
            cleardevice();
            return 6;
        }
        else if(mouse_press(330,230,540,330)==1)
        {   
            cleardevice();
            return 7;
        }
        else if(mouse_press(100,370,310,470)==1)
        {   
            cleardevice();
            return 9;
        }
        else if(mouse_press(330,370,540,470)==1)
        {   
            cleardevice();
            return 8;
        }
        else if(mouse_press(595,5,630,40)==1)
        {   
            cleardevice();
            return 0;
        }

        if(flag!=1&&num[1]==1)
        {
            home_button_recovery(num[1]);
            num[1]=0;
        }
        else if(flag!=2&&num[2]==2)
        {
            home_button_recovery(num[2]);
            num[2]=0;
        }
        else if(flag!=3&&num[3]==3)
        {
            home_button_recovery(num[3]);
            num[3]=0;
        }
        else if(flag!=4&&num[4]==4)
        {
            home_button_recovery(num[4]);
            num[4]=0;
        }
        else if(flag!=5&&num[5]==5)
        {
            home_button_recovery(num[5]);
            num[5]=0;
        }
        else if(flag!=6&&num[6]==6)
        {
            home_button_recovery(num[6]);
            num[6]=0;
        }
        else if(flag!=7&&num[7]==7)
        {
            back_button(RECOVER);
            num[7]=0;
        }
        

    }
}

void home_button_light(int flag)
{
    clrmous(MouseX,MouseY);
    if(flag==1)
    {
        printbox(100,90,310,190,YELLOW,1,5,4);
        setcolor(CYAN);
        settextstyle( DEFAULT_FONT , HORIZ_DIR , 3);
        outtextxy(145,130, "FIELD");
    }
    else if(flag==2)
    {
        printbox(330,90,540,190,YELLOW,1,5,4);
        setcolor(CYAN);
        settextstyle( DEFAULT_FONT , HORIZ_DIR , 3);
        outtextxy(375,130, "DRONE");
    }
    else if(flag==3)
    {
        printbox(100,230,310,330,YELLOW,1,5,4);
        setcolor(CYAN);
        settextstyle( DEFAULT_FONT , HORIZ_DIR , 3);
        outtextxy(160,270, "PEST");
    }
    else if(flag==4)
    {
        printbox(330,230,540,330,YELLOW,1,5,4);
        setcolor(CYAN);
        settextstyle( DEFAULT_FONT , HORIZ_DIR , 3);
        outtextxy(365,270, "DETECT");
    }
    else if(flag==5)
    {
        printbox(100,370,310,470,YELLOW,1,5,4);
        setcolor(CYAN);
        settextstyle( DEFAULT_FONT , HORIZ_DIR , 3);
        outtextxy(135,410, "README");
    }
    else if(flag==6)
    {
        printbox(330,370,540,470,YELLOW,1,5,4);
        setcolor(CYAN);
        settextstyle( DEFAULT_FONT , HORIZ_DIR , 3);
        outtextxy(390,410, "QUIT");
    }

}

void home_button_recovery(int num)
{
    clrmous(MouseX,MouseY);
    printbox(100,90,310,190,DARKGRAY,1,5,4);
    printbox(330,90,540,190,DARKGRAY,1,5,4);
    printbox(100,230,310,330,DARKGRAY,1,5,4);
    printbox(330,230,540,330,DARKGRAY,1,5,4);
    printbox(100,370,310,470,DARKGRAY,1,5,4);
    printbox(330,370,540,470,DARKGRAY,1,5,4);

    setcolor(BLUE);
    settextstyle(DEFAULT_FONT , HORIZ_DIR,3);
    outtextxy(145,130, "FIELD");
    outtextxy(375,130, "DRONE");
    outtextxy(160,270, "PEST");
    outtextxy(365,270, "DETECT");
    outtextxy(135,410, "README");
    outtextxy(390,410, "QUIT");
    if(num == 1)
    {
        printbox(100,90,310,190,DARKGRAY,1,5,4);
        setcolor(BLUE);
        settextstyle(DEFAULT_FONT , HORIZ_DIR,3);
        outtextxy(145,130, "FIELD");
    }
    else if(num == 2)
    {
        printbox(330,90,540,190,DARKGRAY,1,5,4);
        setcolor(BLUE);
        settextstyle(DEFAULT_FONT , HORIZ_DIR,3);
        outtextxy(375,130, "DRONE");
    }
    else if(num == 3)
    {
        printbox(100,230,310,330,DARKGRAY,1,5,4);
        setcolor(BLUE);
        settextstyle(DEFAULT_FONT , HORIZ_DIR,3);
        outtextxy(160,270, "PEST");;
    }
    else if(num == 4)
    {
        printbox(330,230,540,330,DARKGRAY,1,5,4);
        setcolor(BLUE);
        settextstyle(DEFAULT_FONT , HORIZ_DIR,3);
        outtextxy(365,270, "DETECT");
    }
    else if(num == 5)
    {
        printbox(100,370,310,470,DARKGRAY,1,5,4);
        setcolor(BLUE);
        settextstyle(DEFAULT_FONT , HORIZ_DIR,3);
        outtextxy(135,410, "README");
    }
    else if(num == 6)
    {
        printbox(330,370,540,470,DARKGRAY,1,5,4);
        setcolor(BLUE);
        settextstyle(DEFAULT_FONT , HORIZ_DIR,3);
        outtextxy(390,410, "QUIT");
    }
}
