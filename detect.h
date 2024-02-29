#ifndef _DETECT_H_
#define _DETECT_H_

void paint_field( int record[21][26] ,char *nowfield);
void start_button(int flag);
void detect_screen(int record[21][26] , char *nowfield);
int detect_page(char *username,char *nowfield);

#endif
