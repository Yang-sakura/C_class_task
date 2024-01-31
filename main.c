#include "main.h"
#include "public.h"

int wid=5;
int gap=5;

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

void printline(int x,int y,int len,int flag,int COLOR)//x,y是第一个小方块左上角起始点，flag=0横着向右，flag=1竖着向左，len记录画多少个
{
   //wid每格长度,gap小方格之间间隙
    setfillstyle(SOLID_FILL,COLOR);
    while(len)
    {
        bar(x,y,x+wid,y+wid);
        len--;
        if(flag==0){
            x+=wid;
            x+=gap;
        }
        else{
            y+=wid;
            y+=gap;
        }
    }

}
