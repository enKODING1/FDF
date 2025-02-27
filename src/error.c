/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:54:28 by skang             #+#    #+#             */
/*   Updated: 2025/02/27 18:54:30 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	error(int error_type)
{
	if (error_type == FILE_PATH)
	{
		ft_putstr_fd(strerror(errno), 1);
		ft_putstr_fd("\n", 1);
	}
	if (error_type == INVALID_MAP)
		ft_putstr_fd("Invalid Map\n", 1);
	if (error_type == FILE_TYPE)
		ft_putstr_fd("Invalid File type\n", 1);
}
