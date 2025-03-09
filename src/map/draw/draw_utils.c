/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:55:12 by skang             #+#    #+#             */
/*   Updated: 2025/02/27 20:03:48 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	transform_point_(t_pos *pos, int theta)
{
	set_scale(pos, MAP_SCALE);
	// set_isometric_projection(pos);
	rotation_x(pos, theta);
}

void	draw_horizontal_line(t_render_info *info, t_data *img, int i, int j)
{
	t_fdf	curr;
	t_fdf	next;

	if (j >= info->x - 1)
		return ;
	curr = info->map[i][j];
	next = info->map[i][j + 1];
	transform_point_(&curr.pos, info->theta_x);
	transform_point_(&next.pos, info->theta_x);
	draw_line(info->mlx_ptr, info->win_ptr, img, curr, next);
}

void	draw_vertical_line(t_render_info *info, t_data *img, int i, int j)
{
	t_fdf	curr;
	t_fdf	bottom;

	if (i >= info->y - 1)
		return ;
	curr = info->map[i][j];
	bottom = info->map[i + 1][j];
	transform_point_(&curr.pos, info->theta_x);
	transform_point_(&bottom.pos, info->theta_x);
	draw_line(info->mlx_ptr, info->win_ptr, img, curr, bottom);
}

void	process_map_point(t_render_info *info, t_data *img, int i, int j)
{
	draw_horizontal_line(info, img, i, j);
	draw_vertical_line(info, img, i, j);
}

void	render_map(t_render_info *info, t_data *img)
{
	int	i;
	int	j;

	i = 0;
	while (i < info->y)
	{
		j = 0;
		while (j < info->x)
		{
			process_map_point(info, img, i, j);
			j++;
		}
		i++;
	}

	mlx_put_image_to_window(info->mlx_ptr, info->win_ptr, img->img, 0, 0);
	printf("theta: %f\n", info->theta_x);
	info->theta_x += 10;
}
