#include "public.h"
#include "house.h"

void house_screen(int record[21][26] ,char *nowfield)
{
    setbkcolor(WHITE);
    cleardevice();
    clrmous(MouseX,MouseY);

    paint_field(record ,nowfield);

    put_house(25,50,DARKGRAY,LIGHTGRAY,5);

}

void clear_button(int flag)
{
    if(flag == PAINT)
    {
        clrmous(MouseX,MouseY);
        printbox(5,130,95,180,DARKGRAY,1,5,5);
        setcolor(DARKGRAY);
        settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
        outtextxy(10,150,"CLEAR");
    }
    else if(flag == LIGHT)
    {
        clrmous(MouseX,MouseY);
        printbox(5,130,95,180,YELLOW,1,5,5);
        setcolor(CYAN);
        settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
        outtextxy(10,150,"CLEAR");
    }
    else if(flag == RECOVER)
    {
        clear_button(PAINT);
    }
    else if(flag == DELETE)
    {
        setfillstyle(SOLID_FILL,WHITE);
        bar(5,130,95,180);
    }
}

int house_page(char *username,char *nowfield)
{
    int record[21][26];
    int flag = 0;
    int mode = 0;
    int num[5];
    int house_flag=0 ,house=0;
    int x,y;
    char path[50]="C:\\DATA\\";
    // char path[50]="C:\\DATA\\QWQ\\FIELD\\field.dat";
    int i,j,i_recent,j_recent;
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

    house_screen( record ,nowfield);
    mouseinit();
    i=0;j=0;i_recent=0;j_recent;

    while(1)
    {
        newmouse(&MouseX,&MouseY,&press);

        if( mouse_press(25,50,70,95)==2 )//房子未点击
        {
            if( flag!=1 )
            {
                MouseS = 1;
                flag = 1;
                num[1] = 1 ;
                clrmous(MouseX,MouseY);
                put_house(25,50,BROWN,CYAN,5);
            }
        }
        else if( mouse_press(25,50,70,95)==1 ) //房子点击
        {
            mode = 1 ;
            MouseS = 0;
            clrmous(MouseX,MouseY);
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
            return FIELD;
        }
        else 
        {
            MouseS = 0 ;
            flag = 0 ;
        }

        if( flag!=1 && num[1]==1)
        {
            clrmous(MouseX,MouseY);
            put_house(25,50,DARKGRAY,LIGHTGRAY,5);
            num[1]=0;
        }
        else if( flag!=2 && num[2]==1 )
        {
            clrmous(MouseX,MouseY);
            back_button(RECOVER);
            num[1]=0;
        }

        if( mode==1 )
        {
            put_house(25,50,BROWN,CYAN,5);
            clear_button(PAINT);
            put_ok_button(PAINT);
            setfillstyle(SOLID_FILL,WHITE);
            bar(595,5,630,40);
            while(1)
            {
                newmouse(&MouseX,&MouseY,&press);

                if( mouse_press(110,50,630,470)==2 ) //处于画图区域，但未点击
                {
                    if(house_flag != 1 )
                    {
                        MouseS = 8;
                        house_flag = 1;
                    }
                }
                else if( mouse_press(110,50,630,470)==1 )//处于画图区域并且点击
                {
                    if(house != 0) continue;
                    clrmous(MouseX,MouseY);
                    i = (470-MouseY)/20;
                    j = (MouseX - 110)/20;
                    i_recent = i ;
                    j_recent = j ;
                    if( record[i][j] == 1 )
                    {
                        x = 110+j*20 ;
                        y = 470-i*20-20 ;//左上角
                        //右下角 (110 + j * 20 + 20, 470 - i * 20)
                        put_house(x,y,BROWN,CYAN,2);
                        record[i][j] = 3;
                        house = 1;
                    }
                }
                else if(mouse_press(5,400,95,470)==2)//处于ok区域未点击
                {
                    if( house_flag != 2)
                    {
                        MouseS = 1;
                        house_flag = 2;
                        clrmous(MouseX,MouseY);
                        put_ok_button(LIGHT);
                    }
                }
                else if( mouse_press(5,400,95,470)==1 )//处于ok区域并且点击
                {
                    MouseS = 0;
                    mode = 0;

                    if(house == 1) 
                    {
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
                    }
                    
                    clrmous(MouseX,MouseY);
                    setfillstyle(SOLID_FILL,WHITE);
                    bar(0,0,95,480);
                    put_house(25,50,DARKGRAY,LIGHTGRAY,5);

                    back_button(PAINT);
                    clear_button(DELETE);
                    break;
                }
                else if( mouse_press(5,130,95,180)==2 )//清空键未点击
                {
                    if( house_flag != 3 )
                    {
                        MouseS = 1 ;
                        house_flag = 3 ;
                        num[3] = 1;
                        clrmous(MouseX,MouseY);
                        clear_button(LIGHT);
                    }
                }
                else if( mouse_press(5,130,95,180)==1 )//清空键点击
                {
                    if( house!=0 )
                    {
                        clrmous(MouseX,MouseY);
                        x = 110+j_recent*20 ;
                        y = 470-i_recent*20-20 ;//左上角
                        setfillstyle(SOLID_FILL,DARKGRAY);
                        bar(x,y,x+20,y+20);
                        record[i_recent][j_recent] = 1;
                        house = 0 ;
                    }
                }
                else 
                {
                    if(house_flag != 0)
                    {
                        MouseS = 0;
                        house_flag = 0;
                        put_ok_button(RECOVER);
                        clear_button(RECOVER);
                    }
                }
            }
        }
    }
}
