#ifndef _FLYFUNC_H_
#define _FLYFUNC_H_

void save_bk_drone(int nx, int ny);
void clear_drone(int nx, int ny) ;
void draw_drone(int nx, int ny);

int x_record_to_screen(int x);
int y_record_to_screen(int y);
void new_field( int record[21][26] ,char *nowfield);
void update_field(int record[21][26], int drone_x , int drone_y );
void move_drone1(int record[21][26], int x1,int y1,int x2,int y2 );

void simulate( int record[21][26] ,char *nowfield);


typedef struct point 
{
    int x;
    int y;
} Point ;

void simulate_handmode(int record[21][26] , Point *route );

#endif
