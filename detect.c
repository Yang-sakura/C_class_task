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
    
    setcolor(DARKGRAY);
    settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
    outtextxy(13,18,"DAY");

    // put_arrow(15,74,DARKGRAY,1,LEFTARROW);
    // put_arrow(61,74,DARKGRAY,1,RIGHTARROW);
}
void put_calender_number(char *date)//(15,20,90,60)
{
    setfillstyle(SOLID_FILL,WHITE);
    bar(11,25,90,69);
    setcolor(DARKGRAY);
    settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
    if(strlen(date)==3) outtextxy(15,35,date);
    if(strlen(date)==1) outtextxy(39,35,date);
    if(strlen(date)==2) outtextxy(27,35,date);
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
void route_button(int flag)
{
    if(flag == PAINT)
    {
        clrmous(MouseX,MouseY);
        printbox(5,330,95,369,DARKGRAY,1,3,3);
        setcolor(DARKGRAY);
        settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
        outtextxy(13,341,"ROUTE");
    }
    else if(flag == LIGHT)
    {
        clrmous(MouseX,MouseY);
        printbox(5,330,95,369,BLUE,1,3,3);
        setcolor(CYAN);
        settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
        outtextxy(13,341,"ROUTE");
    }
    else if(flag == DELETE)
    {
        setfillstyle(SOLID_FILL,WHITE);
        bar(5,330,95,369);
    }
    else if(flag == RECOVER)
    {
        route_button(PAINT);
    }
}
int detect_page(char *username,char *nowfield)
{
    int ceshi = 0;

    int record[21][26];
    int i,k,pre_x=-1,pre_y=-1,x,y;
    // int pre_press = -1 ;
    int flag = 0,mode = 0, handmode_flag = 0 , automode_flag = 0 , routebutton_flag = 0;
    int num[5];
    char path[100]="C:\\DATA\\";
    char *presentmode;
    char *tempmsgs[2] = {"hand>","auto>"};
    FILE *fp;
    int route[100][2];
    char date[10];

    memset(record , 0 , sizeof(record));
    memset(route,-1,sizeof(route));
    memset(date ,0,sizeof(date));

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

            drop_down_menu(5,169,90,35,2,2, tempmsgs ,WHITE,BLUE,presentmode);
            
            if(strlen(presentmode) != 0) 
            {
                setfillstyle(SOLID_FILL,WHITE);
                bar(5,130,95,169);
                printbox(5,130,95,169,BLUE,1,3,3);
                setcolor(CYAN);
                settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
                outtextxy(13,141,presentmode);
                
                num[1]=10;
            }
            if(presentmode[0]=='h') {
                routebutton_flag = 1 ;
            }
            else if(presentmode[0]=='a') {
                mode = 2;
            }
            
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
            
            if( handmode_flag == 1 ) //&& mode != 1
            {
                simulate_handmode(record,route);
                // handmode_flag = 0;
                // memset(route,0,sizeof(route));
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
        else if( mouse_press(15,20,90,60)==1 ) //日历数字点击
        {
            setfillstyle(SOLID_FILL,WHITE);
            bar(11,25,90,69);
            temp_input(date , 18,35, 3 , 22 ,20,WHITE,3);//4 33 25
            put_calender_number(date);
        }
        else if( mouse_press(5,330,95,369)==2 && presentmode[0]=='h') //route未点击
        {
            if( flag != 6 )
            {
                MouseS = 1 ;
                flag = 6 ;
                num[6] = 1;
                clrmous(MouseX,MouseY);
                route_button(LIGHT);
            }
        }
        else if( mouse_press(5,330,95,369)==1  && presentmode[0]=='h')//route点击
        {
            MouseS = 0;
            clrmous(MouseX,MouseY);

            mode = 1 ;

            if(handmode_flag == 1 && presentmode[0]=='h') //存在hand档的地图 清空地图
            {
                paint_field_right(record , nowfield );
                memset(route,0,sizeof(route));
                handmode_flag = 0 ;
            }
        }
        else 
        {
            if(flag!=0)
            {
                MouseS = 0 ;
                flag = 0 ;
            }
        }

        if( presentmode[0]=='h' && routebutton_flag == 1)
        {
            route_button(PAINT);
            routebutton_flag = 0;
            setfillstyle(SOLID_FILL,BLUE);
            bar(5*ceshi,5*ceshi,5*(ceshi+1),5*(ceshi+1));
            ceshi++;
        }
        else if( presentmode[0]!='h' && routebutton_flag == 1)
        {
            route_button(DELETE) ;
            routebutton_flag = 0 ;
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
        else if( flag!=6 && num[6]==1 && presentmode[0] == 'h')
        {
            clrmous(MouseX,MouseY);
            route_button(RECOVER);
            num[6]=0;
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
                // if(pre_press==0 && press == 1 )
                // {
                if( mouse_press(110,50,630,470)==1 )//处于画图区域并且点击
                {
                    route[k][0] = MouseX;
                    route[k][1] = MouseY;
                    clrmous(MouseX,MouseY);
                        delay(200);
                    setfillstyle(SOLID_FILL,LIGHTBLUE);
                    fillellipse(MouseX, MouseY, 3, 3);
                    
                    if(k!=0) {
                        setlinestyle(DOTTED_LINE, 0, THICK_WIDTH);
                        setcolor(LIGHTBLUE);
                        line(10,10,30,10);

                        settextstyle(DEFAULT_FONT,HORIZ_DIR,2);

                        line(route[k-1][0],route[k-1][1],route[k][0],route[k][1]);
                    }
                    k++;
                }
                // }
                // pre_press = press ;
                
                if( mouse_press(5,330,95,369)==1 ) //
                {
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
            delay(200);
        }
        if(mode == 2) //auto
        {

        }
    }
}
