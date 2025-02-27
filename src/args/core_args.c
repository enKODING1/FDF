/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:53:29 by skang             #+#    #+#             */
/*   Updated: 2025/02/27 18:53:30 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	check_line_length(int prev_length, int current_length)
{
	if (prev_length != -1 && prev_length != current_length)
		return (0);
	return (1);
}

int	process_map_line(char *line, int *prev_x_length)
{
	char	*temp;
	char	**split_line;
	int		map_x_length;
	int		is_valid;

	is_valid = 1;
	temp = ft_strtrim(line, "\n");
	split_line = ft_split(temp, ' ');
	map_x_length = get_map_x_length(split_line);
	if (!check_line_length(*prev_x_length, map_x_length))
		is_valid = 0;
	if (!is_valid_elements(split_line))
		is_valid = 0;
	free_arr(temp);
	free_matrix(split_line);
	*prev_x_length = map_x_length;
	return (is_valid);
}

int	validate_map_file(int fd)
{
	char	*read_line;
	int		prev_x_length;
	int		is_valid;

	prev_x_length = -1;
	is_valid = 1;
	read_line = get_next_line(fd);
	while (read_line)
	{
		if (!process_map_line(read_line, &prev_x_length))
			is_valid = 0;
		free_arr(read_line);
		read_line = get_next_line(fd);
	}
	free_arr(read_line);
	return (is_valid);
}

int	valid_map(char *file_name)
{
	int	fd;
	int	result;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		error(FILE_PATH);
		return (0);
	}
	result = validate_map_file(fd);
	if (!result)
		error(INVALID_MAP);
	close(fd);
	return (result);
}
