/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:54:54 by skang             #+#    #+#             */
/*   Updated: 2025/03/09 21:14:04 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define FILE_PATH 1
# define INVALID_MAP 2
# define FILE_TYPE 3
# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define MAP_SCALE 20
# define MARGIN_RIGHT 300
# define MARGIN_BOTTOM 0

# include "get_next_line.h"
# include "libft.h"
# include "mlx.h"
# include "mlx_int.h"
# include <X11/keysym.h>
# include <errno.h>
# include <math.h>
# include <stdio.h>

typedef struct s_data
{
	void		*img;
	char		*addr;
	int			bpp;
	int			line_length;
	int			endian;
}				t_data;

typedef struct s_pos
{
	int			x;
	int			y;
	int			z;
}				t_pos;

typedef struct s_fdf
{
	t_pos		pos;
	int			color;
}				t_fdf;

typedef struct s_rotation
{
	double		theta_x;
	double		theta_y;
	double		theta_z;
}				t_rotation;

typedef struct s_render_info
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_fdf		**map;
	t_data		*img;
	t_rotation	rotation;
	int			scale;
	int			translate_x;
	int			translate_y;
	int			x;
	int			y;
	int			height;
}				t_render_info;

typedef struct s_line_params
{
	int			dx;
	int			dy;
	int			sx;
	int			sy;
	int			err;
}				t_line_params;

typedef struct s_draw_info
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			color;
}				t_draw_info;

/*args*/
int				valid_format(char *file_name);
int				valid_map(char *file_name);
int				is_valid_integer(const char *nptr);
int				is_valid_elements(char **elements);

/*maps*/
int				create_fdf(char *file_name);
void			set_scale(t_pos *pos, int scale);
void			draw_line(t_render_info *info, t_fdf start, t_fdf end);
t_pos			*set_pos(int x, int y, int z);
int				is_valid_elements(char **elements);
t_fdf			**create_map(int x, int y);
int				get_map_x_length(char **map);
void			set_map_size(char *file_name, int *x, int *y);
void			set_fdf_map(t_fdf **map, char *file_name);
int				ft_atoi_base(char *str, char *base);
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
void			destroy_all(t_render_info *info);
void			draw(t_render_info *info);

/*transform*/
void			rotation_x(t_pos *pos, double theta);
void			rotation_y(t_pos *pos, double theta);
void			rotation_z(t_pos *pos, double theta);
void			set_isometric_projection(t_pos *pos);
void			transform_point(t_pos *pos, t_render_info *info);

/*draw utils*/
void			draw_horizontal_line(t_render_info *info, int i, int j);
void			draw_vertical_line(t_render_info *info, int i, int j);
void			process_map_point(t_render_info *info, int i, int j);
void			render_map(t_render_info *info);

/*map loader*/
void			load_map_data(char *file_name, t_fdf ***map, int *x, int *y);

/*mem*/
void			free_matrix(char **matrix);
void			free_map(t_fdf **map, int height);
void			free_arr(void *arr);

/*error*/
void			error(int error_type);

/*mlx util*/
void			initialize_mlx(void **mlx_ptr, void **win_ptr);

/*hook handler*/
void			rotation_handler(int keycode, t_render_info *info);
void			translate_handler(int keycode, t_render_info *info);
void			scale_handler(int keycode, t_render_info *info);

/*hook utils*/
int				key_hook(int keycode, t_render_info *info);
int				close_hook(t_render_info *info);
#endif
