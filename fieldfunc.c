#include "fieldfunc.h"
#include "public.h"
#include "main.h"

void draw_field_screen()
{
    back_button(PAINT);

    put_pencil(12,50,DARKGRAY,DARKGRAY,LIGHTGRAY,5);
    put_rubber(12,150,DARKGRAY,5);
    put_file(12,260,DARKGRAY,LIGHTGRAY,5);
}

void open_file()
{
    setfillstyle(SOLID_FILL,LIGHTBLUE);
    bar(110,50,630,400);
    printline(110,50,1,104,0,BLUE,5,0);
    printline(110,395,1,104,0,BLUE,5,0);
    printline(110,50,1,70,1,BLUE,5,0);
    printline(625,50,1,70,1,BLUE,5,0);
}

int draw_field_page(char *name)
{
    int record[21][26];
    unsigned file_size;
    void *filebuffer;
    int mode = 0;
    int num[5];
    int flag = 0,file_flag=0;
    int pencil_flag = 0,rubber_flag = 0;
    int (*precord)[26] = record;
    int i;
    FILE *fp;
    char string[80] = "c:\\DATA\\";
    char filename[80];
    strcat(string,name);
    strcat(string,"\\FIELD");
    if(access(string,0)==-1)  //协助创建农田文件夹
    {
        if(mkdir(string)!=0)
        {
            perror("ERROR IN BUILDING THE FIELD PACKAGE!");
            delay(2000);
            exit(1);
        }
    }

    clrmous(MouseX,MouseY);
    setfillstyle(SOLID_FILL,WHITE);
    bar(0,0,95,480);
    draw_field_screen();
    mouseinit();
    while(1)
    {
        
        newmouse(&MouseX,&MouseY,&press);

        if(mouse_press(12,50,77,115)==2)         //铅笔不点击
        {
            if(flag!=1)
            {
                MouseS = 1;
                flag = 1;
                num[1] = 1;
                clrmous(MouseX,MouseY);
                put_pencil(12,50,DARKGRAY,BROWN,LIGHTGRAY,5);
            }
        }
        else if(mouse_press(12,50,77,115)==1)      //铅笔点击
        {
            mode = 1;
            MouseS = 0;
            clrmous(MouseX,MouseY);
        }
        else if(mouse_press(12,150,77,215)==2)     //橡皮不点击
        {
            if(flag!=2)
            {
                MouseS = 1;
                flag = 2;
                num[2] =1;
                clrmous(MouseX,MouseY);
                put_rubber(12,150,LIGHTGRAY,5);
            }
        } 
        else if(mouse_press(12,150,77,215)==1)       //橡皮点击
        {
            mode = 2;
            MouseS = 0;
            clrmous(MouseX,MouseY);
        }
        else if(mouse_press(12,260,77,310)==2)       //文件夹未点击
        {
            if(flag!=3)
            {
                MouseS = 1;
                flag = 3;
                num[3]=1;
                clrmous(MouseX,MouseY);
                put_file(12,260,BLUE,LIGHTBLUE,5);
            }
        }
        else if(mouse_press(12,260,77,310)==1)
        {
            if(file_flag == 0)
            {
                file_size = imagesize(110,50,630,400);
                filebuffer = malloc(file_size);
                if(filebuffer != NULL)
                {
                    getimage(110,50,630,400,filebuffer);
                }
                else
                {
                    perror("ERROR IN REMEMBERING!");
                    delay(3000);
                    exit(1);
                }
                open_file();
                mode =3;
                file_flag = 1;
            }
            else if(file_flag == 1)
            {
                putimage(110,50,filebuffer,COPY_PUT);
                free(filebuffer);
            }
            
        }
        else if(mouse_press(595,5,630,40)==2)        //退出未点击
        {
            if(flag!=4)
            {
                MouseS = 1;
                flag = 4;
                num[4] =1;
                clrmous(MouseX,MouseY);
                back_button(LIGHT);
            }
        } 
        else if(mouse_press(595,5,630,40)==1)        //退出点击
        {
            clrmous(MouseX,MouseY);
            return FIELD;
        }
        else
        {
            if(flag!=5)
            {
                MouseS = 0;
                flag = 5;
            }
        }


        if(flag!=1&&num[1]==1)
        {
            clrmous(MouseX,MouseY);
            put_pencil(12,50,DARKGRAY,DARKGRAY,LIGHTGRAY,5);
            num[1] = 0;
        }
        else if(flag!=2&&num[2]==1)
        {
            clrmous(MouseX,MouseY);
            put_rubber(12,150,DARKGRAY,5);
            num[2] = 0;
        }
        else if(flag!=3&&num[3]==1)
        {
            clrmous(MouseX,MouseY);
            put_file(12,260,DARKGRAY,LIGHTGRAY,5);
            num[3] = 0;
        }
        else if(flag!=4&&num[4]==1)
        {
            clrmous(MouseX,MouseY);
            back_button(RECOVER);
            num[4] = 0;
        }


        if(mode ==1)   //mode1代表画图模式
        {
            put_pencil(12,50,DARKGRAY,BROWN,LIGHTGRAY,5);
            put_ok_button(PAINT);
            setfillstyle(SOLID_FILL,WHITE);
            bar(595,5,630,40);
            while(1)
            {
                newmouse(&MouseX,&MouseY,&press);
                if(mouse_press(110,50,630,470)==2) //处于画图区域，但未点击
                {
                    if(pencil_flag!=1)
                    {
                        MouseS = mode+3;
                        pencil_flag = 1;
                    }
                }
                else if(mouse_press(110,50,630,470)==1)      //处于画图区域并且点击
                {
                    clrmous(MouseX,MouseY);
                    setfillstyle(SOLID_FILL,DARKGRAY);
                    bar(110+20*((MouseX - 110)/20),470-20*((470-MouseY)/20+1),110+20*((MouseX - 110)/20)+20,470-20*((470-MouseY)/20+1)+20);
                    record[(MouseX - 110)/20][(470-MouseY)/20] = 1;               
                }
                else if(mouse_press(5,400,95,470)==2)      //处于ok区域未点击
                {
                    if(pencil_flag!=2)
                    {
                        MouseS = 1;
                        pencil_flag = 2;
                        put_ok_button(LIGHT);
                    }
                }
                else if(mouse_press(5,400,95,470)==1)        //处于ok区域并且点击
                {
                    MouseS = 0;
                    mode = 0;

                    if((fp = fopen("c:\\DATA\\yang\\FIELD\\field.dat","wb"))!=NULL)
                    {
                        for(i=0;i<21;i++)
                        {
                            fwrite(precord[i],sizeof(int),26,fp);
                        }
                    }
                    else
                    {
                        perror("ERROR IN RECORDING!");
                    }
                    fclose(fp);

                    clrmous(MouseX,MouseY);
                    setfillstyle(SOLID_FILL,WHITE);
                    bar(0,0,95,480);
                    break;
                }
                else 
                {
                    if(pencil_flag!=0)
                    {
                        MouseS = 0;
                        pencil_flag = 0;
                        put_ok_button(RECOVER);
                    }
                }
            }
            return DRAW_FIELD;
        }

        if(mode ==2)   //mode2代表擦除模式
        {
            put_rubber(12,150,LIGHTGRAY,5);
            put_ok_button(PAINT);
            setfillstyle(SOLID_FILL,WHITE);
            bar(595,5,630,40);
            while(1)
            {
                newmouse(&MouseX,&MouseY,&press);
                if(mouse_press(110,50,630,470)==2) //处于画图区域，但未点击
                {
                    if(rubber_flag!=1)
                    {
                        MouseS = mode+3;
                        rubber_flag = 1;
                    }
                }
                else if(mouse_press(110,50,630,470)==1)      //处于画图区域并且点击
                {
                    clrmous(MouseX,MouseY);
                    setfillstyle(SOLID_FILL,WHITE);
                    bar(110+20*((MouseX - 110)/20),470-20*((470-MouseY)/20+1),110+20*((MouseX - 110)/20)+20,470-20*((470-MouseY)/20+1)+20);
                    setcolor(DARKGRAY);
                    setlinestyle(DOTTED_LINE,0,NORM_WIDTH);
                    line(110+20*((MouseX - 110)/20),470-20*((470-MouseY)/20+1),110+20*((MouseX - 110)/20),470-20*((470-MouseY)/20+1)+20);
                    line(110+20*((MouseX - 110)/20),470-20*((470-MouseY)/20+1),110+20*((MouseX - 110)/20)+20,470-20*((470-MouseY)/20+1));
                    line(110+20*((MouseX - 110)/20),470-20*((470-MouseY)/20+1)+20,110+20*((MouseX - 110)/20)+20,470-20*((470-MouseY)/20+1)+20);
                    line(110+20*((MouseX - 110)/20)+20,470-20*((470-MouseY)/20+1)+20,110+20*((MouseX - 110)/20)+20,470-20*((470-MouseY)/20+1));
                    record[(MouseX - 110)/20][(470-MouseY)/20] = 0;               
                }
                else if(mouse_press(5,400,95,470)==2)      //处于ok区域未点击
                {
                    if(rubber_flag!=2)
                    {
                        MouseS = 1;
                        rubber_flag = 2;
                        put_ok_button(LIGHT);
                    }
                }
                else if(mouse_press(5,400,95,470)==1)        //处于ok区域并且点击
                {
                    MouseS = 0;
                    mode = 0;

                    if((fp = fopen("c:\\DATA\\yang\\FIELD\\field.dat","wb"))!=NULL)
                    {
                        for(i=0;i<21;i++)
                        {
                            fwrite(precord[i],sizeof(int),26,fp);
                        }
                    }
                    else
                    {
                        perror("ERROR IN RECORDING!");
                    }
                    fclose(fp);

                    clrmous(MouseX,MouseY);
                    setfillstyle(SOLID_FILL,WHITE);
                    bar(0,0,95,480);
                    break;
                }
                else 
                {
                    if(rubber_flag!=0)
                    {
                        MouseS = 0;
                        rubber_flag = 0;
                        put_ok_button(RECOVER);
                    }
                }
            }
            return DRAW_FIELD;
        }
         
    }
}


void put_ok_button(int flag)
{
    if(flag == PAINT)
    {
        clrmous(MouseX,MouseY);
        printbox(5,400,95,470,DARKGRAY,1,5,5);
        setcolor(DARKGRAY);
        settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
        outtextxy(30,425,"OK");
    }
    else if(flag == LIGHT)
    {
        clrmous(MouseX,MouseY);
        printbox(5,400,95,470,YELLOW,1,5,5);
        setcolor(CYAN);
        settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
        outtextxy(30,425,"OK");
    }
    else if(flag == RECOVER)
    {
        put_ok_button(PAINT);
    }
}

