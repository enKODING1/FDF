/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_core.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:55:18 by skang             #+#    #+#             */
/*   Updated: 2025/02/27 20:04:15 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fdf.h"

static void	initialize_line_params(t_fdf start, t_fdf end,
		t_line_params *params)
{
	params->dx = abs(end.pos.x - start.pos.x);
	params->dy = -abs(end.pos.y - start.pos.y);
	if (start.pos.x < end.pos.x)
		params->sx = 1;
	else
		params->sx = -1;
	if (start.pos.y < end.pos.y)
		params->sy = 1;
	else
		params->sy = -1;
	params->err = params->dx + params->dy;
}

static void	draw_pixel(t_draw_info *info, int x, int y)
{
	mlx_pixel_put(info->mlx_ptr, info->win_ptr, x + (WIN_WIDTH / MARGIN_RIGHT),
		y + (WIN_HEIGHT / MARGIN_BOTTOM), info->color);
}

void			my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	// printf("dat_length: %d\n", data->line_length);
	// printf("color: %d\n", color);
	printf("x: %d, y: %d\n", x, y);
	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	// *(unsigned int*)dst = color;
	*(unsigned int*)dst = 0x00FF0000;
}

static void	update_position(t_line_params *params, int *x, int *y)
{
	int	e2;

	e2 = 2 * params->err;
	if (e2 >= params->dy)
	{
		params->err += params->dy;
		*x += params->sx;
	}
	if (e2 <= params->dx)
	{
		params->err += params->dx;
		*y += params->sy;
	}
}

void	draw_line(void *mlx_ptr, void *win_ptr, t_data *img, t_fdf start, t_fdf end)
{
	t_line_params	params;
	t_draw_info		draw_info;
	int				x;
	int				y;

	initialize_line_params(start, end, &params);
	draw_info.mlx_ptr = mlx_ptr;
	draw_info.win_ptr = win_ptr;
	draw_info.color = start.color;
	x = start.pos.x;
	y = start.pos.y;
	while (1)
	{
		// draw_pixel(&draw_info, x, y);
		// if (x < 0)
		// 	x = 0;	
		// if (y < 0)
		// 	y = 0;
		// my_mlx_pixel_put(img, x, y, start.color);
		// my_mlx_pixel_put(img, 100, 10, 0x00FF0000);// 붉은색 선을 대각선으로 그린다.
		// printf("x: %d, y: %d\n", x, y);
		// 화면 범위 검사 (예시로 1920x1080 사용, 오프셋 +300 적용)
	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
				// mlx_pixel_put(mlx_ptr, win_ptr, x + 300, y + 300, 0x00FF0000);
			my_mlx_pixel_put(img, x, y, start.color);
		else
				break;	
		if (x == end.pos.x && y == end.pos.y)
			break ;
		update_position(&params, &x, &y);
	}
	// for(int i = 0; i < 100 ; i++) {
	// 	my_mlx_pixel_put(img, i, i, 0x00FF0000);// 붉은색 선을 대각선으로 그린다.
	// 	my_mlx_pixel_put(img, 5, i, 0x00FF0000);// 붉은색 선을 세로으로 그린다.
	// 	my_mlx_pixel_put(img, i, 5, 0x00FF0000);// 붉은색 선을 가로으로 그린다.
	// }


}
