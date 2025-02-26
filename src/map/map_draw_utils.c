#include "fdf.h"
#include <math.h>

void   rotation_x(t_pos *pos, double theta)
{
        double radian;
        int temp_y;
        int temp_z;
        
        radian = theta * M_PI / 180;
        temp_y = pos->y;
        temp_z = pos->z;

        pos->x = pos->x;
        pos->y = (temp_y*cos(radian) - temp_z*sin(radian));
        pos->z = (temp_y*sin(radian) + temp_z*cos(radian));
}

void    rotation_y(t_pos *pos, double theta)
{
        double radian;
        int temp_x;
        int temp_z;

        radian = theta * M_PI / 180;
        temp_x = pos->x;
        temp_z = pos->z;

        pos->x = (temp_x*cos(radian) + temp_z*sin(radian));
        pos->y = pos->y;
		pos->z = -temp_x * sin(radian) + temp_z * cos(radian);
}

void    rotation_z(t_pos *pos, double theta)
{
        double radian;
        int temp_x;
        int temp_y;

        radian = theta * M_PI / 180;
        temp_x = pos->x;
        temp_y = pos->y;

        pos->x = (temp_x*cos(radian) - temp_y*sin(radian));
        pos->y = (temp_x*sin(radian) + temp_y*cos(radian));
        pos->z = pos->z;
}

void set_isometric_projection(t_pos *pos)
{
        double vertical_axis;
        double horizontal_axis;

        vertical_axis = 45.0;
        horizontal_axis = 35.264;
        rotation_z(pos, vertical_axis);
        rotation_x(pos, horizontal_axis);

        // rotation_z(pos, vertical_axis);
        // rotation_y(pos, 0);
}

void	set_scale(t_pos *pos, int scale)
{
	pos->x *= scale;
	pos->y *= scale;
	pos->z *= scale/6;
}


void draw_line(void *mlx_ptr, void *win_ptr, t_fdf start, t_fdf end)
{
    int dx;
    int dy;
    int sx;
    int sy;
    int err;
    int e2;
    int x;
    int y;
    int color = 0x00FFFF;  // 기본 색상 설정

    dx = abs(end.pos.x - start.pos.x);
    dy = -abs(end.pos.y - start.pos.y);
    
    if (start.pos.x < end.pos.x)
        sx = 1;
    else
        sx = -1;
    
    if (start.pos.y < end.pos.y)
        sy = 1;
    else
        sy = -1;
    
    err = dx + dy;
    x = start.pos.x;
    y = start.pos.y;
    
    while (1)
    {
        // // 화면 범위 검사 (예시로 1920x1080 사용, 오프셋 +300 적용)
        // if (x >= 0 && x < 1920 && y >= 0 && y < 1080)
            mlx_pixel_put(mlx_ptr, win_ptr, x + (WIN_WIDTH/MARGIN_RIGHT), y + (WIN_HEIGHT/MARGIN_BOTTOM), color);
        // else
        //     break;
        
        if (x == end.pos.x && y == end.pos.y)
            break;
        
        e2 = 2 * err;
        if (e2 >= dy)
        {
            err += dy;
            x += sx;
        }
        if (e2 <= dx)
        {
            err += dx;
            y += sy;
        }
    }
}


t_pos	*set_pos(int x, int y, int z)
{
	t_pos	*pos;

	pos = malloc(sizeof(t_pos));
	if (!pos)
		return (0);
	pos->x = x;
	pos->y = y;
	pos->z = z;
	return (pos);
}


