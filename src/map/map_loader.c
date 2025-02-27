/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:34:24 by skang             #+#    #+#             */
/*   Updated: 2025/02/27 19:34:24 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	load_map_data(char *file_name, t_fdf ***map, int *x, int *y)
{
	set_map_size(file_name, x, y);
	*map = create_map(*x, *y);
	set_fdf_map(*map, file_name);
}
