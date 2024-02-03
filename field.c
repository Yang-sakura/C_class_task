#include "public.h"
#include "field.h"
#include "main.h"

void field_screen()
{
    int i;
    printline(100,0,1,480,1,DARKGRAY,5,5);
    setcolor(DARKGRAY);
    settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
    outtextxy(110,10,"NAME:");
    settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
    outtextxy(3,370,"SQUARE");

    setlinestyle(SOLID_LINE,0,THICK_WIDTH);
    line(110,50,110,470);
    line(110,470,630,470);
    line(110,50,108,60);
    line(110,50,112,60);
    line(630,470,620,468);
    line(630,470,620,472);
    setlinestyle(DOTTED_LINE,0,NORM_WIDTH);
    for(i=0;i<26;i++)
    {
        line(110+i*20,50,110+i*20,470);
    }
    for(i=0;i<21;i++)
    {
        line(110,470-i*20,630,470-i*20);
    }


    back_button(PAINT);

    put_field(25,50,LIGHTGRAY,DARKGRAY,5);
    put_sprout(25,150,DARKGRAY,5);
    put_house(25,250,DARKGRAY,LIGHTGRAY,5);
}


void put_sprout(int x,int y,int COLOR,int pix)
{
    printline(x,y,1,2,0,COLOR,pix,0);
    printline(x+7*pix,y,1,2,0,COLOR,pix,0);
    printline(x,y+pix,1,3,0,COLOR,pix,0);
    printline(x+6*pix,y+pix,1,3,0,COLOR,pix,0);
    printline(x,y+2*pix,1,4,0,COLOR,pix,0);
    printline(x+5*pix,y+2*pix,1,4,0,COLOR,pix,0);
    printline(x+pix,y+3*pix,1,7,0,COLOR,pix,0);
    printline(x+2*pix,y+4*pix,1,5,0,COLOR,pix,0);
    printline(x+4*pix,y+5*pix,1,4,1,COLOR,pix,0);
}

void put_field(int x,int y,int LIGHTCOLOR,int DARKCOLOR,int pix)
{
    setfillstyle(SOLID_FILL,LIGHTCOLOR);
    bar(x,y,x+9*pix,y+9*pix);
    printline(x,y,1,9,0,DARKCOLOR,pix,0);
    printline(x,y+4*pix,1,9,0,DARKCOLOR,pix,0);
    printline(x,y+8*pix,1,9,0,DARKCOLOR,pix,0);
    printline(x,y,1,9,1,DARKCOLOR,pix,0);
    printline(x+4*pix,y,1,9,1,DARKCOLOR,pix,0);
    printline(x+8*pix,y,1,9,1,DARKCOLOR,pix,0);
}

void put_house(int x,int y,int DARKCOLOR,int LIGHTCOLOR,int pix)
{
    printline(x+4*pix,y,1,1,0,DARKCOLOR,pix,0);
    printline(x+3*pix,y+pix,1,3,0,DARKCOLOR,pix,0);
    printline(x+2*pix,y+2*pix,1,5,0,DARKCOLOR,pix,0);
    printline(x+pix,y+3*pix,1,7,0,DARKCOLOR,pix,0);
    printline(x,y+4*pix,1,9,0,DARKCOLOR,pix,0);
    setfillstyle(SOLID_FILL,DARKCOLOR);
    bar(x+pix,y+5*pix,x+8*pix,y+9*pix);
    setfillstyle(SOLID_FILL,LIGHTCOLOR);
    bar(x+2*pix,y+5*pix,x+4*pix,y+7*pix);
    printline(x+6*pix,y+7*pix,1,2,1,LIGHTCOLOR,pix,0);

}


int field_page()
{
    int flag = 0;
    int num[5];
    setbkcolor(WHITE);
    field_screen();
    mouseinit();
    
    while(1)
    {
        newmouse(&MouseX,&MouseY,&press);

        if(mouse_press(25,50,70,95)==2)
        {
            if(flag!=1)
            {
                clrmous(MouseX,MouseY);
                put_field(25,50,GREEN,BROWN,5);
                MouseS = 1;
                flag = 1;
                num[1]=1;
            }
        }
        else if(mouse_press(25,150,70,195)==2)
        {
            if(flag!=2)
            {
                clrmous(MouseX,MouseY);
                put_sprout(25,150,GREEN,5);
                MouseS = 1;
                flag = 2;
                num[2]=1;
            }
        }
        else if(mouse_press(25,250,70,295)==2)
        {
            if(flag!=3)
            {
                clrmous(MouseX,MouseY);
                put_house(25,250,BROWN,CYAN,5);
                MouseS = 1;
                flag = 3;
                num[3]=1;
            }
        }
        else if(mouse_press(595,5,630,40)==2)
        {
            if(flag!=4)
            {
                back_button(LIGHT);
                MouseS = 1;
                flag = 4;
                num[4]=1;
            }
        }
        else
        {
            MouseS = 0;
            flag = 0;
        }

        if(mouse_press(25,50,70,95)==1)
        {
            fieldfunc_page();
        }
        else if(mouse_press(25,150,70,195)==1)
        {
            ;
        }
        else if(mouse_press(25,250,70,295)==1)
        {
            ;
        }
        else if(mouse_press(595,5,630,40)==1)
        {
            cleardevice();
            return HOME;
        }

        if(flag!=1&&num[1]==1)
        {
            clrmous(MouseX,MouseY);
            put_field(25,50,LIGHTGRAY,DARKGRAY,5);
            num[1]=0;
        }
        else if(flag!=2&&num[2]==1)
        {
            clrmous(MouseX,MouseY);
            put_sprout(25,150,LIGHTGRAY,5);
            num[2]=0;
        }
        else if(flag!=3&&num[3]==1)
        {
            clrmous(MouseX,MouseY);
            put_house(25,250,DARKGRAY,LIGHTGRAY,5);
            num[3]=0;
        }
        else if(flag!=4&&num[4]==1)
        {
            back_button(RECOVER);
            num[4]=0;
        }
    }
}
