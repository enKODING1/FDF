/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 20:26:24 by skang             #+#    #+#             */
/*   Updated: 2025/02/27 22:15:11 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	if (argc < 2 || argc > 2)
		return (0);
	if (!valid_format(argv[1]))
		return (0);
	if (!valid_map(argv[1]))
		return (0);
	create_fdf(argv[1]);
	return (0);
}
