#include "public.h"
#include "plant.h"

void paint_field( int record[21][26] ,char *nowfield)
{
    int i,j,x,y;
    setbkcolor(WHITE);
    cleardevice();
    clrmous(MouseX,MouseY);

    back_button(PAINT);

    printline(100,0,1,480,1,DARKGRAY,5,5);
    setcolor(DARKGRAY);
    settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
    outtextxy(110,10,"NAME:");
    outtextxy(230,10,nowfield);

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

    for(i=0;i<21;i++)//y
    {
        for(j=0;j<26;j++)//x
        {
            if ( record[i][j] )
            {
                setfillstyle(SOLID_FILL,DARKGRAY);
                bar(110+j*20 , 470-(i+1)*20 ,110+(j+1)*20, 470-i*20);
            }
            if( record[i][j] == 2 )
            {
                x = 110 + j*20 ;
                y = 470-i*20-20 ;//左上角
                //右下角 (110 + j * 20 + 20, 470 - i * 20)
                put_sprout(x,y,GREEN,2);
            }
            
        }
    }
}
void plant_screen( int record[21][26] ,char *nowfield)
{
    paint_field(record ,nowfield);

    put_sprout(12,50,DARKGRAY,7);
    put_shovel(12,150,5,DARKGRAY,DARKGRAY);
}

int plant_page(char *username,char *nowfield)
{
    int record[21][26];
    int flag = 0;
    int mode = 0;
    int num[5];
    int sprout_flag=0 ,shovel_flag=0 ;
    int x,y;
    // char path[50]="C:\\DATA\\";
    char path[50]="C:\\DATA\\QWQ\\FIELD\\field.dat";
    int i,j;
    FILE *fp;

    memset(record , 0 , sizeof(record));

    // strcat(path,username);
    // strcat(path,"\\FIELD\\");
    // strcat(path,nowfield);

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

    plant_screen( record ,nowfield);
    mouseinit();

    while(1)
    {
        newmouse(&MouseX,&MouseY,&press);

        if( mouse_press(12,50,80,110)==2 )//种树未点击
        {
            if(flag != 1)
            {
                MouseS = 1;
                flag = 1;
                num[1] = 1;
                clrmous(MouseX,MouseY);
                put_sprout(12,50,GREEN,7);
            }
        }
        else if( mouse_press(12,50,80,110)==1 )//种树点击
        {
            mode = 1;
            MouseS = 0;
            clrmous(MouseX,MouseY);
        }
        else if( mouse_press(12,150,80,215)==2 )//铲子未点击
        {
            if(flag!=2)
            {
                MouseS = 1;
                flag = 2;
                num[2] = 1;
                clrmous(MouseX,MouseY);
                put_shovel(12,150,5,LIGHTGRAY,BROWN);
            }
        }
        else if( mouse_press(12,150,80,215)==1 )//铲子点击
        {
            mode = 2 ;
            MouseS = 0;
            clrmous(MouseX,MouseY);
        }
        else if( mouse_press(595,5,630,40)==2 )//退出键未点击
        {
            if(flag!=3)
            {
                clrmous(MouseX,MouseY);
                back_button(LIGHT);
                MouseS = 1;
                flag = 3;
                num[3] = 1;
            }
        }
        else if( mouse_press(595,5,630,40)==1 )//退出点击
        {
            clrmous(MouseX,MouseY);
            return FIELD;
        }
        else
        {
            if(flag != 0)
            {
                MouseS = 0;
                flag = 0;
            }
            
        }

        //侧边及返回按键恢复
        if(flag!=1 && num[1]==1)
        {
            clrmous(MouseX,MouseY);
            put_sprout(12,50,DARKGRAY,7);
            num[1] = 0;
        }
        else if(flag!=2 && num[2]==1)
        {
            clrmous(MouseX,MouseY);
            put_shovel(12,150,5,DARKGRAY,DARKGRAY);
            num[2] = 0;
        }
        else if(flag!=3&&num[3]==1)
        {
            clrmous(MouseX,MouseY);
            back_button(RECOVER);
            num[3] = 0;
        }
        
        if(mode == 1)
        {
            clrmous(MouseX,MouseY);
            put_sprout(12,50,GREEN,7);
            put_ok_button(PAINT);
            setfillstyle(SOLID_FILL,WHITE);
            bar(595,5,630,40);//退出按键
            while(1)
            {
                newmouse(&MouseX,&MouseY,&press);
                if(mouse_press(110,50,630,470)==2) //处于画图区域，但未点击
                {
                    if(sprout_flag != 1)
                    {
                        MouseS = mode + 5;//树苗
                        sprout_flag = 1;
                    }
                }
                else if( mouse_press(110,50,630,470)==1 )//处于画图区域并且点击
                {
                    clrmous(MouseX,MouseY);
                    i = (470-MouseY)/20;
                    j = (MouseX - 110)/20;
                    if( record[i][j] == 1)
                    {
                        x = 110+j*20 ;
                        y = 470-i*20-20 ;//左上角
                        //右下角 (110 + j * 20 + 20, 470 - i * 20)
                        put_sprout(x,y,GREEN,2);
                        record[i][j] = 2;
                    }
                }
                else if(mouse_press(5,400,95,470)==2)//处于ok区域未点击
                {
                    if(sprout_flag != 2)
                    {
                        MouseS = 1;
                        sprout_flag = 2;
                        put_ok_button(LIGHT);
                    }
                }
                else if(mouse_press(5,400,95,470)==1)//处于ok区域并且点击
                {
                    MouseS = 0;
                    mode = 0;
                    if ( (fp = fopen(path,"wb")) != NULL )
                    {
                        for(i=0;i<21;i++)
                        {
                            fwrite(record[i],sizeof(int),26,fp);
                        }
                    }
                    else 
                    {
                        perror("error in changing record data!");
                    }
                    fclose(fp);

                    clrmous(MouseX,MouseY);
                    setfillstyle(SOLID_FILL,WHITE);
                    bar(0,0,95,480);
                    put_sprout(12,50,DARKGRAY,7);
                    put_shovel(12,150,5,DARKGRAY,DARKGRAY);
                    back_button(PAINT);
                    
                    break;
                }

                else 
                {
                    if(sprout_flag != 0)
                    {
                        MouseS = 0;
                        sprout_flag = 0;
                        put_ok_button(RECOVER);
                    }
                }
            }
        }

        if(mode == 2 )//铲子
        {
            clrmous(MouseX,MouseY);
            put_shovel(12,150,5,LIGHTGRAY,BROWN);
            put_ok_button(PAINT);
            setfillstyle(SOLID_FILL,WHITE);
            bar(595,5,630,40);
            while(1)
            {
                newmouse(&MouseX,&MouseY,&press);
                if(mouse_press(110,50,630,470)==2)//处于画图区域，但未点击
                {
                    if(shovel_flag !=1)
                    {
                        MouseS = mode + 5;
                        shovel_flag = 1;
                    }
                }
                else if(mouse_press(110,50,630,470)==1)//处于画图区域并且点击
                {
                    clrmous(MouseX,MouseY);
                    i = (470-MouseY)/20;
                    j = (MouseX - 110)/20;
                    if( record[i][j] > 1)
                    {
                        x = 110+j*20 ;
                        y = 470-i*20-20 ;//左上角
                        setfillstyle(SOLID_FILL,DARKGRAY);
                        bar(x,y,x+20,y+20);
                        record[i][j] = 1;
                    }
                }
                else if(mouse_press(5,400,95,470)==2)//处于ok区域未点击
                {
                    if(shovel_flag != 2)
                    {
                        MouseS = 1;
                        shovel_flag = 2;
                        put_ok_button(LIGHT);
                    }
                }
                else if(mouse_press(5,400,95,470)==1)//处于ok区域并且点击
                {
                    MouseS = 0;
                    mode = 0;
                    if ( (fp = fopen(path,"wb")) != NULL )
                    {
                        for(i=0;i<21;i++)
                        {
                            fwrite(record[i],sizeof(int),26,fp);
                        }
                    }
                    else 
                    {
                        perror("error in changing record data!");
                    }
                    fclose(fp);

                    clrmous(MouseX,MouseY);
                    setfillstyle(SOLID_FILL,WHITE);
                    bar(0,0,95,480);
                    put_sprout(12,50,DARKGRAY,7);
                    put_shovel(12,150,5,DARKGRAY,DARKGRAY);
                    back_button(PAINT);
                    
                    break;
                }

            }
        }

    }



}
