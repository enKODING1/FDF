/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:53:33 by skang             #+#    #+#             */
/*   Updated: 2025/02/27 18:53:34 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	if (!is_valid_integer(str))
		return (0);
	return (1);
}

int	is_valid_hex_color(char *str)
{
	int	i;

	i = 0;
	if (str[0] != '0' || (str[1] != 'x' && str[1] != 'X'))
		return (0);
	i = 2;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && (str[i] < 'A' || str[i] > 'F')
			&& (str[i] < 'a' || str[i] > 'f'))
			return (0);
		i++;
	}
	if (i > 8)
		return (0);
	return (1);
}

int	is_valid_number_color_format(char *element)
{
	char	**parts;
	int		result;

	result = 0;
	parts = ft_split(element, ',');
	if (!parts[0] || !parts[1] || parts[2])
	{
		free_matrix(parts);
		return (0);
	}
	if (is_valid_number(parts[0]) && is_valid_hex_color(parts[1]))
		result = 1;
	free_matrix(parts);
	return (result);
}

int	is_valid_elements(char **elements)
{
	int	i;

	i = 0;
	while (elements[i])
	{
		if (!is_valid_number(elements[i])
			&& !is_valid_number_color_format(elements[i]))
			return (0);
		i++;
	}
	return (1);
}
