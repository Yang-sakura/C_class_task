#include "public.h"
#include "logfunc.h"

int check(INFO *user)
{
    int n;
    int i;
    FILE *fp;
    INFO *read;

    if ((fp = fopen("DATA\\USERDATA.dat", "rb+")) == NULL)
    {
        printf("cannot open file UserData.dat");
        delay(3000);
        exit(1);
    }

    fseek(fp, 0, SEEK_END);
    n = ftell(fp) / sizeof(INFO);

    for(i=0;i<n;i++)
    {
        if((read=(INFO *)malloc(sizeof(INFO)))==NULL )
        {
            printf("malloc error!\n");
            delay(3000);
            exit(1);
        }
        fseek(fp, i*sizeof(INFO), SEEK_SET);
        fread(read, sizeof(INFO), 1, fp);
        if(strcmp(read->name,user->name)==0)//用户名已注册
        {
            if(strcmp(read->password,user->password)!=0)//密码错误
            {
                setfillstyle(SOLID_FILL, WHITE);
                bar(261,231,554,269);//密码输入框清空
                setcolor(DARKGRAY);
                settextstyle(DEFAULT_FONT   , HORIZ_DIR,2);
                outtextxy(275, 240, "wrong!");
                delay(1000);
                setfillstyle(SOLID_FILL, WHITE);
                bar(261,231,554,269);
                if(read != NULL)
                {
                    free(read);
                    read=NULL;
                }
                break;
            }
            else if( strcmp(read->password,user->password)==0 )
            {
                clrmous(MouseX,MouseY);
                setfillstyle(SOLID_FILL, WHITE);
                bar(50,70,585,130);//标题清空
                setcolor(BLUE);
                settextstyle(DEFAULT_FONT   , HORIZ_DIR,3);
                outtextxy(70, 100, "login successfully!");
                if(read != NULL)
                {
                    free(read);
                    read=NULL;
                }
                if(fclose(fp)!=0)
                {
                    printf("cannot close Data");
                    delay(3000);
                    exit(1);
                }
                delay(1000);
                setbkcolor(WHITE);
                cleardevice();
                newmouse(&MouseX, &MouseY, &press);
                clrmous(MouseX,MouseY);
                
                return HOME;
            }
        }
        if(user!=NULL)
        {
            free(read);
            read=NULL;
        }
    }
    if(i==n)
    {
        setfillstyle(SOLID_FILL, WHITE);
        bar(261,161,554,199);//255,155,560,205
        setcolor(DARKGRAY);
        settextstyle(DEFAULT_FONT   , HORIZ_DIR,2);
        outtextxy(275, 170, "unregistered!");//用户名输入框(255,155,560,205)
    }
    if(read != NULL)
    {
        free(read);
        read=NULL;
    }
    if(fclose(fp)!=0)
    {
        printf("cannot close Data");
        delay(3000);
        exit(1);
    }
    return 0;
}
void temp_input(char *temp,int x,int y)
{
    char t;
    int i=0,k;
    int maxi=17;
    int w,h;//255,155,560,205 y:40
    // x=266;
    // y=171;
    w=16;
    h=20;
    
    clrmous(MouseX,MouseY);

    setfillstyle(SOLID_FILL, WHITE);
    setcolor(DARKGRAY);
    setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
    settextstyle(DEFAULT_FONT , HORIZ_DIR,2);
    settextjustify(LEFT_TEXT, TOP_TEXT);

    i=strlen(temp);
    outtextxy(x,y,temp);

    line(x+i*w,y,x+i*w,y+h);

    while(bioskey(1))//清空键盘缓冲区中的所有按键事件
    {
        k = bioskey(0);
    }
    while(1)
    {
        t=bioskey(0);
        if(i<maxi)
        {
            if(t==' '||t=='\n'||t=='\r'||t==033)
            //033：esc 012:'\n' 013:'\r' 040:' '
            {
                setfillstyle(SOLID_FILL, WHITE);
                bar(x+i*w-1,y-5,x+i*w+1,y+h+5);//清空光标
                break;
            }
            else 
            {
                if(t!='\b')
                {
                    *(temp+i)=t;
                    *(temp+i+1)='\0';
                    setfillstyle(SOLID_FILL, WHITE);  
                    bar(x,y-5,x+maxi*w,y+h+5);//清空输入区
                    outtextxy(x,y,temp);
                    i++;
                    line(x+i*w,y,x+i*w,y+h);
                }
                else if(i>0)
                {
                    i--;
                    *(temp+i)='\0';
                    *(temp+i+1)='\0';
                    setfillstyle(SOLID_FILL, WHITE);
                    bar(x,y-5,x+maxi*w,y+h+5);//清空输入区
                    outtextxy(x,y,temp);
                    line(x+i*w,y,x+i*w,y+h);
                    
                }

            }
        }
        else if(i>=maxi)
        {
            if(t==' '||t=='\n'||t=='\r'||t==033)//退出键
            {
                setfillstyle(SOLID_FILL, WHITE);
                bar(x+i*w-1,y-5,x+i*w+1,y+h+5);
                break;
            }
            else 
            {
                if(t=='\b'&&i>0)
                {
                    i--;
                    *(temp+i)='\0';
                    setfillstyle(SOLID_FILL, WHITE);
                    bar(x,y-5,x+maxi*w,y+h+5);//清空输入区
                    outtextxy(x,y,temp);
                    line(x+i*w,y,x+i*w,y+h);
                    
                }
            }
        }
    }
}
