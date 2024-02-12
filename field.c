#include "public.h"
#include "field.h"
#include "main.h"

void field_screen()
{
    int i;
    printline(100,0,1,480,1,DARKGRAY,5,5);
    setcolor(DARKGRAY);
    settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
    outtextxy(110,10,"NAME:");
    settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
    outtextxy(3,370,"SQUARE");

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

    put_field(25,50,LIGHTGRAY,DARKGRAY,5);
    put_sprout(25,150,DARKGRAY,5);
    put_house(25,250,DARKGRAY,LIGHTGRAY,5);
}


int field_page(INFO* temp,char* now_field)
{
    
    int flag = 0;
    int num[5];
    int record[21][26];
    char string[80] = "c:\\DATA\\";
    int i;
    FILE * fp;
    cleardevice();
    setbkcolor(WHITE);

    memset(record,0,sizeof(record));

    clrmous(MouseX,MouseY);
    if(strlen(now_field)!=0)
    {
        strcat(string,temp->name);
        strcat(string,"\\FIELD\\");
        strcat(string,now_field);

        if ( (fp = fopen(string,"rb")) != NULL )
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
        paint_field(record ,now_field);

    }

    field_screen();
    mouseinit();
     
    while(1)
    {
        newmouse(&MouseX,&MouseY,&press);

        if(mouse_press(25,50,70,95)==2) //绘制农田未点击
        {
            if(flag!=1)
            {
                clrmous(MouseX,MouseY);
                put_field(25,50,GREEN,BROWN,5);
                MouseS = 1;
                flag = 1;
                num[1]=1;
            }
        }
        else if(mouse_press(25,150,70,195)==2)//放置农作物位置未点击
        {
            if(flag!=2)
            {
                clrmous(MouseX,MouseY);
                put_sprout(25,150,GREEN,5);
                MouseS = 1;
                flag = 2;
                num[2]=1;
            }
        }
        else if(mouse_press(25,250,70,295)==2)//放置无人机位置未点击
        {
            if(flag!=3)
            {
                clrmous(MouseX,MouseY);
                put_house(25,250,BROWN,CYAN,5);
                MouseS = 1;
                flag = 3;
                num[3]=1;
            }
        }
        else if(mouse_press(595,5,630,40)==2)//退出键未点击
        {
            if(flag!=4)
            {
                back_button(LIGHT);
                MouseS = 1;
                flag = 4;
                num[4]=1;
            }
        }
        else
        {
            MouseS = 0;
            flag = 0;
        }

        if(mouse_press(25,50,70,95)==1)      //绘制农田点击
        {
            clrmous(MouseX,MouseY);
            cleardevice();
            return DRAW_FIELD;
        }
        else if(mouse_press(25,150,70,195)==1)
        {
            ;
        }
        else if(mouse_press(25,250,70,295)==1)
        {
            ;
        }
        else if(mouse_press(595,5,630,40)==1)
        {
            cleardevice();
            return HOME;
        }

        if(flag!=1&&num[1]==1)
        {
            clrmous(MouseX,MouseY);
            put_field(25,50,LIGHTGRAY,DARKGRAY,5);
            num[1]=0;
        }
        else if(flag!=2&&num[2]==1)
        {
            clrmous(MouseX,MouseY);
            put_sprout(25,150,LIGHTGRAY,5);
            num[2]=0;
        }
        else if(flag!=3&&num[3]==1)
        {
            clrmous(MouseX,MouseY);
            put_house(25,250,DARKGRAY,LIGHTGRAY,5);
            num[3]=0;
        }
        else if(flag!=4&&num[4]==1)
        {
            back_button(RECOVER);
            num[4]=0;
        }
    }
}
