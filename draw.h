#ifndef _DRAW_H_
#define _DRAW_H_

void put_pencil(int x,int y,int COLOR1,int COLOR2,int COLOR3,int pix);
void put_rubber(int x,int y,int COLOR,int pix);
void put_sprout(int x,int y,int COLOR,int pix);
void put_field(int x,int y,int LIGHTCOLOR,int DARKCOLOR,int pix);
void put_house(int x,int y,int DARKCOLOR,int LIGHTCOLOR,int pix);
void put_file(int x,int y,int DARKCOLOR,int LIGHTCOLOR,int pix);
void put_arrow(int x,int y,int COLOR,int pix,int flag);
void put_shovel(int x,int y,int pix,int COLOR1,int COLOR2);
void put_crop1(int x,int y,int type,int situation);
void put_crop2(int x,int y,int type,int situation);
void put_crop3(int x,int y,int type,int situation);
#endif
