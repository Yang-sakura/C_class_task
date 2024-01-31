#include "main.h"

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
            page = 1; 
            break;

            case SIGH_IN :
            page = 1;
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
        }
        getch();
        closegraph();
    }

    getch();
    closegraph();

}
