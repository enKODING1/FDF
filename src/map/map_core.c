/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_core.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:34:19 by skang             #+#    #+#             */
/*   Updated: 2025/03/09 20:59:25 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <X11/keysym.h>

void	destroy_all(t_render_info *info)
{
	mlx_destroy_image(info->mlx_ptr, info->img->img);
	mlx_destroy_window(info->mlx_ptr, info->win_ptr);
	mlx_destroy_display(info->mlx_ptr);
	free(info->mlx_ptr);
	free_map(info->map, info->y);
	exit(0);
}

void	init_handler(t_render_info *info)
{
	ft_memset(info, 0, sizeof(t_render_info));
	info->rotation.theta_z = 45.0;
	info->rotation.theta_x = 35.264;
	info->rotation.theta_y = 0;
	info->scale = MAP_SCALE;
	info->translate_x = MARGIN_RIGHT;
	info->translate_y = MARGIN_BOTTOM;
	info->height = 1;
}

int	create_fdf(char *file_name)
{
	t_render_info	info;
	t_data			img;

	init_handler(&info);
	initialize_mlx(&info.mlx_ptr, &info.win_ptr);
	img.img = mlx_new_image(info.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_length,
			&img.endian);
	load_map_data(file_name, &info.map, &info.x, &info.y);
	info.img = &img;
	render_map(&info);
	mlx_key_hook(info.win_ptr, key_hook, &info);
	mlx_hook(info.win_ptr, DestroyNotify, StructureNotifyMask, close_hook,
		&info);
	mlx_loop(info.mlx_ptr);
	return (0);
}
