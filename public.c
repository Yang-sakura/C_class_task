#include "public.h"

/* ************************
function:printline
description:画像素风线函数
create:24/1/31
input:int x,int y,int len,int n,int flag,int COLOR,int wid,int gap
      x,y是第一个小方块左上角起始点，flag=0横着向右，flag=1竖着向左，len记录每个块有多长，n记录有多少格
      wid每格宽度，每格长度为len倍的宽度,gap为每格之间间隙
output:void
************************* */
void printline(int x,int y,int len,int n,int flag,int COLOR,int wid,int gap)
{
   //wid每格宽度，每格长度为len倍的宽度,gap为每格之间间隙
   int t;
   setfillstyle(SOLID_FILL,COLOR);
   while(n)
   {
      t=len;
      while(t){
         bar(x,y,x+wid,y+wid);
         if(flag==0) x+=wid;
         else y+=wid;
         t--;
      }
      n--;
      if(flag==0) x+=gap;
      else y+=gap;
   }

}

void printbox(int x1,int y1,int x2,int y2,int COLOR,int len,int wid,int gap)
{
   int ver,hor,sum,remain_ver,remain_hor;//vertical,horizontal
   sum=wid*len+gap;
   hor=abs(x2-x1)/sum;
   remain_hor=abs(x2-x1)-(hor*sum-gap);
   if(remain_hor<wid*len) remain_hor+=wid*len;
   ver=abs(y2-y1)/sum;
   remain_ver=abs(y2-y1)-(ver*sum-gap);
   if(remain_ver<wid*len) remain_ver+=wid*len;
   printline(x1+remain_hor/2,y1    ,len,hor,0,COLOR,wid,gap);
   printline(x1+remain_hor/2,y2-wid,len,hor,0,COLOR,wid,gap);
   printline(x1,y1+remain_ver/2,len,ver,1,COLOR,wid,gap);
   printline(x2-wid,y1+remain_ver/2,len,ver,1,COLOR,wid,gap);

}

void back_button(int flag)
{
    if(flag==PAINT)
    {
        printbox(595,5,630,40,DARKGRAY,1,5,4);
        setcolor(DARKGRAY);
        settextstyle(DEFAULT_FONT   , HORIZ_DIR,3);
        outtextxy(602,10, "x");
    }
    else if(flag==LIGHT)
    {
        printbox(595,5,630,40,BLUE,1,5,4);
        setcolor(BLUE);
        settextstyle(DEFAULT_FONT   , HORIZ_DIR,3);
        outtextxy(602,10, "x");
    }
    else if(flag==RECOVER)
    {
        back_button(PAINT);
    }
    else {
        printf("flag error!");
        delay(3000);
        exit(1);
    }
}
