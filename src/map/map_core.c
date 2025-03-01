/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_core.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:34:19 by skang             #+#    #+#             */
/*   Updated: 2025/02/27 22:14:29 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <X11/keysym.h>

int	key_hook(int keycode, t_render_info *info)
{
	if (keycode == XK_Escape)
	{
		mlx_destroy_window(info->mlx_ptr, info->win_ptr);
		mlx_destroy_display(info->mlx_ptr);
		free(info->mlx_ptr);
		free_map(info->map, info->y);
		exit(0);
	}
	return (0);
}

int	close_hook(t_render_info *info)
{
	mlx_destroy_window(info->mlx_ptr, info->win_ptr);
	mlx_destroy_display(info->mlx_ptr);
	free(info->mlx_ptr);
	free_map(info->map, info->y);
	exit(0);
}

int	create_fdf(char *file_name)
{
	t_render_info	info;
	t_data img;

	ft_memset(&info, 0, sizeof(t_render_info));
	initialize_mlx(&info.mlx_ptr, &info.win_ptr);
	img.img = mlx_new_image(info.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_length, &img.endian);
	load_map_data(file_name, &info.map, &info.x, &info.y);
	render_map(&info, &img);
	// for(int i = 0; i < 100 ; i++) {
	// 	my_mlx_pixel_put(&img, i, i, 0x00FF0000);// 붉은색 선을 대각선으로 그린다.
	// 	my_mlx_pixel_put(&img, 5, i, 0x00FF0000);// 붉은색 선을 세로으로 그린다.
	// 	my_mlx_pixel_put(&img, i, 5, 0x00FF0000);// 붉은색 선을 가로으로 그린다.
	// }
	// mlx_put_image_to_window(info.mlx_ptr, info.win_ptr, img.img, 0, 0);//이미지를 윈도우에 올린다.

	mlx_key_hook(info.win_ptr, key_hook, &info);
	mlx_hook(info.win_ptr, DestroyNotify, StructureNotifyMask, close_hook,
		&info);
	mlx_loop(info.mlx_ptr);
	return (0);
}
