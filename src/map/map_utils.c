/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:55:23 by skang             #+#    #+#             */
/*   Updated: 2025/02/27 19:34:29 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_fdf	**create_map(int x, int y)
{
	int		i;
	t_fdf	**map;

	i = 0;
	map = (t_fdf **)malloc(sizeof(t_fdf *) * y);
	while (i < y)
	{
		map[i] = (t_fdf *)malloc(sizeof(t_fdf) * x);
		i++;
	}
	return (map);
}

int	get_map_x_length(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		i++;
	}
	return (i);
}

void	set_map_size(char *file_name, int *x, int *y)
{
	int		fd;
	char	*read_line;
	char	*trim_line;
	char	**split_line;

	fd = open(file_name, O_RDONLY);
	read_line = get_next_line(fd);
	while (read_line)
	{
		trim_line = ft_strtrim(read_line, "\n");
		split_line = ft_split(trim_line, ' ');
		if (*x == 0)
			*x = get_map_x_length(split_line);
		free_arr(read_line);
		free_arr(trim_line);
		free_matrix(split_line);
		read_line = get_next_line(fd);
		*y += 1;
	}
	close(fd);
}

void	parse_element(t_fdf *map_element, char *element)
{
	char	**parts;

	if (ft_strchr(element, ','))
	{
		parts = ft_split(element, ',');
		map_element->pos.z = ft_atoi(parts[0]);
		if (parts[1] && parts[1][0] == '0' && (parts[1][1] == 'x'
				|| parts[1][1] == 'X'))
		{
			map_element->color = ft_atoi_base(parts[1] + 2, "0123456789abcdef");
		}
		else
		{
			map_element->color = 0xFFFFFF;
		}
		free_matrix(parts);
	}
	else
	{
		map_element->pos.z = ft_atoi(element);
		map_element->color = 0xFFFFFF;
	}
}

void	set_fdf_map(t_fdf **map, char *file_name)
{
	int		fd;
	int		x;
	int		y;
	char	*read_line;
	char	*trim_line;
	char	**split_line;

	fd = open(file_name, O_RDONLY);
	read_line = get_next_line(fd);
	x = 0;
	y = 0;
	while (read_line)
	{
		trim_line = ft_strtrim(read_line, "\n");
		split_line = ft_split(trim_line, ' ');
		while (split_line[x])
		{
			map[y][x].pos.x = x;
			map[y][x].pos.y = y;
			parse_element(&map[y][x], split_line[x]);
			x++;
		}
		x = 0;
		y++;
		free_arr(read_line);
		free_arr(trim_line);
		free_matrix(split_line);
		read_line = get_next_line(fd);
	}
	close(fd);
}
