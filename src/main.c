/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 20:26:24 by skang             #+#    #+#             */
/*   Updated: 2025/02/16 20:26:25 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include "mlx.h"
#include "mlx_int.h"

int	main(int argc, char **argv)
{
	

	if (argc < 2 || argc > 2)
		return (0);

	if (!valid_format(argv[1]))
	{
		printf("format error\n");
		return 0;
	}

	if (!valid_map(argv[1]))
	{
		printf("failed!\n");
		return 0;	
	}
		
	create_fdf(argv[1]);		
	return (0);
}
