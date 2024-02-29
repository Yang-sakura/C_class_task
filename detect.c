#include "public.h"
#include "detect.h"
#include "flyfunc.h"

void detect_screen(int record[21][26] , char *nowfield)
{
    setbkcolor(WHITE);
    cleardevice();
    clrmous(MouseX,MouseY);

    paint_field(record ,nowfield);

    start_button(PAINT);
}
void start_button(int flag)
{
    if(flag == PAINT)
    {
        clrmous(MouseX,MouseY);
        printbox(5,130,95,180,DARKGRAY,1,5,5);
        setcolor(DARKGRAY);
        settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
        outtextxy(10,150,"START");
    }
    else if(flag == LIGHT)
    {
        clrmous(MouseX,MouseY);
        printbox(5,130,95,180,YELLOW,1,5,5);
        setcolor(CYAN);
        settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
        outtextxy(10,150,"START");
    }
    else if(flag == RECOVER)
    {
        start_button(PAINT);
    }
    else if(flag == DELETE)
    {
        setfillstyle(SOLID_FILL,WHITE);
        bar(5,130,95,180);
    }
}
int detect_page(char *username,char *nowfield)
{
    int record[21][26];
    int i;
    int flag=0;
    int num[5];
    char path[100]="C:\\DATA\\";
    FILE *fp;

    memset(record , 0 , sizeof(record));

    strcat(path,username);
    strcat(path,"\\FIELD\\");
    strcat(path,nowfield);

    if ( (fp = fopen(path,"rb")) != NULL )
    {
        for(i=0; i<21 ;i++ )
        {
            fread( record[i],sizeof(int), 26 ,fp);
        }
    }
    else 
    {
        perror("error in opening fieldfile!");
    }
    fclose(fp);

    detect_screen(record , nowfield);
    mouseinit();
    
    while(1)
    {
        newmouse(&MouseX,&MouseY,&press);

        if( mouse_press(5,130,95,180)==2 )//开始未点击
        {
            if( flag != 1 )
            {
                MouseS = 1 ;
                flag = 1 ;
                num[1] = 1;
                clrmous(MouseX,MouseY);
                start_button(LIGHT);
            }
        }
        else if( mouse_press(5,130,95,180)==1 )//开始点击
        {
            MouseS = 0;
            clrmous(MouseX,MouseY);

            simulate(record , username);
        }
        else if( mouse_press(595,5,630,40)==2 )//退出键未点击
        {
            if( flag!=2 )
            {
                MouseS = 1 ;
                flag = 2 ;
                num[2] = 1;
                clrmous(MouseX,MouseY);
                back_button(LIGHT);
            }
        }
        else if( mouse_press(595,5,630,40)==1 )//退出点击
        {
            clrmous(MouseX,MouseY);
            return HOME;
        }
        else 
        {
            MouseS = 0 ;
            flag = 0 ;
        }

        if( flag!=1 && num[1]==1)
        {
            clrmous(MouseX,MouseY);
            start_button(RECOVER);
            num[1]=0;
        }
        else if( flag!=2 && num[2]==1 )
        {
            clrmous(MouseX,MouseY);
            back_button(RECOVER);
            num[2]=0;
        }


    }
}
