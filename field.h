#ifndef _FIELD_H_
#define _FIELD_H_

#include "fieldfunc.h"
void field_screen();
int field_page();
void put_sprout(int x,int y,int COLOR,int pix);
void put_field(int x,int y,int DARKCOLOR,int LIGHTCOLOR,int pix);
void put_house(int x,int y,int DARKCOLOR,int LIGHTCOLOR,int pix);

#endif
