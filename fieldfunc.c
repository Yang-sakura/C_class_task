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

    put_pencil(10,50,DARKGRAY,DARKGRAY,LIGHTGRAY,5);
}

void fieldfunc_page(char *name)
{
    int record[21][26];
    int mode = 0;
    int flag = 0;
    int (*precord)[26] = record;
    int i;
    FILE *fp;
    char string[80] = "c:\\DATA\\";
    char filename[80];
    strcat(string,name);
    strcat(string,"\\FIELD");
    if(access(string,0)==-1)
    {
        if(mkdir(string)!=0)
        {
            perror("ERROR IN BUILDING THE FIELD PACKAGE!");
            delay(2000);
            exit(1);
        }
    }



    clrmous(MouseX,MouseY);
    cleardevice();
    fieldfunc_screen();
    mouseinit();
    while(1)
    {
        newmouse(&MouseX,&MouseY,&press);

        if(mouse_press(10,50,75,115)==2)         //铅笔不点击
        {
            if(flag!=1)
            {
                MouseS = 1;
                flag = 1;
                clrmous(MouseX,MouseY);
                put_pencil(10,50,DARKGRAY,BROWN,LIGHTGRAY,5);
            }
        }
        else if(mouse_press(10,50,75,115)==1)     //mode1代表画图模式
        {
            mode = 1;
            MouseS = mode+3;
            clrmous(MouseX,MouseY);
            put_pencil(10,50,DARKGRAY,BROWN,LIGHTGRAY,5);
            printbox(5,350,80,470,DARKGRAY,1,5,5);
            settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
            outtextxy(400,10,"OK");
        
        }

        if(mouse_press(595,5,630,40)==1)
        exit(1);
        
        if(mode ==1)
        {
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
                else if(mouse_press(5,350,80,470)==1)
                {
                    MouseS = 1;
                    mode = 0;
                    break;
                }
                if((fp = fopen("c:\\DATA\\yang\\FIELD\\field.dat","wb"))!=NULL)
                {
                    for(i=0;i<21;i++)
                    {
                        fwrite(precord[i],sizeof(int),26,fp);
                    }
                }
                fclose(fp);
            }
        }
         
    }
}
