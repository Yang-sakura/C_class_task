#include "public.h"
#include "detect.h"
#include "flyfunc.h"
#include "detectf.h"

void detect_screen(int record[21][26] , char *nowfield ,int language)
{
    setbkcolor(WHITE);
    cleardevice();
    clrmous(MouseX,MouseY);

    paint_field(record ,nowfield,language);

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

    bar(5,70,95,73);//73-117  44 22 73-95 95-117 x:68-92
    bar(65,70,68,120);
    
    setcolor(DARKGRAY);
    settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
    outtextxy(15,18,"DAY");

    put_up_arrow(72,90,2);
    put_down_arrow(72,100,2);
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
void put_calender_weather(char weather[10])
{
    setfillstyle(SOLID_FILL,WHITE);
    bar(8,73,65,117);
    if(strcmp(weather,"cloud") == 0 ) {
        put_cloud(15,100,3);
    }
    else if(strcmp(weather,"sun")==0 ) {
        put_sun(28,86,3,RED);
    }
    else if(strcmp(weather,"rain")==0 ) {
        put_rain(20,95,3);
    }
    else if(strcmp(weather,"snow")==0 ) {
        put_snow(20,95,3);
    }
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
int detect_page(char *username,char *nowfield,int language)
{
    int record[21][26];
    int i,j,k,pre_x=-1,pre_y=-1,x,y,temp_date;
    int flag = 0,flag2 = 0 , mode = 0, handmode_flag = 0 , automode_flag = 0 , routebutton_flag = 0 , line_flag = 0,field_flag=0;
    int random_weather ;
    int num[10];
    char path[100]="C:\\DATA\\";
    char *presentmode;
    char *tempmsgs[2] = {"hand>","auto>"};
    FILE *fp;
    int route[100][2];
    char date[10] = "1" , compare[10] ;
    char weather[10] = "cloud" ;

    memset(record , 0 , sizeof(record));
    memset(route,-1, sizeof(route));
    memset(compare , 0 , sizeof(compare));

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

    detect_screen(record , nowfield,language);
    mouseinit();
    if( strlen(date) != 0 ) {
        put_calender_number(date);
        change_weather(weather);
        put_calender_weather(weather);
    }
    
    while(1)
    {
        newmouse(&MouseX,&MouseY,&press);

        if( mouse_press(5,130,95,169)==2 )//mode未点击5,130,95,169
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
            if(presentmode[0]=='a') {
                if(line_flag != 0 )
                {
                    paint_field_right(record , nowfield ,language);
                    line_flag = 0 ;
                }
                mode = 2;
            }
            delay(200);
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
            
            if( handmode_flag == 1 && presentmode[0] == 'h') 
            {
                simulate_handmode(record,route);
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
            delay(200);
            show_chart(record,nowfield);
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
            MouseS = 0 ;
            clrmous(MouseX,MouseY);
            return HOME;
        }
        else if( mouse_press(15,20,90,60)==1 ) //日历数字点击
        {
            strcpy(compare , date );
            setfillstyle(SOLID_FILL,WHITE);
            bar(11,25,90,69);
            temp_input(date , 18,35, 3 , 22 ,20,WHITE,3);//4 33 25
            put_calender_number(date);
            if(strcmp(compare , date )!= 0  ) {
                change_weather(weather);
                put_calender_weather(weather);
                recover_field(record,username,nowfield);
                grow(record , atoi(date));//每次日期改变时,都刷新右侧地图
                field_flag = 1 ;
            }
        }
        else if( mouse_press(68,73,92,95)==1 )// 上箭头
        {
            strcpy(compare , date );
            setfillstyle(SOLID_FILL,WHITE);
            bar(11,25,90,69);
            temp_date = atoi(date);
            if(temp_date >= CALENDER_MAX ) continue ;
            temp_date++ ;
            itoa(temp_date , date , 10 );
            put_calender_number(date);
            change_weather(weather);
            put_calender_weather(weather);
            if(temp_date == 2 )
            {
                if(strcmp(compare , date )!= 0  ) {
                    grow(record , atoi(date));//每次日期改变时,都刷新右侧地图
                    field_flag = 1 ;
                }
            }
            else {
                if(strcmp(compare , date )!= 0  ) {
                    grow_oneday(record , temp_date);
                    field_flag = 1 ;
                }
            }
            delay(200);
        }
        else if( mouse_press(68,95,92,117)==1 )// 下箭头
        {
            strcpy(compare , date );
            setfillstyle(SOLID_FILL,WHITE);
            bar(11,25,90,69);
            temp_date = atoi(date);
            if(temp_date==1) continue ;
            temp_date-- ;
            itoa(temp_date , date , 10 );
            put_calender_number(date);
            change_weather(weather);
            put_calender_weather(weather);
            if(strcmp(compare , date )!= 0  ) {
                grow(record , atoi(date));//每次日期改变时,都刷新右侧地图
                field_flag = 1 ;
            }
            delay(200);
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

            if(handmode_flag == 1 ) //存在hand档的地图 清空地图
            {
                paint_field_right(record , nowfield,language);
                memset(route,0,sizeof(route));
                handmode_flag = 0 ;
            }

            mode = 1 ;
            delay(200);
        }
        else 
        {
            if(flag!=0)
            {
                MouseS = 0 ;
                flag = 0 ;
            }
        }

        if( presentmode[0]=='h' && routebutton_flag == 0)
        {
            route_button(PAINT);
            routebutton_flag = 1;
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
            num[6] = 0;
        }

        if(mode == 1) //选择hand后选点
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
                if( mouse_press(110,50,630,470)==1 )//处于画图区域并且点击
                {
                    if(k==0) {
                        i = (470-MouseY)/20;
                        j = (MouseX - 110)/20;
                        if(record[i][j] < 3 || record[i][j] > 6 ) {
                            setfillstyle(SOLID_FILL,WHITE);
                            bar(110,0,640,50);
                            setcolor(DARKGRAY);
                            settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
                            outtextxy(110,18,"please start from a house!");
                            delay(1500);
                            setfillstyle(SOLID_FILL,WHITE);
                            bar(110,0,640,50);
                            setcolor(DARKGRAY);
                            settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
                            outtextxy(110,18,"please choose your route!");
                            continue ;
                        }
                    }
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
                    if(line_flag != 1 ) line_flag = 1 ;
                }
                if( mouse_press(5,330,95,369)==1 ) //route点击
                {
                    route[k][0] = route[0][0];
                    route[k][1] = route[0][1];
                    setlinestyle(DOTTED_LINE, 0, THICK_WIDTH);
                    setcolor(LIGHTBLUE);
                    line(route[k-1][0],route[k-1][1],route[k][0],route[k][1]);

                    clrmous(MouseX , MouseY);
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
            setfillstyle(SOLID_FILL,WHITE);
            bar(5,130,95,169);
            mode_button(RECOVER);
            delay(200);
        }
        if(mode == 2) //auto
        {
            clrmous(MouseX,MouseY);
            flag2 = 0 ;
            while(1)
            {
                newmouse(&MouseX,&MouseY,&press);
                if( mouse_press(5,180,95,219)==2 )//start未点击
                {
                    if( flag2 != 1 )
                    {
                        MouseS = 1 ;
                        flag2 = 1 ;
                        num[7] = 1;
                        clrmous(MouseX,MouseY);
                        start_button(LIGHT);
                    }
                }
                else if( mouse_press(5,180,95,219)==1 )//start点击
                {
                    MouseS = 0;
                    clrmous(MouseX,MouseY);
                    auto_simulate( record , date ,username , nowfield);
                }
                else if( mouse_press(5,130,95,169)==1 )//mode点击
                {
                    MouseS = 0;
                    clrmous(MouseX,MouseY);
                    mode = 0 ;
                    break ;
                }
                else if( mouse_press(595,5,630,40)==2 )//退出键未点击
                {
                    if( flag2!=2 )
                    {
                        MouseS = 1 ;
                        flag2 = 2 ;
                        num[8] = 1;
                        clrmous(MouseX,MouseY);
                        back_button(LIGHT);
                    }
                }
                else if( mouse_press(595,5,630,40) == 1 )//退出点击
                {
                    MouseS = 0 ;
                    clrmous(MouseX,MouseY);
                    delay(200);
                    return HOME;
                }
                else 
                {
                    if(flag2 != 0)
                    {
                        MouseS = 0;
                        flag2 = 0;
                    }
                }

                if( flag2 != 1 && num[7]==1 )
                {
                    clrmous(MouseX,MouseY);
                    start_button(RECOVER);
                    num[7] = 0;
                }
                else if( flag2 != 2 && num[8]==1 )
                {
                    clrmous(MouseX,MouseY);
                    back_button(RECOVER);
                    num[8] = 0;
                }
            }
            setfillstyle(SOLID_FILL,WHITE);
            bar(5,130,95,169);
            mode_button(RECOVER);
            delay(200);
        }
    }
}
void auto_simulate(int record[21][26], char *date_char ,char *username , char *nowfield)
{
    int date ,i,j, add = 1 , flag = 0 , startlight = 1 , pauselight = 0 ;
    long long int time ;
    int num[10];
    char date_temp[10];
    char weather[10];
    int houserecord[4][2];

    memset(houserecord,0,sizeof(houserecord));
    memset(date_temp,0,sizeof(date_temp));
    memset(num,0,sizeof(num));
    date = atoi( date_char );//从date天开始
    if(date != 1) {
        grow(record , date );
    }

    mouseinit();

    find_house(record,houserecord);

    while(1)
    {
        newmouse(&MouseX,&MouseY,&press);

        if(time%600000 == 0) 
        {
            itoa(date , date_temp , 10);
            put_calender_number(date_temp);
            change_weather(weather);
            put_calender_weather(weather);
            
            grow_oneday(record,date);

            if(date % 3 == 0) //侦测天数
            {
                // fly_detect( record , find_closest_house(record) );
                fly_spray(record,4);
            }

            time = 0;
            date++ ;
        }
        if( mouse_press(5,180,95,219)==2 )//start未点击
        {
            if(startlight == 0)
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
        }
        else if( mouse_press(5,180,95,219)==1 )//start点击5,180,95,219
        {
            MouseS = 0;
            clrmous(MouseX,MouseY);
            
            startlight = 1;
            if(pauselight == 1)
            {
                pauselight = 0 ;
                pause_button(RECOVER);
            }
            delay(50);
        }
        else if( mouse_press(5,230,95,269)==2 )//pause未点击
        {
            if(pauselight == 0)
            {
                if( flag != 2 )
                {
                    MouseS = 1 ;
                    flag = 2 ;
                    num[2] = 1;
                    clrmous(MouseX,MouseY);
                    pause_button(LIGHT);
                }
            }
        }
        else if( mouse_press(5,230,95,269)==1 )//pause点击
        {
            MouseS = 0;
            clrmous(MouseX,MouseY);

            pauselight = 1 ;
            if(startlight == 1) {
                startlight = 0 ;
                start_button(RECOVER);
            }
            delay(50);
        }
        else if( mouse_press(5,130,95,169)==1 )//mode点击
        {
            MouseS = 0;
            clrmous(MouseX,MouseY);
            itoa(date,date_char,10);
            delay(200);
            return ;
        }
        else if( mouse_press(15,20,90,60)==1 ) //日历数字点击
        {
            setfillstyle(SOLID_FILL,WHITE);
            bar(11,25,90,69);
            temp_input(date_temp , 18,35, 3 , 22 ,20,WHITE,3);//4 33 25
            put_calender_number(date_temp);
            if( date+1 == atoi( date_temp ) ) {
                date = date+1 ;
                change_weather(weather);
                put_calender_weather(weather);
                grow_oneday(record,date);
            }
            else {
                recover_field(record,username,nowfield);
                date = atoi(date_temp);
                change_weather(weather);
                put_calender_weather(weather);
                grow(record , date );
            }
        }
        else if( mouse_press(595,5,630,40)==2 )//退出键未点击
        {
            if( pauselight == 1 )
            {
                if(flag!=3)
                {
                    MouseS = 1 ;
                    flag = 3 ;
                    num[3] = 1;
                    clrmous(MouseX,MouseY);
                    back_button(LIGHT);
                }
            }
        }
        else if( mouse_press(595,5,630,40)==1 )//退出点击
        {
            MouseS = 0 ;
            clrmous(MouseX,MouseY);
            itoa(date,date_char,10);
            
            delay(200);
            return ;
        }
        else 
        {
            if(flag!=0)
            {
                MouseS = 0;
                flag = 0;
            }
        }

        if( flag!=1 && num[1]==1 )
        {
            num[1]=0;
            if(startlight!=1) {
                clrmous(MouseX,MouseY);
                start_button(RECOVER);
                
            }
        }
        else if( flag!=2 && num[2]==1 )
        {
            num[2]=0;
            if(pauselight != 1) {
                clrmous(MouseX,MouseY);
                pause_button(RECOVER);     
            }
        }
        else if( flag!=3 && num[3]==1 )
        {
            clrmous(MouseX,MouseY);
            back_button(RECOVER);
            num[3]=0;
        }
        if(startlight) time++ ;
        if(date > CALENDER_MAX) {
            itoa(date,date_char,10);
            return ;
        }
    }
    return ;
}

void show_chart(int record[21][26],char* now_field)
{
    int i,j;
    int flag = 0;
    double height[20];
    char *strheight[20];
    double sum[5];
    double crop1_sprout = 100,crop1_transition = 50,crop1_crop = 150;
    double crop2_sprout = 200,crop2_transition = 170,crop2_crop = 30;
    double crop3_sprout = 300,crop3_transition = 0,crop3_crop = 200;
    double crop1_sick = 60, crop1_healthy = 30;
    double crop2_sick = 10, crop2_healthy = 80;
    double crop3_sick = 45, crop3_healthy = 60;
    double locust = 10,ladybug = 5;

    for(i=0;i<21;i++)
    {
        for(j=0;j<26;j++)
        {
            if(record[i][j]>=10&&record[i][j]<=19) crop1_sprout++;
            else if(record[i][j]>=20&&record[i][j]<=29) crop1_transition++;
            else if(record[i][j]>=30&&record[i][j]<=39) crop1_crop++;
            else if(record[i][j]>=40&&record[i][j]<=49) crop2_sprout++;
            else if(record[i][j]>=50&&record[i][j]<=59) crop2_transition++;
            else if(record[i][j]>=60&&record[i][j]<=69) crop2_crop++;
            else if(record[i][j]>=70&&record[i][j]<=79) crop3_sprout++;
            else if(record[i][j]>=80&&record[i][j]<=89) crop3_transition++;
            else if(record[i][j]>=90&&record[i][j]<=99) crop3_crop++;
            
            if((record[i][j]>=10&&record[i][j]<=39)&&record[i][j]%10!=0) crop1_sick++;
            else if((record[i][j]>=10&&record[i][j]<=39)&&record[i][j]%10==0) crop1_healthy++;
            else if((record[i][j]>=40&&record[i][j]<=69)&&record[i][j]%10!=0) crop2_sick++;
            else if((record[i][j]>=40&&record[i][j]<=69)&&record[i][j]%10==0) crop2_healthy++;
            else if((record[i][j]>=70&&record[i][j]<=99)&&record[i][j]%10!=0) crop3_sick++;
            else if((record[i][j]>=70&&record[i][j]<=99)&&record[i][j]%10==0) crop3_healthy++;

            if((record[i][j]>=10&&record[i][j]<=99)&&((record[i][j]%10)>=1&&(record[i][j]%10)<=BUG)) locust++;
            else if((record[i][j]>=10&&record[i][j]<=99)&&((record[i][j]%10)>BUG&&(record[i][j]%10)<=9)) ladybug++;
        }
    }

    memset(height,0,sizeof(height));
    memset(sum,0,sizeof(sum));
    memset(strheight,0,sizeof(strheight));
    sum[0] = (crop1_sprout + crop1_transition + crop1_crop + crop2_sprout + crop2_transition + crop2_crop + crop3_sprout + crop3_transition + crop3_crop);
    sum[1] = (locust+ladybug);
    height[0] = (crop1_sprout/sum[0])*100;
    height[1] = (crop1_transition/sum[0])*100;
    height[2] = (crop1_crop/sum[0])*100;
    height[3] = (crop2_sprout/sum[0])*100;
    height[4] = (crop2_transition/sum[0])*100;
    height[5] = (crop2_crop/sum[0])*100;
    height[6] = (crop3_sprout/sum[0])*100;
    height[7] = (crop3_transition/sum[0])*100;
    height[8] = (crop3_crop/sum[0])*100;

    height[9] = (crop1_healthy/sum[0]*100);
    height[10] = (crop1_sick/sum[0]*100);
    height[11] = (crop2_healthy/sum[0]*100);
    height[12] = (crop2_sick/sum[0]*100);
    height[13] = (crop3_healthy/sum[0]*100);
    height[14] = (crop3_sick/sum[0]*100);

    height[15] = (locust/sum[1])*100;
    height[16] = (ladybug/sum[1])*100;


    setfillstyle(SOLID_FILL,WHITE);
    bar(105,0,640,480);

    setcolor(DARKGRAY);
    settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
    outtextxy(427,210,"RICE");
    outtextxy(494,210,"CORN");
    outtextxy(557,210,"CANE");
    outtextxy(545,42,"SPROUT");
    outtextxy(545,52,"TRANSITION");
    outtextxy(545,62,"CROP");
    outtextxy(173,210,"LOCUST");
    outtextxy(250,210,"LADYBUG");
    outtextxy(295,292,"HEALTHY");
    outtextxy(295,302,"SICK");
    outtextxy(160,450,"RICE");
    outtextxy(220,450,"CORN");
    outtextxy(280,450,"CANE");

    setfillstyle(SOLID_FILL,RED);
    bar(530,40,540,50);
    bar(420,200-((int)height[0])*2,435,200);
    bar(485,200-((int)height[3])*2,500,200);
    bar(550,200-((int)height[6])*2,565,200);

    setfillstyle(SOLID_FILL,BLUE);
    bar(530,51,540,60);
    bar(436,200-((int)height[1])*2,450,200);
    bar(501,200-((int)height[4])*2,515,200);
    bar(566,200-((int)height[7])*2,580,200);

    setfillstyle(SOLID_FILL,LIGHTGREEN);
    bar(530,61,540,70);
    bar(451,200-((int)height[3])*2,465,200);
    bar(516,200-((int)height[5])*2,530,200);
    bar(581,200-((int)height[8])*2,595,200);

    setfillstyle(SOLID_FILL,CYAN);
    bar(190,200-((int)height[15]),205,200);
    bar(270,200-((int)height[16]),285,200);

    setfillstyle(SOLID_FILL,MAGENTA);
    bar(280,290,290,300);
    bar(160,440-((int)height[9])*2,175,440);
    bar(220,440-((int)height[11])*2,235,440);
    bar(280,440-((int)height[13])*2,295,440);

    setfillstyle(SOLID_FILL,LIGHTBLUE);
    bar(280,301,290,310);
    bar(176,440-((int)height[10])*2,190,440);
    bar(236,440-((int)height[12])*2,250,440);
    bar(296,440-((int)height[14])*2,310,440);



    
    setcolor(DARKGRAY);
    setlinestyle(SOLID_LINE,0,THICK_WIDTH);
    line(130,200,355,200);
    line(130,200,130,40);
    line(395,200,620,200);
    line(395,200,395,40);
    line(130,440,355,440);
    line(130,440,130,280);
    line(395,440,620,440);
    line(395,440,395,280);
    
    line(355,200,345,197);
    line(355,200,345,203);
    line(133,50,130,40);
    line(127,50,130,40);
    line(610,203,620,200);
    line(610,197,620,200);
    line(392,50,395,40);
    line(398,50,395,40);
    line(345,437,355,440);
    line(345,443,355,440);
    line(133,290,130,280);
    line(127,290,130,280);
    line(610,443,620,440);
    line(610,437,620,440);
    line(398,290,395,280);
    line(392,290,395,280);
    
    settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
    outtextxy(200,20,"PEST RATE");
    outtextxy(435,20,"CROP SITUATION RATE");
    outtextxy(185,260,"SICK CROP RATE");
    outtextxy(455,260,"SPROUTING RATE");

    mouseinit();
    while(1)
    {
        newmouse(&MouseX,&MouseY,&press);
        if(mouse_press(5,280,95,319)==2)
        {
            if(flag!=1)
            {
                MouseS = 1;
                flag = 1;
            }
        }
        else if(mouse_press(5,280,95,319)==1)
        {
            return;
        }
        else
        {
            if(flag!=0)
            {
                MouseS = 0;
                flag = 0;
            }
        }
    }
}

void setinfo(char *username,struct droneinfo record[])
{
    int i;
    int flag = 0;
    char string[80] = "c:\\DATA";
    char stringnow[80];
    FILE* fp;
    clrmous(MouseX,MouseY);
    setfillstyle(SOLID_FILL,BLUE);
    bar(100,100,540,400);
    setfillstyle(SOLID_FILL,LIGHTBLUE);
    bar(100,100,540,105);
    bar(100,100,105,400);
    bar(100,395,540,400);
    bar(535,100,540,400);
    for(i=0;i<5;i++)
    {
        bar(100,100+50*(i+1),540,105+50*(i+1));
    }
    bar(260,100,265,400);

    settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
    outtextxy(110,120,"HOUSE1");
    outtextxy(110,170,"HOUSE2");
    outtextxy(110,220,"HOUSE3");
    outtextxy(110,270,"HOUSE4");

    strcat(string,"\\");
    strcat(string,username);
    strcat(string,"\\");

    mouseinit();
    while(1)
    {
        newmouse(&MouseX,&MouseY,&press);
        if(mouse_press(270,105,535,150)==2)
        {
            if(flag!=1)
            {
                MouseS = 2;
                flag = 1;
            }
        }
        else if(mouse_press(270,105,535,150)==1)
        {
            temp_input(record[0].name,280,119,5,25,20,BLUE,3);
            strcpy(stringnow,string);
            strcat(stringnow,"DRONE\\");
            strcat(stringnow,record[0].name);
            strcat(stringnow,".dat");
            if((fp=fopen(stringnow,"rb"))!=NULL)
            {
                fread(&record[0],sizeof(DRONEINFO),1,fp);
                
            }
            else
            {
                warning("NOT EXIST!",280,255,1);
                delay(100);
                setfillstyle(SOLID_FILL,BLUE);
                bar(280,110,525,140);
                memset(record[0].name,0,sizeof(record[0].name));
            }
            settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
                outtextxy(320,100,record[0].name);
                outtextxy(320,100,record[0].weight);
        }
        else if(mouse_press(270,155,535,200)==2)
        {
            if(flag!=2)
            {
                MouseS = 2;
                flag = 2;
            }
        }
        else if(mouse_press(270,155,535,200)==1)
        {
            temp_input(record[1].name,280,169,5,25,20,BLUE,3);
        }
        else if(mouse_press(270,205,535,250)==2)
        {
            if(flag!=3)
            {
                MouseS = 2;
                flag = 3;
            }
        }
        else if(mouse_press(270,205,535,250)==1)
        {
            temp_input(record[2].name,280,219,5,25,20,BLUE,3);
        }
        else if(mouse_press(270,255,535,300)==2)
        {
            if(flag!=4)
            {
                MouseS = 2;
                flag = 4;
            }
        }
        else if(mouse_press(270,255,535,300)==1)
        {
            temp_input(record[3].name,280,119,5,25,20,BLUE,3);
        }
        else
        {
            if(flag!=0)
            {
                flag = 0;
                MouseS = 0;
            }
        }
    }
}

