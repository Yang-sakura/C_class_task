#include "public.h"
#include "dronefunc.h"

void dronefunc_screen()
{
    back_button(PAINT);
    put_drone2(12,140,DARKGRAY,LIGHTGRAY,15);
    printbox(350,60,570,120,DARKGRAY,1,5,5);
    printbox(350,160,570,220,DARKGRAY,1,5,5);
    printbox(350,260,570,320,DARKGRAY,1,5,5);
    printbox(350,360,570,420,DARKGRAY,1,5,5);
    settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
    outtextxy(220,80,"NAME:");
    outtextxy(220,180,"TYPE:");
    outtextxy(220,280,"WAY :");
    outtextxy(220,380,"TIME:");
    printbox(400,430,520,470,DARKGRAY,1,5,5); 
    outtextxy(440,440,"OK");

}

int drone_list_page(char *username,DRONEINFO *nowdrone)
{
    int flag;
    int num[3];
    char time[10];
    FILE *fp;
    char string[80] = "c:\\DATA\\";
    strcat(string,username);
    strcat(string,"\\DRONE\\");
    strcat(string,nowdrone->name);
    strcat(string,".dat");
    setcolor(DARKGRAY);
    settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
    outtextxy(360,75,nowdrone->name);

    memset(time,0,sizeof(time));
    
    dronefunc_screen();
    setcolor(DARKGRAY);
    settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
    outtextxy(360,175,nowdrone->type);
    itoa(nowdrone->flying_time,time,10);
    outtextxy(360,375,time);

    mouseinit();
    while(1)
    {
        newmouse(&MouseX,&MouseY,&press);

        if(mouse_press(350,160,570,220)==2)           //型号
        {
            if(flag!=1)
            {
                MouseS = 2;
                flag = 1;
            }
        }
        else if(mouse_press(350,160,570,220)==1)
        {
            temp_input(nowdrone->type,360,175,6,33,30,WHITE,4);
        }
        else if(mouse_press(350,360,570,420)==2)      //时间
        {
            if(flag!=2)
            {
                MouseS = 2;
                flag = 2;
            }
        }
        else if(mouse_press(350,360,570,420)==1)
        {
            temp_input(time,360,375,6,33,30,WHITE,4);
            nowdrone->flying_time = atoi(time);
        }
        else if(mouse_press(595,5,630,40)==2)
        {
            if(flag!=3)
            {
                MouseS = 1;
                flag = 3;
                num[1] = 1;
                back_button(LIGHT);
            }
        }
        else if(mouse_press(595,5,630,40)==1)
        {
            clrmous(MouseX,MouseY);
            cleardevice();
            MouseS = 0;
            return HOME;
        }
        else if(mouse_press(400,430,520,470)==2)
        {
            if(flag!=4)
            {
                MouseS = 1;
                flag = 4;
                num[2] = 1;
                clrmous(MouseX,MouseY);
                printbox(400,430,520,470,YELLOW,1,5,5);
                setcolor(CYAN);
                settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
                outtextxy(440,440,"OK");
            }
        }
        else if(mouse_press(400,430,520,470)==1)
        {
            clrmous(MouseX,MouseY);
            cleardevice();
            MouseS = 0;
            
            if((fp=fopen(string,"wb+"))!=NULL)
            {
                if((fwrite(nowdrone,sizeof(DRONEINFO),1,fp))!=1)
                {
                    perror("ERROR IN WRITING");
                    delay(3000);
                    exit(1);
                }
            }
            else
            {
                perror("ERROR IN OPENING FILE!");
            }
            fclose(fp);
            return DRONE;
        }
        else
        {
            if(flag!=0)
            {
                MouseS = 0;
                flag = 0;
            }
        }

        if(flag!=3&&num[1]==1)
        {
            clrmous(MouseX,MouseY);
            back_button(RECOVER);
            num[1] = 0;
        }
        else if(flag!=4&&num[2]==1)
        {
            clrmous(MouseX,MouseY);
            printbox(400,430,520,470,DARKGRAY,1,5,5);
            setcolor(DARKGRAY);
            settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
            outtextxy(440,440,"OK");
            num[2] = 0;
        }
    }
}
