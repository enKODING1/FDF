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

#include "fdf.h"

int	create_fdf(char *file_name)
{
	t_render_info	info;

	info.x = 0;
	info.y = 0;
	initialize_mlx(&info.mlx_ptr, &info.win_ptr);
	load_map_data(file_name, &info.map, &info.x, &info.y);
	render_map(&info);
	mlx_loop(info.mlx_ptr);
	mlx_destroy_display(info.mlx_ptr);
	mlx_destroy_window(info.mlx_ptr, info.win_ptr);
	return (0);
}
