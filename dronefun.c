#include "public.h"
#include "dronefunc.h"

void dronefunc_screen()
{
    back_button(PAINT);
    put_drone2(12,140,DARKGRAY,LIGHTGRAY,15);
    printbox(350,30,570,90,DARKGRAY,1,5,5);
    printbox(350,120,570,180,DARKGRAY,1,5,5);
    printbox(350,210,570,270,DARKGRAY,1,5,5);
    printbox(350,300,570,360,DARKGRAY,1,5,5);
    printbox(350,390,570,450,DARKGRAY,1,5,5);
    settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
    outtextxy(180,50,"   NAME");
    outtextxy(180,140," WEIGHT");
    outtextxy(180,230,"   WING");
    outtextxy(180,320,"WEATHER ");
    outtextxy(180,410,"   TIME");
    printbox(35,360,185,440,DARKGRAY,1,5,5); 
    outtextxy(87,390,"OK");

}

int drone_list_page(char *username,DRONEINFO *nowdrone)
{
    int flag;
    int num[3];
    char dronename[20];
    char *weather_msgs[3]={"ALL","RAIN","SNOW"};
    FILE *fp;
    int power;
    double factor;
    char string[80] = "c:\\DATA\\";
    strcat(string,username);
    strcat(string,"\\DRONE\\");
    strcat(string,nowdrone->name);
    strcat(string,".dat");
    

    setcolor(DARKGRAY);
    settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
    outtextxy(360,45,nowdrone->name);
    strcpy(dronename,nowdrone->name);
    memset(nowdrone->weight,0,sizeof(nowdrone->weight));
    memset(nowdrone->time,0,sizeof(nowdrone->time));
    memset(nowdrone->weather,0,sizeof(nowdrone->weather));
    memset(nowdrone->wing,0,sizeof(nowdrone->wing));
    if((fp=fopen(string,"rb"))!=NULL)
        {
            if((fread(nowdrone,sizeof(DRONEINFO),1,fp))!=1)
            {
                perror("ERROR IN READING");
            }
        }
        else
        {
            perror("ERROR IN CREATING!");
        }
            fclose(fp);

    
    dronefunc_screen();
    setcolor(DARKGRAY);
    settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
    outtextxy(360,135,nowdrone->weight);
    outtextxy(360,225,nowdrone->wing);
    outtextxy(360,315,nowdrone->weather);
    outtextxy(360,405,nowdrone->time);

    mouseinit();
    while(1)
    {
        newmouse(&MouseX,&MouseY,&press);

        if(mouse_press(350,120,570,180)==2)           //weight
        {
            if(flag!=1)
            {
                MouseS = 2;
                flag = 1;
            }
        }
        else if(mouse_press(350,120,570,180)==1)
        {
            temp_input(nowdrone->weight,360,135,6,33,30,WHITE,4);
        }
        else if(mouse_press(350,210,570,270)==2)      //wing
        {
            if(flag!=2)
            {
                MouseS = 2;
                flag = 2;
            }
        }
        else if(mouse_press(350,210,570,270)==1)
        {
            temp_input(nowdrone->wing,360,225,6,33,30,WHITE,4);
        }
        else if(mouse_press(350,300,570,360)==2)      //scale
        {
            if(flag!=3)
            {
                MouseS = 1;
                flag = 3;
            }
        }
        else if(mouse_press(350,300,570,360)==1)
        {
            drop_down_menu(350,360,220,50,3,4,weather_msgs,LIGHTGRAY,DARKGRAY,nowdrone->weather);
            delay(100);
            setfillstyle(SOLID_FILL,WHITE);
            bar(360,310,560,350);
            clrmous(MouseX,MouseY);
            setcolor(DARKGRAY);
            settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
            outtextxy(360,315,nowdrone->weather);
            // temp_input(nowdrone->weather,360,315,6,33,30,WHITE,4);
        }
        else if(mouse_press(350,390,570,450)==2)      //time
        {
            if(flag!=4)
            {
                MouseS = 2;
                flag = 4;
            }
        }
        else if(mouse_press(350,390,570,450)==1)
        {
            temp_input(nowdrone->time,360,405,6,33,30,WHITE,4);
        }
        else if(mouse_press(595,5,630,40)==2)
        {
            if(flag!=5)
            {
                MouseS = 1;
                flag = 5;
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
        else if(mouse_press(35,360,185,440)==2)
        {
            if(flag!=6)
            {
                MouseS = 1;
                flag = 6;
                num[2] = 1;
                clrmous(MouseX,MouseY);
                printbox(35,360,185,440,YELLOW,1,5,5);
                setcolor(CYAN);
                settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
                outtextxy(87,390,"OK");
            }
        }
        else if(mouse_press(35,360,185,440)==1)
        {
            clrmous(MouseX,MouseY);
            cleardevice();
            MouseS = 0;
            strcpy(nowdrone->name,dronename);
            factor = 4*atoi(nowdrone->weight)-atoi(nowdrone->time);
            power = (atoi(nowdrone->wing)*100*(factor*log(factor)-factor)+atoi(nowdrone->time)*atoi(nowdrone->time))/(400+2*atoi(nowdrone->weight));
            
            itoa(power,nowdrone->power,10);
            if((fp=fopen(string,"wb"))!=NULL)  //.dat   .txt
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

        if(flag!=5&&num[1]==1)
        {
            clrmous(MouseX,MouseY);
            back_button(RECOVER);
            num[1] = 0;
        }
        else if(flag!=6&&num[2]==1)
        {
            clrmous(MouseX,MouseY);
            printbox(35,360,185,440,DARKGRAY,1,5,5);
            setcolor(DARKGRAY);
            settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
            outtextxy(87,390,"OK");
            num[2] = 0;
        }
    }
}
