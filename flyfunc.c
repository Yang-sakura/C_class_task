#include "public.h"
#include "flyfunc.h"

void new_field( int record[21][26] ,char *nowfield)
{
    int i,j,x,y;

    setfillstyle(SOLID_FILL,WHITE);
    bar(110,50,630,470);

    setlinestyle(SOLID_LINE,0,THICK_WIDTH);
    line(110,50,110,470);//110,50  630,470
    line(110,470,630,470);
    line(110,50,108,60);
    line(110,50,112,60);
    line(630,470,620,468);
    line(630,470,620,472);

    setlinestyle(DOTTED_LINE,0,NORM_WIDTH);
    for(i=0;i<26;i++)
    {
        line(110+i*20,50,110+i*20,470);
    }
    for(i=0;i<21;i++)
    {
        line(110,470-i*20,630,470-i*20);
    }

    for(i=0;i<21;i++)//y
    {
        for(j=0;j<26;j++)//x
        {
            if ( record[i][j] )
            {
                setfillstyle(SOLID_FILL,DARKGRAY);
                bar(110+j*20 , 470-(i+1)*20 ,110+(j+1)*20, 470-i*20);
            }
            if( record[i][j] == 2 )
            {
                x = 110 + j*20 ;
                y = 470-i*20-20 ;//左上角
                //右下角 (110 + j * 20 + 20, 470 - i * 20)
                put_sprout(x,y,GREEN,2);
            }
            else if( record[i][j]==3 )
            {
                x = 110 + j*20 ;
                y = 470-i*20-20 ;//左上角
                //右下角 (110 + j * 20 + 20, 470 - i * 20)
                put_house(x,y,BROWN,CYAN,2);
            }
        }
    }
}
void update_field(int record[21][26], int drone_x , int drone_y )
{
    int x,y,i,j,center_x,center_y;
    if(drone_x<=90 || drone_x>=650 || drone_y<30 || drone_y>490 ) return ;//110,50  630,470
    center_x = ((470 - drone_y)/20);
    center_y = ((drone_x - 110)/20);
    for(i= center_x-1 ;i<=center_x+1;i++ )
    {
        for( j=center_y-1; j<=center_y+1; j++ )
        {
            if( i<0 || j<0 ) continue;
            x = 110+j*20 ;
            y = 470-i*20-20 ;//左上角
            if(record[i][j] == 0 ) {
                setfillstyle(SOLID_FILL,WHITE);
                bar(x,y,x+20,y+20);
                setcolor(DARKGRAY);
                setlinestyle(DOTTED_LINE,0,NORM_WIDTH);
                line(x,y,x,y+20);
                line(x,y,x+20,y);
                line(x,y+20,x+20,y+20);
                line(x+20,y+20,x+20,y);
            }
            else if(record[i][j] == 1 ) {
                setfillstyle(SOLID_FILL,DARKGRAY);
                bar(x,y,x+20,y+20);
            }
            else if(record[i][j] == 2) {
                setfillstyle(SOLID_FILL,DARKGRAY);
                bar(x,y,x+20,y+20);
                put_sprout(x,y,GREEN,2);
            }
            else if( record[i][j]==3 ){
                setfillstyle(SOLID_FILL,DARKGRAY);
                bar(x,y,x+20,y+20);
                put_house(x,y,BROWN,CYAN,2);
            }
        }
    }
}
void move_drone1(int record[21][26], int x1,int y1,int x2,int y2 )
{
    int i,j,step;
    double step_x,step_y,x,y ;
    step = max( abs(x2-x1),abs(y2-y1));
    step_x = (x2-x1) / (float)step;
    step_y = (y2-y1) / (float)step;
    x = x1;
    y = y1;
    for( i=0 ;i<=step ;i++)
    {
        update_field(record,(int)x,(int)y);
        put_drone1((int)x,(int)y,2);
        x += step_x;
        y += step_y;
        delay(50);
    }
    update_field(record,(int)x,(int)y);
}
int x_record_to_screen(int x)
{
    return 110+ x*20 ;
}
int y_record_to_screen(int y)
{
    return 470-y*20-20 ;
}
void simulate( int record[21][26] ,char *username)
{
    int house_x,house_y,house_screen_x,house_screen_y;
    int i,j;
    // char path[100]="C:\\DATA\\";
    // FILE *fp;

    for(i=0;i<21;i++)//y
    {
        for(j=0;j<26;j++)//x
        {
            if( record[i][j]==3 ) {
                house_x = j ;
                house_y = i ;
            }
        }
    }
    house_screen_x = 110+house_x*20 ;
    house_screen_y = 470-house_y*20-20 ;

    AdjacencyMatrix(record , username);

    // strcat(path,username);
    // strcat(path,"\\TRACE\\EXAMPLE.dat");
    
    // if(access(path,0) == -1)
    // {
    //     if(mkdir(path)!=0)
    //     {
    //         perror("ERROR IN BUILDING THE TRACE PACKAGE!");
    //         delay(2000);
    //         exit(1);
    //     }
    // }
    // fp = fopen(path,"rb");



    fclose(fp);
    // move_drone1(record,house_screen_x,house_screen_y,house_screen_x+200,house_screen_y-100);
}
int min_dijk(int dis[],int flag[], int num)
{
    int min = MAX , i ,min_index=-13;
    for(i=0;i<num;i++)
    {
        if(flag[i]==0 && dis[i] <= min )
        {
            min = dis[i] ;
            min_index = i ;
        }
    }
    return min_index;
}
void dijkstra(int **graph, int start, int num , char *username ,int *output) 
{
    int w,temp,u,v,count,i,t,end;
    int *dis = (int *)malloc(num * sizeof(int));
    int *flag = (int *)malloc(num * sizeof(int));
    int *pre = (int *)malloc(num * sizeof(int));
    // int *output = (int *)malloc(num * sizeof(int));
    char path[100]="C:\\DATA\\";
    FILE *fp;

    if (dis == NULL || flag == NULL || pre == NULL ) {
        free(dis);
        free(flag);
        free(pre);
        // free(output);
        perror("Memory allocation for dis failed");
    }

    memset(dis,0x7f, num * sizeof(int));
    memset(flag,0, num * sizeof(int));
    memset(pre, -1, num * sizeof(int)); 
    // memset(output ,0, num * sizeof(int));

    dis[start] = 0;
    flag[start] = 1;
    u = start;
    count = 1;
    while( count < num)
    {
        for(v=0 ; v<num ; v++)
        {
            if(!flag[v] && graph[u][v] && dis[u]!= MAX && dis[u]+graph[u][v]<dis[v] )
            {
                dis[v] = dis[u] + graph[u][v];
                pre[v] = u;
            }
        }
        u = min_dijk(dis,flag,num);
        if (u == -1) break;
        flag[u] = 1;
        if(u >= num-1 ) u = -1;
        u++ ;
        count++ ;
    }
    t = 1;
    u = end;
    while( u != -1 )
    {
        t++;
        output[t-1] = u;
        u = pre[u] ;
    }

    // strcat(path,username);
    // strcat(path,"\\TRACE");
    // if(access(path,0) == -1)
    // {
    //     if(mkdir(path)!=0)
    //     {
    //         perror("ERROR IN BUILDING THE TRACE PACKAGE!");
    //         delay(2000);
    //         exit(1);
    //     }
    // }
    // strcat(path,"\\EXAMPLE.dat");
    // fp = fopen(path,"w");
    // if(fp == NULL) {
    //     perror("file creating failed");
    // }
    // for(i=t;i>=1;i--)
    // {
    //     fread(&output[i] , sizeof(int), 1, fp) ;
    // }

    fclose(fp);
    free(dis);
    free(flag);
    // free(output);
}
int calculatedistance(Position a, Position b) 
{
    return abs(a.x - b.x) + abs(a.y - b.y);
}
void AdjacencyMatrix( int record[MAP_ROWS ][MAP_COLS ] , char *username)
{
    int num = 0;
    Position house_Position = {-1, -1};
    int i, j, k, count , house_count ,end;
    Position *points;
    int **adjMatrix;
    int *output;
    // char path[100]="C:\\DATA\\";
    // FILE *fp;

    for (i = 0; i < MAP_ROWS; i++) 
    {
        for (j = 0; j < MAP_COLS; j++) 
        {
            if (record[i][j] == 2 || record[i][j] == 3 ) {
                num++;
            }
        }
    }

    points = (Position *)malloc(num * sizeof(Position));
    if (points == NULL) 
    {
        perror("Memory allocation failed.");
    }
    count = 0;
    for (i = 0; i < MAP_ROWS; i++) 
    {
        for (j = 0; j < MAP_COLS; j++)
        {
            if (record[i][j] == 2 || record[i][j] == 3) {
                points[count].x = i;
                points[count].y = j;
                if (record[i][j] == 3) {
                    house_Position = points[count];
                    house_count = count ;
                }
                count++;
            }
        }
    }
    
    adjMatrix = (int **)malloc(num * sizeof(int *));
    if (adjMatrix == NULL) {
        free(points);
        perror("Memory allocation failed.");
    }
    for (i = 0; i < num; i++) 
    {
        adjMatrix[i] = (int *)malloc(num * sizeof(int));
        if (adjMatrix[i] == NULL) //出错时释放已分配的内存
        {
            for (k = 0; k < i; k++) {
                free(adjMatrix[k]);
            }
            free(adjMatrix);
            free(points);
            perror("Memory allocation failed.");
        }
    }
    for (i = 0; i < num; i++) 
    {
        for (j = 0; j < num; j++) 
        {
            adjMatrix[i][j] = calculatedistance(points[i], points[j]);
        }
    }

    output = (int *)malloc(num * sizeof(int) );
    
    dijkstra(adjMatrix , house_count , num ,  username, output) ;

    // strcat(path,username);
    // strcat(path,"\\TRACE");
    // if(access(path,0) == -1)
    // {
    //     if(mkdir(path)!=0)
    //     {
    //         perror("ERROR IN BUILDING THE TRACE PACKAGE!");
    //         delay(2000);
    //         exit(1);
    //     }
    // }
    // strcat(path,"\\EXAMPLE.dat");
    // fp = fopen(path,"rb");
    // if(fp == NULL) {
    //     perror("file opening failed");
    // }
    // i=1;
    // while(fread(&output[i] , sizeof(int), 1, fp) == 1){
    //     i++;
    // }
    // fclose(fp);

    for(j=1;j<=i-1;j++)
    {
        move_drone1(record,x_record_to_screen(points[j].x),y_record_to_screen(points[j].y),x_record_to_screen(points[j+1].x),y_record_to_screen(points[j+1].y));
    }

    //释放内存
    for (i = 0; i < num; i++) {
        free(adjMatrix[i]);
    }
    free(adjMatrix);
    free(points);
}
