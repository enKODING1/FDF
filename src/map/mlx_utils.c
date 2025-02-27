/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:34:32 by skang             #+#    #+#             */
/*   Updated: 2025/02/27 19:34:33 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	initialize_mlx(void **mlx_ptr, void **win_ptr)
{
	*mlx_ptr = mlx_init();
	*win_ptr = mlx_new_window(*mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "fdf");
}
