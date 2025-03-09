/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:48:02 by skang             #+#    #+#             */
/*   Updated: 2025/03/09 20:59:16 by skang            ###   ########.fr       */
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

void	transform_point(t_pos *pos, t_render_info *info)
{
	set_scale(pos, info->scale);
	rotation_z(pos, info->rotation.theta_z);
	rotation_x(pos, info->rotation.theta_x);
	rotation_y(pos, info->rotation.theta_y);
}
