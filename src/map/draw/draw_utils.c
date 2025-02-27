/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:55:12 by skang             #+#    #+#             */
/*   Updated: 2025/02/27 19:33:44 by skang            ###   ########.fr       */
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
	transform_point(&curr.pos);
	transform_point(&next.pos);
	draw_line(info->mlx_ptr, info->win_ptr, curr, next);
}

void	draw_vertical_line(t_render_info *info, int i, int j)
{
	t_fdf	curr;
	t_fdf	bottom;

	if (i >= info->y - 1)
		return ;
	curr = info->map[i][j];
	bottom = info->map[i + 1][j];
	transform_point(&curr.pos);
	transform_point(&bottom.pos);
	draw_line(info->mlx_ptr, info->win_ptr, curr, bottom);
}

void	draw_point(t_render_info *info, int i, int j)
{
	t_fdf	point;

	point = info->map[i][j];
	transform_point(&point.pos);
	mlx_pixel_put(info->mlx_ptr, info->win_ptr, (point.pos.x) + (WIN_WIDTH
			/ MARGIN_RIGHT), (point.pos.y) + (WIN_HEIGHT / MARGIN_BOTTOM),
		point.color);
}

void	process_map_point(t_render_info *info, int i, int j)
{
	draw_horizontal_line(info, i, j);
	draw_vertical_line(info, i, j);
	draw_point(info, i, j);
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
}
