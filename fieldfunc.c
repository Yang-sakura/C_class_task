#include "fieldfunc.h"
#include "public.h"

void fieldfunc_screen()
{
    int i;
    printline(100,0,1,480,1,DARKGRAY,5,5);
    setcolor(DARKGRAY);
    settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
    outtextxy(110,10,"NAME:");

    setlinestyle(SOLID_LINE,0,THICK_WIDTH);
    line(110,50,110,470);
    line(110,470,630,470);
    line(110,50,108,60);
    line(110,50,112,60);
    line(630,470,620,468);
    line(630,470,620,472);
    setlinestyle(DOTTED_LINE,0,NORM_WIDTH);
    for(i=0;i<26;i++)
    {
        line(110+i*20,50,110+i*20,470);
    }
    for(i=0;i<21;i++)
    {
        line(110,470-i*20,630,470-i*20);
    }

    back_button(PAINT);
}

void fieldfunc_page()
{
    int record[21][26];
    int flag = 0;
    int (*precord)[26] = record;
    int i;
    FILE *fp;
    clrmous(MouseX,MouseY);
    cleardevice();
    fieldfunc_screen();
    while(1)
    {
        newmouse(&MouseX,&MouseY,&press);
        if(mouse_press(110,50,630,470)==1)
        {
            clrmous(MouseX,MouseY);
            setfillstyle(SOLID_FILL,DARKGRAY);
            bar(110+20*((MouseX - 110)/20),470-20*((470-MouseY)/20+1),110+20*((MouseX - 110)/20)+20,470-20*((470-MouseY)/20+1)+20);
            record[(MouseX - 110)/20][(470-MouseY)/20] = 1;
            

        }
        if((fp = fopen("c:\\code\\source\\file\\field.dat","wb"))!=NULL)
            {
                for(i=0;i<21;i++)
                {
                    fwrite(precord[i],sizeof(int),26,fp);
                }
            }
            fclose(fp);

        if(mouse_press(595,5,630,40)==1)
        exit(1);
        
        
        
        
    }
}

