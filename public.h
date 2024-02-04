#ifndef _PUBLIC_H_
#define _PUBLIC_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <graphics.h>
#include <math.h>
#include <bios.h>
#include <conio.h>
#include <dos.h>
#include <time.h>

#include "hz.h"
#include "mouse.h"

#define NUM0 0x5230
#define NUM1 0x4f31
#define NUM2 0x5032
#define NUM3 0x5133
#define NUM4 0x4134
#define NUM5 0x4c35
#define NUM6 0x4d36
#define NUM7 0x4737
#define NUM8 0x4838
#define NUM9 0x4939
#define F2 0x3c00
#define F3 0x3d00
#define F4 0x3e00
#define F5 0x3f00
#define F6 0x4000
#define F7 0x4100
#define F8 0x4200
#define F9 0x4300
#define F10 0x4400
#define F1 0x3b00
#define ENTER 0x1c0d
#define BACK 0x0e08
#define ESC 0x011b
#define UP 0x4800
#define DOWN 0x5000
#define RIGHT 0x4d00
#define LEFT 0x4b00
#define ONE 0x0231
#define TWO 0x0332
#define THREE 0x0433
#define FOUR 0x0534
#define FIVE 0x0635
#define SIX 0x0736
#define SEVEN 0x0837
#define EIGHT 0x0938
#define NINE 0x0a39
#define ZERO 0x0b30

#define WELCOME 0
#define LOGIN 1
#define SIGHUP 2
#define HOME 3
#define FIELD 4
#define DRONE 5
#define PESTICIDE 6
#define DETECTOR 7
#define QUIT 8


#define PAINT 0
#define RECOVER 1
#define LIGHT 2

void printline(int x,int y,int len,int n,int flag,int COLOR,int wid,int gap);
//x,y是第一个小方块左上角起始点，flag=0横着向右，flag=1竖着向下，len每格长度是宽度的多少倍数，n记录画多少个,COLOR是画线颜色
void printbox(int x1,int y1,int x2,int y2,int COLOR,int len,int wid,int gap);
void back_button(int flag);

typedef struct userinfo
{
    char name[18];
    char password[18];
} INFO;

#endif
