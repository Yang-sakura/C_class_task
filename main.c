#include "main.h"
#include "public.h"

void main()
{
    int gdriver = VGA;
    int gmode = VGAHI;
    int page = 1;
    initgraph(&gdriver,&gmode,"c:\\borlandc\\bgi");

    while(1)
    {
        switch(page)
        {
            case WELCOME :
               page = 1; 
               break;

            case LOGIN :
               page = login_page();
               break;

            case SIGH_UP :
               page = 1;
               break;

            case HOME :
               page = 1;
               break;

            case FIELD :
               page = 1;
               break;

            case DRONE :
               page = 1;
               break;

            case PESTICIDE :
               page = 1;
               break;

            case DETECTOR :
               page = 1;
               break; 
			default :
				exit(1);
        }
    }
      getch();
      closegraph();
}

/* ************************
function:printline
description:画像素风线函数
create:24/1/31
input:int x,int y,int len,int n,int flag,int COLOR
      x,y是第一个小方块左上角起始点，flag=0横着向右，flag=1竖着向左，len记录每个块有多长，n记录有多少格
output:void
************************* */
void printline(int x,int y,int len,int n,int flag,int COLOR)
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
