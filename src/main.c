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
#include "get_next_line_bonus.h"
#include "libft.h"
#include "mlx.h"
#include "mlx_int.h"
#include <fcntl.h>
#include <math.h>

t_pos	*set_pos(int x, int y, int z)
{
	t_pos	*pos;

	pos = malloc(sizeof(t_pos));
	if (!pos)
		return (0);
	pos->x = x;
	pos->y = y;
	pos->z = z;
	return (pos);
}

void   rotation_x(t_pos *pos, double theta)
{
        double radian;
        int temp_y;
        int temp_z;
        
        radian = theta * M_PI / 180;
        temp_y = pos->y;
        temp_z = pos->z;

        pos->x = pos->x;
        pos->y = (temp_y*cos(radian) - temp_z*sin(radian));
        pos->z = (temp_y*sin(radian) + temp_z*cos(radian));
}

void    rotation_y(t_pos *pos, double theta)
{
        double radian;
        int temp_x;
        int temp_z;

        radian = theta * M_PI / 180;
        temp_x = pos->x;
        temp_z = pos->z;

        pos->x = (temp_x*cos(radian) + temp_z*sin(radian));
        pos->y = pos->y;
		pos->z = -temp_x * sin(radian) + temp_z * cos(radian); // Corrected line
}

void    rotation_z(t_pos *pos, double theta)
{
        double radian;
        int temp_x;
        int temp_y;

        radian = theta * M_PI / 180;
        temp_x = pos->x;
        temp_y = pos->y;

        pos->x = (temp_x*cos(radian) - temp_y*sin(radian));
        pos->y = (temp_x*sin(radian) + temp_y*cos(radian));
        pos->z = pos->z;
}

void set_isometric_projection(t_pos *pos)
{
        double vertical_axis;
        double horizontal_axis;

        vertical_axis = 45.0;
        horizontal_axis = 35.264;
        rotation_z(pos, vertical_axis);
        rotation_x(pos, horizontal_axis);

        // rotation_z(pos, vertical_axis);
        // rotation_y(pos, 0);
}

// void	show_lst(void *pos)
// {
//     if (((t_pos *)pos)->x == 0)
//     {
//         printf("\n");
//     }
// 	printf("[%d, %d, %d]", ((t_pos *)pos)->x, ((t_pos *)pos)->y,
// 		((t_pos *)pos)->z);
//     // printf("%d ", ((t_pos *)pos)->z);
// }

int	main(int argc, char **argv)
{
	int		fd;
	char	*read_line;
	void	*mlx_ptr;
	char	**pos_str;
	t_list	*lst;
	t_stack	*stack;
	t_pos	*data;
	int		y;
	int		i;
	char	*temp;

	if (argc < 2 || argc > 2)
		return (0);
	void *win_ptr;
	stack = malloc(sizeof(t_stack));
	if (!stack)
		return (0);
	stack->top = lst;
    lst = NULL;
	fd = open(argv[1], O_RDONLY);
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 800, 800, "title");
	y = 0;
	while (1)
	{
		read_line = get_next_line(fd);
		if (!read_line)
			break ;
		pos_str = ft_split(read_line, ' ');
		i = 0;
		while (pos_str[i] != NULL)
		{
			temp = ft_strdup(pos_str[i]);
			data = set_pos(i, y, ft_atoi(temp));
			ft_lstadd_back(&lst, ft_lstnew(data));
			// printf("pos: %d\n", ft_atoi(pos_str[i]));
			i++;
		}
		free(read_line);
		// free(pos_str);
		y++;
	}
	// ft_lstiter(lst, show_lst);
    // lst = stack->top;
    int scale = 4;
    while(lst)
    {
        t_pos *pos;
        pos = ((t_pos *)lst->content);
        // printf("x:%d, y: %d\n", pos->x, pos->y);
        // printf("hello\n");
        // if (pos->z != 0)
        {
			pos->x *= scale;
			pos->y *= scale;
			pos->z *= scale + 6;
            set_isometric_projection(pos);
	        mlx_pixel_put(mlx_ptr, win_ptr, (pos->x) + (500/2), (pos->y) + (500/2), 0xFF0000);
        }
        lst = lst->next;
    }
	mlx_loop(mlx_ptr);
	return (0);
}
