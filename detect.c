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
void put_calender_weather(char *weather)
{
    setfillstyle(SOLID_FILL,WHITE);
    bar(8,73,65,117);
    if(strcmp(weather,"cloud")==0 ) {
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
int detect_page(char *username,char *nowfield)
{
    int record[21][26];
    int i,k,pre_x=-1,pre_y=-1,x,y,temp_date;
    int flag = 0,flag2 = 0 , mode = 0, handmode_flag = 0 , automode_flag = 0 , routebutton_flag = 0 , line_flag = 0,field_flag=0;
    int num[10];
    char path[100]="C:\\DATA\\";
    char *presentmode;
    char *tempmsgs[2] = {"hand>","auto>"};
    FILE *fp;
    int route[100][2];
    char date[10] = "1" , compare[10] ;

    memset(record , 0 , sizeof(record));
    memset(route,-1,sizeof(route));
    memset(compare , 0 ,sizeof(compare));

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
    if( strlen(date) != 0 ) {
        put_calender_number(date);
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
                    paint_field_right(record , nowfield );
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
            strcpy(compare , date );
            setfillstyle(SOLID_FILL,WHITE);
            bar(11,25,90,69);
            temp_input(date , 18,35, 3 , 22 ,20,WHITE,3);//4 33 25
            put_calender_number(date);
            if(strcmp(compare , date )!= 0  ) {
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
                paint_field_right(record , nowfield );
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
                    if(line_flag != 1 ) line_flag = 1 ;
                }
                
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
                    auto_simulate( record , date );
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
                else if( mouse_press(595,5,630,40)==1 )//退出点击
                {
                    MouseS = 0 ;
                    clrmous(MouseX,MouseY);
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
            delay(200);
        }
    }
}
void recover_field(int record[21][26],char *username , char *nowfield )
{
    int i,j ;
    char path[100]="C:\\DATA\\";
    FILE *fp;
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
}
void grow(int record[21][26] , int date ) //reord从最初始状态，直接计算date状态时现象
{
    int i,j,k,x,y,random_grow, random_health , state , health ,crop;
    srand((unsigned)time(NULL));
    
    for(i=0;i<21;i++)//y
    {
        for(j=0;j<26;j++)//x 
        {
            x = 110 + j*20 ;
            y = 470-i*20-20 ;
            if ( record[i][j] )
            {
                setfillstyle(SOLID_FILL,DARKGRAY);
                bar(x , y , x+20 , y+20 );
            }
            if((record[i][j]>=10 && record[i][j]<=39)) //crop1 / 12  24
            {
                crop = 1 ;
                state = SPROUT ;
                health = HEALTHY ;
                random_grow = rand() % 100 ;//0-99
                if(date >= CROP1_STATE1 ) {
                    if(random_grow <= 90) {
                        state = TRANSITION ;
                    }
                }  
                if(date >= CROP1_STATE2 ) {
                    random_grow = rand() % 100 ;
                    if(state == TRANSITION && random_grow <= 90) {
                        state = CROP ;
                    }
                }
                random_health = rand() % 100 ;
                if(random_health <= 20) health = SICK ;
                else health = HEALTHY ;

                put_crop1(x,y,state , health);
            }
            else if(record[i][j]>=40 && record[i][j]<=69) //crop2  / 10 20
            {
                crop = 2 ;
                state = SPROUT ;
                health = HEALTHY ;
                random_grow = rand() % 100 ;//0-99
                if(date >= CROP2_STATE1 ) {
                    if(random_grow <= 90) {
                        state = TRANSITION ;
                    }
                }  
                if(date >= CROP2_STATE2 ) {
                    random_grow = rand() % 100 ;
                    if(state == TRANSITION && random_grow <= 90) {
                        state = CROP ;
                    }
                }
                random_health = rand() % 100 ;
                if(random_health <= 20) health = SICK ;
                else health = HEALTHY ;

                put_crop2(x,y,state , health);
            }
            else if(record[i][j]>=70 && record[i][j]<=99) //crop3 / 14 28
            {
                crop = 3 ;
                state = SPROUT ;
                health = HEALTHY ;
                random_grow = rand() % 100 ;//0-99
                if(date >= CROP3_STATE1 ) {
                    if(random_grow <= 90) {
                        state = TRANSITION ;
                    }
                }  
                if(date >= CROP3_STATE2 ) {
                    random_grow = rand() % 100 ;
                    if(state == TRANSITION && random_grow <= 90) {
                        state = CROP ;
                    }
                }
                random_health = rand() % 100 ;
                if(random_health <= 20) health = SICK ;
                else health = HEALTHY ;

                put_crop3(x,y,state , health);
            }
            else if( record[i][j]==3 )
            {
                put_house(x,y,BROWN,CYAN,2);
            }
            else if( record[i][j]==4 )
            {
                put_house(x,y,BROWN,MAGENTA,2);
            }
            else if( record[i][j]==5 )
            {
                put_house(x,y,BROWN,YELLOW,2);
            }
            else if( record[i][j]==6 )
            {
                put_house(x,y,BROWN,BLUE,2);
            }
        }
    }
}
void grow_oneday(int record[21][26] ,int date)
{
    int random_sick ,random_state ,health , state ,crop ,one_place , ten_place ,date_one,date_ten;
    int i , j ,x,y;
    srand((unsigned)time(NULL));
    for(i=0;i<21;i++)//y
    {
        for(j=0;j<26;j++) //x
        {
            x = 110 + j*20 ;
            y = 470-i*20-20 ;
            one_place = record[i][j] % 10 ;
            ten_place = record[i][j]/10 ;
            date_one = date % 10 ;
            date_ten = date / 10 ;
            
            random_sick = rand() % 100 ;
            health = HEALTHY ;
            if(one_place == 0 && ten_place!=0)
            {
                if(random_sick <= 3 && one_place <= 8) {
                    record[i][j] += 3 ;
                    health = SICK ;
                }
            }
            else if(one_place != 0 ) {
                health = SICK ;
            }

            random_state = rand() % 100 ;
            if(date >= CROP1_STATE1-3 && date <= CROP1_STATE1+3 && ten_place==1 ) {
                state = SPROUT ;
                if(random_state <= 90) {
                    state = TRANSITION ;
                    record[i][j]+=10 ;
                }
            }
            else if(date >= CROP1_STATE2-3 && date <= CROP1_STATE2+3 && ten_place==2 ) {
                state = TRANSITION ;
                if(random_state <= 90) {
                    state = CROP ;
                    record[i][j]+=10 ;
                }
            }
            else if(date >= CROP2_STATE1-3 && date <= CROP2_STATE1+3 && ten_place==4 ) {
                state = SPROUT ;
                if(random_state <= 90) {
                    state = TRANSITION ;
                    record[i][j]+=10 ;
                }
            }
            else if(date >= CROP2_STATE2-3 && date <= CROP2_STATE2+3 && ten_place==5 ) {
                state = TRANSITION ;
                if(random_state <= 90) {
                    state = CROP ;
                    record[i][j]+=10 ;
                }
            }
            else if(date >= CROP3_STATE1-3 && date <= CROP3_STATE1+3 && ten_place==7 ) {
                state = SPROUT ;
                if(random_state <= 90) {
                    state = TRANSITION ;
                    record[i][j]+=10 ;
                }
            }
            else if(date >= CROP3_STATE2-3 && date <= CROP3_STATE2+3 && ten_place==8 ) {
                state = TRANSITION ;
                if(random_state <= 90) {
                    state = CROP ;
                    record[i][j]+=10 ;
                }
            }

            if((record[i][j]>=10 && record[i][j]<=39 ))
            {
                crop = 1;
                // setfillstyle(SOLID_FILL,DARKGRAY);
                // bar(x,y,x+20,y+20);
                // delay(50);
                put_crop1(x,y,state,health);
            }
            else if((record[i][j]>=40 && record[i][j]<=69)) {
                crop = 2 ;
                // setfillstyle(SOLID_FILL,DARKGRAY);
                // bar(x,y,x+20,y+20);
                put_crop2(x,y,state,health);
            }
            else if((record[i][j]>=70 && record[i][j]<=99)) {
                crop = 3 ;
                // setfillstyle(SOLID_FILL,DARKGRAY);
                // bar(x,y,x+20,y+20);
                put_crop3(x,y,state,health);
            }
        }
    }
}
void auto_simulate(int record[21][26], char *date_char )
{
    int date ,i,j, add = 1 , flag = 0 , startlight = 1 , pauselight = 0 ;
    long long int time ;
    int num[10];
    char date_temp[10];

    memset(date_temp,0,sizeof(date_temp));
    memset(num,0,sizeof(num));
    date = atoi( date_char );//从date天开始
    grow(record , date );

    mouseinit();

    while(1)
    {
        newmouse(&MouseX,&MouseY,&press);

        if(time%1000000 == 0) 
        {
            itoa(date , date_temp , 10);
            put_calender_number(date_temp);
            grow_oneday(record,date);
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
            delay(200);
            break ;
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
            delay(200);
            return HOME;
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
            if(startlight!=1) {
                clrmous(MouseX,MouseY);
                start_button(RECOVER);
                num[1]=0;
            }
        }
        else if( flag!=2 && num[2]==1 )
        {
            if(pauselight != 1) {
                clrmous(MouseX,MouseY);
                pause_button(RECOVER);
                num[2]=0;
            }
        }
        else if( flag!=3 && num[3]==1 )
        {
            clrmous(MouseX,MouseY);
            back_button(RECOVER);
            num[3]=0;
        }
        if(startlight) time++ ;
        if(date > CALENDER_MAX) break ;
    }
}
