#ifndef FDF_H
# define FDF_H

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

typedef struct s_stack{
    t_list *top;
    int max_x;
    int max_y;
} t_stack;

typedef struct s_fdf{
    t_pos pos;
    int color;
} t_fdf;

/*args*/
int valid_format(char *file_name);
int		valid_map(char *file_name);
int is_valid_integer(const char *nptr);

/*maps*/
void   rotation_x(t_pos *pos, double theta);
void    rotation_y(t_pos *pos, double theta);
void    rotation_z(t_pos *pos, double theta);
void set_isometric_projection(t_pos *pos);
void	set_scale(t_pos *pos, int scale);
void draw_line(void *mlx_ptr, void *win_ptr, t_pos start, t_pos end);
t_pos	*set_pos(int x, int y, int z);
int is_valid_elements(char **elements);
t_fdf **	create_map(int x, int y);
void	stack_to_map(t_stack *stack, t_fdf **map);
void show_map(t_fdf **map, int x, int y);
int		get_map_x_length(char **map);
int		get_map_y_length(char **map);
void view_matrix(char **matrix);
void	show_lst(void *pos);

/*mem*/
void free_matrix(char **matrix);


#endif 