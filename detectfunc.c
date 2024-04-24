#include "public.h"
#include "detectfunc.h"

void change_weather(char *weather)
{
    int random_weather ;
    srand((unsigned)time(NULL));
    random_weather = rand() % 100 ;
    if(random_weather <= 20 ) {
        strcpy(weather,"sun");
    }
    else if(random_weather >20 && random_weather <= 40 ) {
        strcpy(weather,"rain");
    }
    else if(random_weather > 40 && random_weather <=50 ) {
        strcpy(weather,"snow");
    }
    else {
        strcpy(weather,"cloud");
    }
    return ;
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

                if(date ==  1) health = HEALTHY ;

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

                if(date ==  1) health = HEALTHY ;

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

                if(date ==  1) health = HEALTHY ;

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
    int random_sick ,random_state ,health , state ,one_place , ten_place ,date_one,date_ten,crop = -1;
    int i , j ,x,y;
    char temp_out[20];
    srand((unsigned)time(NULL));
    setwritemode(COPY_PUT);
    if(date == 1 ) return ;
    for(i=0;i<21;i++)//y
    {
        for(j=0;j<26;j++) //x
        {
            if(record[i][j] < 10 ) continue ;
            x = 110 + j*20 ;
            y = 450 - i*20 ;
            one_place = record[i][j] % 10 ;
            ten_place = record[i][j] / 10 ;
            date_one = date % 10 ;
            date_ten = date / 10 ;
            health = HEALTHY ;
            state = SPROUT ;

            random_sick = rand() % 100 ;
            if(record[i][j] >= 10 )
            {
                if(one_place == 0 )
                {
                    if(random_sick <= 3 ) {
                        record[i][j] += 3 ;
                        health = SICK ;
                    }
                }
                else if(one_place != 0 ) {
                    health = SICK ;
                }
            }
            crop = -1 ;
            
            if( record[i][j]>=10 && record[i][j]<=39 ){
                crop = 1 ;
                if(record[i][j]>=10 && record[i][j]<=19 ) {
                    state = SPROUT ;
                } 
                else if(record[i][j]>=20 && record[i][j]<=29 ) {
                    state = TRANSITION ;
                } 
                else if(record[i][j]>=30 && record[i][j]<=39 ) {
                    state = CROP ;
                } 
            }
            else if( record[i][j]>=40 && record[i][j]<=69 ){
                crop = 2 ;
                if(record[i][j]>=40 && record[i][j]<=49 ) {
                    state = SPROUT ;
                } 
                else if(record[i][j]>=50 && record[i][j]<=59 ) {
                    state = TRANSITION ;
                } 
                else if(record[i][j]>=60 && record[i][j]<=69 ) {
                    state = CROP ;
                } 
            }
            else if( record[i][j]>=70 && record[i][j]<=99 ){
                crop = 3 ;
                if(record[i][j]>=70 && record[i][j]<=79 ) {
                    state = SPROUT ;
                } 
                else if(record[i][j]>=80 && record[i][j]<=89 ) {
                    state = TRANSITION ;
                } 
                else if(record[i][j]>=90 && record[i][j]<=99 ) {
                    state = CROP ;
                } 
            }
                        
            random_state = rand() % 100 ;
            if(date >= CROP1_STATE1-3 && date <= CROP1_STATE1+3 && ten_place == 1 ) {
                crop = 1 ;
                state = SPROUT ;
                if(random_state <= 90 && record[i][j] <= 20 ) {
                    state = TRANSITION ;
                    record[i][j]+=10 ;
                }
            }
            else if(date >= CROP1_STATE2-3 && date <= CROP1_STATE2+3 && ten_place==2 ) {
                crop = 1 ;
                state = TRANSITION ;
                if(random_state <= 90 && record[i][j] <= 30 ) {
                    state = CROP ;
                    record[i][j]+=10 ;
                }
            }
            else if(date >= CROP2_STATE1-3 && date <= CROP2_STATE1+3 && ten_place==4 ) {
                crop = 2 ;
                state = SPROUT ;
                if(random_state <= 90 && record[i][j] <= 40 ) {
                    state = TRANSITION ;
                    record[i][j]+=10 ;
                }
            }
            else if(date >= CROP2_STATE2-3 && date <= CROP2_STATE2+3 && ten_place==5 ) {
                crop = 2 ;
                state = TRANSITION ;
                if(random_state <= 90 && record[i][j] <= 60 ) {
                    state = CROP ;
                    record[i][j]+=10 ;
                }
            }
            else if(date >= CROP3_STATE1-3 && date <= CROP3_STATE1+3 && ten_place==7 ) {
                crop = 3 ;
                state = SPROUT ;
                if(random_state <= 90 && record[i][j] <= 80 ) {
                    state = TRANSITION ;
                    record[i][j]+=10 ;
                }
            }
            else if(date >= CROP3_STATE2-3 && date <= CROP3_STATE2+3 && ten_place==8 ) {
                crop = 3 ;
                state = TRANSITION ;
                if(random_state <= 90 && record[i][j] <= 90 ) {
                    state = CROP ;
                    record[i][j]+=10 ;
                }
            }
            // setlinestyle(SOLID_LINE,0,NORM_WIDTH);
            // setcolor(RED);
            // line(x,y+20,x+20,y+20);
            if(crop == 1 )
            {
                put_crop1(x,y,state,health);
            }
            else if(crop == 2)
            {
                put_crop2(x,y,state,health);
            }
            else if(crop == 3 )
            {
                put_crop3(x,y,state,health);
            }
        }
    }
}
void find_house(int record[21][26] , int houserecord[4][2])
{
    int i,j,k ;
    k = 0 ;
    for(i=0;i<21;i++)//y
    {
        for(j=0;j<26;j++)//x
        {
            if( record[i][j]==3 )
            {
                houserecord[k][0] = i ;
                houserecord[k][1] = j ;
                k++ ;
            }
            else if( record[i][j]==4 )
            {
                houserecord[k][0] = i ;
                houserecord[k][1] = j ;
                k++ ;
            }
            else if( record[i][j]==5 )
            {
                houserecord[k][0] = i ;
                houserecord[k][1] = j ;
                k++ ;
            }
            else if( record[i][j]==6 )
            {
                houserecord[k][0] = i ;
                houserecord[k][1] = j ;
                k++ ;
            }
            if( k >= 4 ) return ;
        }
    }
}
Point find_closest_house(int record[21][26])
{
    Point house ;
    int i,j,crop_i = -1, crop_j = -1;
    float dis = MAX ,temp_dis;
    for(i=0;i<21;i++)//y
    {
        for(j=0;j<26;j++)//x
        {
            if(record[i][j]>=10 && crop_i == -1) //左下角第一个植株
            {
                crop_i = i ;
                crop_j = j ;
            }
            else if( record[i][j]>=3 && record[i][j]<=6 ) 
            {
                temp_dis = sqrt((i-crop_i)*(i-crop_i)+(j-crop_j)*(j-crop_j)) ;
                if( temp_dis < dis ) {
                    dis = temp_dis ;
                    house.x = 110 + j*20 ;
                    house.y = 470-i*20-20 ;
                }
            }
        }
    }
    return house ;
}
// i = (470-MouseY)/20;
// j = (MouseX - 110)/20;
// x = 110 + j*20 ;
// y = 470-i*20-20 ;
void show_chart(int record[21][26] ,char *nowfield)
{
    setfillstyle(SOLID_FILL,BLUE);
    bar(200,200,300,300);
    paint_field_right(record);
    while(1)
    {
        newmouse(&MouseX,&MouseY,&press);
        
        if( mouse_press(595,5,630,40)==1 )//退出点击
        {
            MouseS = 0 ;
            clrmous(MouseX,MouseY);
            delay(200);
            return ;
        }
    }
}
