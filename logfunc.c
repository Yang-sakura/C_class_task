#include "public.h"
#include "logfunc.h"

int check(INFO *user)
{
    char path[30]="C:\\DATA\\";
    INFO read;
    FILE *fp;

    strcat(path,user->name);
    if(access(path,0) == -1) // 检查文件夹是否存在
    {
        title_warning("User not registered!",LOGIN);
        return 0;
    }

    strcat(path,"\\info");
    fp= fopen(path,"rb");

    if(fp==NULL ) {
        printf("cannot open infofile.dat");
        delay(3000);
        exit(1);
    }
    if( fread(&read,sizeof(INFO),1,fp) ==1 )
    {
        fclose(fp);
        if(strcmp(read.password,user->password) == 0)//密码匹配
        {
            title_warning("Login successfully!",0);
            return 1;
        }
        else {
            title_warning("Password incorrect!",LOGIN);
            return 0;
        }
    }
    else {
        printf("error reading userinfo file");
        delay(3000);
        exit(1);
    }
    fclose(fp);
    return 0;
}
void temp_input(char *temp,int x,int y)
{
    char t;
    int i=0,key,j;
    int maxi=17;
    int w=16 , h=20 ;
    int scan_code,ascii;
    int cursor = 0 ;
    
    clrmous(MouseX,MouseY);

    setfillstyle(SOLID_FILL, WHITE);
    setcolor(DARKGRAY);
    setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
    settextstyle(DEFAULT_FONT , HORIZ_DIR,2);
    settextjustify(LEFT_TEXT, TOP_TEXT);

    i = strlen(temp);
    cursor = i;
    outtextxy(x,y,temp);
    line(x+cursor*w,y,x+cursor*w,y+h);

    while(bioskey(1))//清空键盘缓冲区中的所有按键事件
    {
        key = bioskey(0);
    }
    while(1)
    {
        key=bioskey(0);
        ascii = key & 0x00FF;
        scan_code = key>>8;

        if(scan_code==0x4B && ascii != '4')//左箭头键
        {
            if( cursor>0 ) {
                cursor--;
                bar(x,y-5,x+maxi*w,y+h+5);
                outtextxy(x,y,temp);
                line(x+cursor*w,y,x+cursor*w,y+h);
            }
            continue;
        }
        if(scan_code==0x4D && ascii != '6')//右箭头键
        {
            if( cursor <i ) {
                cursor++;
                bar(x,y-5,x+maxi*w,y+h+5);
                outtextxy(x,y,temp);
                line(x+cursor*w,y,x+cursor*w,y+h);
            }
            continue;
        }

        if(i < maxi)
        {
            if(ascii==' ' || ascii=='\n' || ascii=='\r' || ascii==27)//处理空格、换行、回车和ESC键
            {
                setfillstyle(SOLID_FILL, WHITE);
                bar(x+cursor*w-1,y-5,x+cursor*w+1,y+h+5);//清空光标
                break;
            }
            else 
            {
                if(ascii !='\b') 
                {
                    if( i<maxi ) 
                    {
                        for(j=i;j>=cursor;j--) {
                            temp[j+1]=temp[j];
                        }
                        temp[cursor]=ascii;
                        cursor++;
                        i++;
                    }
                }
                else if(ascii=='\b')
                {
                    if( cursor>0 )  //从光标位置开始删除字符
                    {
                        for(j=cursor;j<i;j++) {
                            temp[j-1]=temp[j];
                        }
                        temp[i-1]='\0';
                        cursor--;
                        i--;
                    }
                }
                bar(x,y-5,x+maxi*w,y+h+5);
                outtextxy(x,y,temp);
                line(x+cursor*w,y,x+cursor*w,y+h);
            }
        }
        else if(i>=maxi)
        {
            if(ascii==' ' || ascii=='\n' || ascii=='\r' || ascii==27)//退出键
            {
                setfillstyle(SOLID_FILL, WHITE);
                bar(x+cursor*w-1,y-5,x+cursor*w+1,y+h+5);
                break;
            }
            else 
            {
                if(ascii=='\b' )
                {
                    if( cursor>0 )  //从光标位置开始删除字符
                    {
                        for(j=cursor;j<i;j++) {
                            temp[j-1]=temp[j];
                        }
                        temp[i-1]='\0';
                        cursor--;
                        i--;
                    }
                    bar(x,y-5,x+maxi*w,y+h+5);
                    outtextxy(x,y,temp);
                    line(x+cursor*w,y,x+cursor*w,y+h);
                }
            }
        }
    }
}
int userinfo_input(INFO *user,int *state1,int *state2)
{
    //state1姓名输入状态 state2密码输入状态
    int k;
    if( *state1==1 && *state2==1 )
    {
        creat_userinfo_file(user);

        clrmous(MouseX,MouseY);
        setfillstyle(SOLID_FILL, WHITE);
        bar(50,70,585,130);//标题清空
        setcolor(BLUE);
        settextstyle(DEFAULT_FONT   , HORIZ_DIR,3);
        outtextxy(70, 100, "Signed up successfully!");
        delay(2000);

        return 1;
    }
    else 
    {
        if(*state1 != 1)
        {
            if( user_exist_check(user->name)==0 )//用户名未注册过
            {
                *state1 = 1;
                creat_user_directory(user);
            }
            else //用户名注册过
            {
                clrmous(MouseX,MouseY);
                setfillstyle(SOLID_FILL, WHITE);
                bar(50,70,585,130);//标题清空
                setcolor(BLUE);
                settextstyle(DEFAULT_FONT   , HORIZ_DIR,3);
                outtextxy(70, 100, "Name is repeated!");
                delay(2000);

                if(user!=NULL) memset(user,0,sizeof(INFO));

                cleardevice();
                signup_bkpaint();
                return 0;
            }
        }
        else if( *state2!=1 )
        {
            k = password_check(user->password);
            if( k==1 ) {
                password_warning("too short!");
                if(user->password != NULL) {
                    user->password[0] = '\0';//清空已储存的密码值
                }
                return 0;
            }
            else if(k==2 || k==3) {
                password_warning("illegal!");
                if(user->password != NULL) {
                    user->password[0] = '\0';
                }
                return 0;
            }
            else if( k==0 ) {
                *state2 = 1 ;
            }
        }
    }
    return 0;
}
void password_warning(char *s)
{
    clrmous(MouseX,MouseY);

    setfillstyle(SOLID_FILL, WHITE);
    bar(261,231,554,269);//密码输入框清空

    setcolor(DARKGRAY);
    settextstyle(DEFAULT_FONT   , HORIZ_DIR,2);
    outtextxy(275, 240, s);

    delay(2000);

    setfillstyle(SOLID_FILL, WHITE);
    bar(261,231,554,269);// 再次清空密码输入框
}
void title_warning(char *s,int PAGE)
{
    clrmous(MouseX,MouseY);

    setfillstyle(SOLID_FILL, WHITE);
    bar(50,70,585,130);//标题清空

    setcolor(BLUE);
    settextstyle(DEFAULT_FONT   , HORIZ_DIR,3);
    outtextxy(70, 100, s);

    delay(2000);

    if(PAGE==SIGNUP) 
    {
        setfillstyle(SOLID_FILL, WHITE);
        bar(50,70,585,130);//标题清空
        setcolor(BLUE);
        settextstyle(DEFAULT_FONT   , HORIZ_DIR,3);
        outtextxy(70, 100, "Please sign up here...");
    }
    else if(PAGE == LOGIN)
    {
        setfillstyle(SOLID_FILL, WHITE);
        bar(50,70,585,130);//标题清空
        setcolor(BLUE);
        settextstyle(DEFAULT_FONT   , HORIZ_DIR,3);
        outtextxy(70, 100, "Please log in here...");
    }
}
int password_check(const char *password)
{
    int upper_count = 0 ;
    int lower_count = 0 ;
    int digit_count = 0 ;
    const char *p;

    if(strlen(password) <=6 ) {
        return 1;// 检查密码长度是否大于六位
    }
    for( p=password ; *p ; p++ )
    {
        if(*p>='A' && *p<='Z') {
            upper_count=1;
        }
        else if(*p>='a' && *p<='z') {
            lower_count=1;
        }
        else if(*p>='0' && *p<='9') {
            digit_count=1;
        }
        else {
            return 2;// 如果字符既不是大写字母也不是小写字母也不是数字，返回2
        }
    }
    if((!upper_count) || (!lower_count) || (!digit_count) ) {
        return 3;
    }
    return 0;//合法
}
int user_exist_check(const char *username)
{
    char path[50];
    sprintf(path,"C:\\DATA\\%s",username);
    if( access(path,0)!=-1 ){
        return 1;//该用户名的文件夹存在
    }
    else {
        return 0;////该用户名的文件夹不存在
    }
}
void creat_user_directory(INFO *user)
{
    char path[30];
    strcpy(path,"C:\\DATA\\");
    strcat(path,user->name);

    if(access(path,0)==-1)
    {
        if(mkdir(path)!=0)
        {
            perror("error creat_user_directory !");
            exit(1);
        }
    }
}
void creat_userinfo_file(INFO *user)
{
    char path[30];
    char filename[30];
    FILE *fp;

    sprintf(path,"C:\\DATA\\%s",user->name);
    if( access(path,0)==-1 ){
        perror("error dir didin't exist !");
        return ;
    }
    sprintf(filename,"%s\\info",path);

    fp=fopen(filename,"wb");
    if(fp==NULL ) {
        perror("error file can't open !");
        return ;
    }
    if(fwrite( user,sizeof(INFO),1,fp) != 1 ) {
        perror("error writing to file!");
        fclose(fp);
        return ;
    }
    fclose(fp);
}
