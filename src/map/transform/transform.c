/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:48:02 by skang             #+#    #+#             */
/*   Updated: 2025/02/27 19:48:03 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_scale(t_pos *pos, int scale)
{
	pos->x *= scale;
	pos->y *= scale;
	pos->z *= scale / 6;
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

void	transform_point(t_pos *pos)
{
	set_scale(pos, MAP_SCALE);
	set_isometric_projection(pos);
}
