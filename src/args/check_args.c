/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:53:24 by skang             #+#    #+#             */
/*   Updated: 2025/02/27 18:53:25 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	valid_format(char *file_name)
{
	char	*start;

	start = ft_strrchr(file_name, '.');
	if (!start)
		return (0);
	if (ft_strncmp(start, ".fdf", 5) == 0)
		return (1);
	error(FILE_TYPE);
	return (0);
}
