/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:34:36 by skang             #+#    #+#             */
/*   Updated: 2025/02/27 19:34:37 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotation_x(t_pos *pos, double theta)
{
	double	radian;
	int		temp_y;
	int		temp_z;

	radian = theta * M_PI / 180;
	temp_y = pos->y;
	temp_z = pos->z;
	pos->x = pos->x;
	pos->y = (temp_y * cos(radian) - temp_z * sin(radian));
	pos->z = (temp_y * sin(radian) + temp_z * cos(radian));
}

void	rotation_y(t_pos *pos, double theta)
{
	double	radian;
	int		temp_x;
	int		temp_z;

	radian = theta * M_PI / 180;
	temp_x = pos->x;
	temp_z = pos->z;
	pos->x = (temp_x * cos(radian) + temp_z * sin(radian));
	pos->y = pos->y;
	pos->z = -temp_x * sin(radian) + temp_z * cos(radian);
}

void	rotation_z(t_pos *pos, double theta)
{
	double	radian;
	int		temp_x;
	int		temp_y;

	radian = theta * M_PI / 180;
	temp_x = pos->x;
	temp_y = pos->y;
	pos->x = (temp_x * cos(radian) - temp_y * sin(radian));
	pos->y = (temp_x * sin(radian) + temp_y * cos(radian));
	pos->z = pos->z;
}

void	set_isometric_projection(t_pos *pos)
{
	double	vertical_axis;
	double	horizontal_axis;

	vertical_axis = 45.0;
	horizontal_axis = 35.264;
	rotation_z(pos, vertical_axis);
	rotation_x(pos, horizontal_axis);
}

void	transform_point(t_pos *pos)
{
	set_scale(pos, MAP_SCALE);
	set_isometric_projection(pos);
}
