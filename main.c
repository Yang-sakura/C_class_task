#include "main.h"
#include "public.h"

void main()
{
    int gdriver = VGA;
    int gmode = VGAHI;
    int page = 0;
    INFO *temp;
    initgraph(&gdriver,&gmode,"c:\\borlandc\\bgi");

    while(1)
    {
        switch(page)
        {
            case WELCOME :
               page = welcome_page(); //0
               break;

            case LOGIN :
               page = login_page(temp);//1
               break;

            case SIGHUP :
               page = signup_page();//2
               break;

            case HOME :
               page = home_page(temp);
               break;

            case FIELD :
               page = field_page(temp);
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
