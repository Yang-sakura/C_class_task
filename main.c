#include "main.h"
#include "public.h"

void main()
{
    int gdriver = VGA;
    int gmode = VGAHI;
    int page = LOGIN;
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
               page = field_page(temp,now_field);
               break;

            case DRONE :
               page = drone_page(temp->name,drone->name,drone);
               break;

            case PESTICIDE :
               page = HOME;
               break;

            case DETECTOR :
               page = detect_page(temp->name,now_field);
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

	    case DRONE_LIST:
               page = drone_list_page(temp->name,drone);
               break;
			default :
				exit(1);
        }
    }
      getch();
      closegraph();
}
