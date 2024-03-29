#include "main.h"
#include "public.h"

void main()
{
    int gdriver = VGA;
    int gmode = VGAHI;
    int page = HOME;
    INFO *temp;
    char *now_field;
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

            case SIGNUP :
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
            
            case DRAW_FIELD:
               page = draw_field_page(temp->name,now_field);
               break;

            case PLANT :
               page = plant_page(temp->name,now_field);
               break;
            
            case HOUSE :
               page = house_page(temp->name,now_field);
               break;
            
			default :
				exit(1);
        }
    }
      getch();
      closegraph();
}
