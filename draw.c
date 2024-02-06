#include "public.h"
#include "draw.h"

void put_pencil(int x,int y,int COLOR1,int COLOR2,int COLOR3,int pix)
{
    printline(x,y,1,4,0,COLOR1,pix,0);
    printline(x,y+pix,1,3,0,COLOR1,pix,0);
    printline(x,y+2*pix,1,2,0,COLOR1,pix,0);
    printline(x,y+3*pix,1,1,0,COLOR1,pix,0);
    printline(x+3*pix,y+pix,1,2,0,COLOR2,pix,0);
    printline(x+2*pix,y+2*pix,1,4,0,COLOR2,pix,0);
    printline(x+pix,y+3*pix,1,6,0,COLOR2,pix,0);
    printline(x+pix,y+4*pix,1,7,0,COLOR2,pix,0);
    printline(x+2*pix,y+5*pix,1,7,0,COLOR2,pix,0);
    printline(x+3*pix,y+6*pix,1,7,0,COLOR2,pix,0);
    printline(x+4*pix,y+7*pix,1,7,0,COLOR2,pix,0);
    printline(x+5*pix,y+8*pix,1,6,0,COLOR2,pix,0);
    printline(x+6*pix,y+9*pix,1,4,0,COLOR2,pix,0);
    printline(x+7*pix,y+10*pix,1,2,0,COLOR2,pix,0);
    printline(x+11*pix,y+8*pix,1,1,0,COLOR3,pix,0);
    printline(x+10*pix,y+9*pix,1,3,0,COLOR3,pix,0);
    printline(x+9*pix,y+10*pix,1,4,0,COLOR3,pix,0);
    printline(x+8*pix,y+11*pix,1,4,0,COLOR3,pix,0);
    printline(x+9*pix,y+12*pix,1,2,0,COLOR3,pix,0);

    
}

void put_rubber(int x,int y,int COLOR,int pix)
{
    printline(x+4*pix,y,1,1,0,COLOR,pix,0);
    printline(x+3*pix,y+pix,1,3,0,COLOR,pix,0);
    printline(x+2*pix,y+2*pix,1,5,0,COLOR,pix,0);
    printline(x+pix,y+3*pix,1,7,0,COLOR,pix,0);
    printline(x,y+4*pix,1,9,0,COLOR,pix,0);
    printline(x+pix,y+5*pix,1,9,0,COLOR,pix,0);
    printline(x+2*pix,y+6*pix,1,9,0,COLOR,pix,0);
    printline(x+3*pix,y+7*pix,1,9,0,COLOR,pix,0);
    printline(x+4*pix,y+8*pix,1,9,0,COLOR,pix,0);
    printline(x+5*pix,y+9*pix,1,7,0,COLOR,pix,0);
    printline(x+6*pix,y+10*pix,1,5,0,COLOR,pix,0);
    printline(x+7*pix,y+11*pix,1,3,0,COLOR,pix,0);
    printline(x+8*pix,y+12*pix,1,1,0,COLOR,pix,0);    
}

void put_file(int x,int y,int DARKCOLOR,int LIGHTCOLOR,int pix)
{
    int i;
    setfillstyle(SOLID_FILL,DARKCOLOR);
    bar(x,y,x+13*pix,y+10*pix);

    setfillstyle(SOLID_FILL,LIGHTCOLOR);
    bar(x+pix,y+pix,x+12*pix,y+9*pix);

    setfillstyle(SOLID_FILL,DARKCOLOR);
    for(i=0;i<=6;i++)
        bar(x+i*pix,y+i*pix,x+(i+1)*pix,y+(i+1)*pix);
    for(i=0;i<=6;i++)
        bar(x+(12-i)*pix,y+i*pix,x+(13-i)*pix,y+(i+1)*pix);
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

void put_shovel(int x,int y)
{
    setcolor(DARKGRAY);
    setlinestyle(SOLID_LINE,0,NORM_WIDTH);
    line(x-1,y-2,x+2,y-2);
    line(x-1,y-1,x+3,y-1);
    line(x-1,y,x+4,y);
    line(x-1,y+1,x+3,y+1);
    line(x,y+2,x+2,y+2);
    putpixel(x+1,y+3,DARKGRAY);

    setcolor(BROWN);
    line(x+3,y+2,x+4,y+2);

    line(x+3,y+3,x+5,y+3);//x-1 y-2
    line(x+4,y+4,x+6,y+4);
    line(x+5,y+5,x+7,y+5);
    line(x+6,y+6,x+8,y+6);
    line(x+7,y+7,x+9,y+7);

    line(x+8,y+8,x+11,y+8);
    line(x+9,y+9,x+10,y+9);
    line(x+8,y+10,x+9,y+10);
    putpixel(x+11,y+7,BROWN);

}

