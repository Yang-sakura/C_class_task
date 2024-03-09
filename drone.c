#include "public.h"
#include "drone.h"
#include "main.h"

void drone_screen()
{
    back_button(PAINT);

    put_drone2(12,140,DARKGRAY,LIGHTGRAY,15);
    printbox(300,60,550,200,DARKGRAY,1,5,5);
    printbox(300,260,550,400,DARKGRAY,1,5,5);
    setcolor(DARKGRAY);
    settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
    outtextxy(330,117,"CREATE");
    outtextxy(345,317,"DRONE");
}

void open_file2()
{
    clrmous(MouseX,MouseY);
    setfillstyle(SOLID_FILL,LIGHTBLUE);
    bar(110,50,630,400);
    printline(110,50,1,104,0,BLUE,5,0);
    printline(110,395,1,104,0,BLUE,5,0);
    printline(110,50,1,70,1,BLUE,5,0);
    printline(625,50,1,70,1,BLUE,5,0);
    printline(110,95,1,104,0,BLUE,5,0);
    printline(110,145,1,104,0,BLUE,5,0);
    printline(110,195,1,104,0,BLUE,5,0);
    printline(110,245,1,104,0,BLUE,5,0);
    printline(110,295,1,104,0,BLUE,5,0);
    printline(110,345,1,104,0,BLUE,5,0);
    printline(110,395,1,104,0,BLUE,5,0);
    
    put_arrow(120,353,DARKGRAY,5,1);
    put_arrow(540,353,DARKGRAY,5,2);
}


int drone_page(char *username,char *drone_name_now,DRONEINFO *drone)
{
    struct ffblk ffblk;   
    int flag;
    int num[4];
    int file_flag;
    int filenum[10];
    int mode = 0;
    int done;
    int i;
    int file_number=0;
    int filetime = 1;
    int pagemax;
    int page = 0;
    char string[80] = "c:\\DATA\\";
    char stringnow[80];
    char stringall[80];
    char drone_list[40][20];
    char drone_name[20];
    FILE *fp;
    strcat(string,username);
    strcat(string,"\\DRONE");

    strcpy(stringall,string);
    strcat(stringall,"\\*.*");

    if(access(string,0)==-1)  //协助创建无人机文件夹
    {
        if(mkdir(string)!=0)
        {
            perror("ERROR IN BUILDING THE FIELD PACKAGE!");
            delay(2000);
            exit(1);
        }
    }

    memset(drone_name,0,sizeof(drone_name));

    clrmous(MouseX,MouseY);
    cleardevice();

    drone_screen();
    mouseinit();
    while(1)
    {
        newmouse(&MouseX,&MouseY,&press);
        if(mouse_press(300,60,550,200)==2)
        {
            if(flag!=1)
            {
                MouseS = 1;
                flag = 1;
                num[1] = 1;
                clrmous(MouseX,MouseY);
                printbox(300,60,550,200,YELLOW,1,5,5);
                setcolor(CYAN);
                settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
                outtextxy(330,117,"CREATE");
            }
        }
        else if(mouse_press(300,60,550,200)==1)
        {
            clrmous(MouseX,MouseY);
            setfillstyle(SOLID_FILL,WHITE);
            bar(300,60,550,200);
            printbox(300,60,550,200,YELLOW,1,5,5);
            temp_input(drone_name,330,117,6,33,25,WHITE,4);
            if(strlen(drone_name)!=0)
            {
                strcpy(stringnow,string);
                strcat(stringnow,"\\");
                strcat(stringnow,drone_name);
                strcat(stringnow,".dat");
                if((fp=fopen(stringnow,"wb+"))!=NULL)
                {
                    fread(&drone,sizeof(DRONEINFO),1,fp);
                }
                else
                {
                    perror("ERROR IN CREATING!");
                }
                fclose(fp);
                free(drone_list);
                clrmous(MouseX,MouseY);
                cleardevice();
                MouseS = 0;
                strcpy(drone_name_now,drone_name);
                return DRONE_LIST;
                
            }
        }
        else if(mouse_press(300,260,550,400)==2)
        {
            if(flag!=2)
            {
                MouseS = 1;
                flag = 2;
                num[2] = 1;
                clrmous(MouseX,MouseY);
                printbox(300,260,550,400,YELLOW,1,5,5);
                setcolor(CYAN);
                settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
                outtextxy(345,317,"DRONE");
            }
        }
        else if(mouse_press(300,260,550,400)==1)
        {
            mode = 2;
        }
        else if(mouse_press(595,5,630,40)==2)
        {
            if(flag!=3)
            {
                MouseS = 1;
                flag = 3;
                num[3] = 1;
                back_button(LIGHT);
            }
        }
        else if(mouse_press(595,5,630,40)==1)
        {
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

        if(flag!=1&&num[1]==1)
        {
            clrmous(MouseX,MouseY);
            printbox(300,60,550,200,DARKGRAY,1,5,5);
            setcolor(DARKGRAY);
            settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
            outtextxy(330,117,"CREATE");
            num[1]=0;
        }
        else if(flag!=2&&num[2]==1)
        {
            clrmous(MouseX,MouseY);
            printbox(300,260,550,400,DARKGRAY,1,5,5);
            setcolor(DARKGRAY);
            settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
            outtextxy(345,317,"DRONE");
            num[2]=0;
        }
        else if(flag!=3&&num[3]==1)
        {
            back_button(RECOVER);
            num[3]=0;
        }

        if(mode == 1)
        {
            setfillstyle(SOLID_FILL,WHITE);
            bar(80,0,640,480);

            open_file2();
            put_arrow(120,353,DARKGRAY,5,1);
            put_arrow(540,353,DARKGRAY,5,2);
            back_button(PAINT);
            
            memset(drone_list,0,sizeof(drone_list));
            while(1)
            {
                newmouse(&MouseX,&MouseY,&press);
                if(filetime == 1)
                {
                    file_number = 0;
                    i=0;
                    done = findfirst(stringall,&ffblk,0);
                    while(!done)
                    {
                        strcpy(drone_list[i],ffblk.ff_name);
                        string_limitation(drone_list[i],15);
                        done = findnext(&ffblk);
                        i++;
                        file_number++;
                    }
                    open_file2();
                    setcolor(DARKGRAY);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
                    pagemax = file_number/6;
                    if(file_number%6==0)
                    {
                        pagemax -=1;
                    }
                    if((file_number-6*page)>=0)
                    {
                        for(i=0;i<6;i++)
                        {
                            clrmous(MouseX,MouseY);
                            outtextxy(118,60+50*(i),drone_list[i+page*6]);
                        }
                    }
                    filetime = 0;
                }
                
                if(mouse_press(595,5,630,40)==2)
                {
                    if(file_flag!=1)
                    {
                        MouseS = 1;
                        file_flag = 1;
                        filenum[1] = 1;
                        clrmous(MouseX,MouseY);
                        back_button(LIGHT);
                    }
                }
                else if(mouse_press(595,5,630,40)==1)
                {
                    clrmous(MouseX,MouseY);
                    cleardevice();
                    mode = 0;
                    MouseS = 0;
                    return DRONE;
                }
                else if(mouse_press(115,55,625,95)==2)
                {
                    if(file_flag!=2)
                    {
                        MouseS = 1;
                        file_flag = 2;
                        filenum[2] = 1;
                        clrmous(MouseX,MouseY);
                        setcolor(CYAN);
                        settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
                        outtextxy(118,60+50*0,drone_list[0+page*6]);
                    }
                }
                else if(mouse_press(115,55,625,95)==1)
                {
                    for(i=0;i<strlen(drone_list[0+page*6])-4;i++)
                        drone_name_now[i] = drone_list[0+page*6][i];
                    return DRONE_LIST;
                }
                else if(mouse_press(115,100,625,145)==2)
                {
                    if(file_flag!=3)
                    {
                        MouseS = 1;
                        file_flag = 3;
                        filenum[3] = 1;
                        clrmous(MouseX,MouseY);
                        setcolor(CYAN);
                        settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
                        outtextxy(118,60+50*1,drone_list[1+page*6]);
                    }
                }
                else if(mouse_press(115,100,625,145)==1)
                {
                    for(i=0;i<strlen(drone_list[1+page*6])-4;i++)
                        drone_name_now[i] = drone_list[1+page*6][i];
                    return DRONE_LIST;
                    return DRONE_LIST;
                }
                else if(mouse_press(115,150,625,195)==2)
                {
                    if(file_flag!=4)
                    {
                        MouseS = 1;
                        file_flag = 4;
                        filenum[4] = 1;
                        clrmous(MouseX,MouseY);
                        setcolor(CYAN);
                        settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
                        outtextxy(118,60+50*2,drone_list[2+page*6]);
                    }
                }
                else if(mouse_press(115,150,625,195)==1)
                {
                    for(i=0;i<strlen(drone_list[2+page*6])-4;i++)
                        drone_name_now[i] = drone_list[2+page*6][i];
                    return DRONE_LIST;
                }
                else if(mouse_press(115,200,625,245)==2)
                {
                    if(file_flag!=2)
                    {
                        MouseS = 1;
                        file_flag = 5;
                        filenum[5] = 1;
                        clrmous(MouseX,MouseY);
                        setcolor(CYAN);
                        settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
                        outtextxy(118,60+50*3,drone_list[3+page*6]);
                    }
                }
                else if(mouse_press(115,200,625,245)==1)
                {
                    for(i=0;i<strlen(drone_list[3+page*6])-4;i++)
                        drone_name_now[i] = drone_list[3+page*6][i];
                    return DRONE_LIST;
                }
                else if(mouse_press(115,250,625,295)==2)
                {
                    if(file_flag!=6)
                    {
                        MouseS = 1;
                        file_flag = 6;
                        filenum[6] = 1;
                        clrmous(MouseX,MouseY);
                        setcolor(CYAN);
                        settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
                        outtextxy(118,60+50*4,drone_list[4+page*6]);
                    }
                }
                else if(mouse_press(115,250,625,295)==1)
                {
                    for(i=0;i<strlen(drone_list[4+page*6])-4;i++)
                        drone_name_now[i] = drone_list[4+page*6][i];
                    return DRONE_LIST;
                }
                else if(mouse_press(115,300,625,345)==2)
                {
                    if(file_flag!=7)
                    {
                        MouseS = 1;
                        file_flag = 7;
                        filenum[7] = 1;
                        clrmous(MouseX,MouseY);
                        setcolor(CYAN);
                        settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
                        outtextxy(118,60+50*5,drone_list[5+page*6]);
                    }
                }
                else if(mouse_press(115,300,625,345)==1)
                {
                    for(i=0;i<strlen(drone_list[5+page*6])-4;i++)
                        drone_name_now[i] = drone_list[5+page*6][i];
                    return DRONE_LIST;
                }
                else if(mouse_press(120,353,200,393)==2)
                {
                    if(file_flag!=8)
                    {
                        MouseS = 1;
                        file_flag = 8;
                        filenum[8] = 1;
                        clrmous(MouseX,MouseY);
                        put_arrow(120,353,CYAN,5,1);
                    }
                }
                else if(mouse_press(120,353,200,393)==1)
                {
                    delay(50);
                    if(page>=1)
                    {
                        page--;
                        filetime = 1;
                    }
                }
                else if(mouse_press(540,353,620,393)==2)
                {
                    if(file_flag!=9)
                    {
                        MouseS = 1;
                        file_flag = 9;
                        filenum[9] = 1;
                        clrmous(MouseX,MouseY);
                        put_arrow(540,353,CYAN,5,2);
                    }
                }
                else if(mouse_press(540,353,620,393)==1)
                {
                    delay(50);
                    if(page<pagemax)
                    {
                        page++;
                        filetime = 1;
                    }
                }
                else
                {
                    if(file_flag!=0)
                    {
                        MouseS = 1;
                        file_flag = 0;
                    }
                }

                if(file_flag!=1&&filenum[1]==1)
                {
                    clrmous(MouseX,MouseY);
                    back_button(RECOVER);
                    filenum[1] = 0;
                }
                else if(file_flag!=2&&filenum[2]==1)
                {
                    clrmous(MouseX,MouseY);
                    setcolor(DARKGRAY);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
                    outtextxy(118,60+50*0,drone_list[0+page*6]);
                    filenum[2] = 0;
                }
                else if(file_flag!=3&&filenum[3]==1)
                {
                    clrmous(MouseX,MouseY);
                    setcolor(DARKGRAY);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
                    outtextxy(118,60+50*1,drone_list[1+page*6]);
                    filenum[3] = 0;
                }
                else if(file_flag!=4&&filenum[4]==1)
                {
                    clrmous(MouseX,MouseY);
                    setcolor(DARKGRAY);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
                    outtextxy(118,60+50*2,drone_list[2+page*6]);
                    filenum[4] = 0;
                }
                else if(file_flag!=5&&filenum[5]==1)
                {
                    clrmous(MouseX,MouseY);
                    setcolor(DARKGRAY);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
                    outtextxy(118,60+50*3,drone_list[3+page*6]);
                    filenum[5] = 0;
                }
                else if(file_flag!=6&&filenum[6]==1)
                {
                    clrmous(MouseX,MouseY);
                    setcolor(DARKGRAY);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
                    outtextxy(118,60+50*4,drone_list[4+page*6]);
                    filenum[6] = 0;
                }
                else if(file_flag!=7&&filenum[7]==1)
                {
                    clrmous(MouseX,MouseY);
                    setcolor(DARKGRAY);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
                    outtextxy(118,60+50*5,drone_list[5+page*6]);
                    filenum[7] = 0;
                }
                else if(file_flag!=8&&filenum[8]==1)
                {
                    clrmous(MouseX,MouseY);
                    put_arrow(120,353,DARKGRAY,5,1);
                    filenum[8] = 0;
                }
                else if(file_flag!=9&&filenum[9]==1)
                {
                    clrmous(MouseX,MouseY);
                    put_arrow(540,353,DARKGRAY,5,2);
                    filenum[9] = 0;
                }

            }
        }
    }
}
