#include "public.h"
#include "detect.h"
#include "flyfunc.h"

void detect_screen(int record[21][26] , char *nowfield )
{
    setbkcolor(WHITE);
    cleardevice();
    clrmous(MouseX,MouseY);

    paint_field(record ,nowfield);

    put_calender();

    mode_button(PAINT);
    start_button(PAINT);
    pause_button(PAINT);
    chart_button(PAINT);
}
void put_calender(void)
{
    
    setfillstyle(SOLID_FILL,DARKGRAY);
    bar(5,10,95,13);//(5,10) (95,120)
    bar(5,10,8,120);
    bar(5,117,95,120);
    bar(92,10,95,120);

    bar(5,70,95,73);
    bar(65,70,68,120);
    // bar(5,67,95,70);//70-90  17/2 8
    // bar(48,70,52,87);
    setcolor(DARKGRAY);
    settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
    outtextxy(13,18,"DAY");

    settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
    // if(strlen(date)==3) outtextxy(15,35,date);
    // if(strlen(date)==1) outtextxy(39,35,date);
    // if(strlen(date)==2) outtextxy(27,35,date);
    outtextxy(27,35,"29");

    // put_arrow(15,74,DARKGRAY,1,LEFTARROW);
    // put_arrow(61,74,DARKGRAY,1,RIGHTARROW);
    
}

void mode_button(int flag)
{
    if(flag == PAINT)
    {
        clrmous(MouseX,MouseY);
        printbox(5,130,95,169,DARKGRAY,1,3,3);
        setcolor(DARKGRAY);
        settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
        outtextxy(13,141,"MODE>");
    }
    else if(flag == LIGHT)
    {
        clrmous(MouseX,MouseY);
        printbox(5,130,95,169,BLUE,1,3,3);//39
        setcolor(CYAN);
        settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
        outtextxy(13,141,"MODE>");
    }
    else if(flag == RECOVER)
    {
        mode_button(PAINT);
    }
}
void start_button(int flag)
{
    if(flag == PAINT)
    {
        clrmous(MouseX,MouseY);
        printbox(5,180,95,219,DARKGRAY,1,3,3);
        setcolor(DARKGRAY);
        settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
        outtextxy(13,191,"START");
    }
    else if(flag == LIGHT)
    {
        clrmous(MouseX,MouseY);
        printbox(5,180,95,219,BLUE,1,3,3);
        setcolor(CYAN);
        settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
        outtextxy(13,191,"START");
    }
    else if(flag == RECOVER)
    {
        start_button(PAINT);
    }
}
void pause_button(int flag)
{
    if(flag == PAINT)
    {
        clrmous(MouseX,MouseY);
        printbox(5,230,95,269,DARKGRAY,1,3,3);
        setcolor(DARKGRAY);
        settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
        outtextxy(13,241,"PAUSE");
    }
    else if(flag == LIGHT)
    {
        clrmous(MouseX,MouseY);
        printbox(5,230,95,269,BLUE,1,3,3);
        setcolor(CYAN);
        settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
        outtextxy(13,241,"PAUSE");
    }
    else if(flag == RECOVER)
    {
        pause_button(PAINT);
    }
}
void chart_button(int flag)
{
    if(flag == PAINT)
    {
        clrmous(MouseX,MouseY);
        printbox(5,280,95,319,DARKGRAY,1,3,3);
        setcolor(DARKGRAY);
        settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
        outtextxy(13,291,"CHART");
    }
    else if(flag == LIGHT)
    {
        clrmous(MouseX,MouseY);
        printbox(5,280,95,319,BLUE,1,3,3);
        setcolor(CYAN);
        settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
        outtextxy(13,291,"CHART");
    }
    else if(flag == RECOVER)
    {
        chart_button(PAINT);
    }
}
int detect_page(char *username,char *nowfield)
{
    int record[21][26];
    int i,k,pre_x=-1,pre_y=-1;
    int flag=0,mode = 0, handmode_flag = 0 , automode_flag = 0;
    int num[5];
    char path[100]="C:\\DATA\\";
    char *presentmode;
    char *tempmsgs[2]={"hand>","auto>"};
    FILE *fp;
    struct point route[100];

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

        if( mouse_press(5,130,95,169)==2 )//new_mode未点击5,130,95,169
        {
            if( flag != 1 && num[1]!=10)
            {
                MouseS = 1 ;
                flag = 1 ;
                num[1] = 1;
                clrmous(MouseX,MouseY);
                mode_button(LIGHT);
            }
        }
        else if( mouse_press(5,130,95,169)==1 )//mode点击
        {
            MouseS = 0;
            clrmous(MouseX,MouseY);

            if(handmode_flag==1) continue;

            // drop_down_menu(int x,int y,int wide,int h,int n,int lettersize,char **msgs,int lightcolor,int darkcolor,char *record)
            drop_down_menu(5,169,90,35,2,2, tempmsgs ,WHITE,BLUE,presentmode);
            if(strlen(presentmode)!=0) 
            {
                setfillstyle(SOLID_FILL,WHITE);
                bar(5,130,95,169);
                printbox(5,130,95,169,BLUE,1,3,3);
                setcolor(CYAN);
                settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
                outtextxy(13,141,presentmode);
                
                num[1]=10;
            }
            if(presentmode[0]=='h') mode=1;
            
        }
        else if( mouse_press(5,180,95,219)==2 )//start未点击
        {
            if( flag != 3 )
            {
                MouseS = 1 ;
                flag = 3 ;
                num[3] = 1;
                clrmous(MouseX,MouseY);
                start_button(LIGHT);
            }
        }
        else if( mouse_press(5,180,95,219)==1 )//start点击5,180,95,219
        {
            MouseS = 0;
            clrmous(MouseX,MouseY);
            // simulate(record , username);
            
            if( handmode_flag == 1 ) {
                simulate_handmode(record,route);
                handmode_flag=0;
                memset(route,0,sizeof(route));
            }

        }
        else if( mouse_press(5,230,95,269)==2 )//pause未点击
        {
            if( flag != 4 )
            {
                MouseS = 1 ;
                flag = 4 ;
                num[4] = 1;
                clrmous(MouseX,MouseY);
                pause_button(LIGHT);
            }
        }
        else if( mouse_press(5,230,95,269)==1 )//pause点击
        {
            MouseS = 0;
            clrmous(MouseX,MouseY);

        }
        else if( mouse_press(5,280,95,319)==2 )//chart未点击
        {
            if( flag != 5 )
            {
                MouseS = 1 ;
                flag = 5 ;
                num[5] = 1;
                clrmous(MouseX,MouseY);
                chart_button(LIGHT);
            }
        }
        else if( mouse_press(5,280,95,319)==1 )//chart点击
        {
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
            mode_button(RECOVER);
            num[1]=0;
        }
        else if( flag!=2 && num[2]==1 )
        {
            clrmous(MouseX,MouseY);
            back_button(RECOVER);
            num[2]=0;
        }
        else if( flag!=3 && num[3]==1 )
        {
            clrmous(MouseX,MouseY);
            start_button(RECOVER);
            num[3]=0;
        }
        else if( flag!=4 && num[4]==1 )
        {
            clrmous(MouseX,MouseY);
            pause_button(RECOVER);
            num[4]=0;
        }
        else if( flag!=5 && num[5]==1 )
        {
            clrmous(MouseX,MouseY);
            chart_button(RECOVER);
            num[5]=0;
        }

        if(mode==1) //选择hand后选点
        {
            clrmous(MouseX,MouseY);
            setfillstyle(SOLID_FILL,WHITE);
            bar(110,0,640,50);
            setcolor(DARKGRAY);
            settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
            outtextxy(110,18,"please choose your route!");
            k=0;
            while(1)
            {
                newmouse(&MouseX,&MouseY,&press);
                if(mouse_press(110,50,630,470)==1)//处于画图区域并且点击
                {
                    clrmous(MouseX,MouseY);
                    delay(10);
                    setfillstyle(SOLID_FILL,LIGHTBLUE);
                    fillellipse(MouseX, MouseY, 3, 3);

                    // setcolor(LIGHTBLUE);
                    // circle(MouseX,MouseY,2);

                    route[k].x = MouseX;
                    route[k].y = MouseY;
                    k++;

                    // if(pre_x!=-1 && pre_y!= -1 ) 
                    // {
                    //     setlinestyle(DOTTED_LINE, 0, THICK_WIDTH);
                    //     setcolor(LIGHTBLUE);
                    //     line(10,10,30,10);
                    //     line(pre_x,pre_y,MouseX,MouseY);
                    //     pre_x = MouseX;
                    //     pre_y = MouseY;
                    // }
                    if(k!=1) {
                        setlinestyle(DOTTED_LINE, 0, THICK_WIDTH);
                        setcolor(LIGHTBLUE);
                        line(10,10,30,10);
                        line(route[k-1].x,route[k-1].y,route[k].x,route[k].y);
                    }
                }
                if( mouse_press(5,130,95,169)==1 ) {
                    clrmous(MouseX,MouseY);
                    setfillstyle(SOLID_FILL,WHITE);
                    bar(110,0,640,50);
                    back_button(PAINT);
                    setcolor(DARKGRAY);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
                    outtextxy(110,10,"NAME:");
                    outtextxy(260,10,nowfield);
                    mode = 0 ;
                    k = 0;
                    break;
                }
            }
            handmode_flag = 1;
        }
        
    }
}
