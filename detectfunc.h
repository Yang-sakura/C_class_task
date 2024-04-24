#ifndef _DETECTFUNC_H_
#define _DETECTFUNC_H_

#include "detectfunc.h"
#include "public.h"
#include "detect.h"

void change_weather(char *weather);
void recover_field(int record[21][26],char *username , char *nowfield );
void grow(int record[21][26] , int date );
void grow_oneday(int record[21][26] ,int date);
void find_house(int record[21][26] , int houserecord[4][2]);
Point find_closest_house(int record[21][26]);

void show_chart(int record[21][26],char *nowfield);

#endif
