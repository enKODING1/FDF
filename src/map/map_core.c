/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_core.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:34:19 by skang             #+#    #+#             */
/*   Updated: 2025/02/27 19:34:19 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <X11/keysym.h>  // XK_Escape 용도
#include "fdf.h"

int	key_hook(int keycode, t_render_info *info)
{
	if (keycode == XK_Escape)
	{
		mlx_destroy_window(info->mlx_ptr, info->win_ptr);
		mlx_destroy_display(info->mlx_ptr);
		free_map(info->map, info->y);
		exit(0);
	}
	return (0);
}

int	close_hook(t_render_info *info)
{
	mlx_destroy_window(info->mlx_ptr, info->win_ptr);
	mlx_destroy_display(info->mlx_ptr);
	free_map(info->map, info->y);
	exit(0);
}

int	create_fdf(char *file_name)
{
	t_render_info	info;

	ft_memset(&info, 0, sizeof(t_render_info));
	initialize_mlx(&info.mlx_ptr, &info.win_ptr);
	load_map_data(file_name, &info.map, &info.x, &info.y);
	render_map(&info);

	mlx_key_hook(info.win_ptr, key_hook, &info);
	mlx_hook(info.win_ptr, DestroyNotify, StructureNotifyMask, close_hook, &info);
	
	mlx_loop(info.mlx_ptr);
	return (0);
}

