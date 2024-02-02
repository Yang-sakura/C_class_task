#include "main.h"
#include "public.h"

void main()
{
    int gdriver = VGA;
    int gmode = VGAHI;
    int page = 0;
    initgraph(&gdriver,&gmode,"c:\\borlandc\\bgi");

    while(1)
    {
        switch(page)
        {
            case WELCOME :
               page = welcome_page(); //0
               break;

            case LOGIN :
               page = login_page();//1
               break;

            case SIGH_UP :
               page = signup_page();//2
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
