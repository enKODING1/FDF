/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:54:54 by skang             #+#    #+#             */
/*   Updated: 2025/02/27 20:18:21 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define FILE_PATH 1
# define INVALID_MAP 2
# define FILE_TYPE 3
# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define MAP_SCALE 25
# define MARGIN_RIGHT 2
# define MARGIN_BOTTOM 15

# include "get_next_line.h"
# include "libft.h"
# include "mlx.h"
# include "mlx_int.h"
# include <errno.h>
# include <math.h>
# include <stdio.h>

typedef struct s_pos
{
	int		x;
	int		y;
	int		z;
}			t_pos;

typedef struct s_fdf
{
	t_pos	pos;
	int		color;
}			t_fdf;

typedef struct s_render_info
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_fdf	**map;
	int		x;
	int		y;
}			t_render_info;

typedef struct s_line_params
{
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		err;
}			t_line_params;

typedef struct s_draw_info
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		color;
}			t_draw_info;

/*args*/
int			valid_format(char *file_name);
int			valid_map(char *file_name);
int			is_valid_integer(const char *nptr);
int			is_valid_elements(char **elements);

/*maps*/
int			create_fdf(char *file_name);
void		set_scale(t_pos *pos, int scale);
void		draw_line(void *mlx_ptr, void *win_ptr, t_fdf start, t_fdf end);
t_pos		*set_pos(int x, int y, int z);
int			is_valid_elements(char **elements);
t_fdf		**create_map(int x, int y);
int			get_map_x_length(char **map);
void		set_map_size(char *file_name, int *x, int *y);
void		set_fdf_map(t_fdf **map, char *file_name);
int			ft_atoi_base(char *str, char *base);

/*transform*/
void		rotation_x(t_pos *pos, double theta);
void		rotation_y(t_pos *pos, double theta);
void		rotation_z(t_pos *pos, double theta);
void		set_isometric_projection(t_pos *pos);
void		transform_point(t_pos *pos);

/*draw utils*/
void		draw_horizontal_line(t_render_info *info, int i, int j);
void		draw_vertical_line(t_render_info *info, int i, int j);
void		draw_point(t_render_info *info, int i, int j);
void		process_map_point(t_render_info *info, int i, int j);
void		render_map(t_render_info *info);

/*map loader*/
void		load_map_data(char *file_name, t_fdf ***map, int *x, int *y);

/*mem*/
void		free_matrix(char **matrix);
void		free_arr(void *arr);

/*error*/
void		error(int error_type);

/*mlx util*/
void		initialize_mlx(void **mlx_ptr, void **win_ptr);

#endif
