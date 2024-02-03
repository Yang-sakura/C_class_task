#include "fieldfunc.h"
#include "public.h"

void fieldfunc_screen()
{
    printline(100,0,1,480,1,DARKGRAY,5,5);
    setcolor(DARKGRAY);
    settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
    outtextxy(110,10,"NAME:");

    setlinestyle(SOLID_LINE,0,THICK_WIDTH);
    line(110,50,110,470);
    line(110,470,630,470);
    line(110,50,108,60);
    line(110,50,112,60);
    line(630,470,620,468);
    line(630,470,620,472);
    setlinestyle(DOTTED_LINE,0,NORM_WIDTH);
    line(240,50,240,470);
    line(370,50,370,470);
    line(500,50,500,470);
    line(630,50,630,470);
    line(110,340,630,340);
    line(110,210,630,210);
    line(110,80,630,80);

    back_button(PAINT);
}

void fieldfunc_page()
{
    int record[105][85];
    clrmous(MouseX,MouseY);
    cleardevice();
    fieldfunc_screen();
    while(1)
    {
        newmouse(&MouseX,&MouseY,&press);
        record_field(MouseX,MouseY,record);
    }
}

void record_field(int MouseX,int MouseY,int **record)
{
    int cal_x,cal_y;      //cal_x,cal_y代表直角坐标系中的坐标
    int pix_x,pix_y;      //pix_x,pix_y代表像素坐标系中的坐标

    cal_x = MouseX - 110;
    cal_y = 470 - MouseY;
    pix_x = (cal_x/20);
    pix_y = (cal_y/20);
    record[pix_x][pix_y] = 1;
    setfillstyle(SOLID_FILL,BLACK);
    bar(pix_x,pix_y,pix_x+20,pix_y+20);
}
