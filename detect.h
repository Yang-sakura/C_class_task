#ifndef _DETECT_H_
#define _DETECT_H_

void put_calender(void);
void put_calender_number(char *date);
void pause_button(int flag);
void mode_button(int flag);
void chart_button(int flag);
void paint_field( int record[21][26] ,char *nowfield);
void start_button(int flag);
void detect_screen(int record[21][26] , char *nowfield);
int detect_page(char *username,char *nowfield);

#endif
