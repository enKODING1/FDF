#ifndef FDF_H
# define FDF_H
# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define MAP_SCALE 8 
# define MARGIN_RIGHT 5
# define MARGIN_BOTTOM 9

#include "libft.h"
#include "get_next_line.h"
#include "mlx.h"
#include "mlx_int.h"
#include <stdio.h>


typedef struct s_pos{
    int x;
    int y;
    int z;
} t_pos;

typedef struct s_fdf{
    t_pos pos;
    int color;
} t_fdf;


/*args*/
int valid_format(char *file_name);
int		valid_map(char *file_name);
int is_valid_integer(const char *nptr);

/*maps*/
int    create_fdf(char *file_name);
void   rotation_x(t_pos *pos, double theta);
void    rotation_y(t_pos *pos, double theta);
void    rotation_z(t_pos *pos, double theta);
void set_isometric_projection(t_pos *pos);
void	set_scale(t_pos *pos, int scale);
void draw_line(void *mlx_ptr, void *win_ptr, t_fdf start, t_fdf end);
t_pos	*set_pos(int x, int y, int z);
int is_valid_elements(char **elements);
t_fdf **	create_map(int x, int y);
void show_map(t_fdf **map, int x, int y);
int		get_map_x_length(char **map);
int		get_map_y_length(char **map);
void view_matrix(char **matrix);
void	show_lst(void *pos);
void    set_map_size(char *file_name, int *x, int *y);
void    set_fdf_map(t_fdf **map, char *file_name);

/*mem*/
void free_matrix(char **matrix);
void free_arr(void *arr);


#endif 