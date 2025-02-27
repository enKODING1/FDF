/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_core.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:55:18 by skang             #+#    #+#             */
/*   Updated: 2025/02/27 19:33:33 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void	set_scale(t_pos *pos, int scale)
{
	pos->x *= scale;
	pos->y *= scale;
	pos->z *= scale / 6;
}

void	draw_line(void *mlx_ptr, void *win_ptr, t_fdf start, t_fdf end)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;
	int	x;
	int	y;

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
		mlx_pixel_put(mlx_ptr, win_ptr, x + (WIN_WIDTH / MARGIN_RIGHT), y
			+ (WIN_HEIGHT / MARGIN_BOTTOM), start.color);
		if (x == end.pos.x && y == end.pos.y)
			break ;
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
