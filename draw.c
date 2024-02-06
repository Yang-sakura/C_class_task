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

