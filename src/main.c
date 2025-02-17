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

void	show_lst(void *pos)
{
    if (((t_pos *)pos)->x == 0)
    {
        printf("\n");
    }
	printf("[%d, %d, %d]", ((t_pos *)pos)->x, ((t_pos *)pos)->y,
		((t_pos *)pos)->z);
    // printf("%d ", ((t_pos *)pos)->z);
}

t_fdf **	create_map(int x, int y)
{
	int i;
	t_fdf **map;

	i = 0;
	map = (t_fdf **)malloc(sizeof(t_fdf *) * y);
	while(i < y)
	{
		map[i] = (t_fdf*)malloc(sizeof(t_fdf) * x);
		i++;
	}

	return map;
}

void	stack_to_map(t_stack *stack, t_fdf **map)
{
	int i;
	int j;
	t_list *lst;	

	i = 0;
	j = 0;
	lst = stack->top;
	while(i < stack->max_y)
	{
		j = 0;
		while(j < stack->max_x)
		{
			map[i][j].pos.x = ((t_pos *)lst->content)->x;
			map[i][j].pos.y = ((t_pos *)lst->content)->y;
			map[i][j].pos.z = ((t_pos *)lst->content)->z;
			lst = lst->next;
			j++;
		}
		i++;
	}
}

void show_map(t_fdf **map, int x, int y)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(i < y)
	{
		j = 0;
		while(j < x)
		{
			printf("[%d, %d, %d] ", map[i][j].pos.x, map[i][j].pos.y, map[i][j].pos.z);
			j++;
		}
		printf("\n");
		i++;
	}
}

int	main(int argc, char **argv)
{
	int		fd;
	char	*read_line;
	void	*mlx_ptr;
	char	**pos_str;
	t_list	*lst;
	t_stack	*stack;
	t_pos	*data;
	int		j;
	int		i;
	char	*temp;
	t_fdf	**map;

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
	j = 0;
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
			data = set_pos(i, j, ft_atoi(temp));
			ft_lstadd_back(&lst, ft_lstnew(data));
			// printf("pos: %d\n", ft_atoi(pos_str[i]));
			i++;
		}
		stack->max_x = i;	
		free(read_line);
		// free(pos_str);
		j++;
	}
	stack->max_y = j;
	stack->top = lst;
	// ft_lstiter(stack->top, show_lst);
    // lst = stack->top;
	map = create_map(stack->max_x, stack->max_y);
	
	// ft_lstiter(stack->top, show_lst);
	stack_to_map(stack, map);
	show_map(map, stack->max_x,stack->max_y);


    int scale = 4;
	i = 0;
	j = 0;
    while(i < stack->max_y)
    {
		j = 0;
		while(j < stack->max_x)
		{
		    t_pos *pos;
  		    pos = &map[i][j].pos;
			pos->x *= scale;
			pos->y *= scale;
			pos->z *= scale + 6;
            set_isometric_projection(pos);
	        mlx_pixel_put(mlx_ptr, win_ptr, (pos->x) + (500/2), (pos->y) + (500/2), 0xFF0000);
			j++;
		}
		i++;
     }
	mlx_loop(mlx_ptr);
	return (0);
}
