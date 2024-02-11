#ifndef _HOUSE_H_
#define _HOUSE_H_

void house_screen(int record[21][26] ,char *nowfield);
void clear_button(int flag);
int house_page(char *username,char *nowfield);
void paint_field( int record[21][26] ,char *nowfield);
void put_ok_button(int flag);

#endif
