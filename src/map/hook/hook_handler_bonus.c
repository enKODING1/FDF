/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 21:13:37 by skang             #+#    #+#             */
/*   Updated: 2025/03/09 21:13:39 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotation_handler(int keycode, t_render_info *info)
{
	if (keycode == XK_Down)
		(info->rotation).theta_x -= 10;
	if (keycode == XK_Up)
		(info->rotation).theta_x += 10;
	if (keycode == XK_Left)
		(info->rotation).theta_y -= 10;
	if (keycode == XK_Right)
		(info->rotation).theta_y += 10;
	if (keycode == XK_q)
		(info->rotation).theta_z += 10;
	if (keycode == XK_e)
		(info->rotation).theta_z -= 10;
}

void	translate_handler(int keycode, t_render_info *info)
{
	if (keycode == XK_w)
		info->translate_y -= 10;
	if (keycode == XK_a)
		info->translate_x -= 10;
	if (keycode == XK_d)
		info->translate_x += 10;
	if (keycode == XK_s)
		info->translate_y += 10;
}

void	scale_handler(int keycode, t_render_info *info)
{
	if (keycode == XK_KP_Add)
		info->scale += 1;
	if (keycode == XK_KP_Subtract)
		info->scale -= 1;
	if (keycode == XK_bracketleft)
		info->height -= 1;
	if (keycode == XK_bracketright)
		info->height += 1;
}
