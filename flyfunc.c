#include "public.h"
#include "flyfunc.h"

void *drone_buffer;
int drone_flag = 0;

void move_drone1(int record[21][26], int x1,int y1,int x2,int y2 )
{
    int i,step;
    double step_x,step_y,x,y ;
    step = max( abs(x2-x1),abs(y2-y1));
    if(step<1) step = 1;
    step /= 1.5;//速度修改
    step_x = (x2-x1) / (float)step;
    step_y = (y2-y1) / (float)step;
    x = x1;
    y = y1;
    for( i=0 ;i<=step ;i++)
    {
        save_bk_drone((int)x,(int)y);
        draw_drone(x,y);
        delay(50);
        clear_drone((int)x,(int)y);
        x += step_x;
        y += step_y;
    }
    save_bk_drone((int)x,(int)y);
    draw_drone(x,y);
    clear_drone((int)x,(int)y);
}
void save_bk_drone(int nx, int ny)
{
	int size;
	size = imagesize(nx-10, ny-10, nx + 20, ny + 20);
	drone_buffer = malloc(size);
	if (drone_buffer != NULL)
		getimage(nx-10, ny-10, nx + 20, ny + 20 , drone_buffer);
	else
		printf("Error");
}
void clear_drone(int nx, int ny) 
{
	if (drone_flag == 1)
	{
		setwritemode(XOR_PUT);
		put_drone1(nx, ny,2);
		putimage(nx-10, ny-10, drone_buffer, COPY_PUT);
		free(drone_buffer);
		drone_flag = 0;
		setwritemode(COPY_PUT);
	}
}
void draw_drone(int nx, int ny)
{
	if (drone_flag == 0)
	{
		setwritemode(COPY_PUT);
		put_drone1(nx, ny,2);
		drone_flag = 1;
	}
}
int x_record_to_screen(int x)
{
    return 110+ x*20 + 5 ; //110+ x*20格子左上角x
}
int y_record_to_screen(int y)
{
    return 470-y*20-20 + 5; //470-y*20-20格子左上角y
}
void simulate( int record[21][26] ,char *nowfield )
{
    int house_x,house_y,house_screen_x,house_screen_y;
    int i,j,k;
    
}
void simulate_handmode(int record[21][26] , int route[100][2] )
{
    int i=0;
    while(route[i+1][0]!=-1)
    {
    //     setfillstyle(SOLID_FILL,LIGHTBLUE);
    //     bar(10+i*10,10+i*10,10+(i+1)*10,10+(i+1)*10);
        move_drone1(record,route[i][0],route[i][1],route[i+1][0],route[i+1][1]);
        i++;
    }
    // setfillstyle(SOLID_FILL,RED);
    //     bar(400,400,405,405);
}
