/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 21:13:44 by skang             #+#    #+#             */
/*   Updated: 2025/03/09 21:13:47 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	clear_image(t_data *img)
{
	ft_memset(img->addr, 0, WIN_WIDTH * WIN_HEIGHT * (img->bpp / 8));
}

void	draw(t_render_info *info)
{
	clear_image(info->img);
	mlx_clear_window(info->mlx_ptr, info->win_ptr);
	render_map(info);
}

int	key_hook(int keycode, t_render_info *info)
{
	if (keycode == XK_Escape)
		destroy_all(info);
	rotation_handler(keycode, info);
	translate_handler(keycode, info);
	scale_handler(keycode, info);
	draw(info);
	return (0);
}

int	close_hook(t_render_info *info)
{
	destroy_all(info);
	return (0);
}
