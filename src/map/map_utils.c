#include "fdf.h"

int is_valid_elements(char **elements)
{
	int i;
	int j;

	i = 0 ;
	while(elements[i])
	{
		j = 0;
		printf("[%s]", elements[i]);
		// number,color 가 아닐 경우 처리
		if (!is_valid_integer(elements[i]))
			return 0;
		i++;
	}
	printf("\n");
	return 1;
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
			printf("[%d][%d], ", i, j);
			map[i][j].pos.x = ((t_pos *)lst->content)->x;
			map[i][j].pos.y = ((t_pos *)lst->content)->y;
			map[i][j].pos.z = ((t_pos *)lst->content)->z;
			lst = lst->next;
			j++;
		}
		printf("\n");
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

int		get_map_x_length(char **map)
{
		int i;
		
		i = 0;
		while(map[i])	
			i++;	
		return i;
}

int		get_map_y_length(char **map)
{
		int i;

		i = 0;
		while(map[i])
			i++;

		return i;
}

void view_matrix(char **matrix)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(matrix[i])
	{
		printf("[%s] ", matrix[i]);	
		i++;
	}
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