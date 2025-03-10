/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:55:12 by skang             #+#    #+#             */
/*   Updated: 2025/03/09 20:35:21 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_horizontal_line(t_render_info *info, int i, int j)
{
	t_fdf	curr;
	t_fdf	next;

	if (j >= info->x - 1)
		return ;
	curr = info->map[i][j];
	next = info->map[i][j + 1];
	if (curr.pos.z != 0)
		curr.pos.z *= info->height;
	if (next.pos.z != 0)
		next.pos.z *= info->height;
	transform_point(&curr.pos, info);
	transform_point(&next.pos, info);
	draw_line(info, curr, next);
}

void	draw_vertical_line(t_render_info *info, int i, int j)
{
	t_fdf	curr;
	t_fdf	bottom;

	if (i >= info->y - 1)
		return ;
	curr = info->map[i][j];
	bottom = info->map[i + 1][j];
	if (curr.pos.z != 0)
		curr.pos.z *= info->height;
	if (bottom.pos.z != 0)
		bottom.pos.z *= info->height;
	transform_point(&curr.pos, info);
	transform_point(&bottom.pos, info);
	draw_line(info, curr, bottom);
}

void	process_map_point(t_render_info *info, int i, int j)
{
	draw_horizontal_line(info, i, j);
	draw_vertical_line(info, i, j);
}

void	render_map(t_render_info *info)
{
	int	i;
	int	j;

	i = 0;
	while (i < info->y)
	{
		j = 0;
		while (j < info->x)
		{
			process_map_point(info, i, j);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(info->mlx_ptr, info->win_ptr, info->img->img, 0, 0);
}
