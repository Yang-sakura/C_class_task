#ifndef _FLYFUNC_H_
#define _FLYFUNC_H_

int x_record_to_screen(int x);
int y_record_to_screen(int y);
void new_field( int record[21][26] ,char *nowfield);
void update_field(int record[21][26], int drone_x , int drone_y );
void move_drone1(int record[21][26], int x1,int y1,int x2,int y2 );
void simulate( int record[21][26] ,char *username);
void AdjacencyMatrix( int record[MAP_ROWS ][MAP_COLS ] , char *username);
void dijkstra(int **graph, int start, int num , char *username ,int *output) ;

typedef struct 
{
    int x;
    int y;
} Position;

typedef struct Point 
{
    int x;
    int y;
} Point;

#endif
