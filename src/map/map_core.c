#include "fdf.h"

int create_fdf(char *file_name)
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
    void *win_ptr;
    stack = malloc(sizeof(t_stack));
	if (!stack)
		return (0);
	stack->top = lst;
    lst = NULL;
	fd = open(file_name, O_RDONLY);
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 1920, 1080, "title");
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
	printf("msp: %d, %d\n", stack->max_x, stack->max_y);
	ft_lstiter(stack->top, show_lst);
    lst = stack->top;
	map = create_map(stack->max_x, stack->max_y);
	
	ft_lstiter(stack->top, show_lst);
	stack_to_map(stack, map);
	show_map(map, stack->max_x,stack->max_y);

    int scale = 30;
	i = 0;
	j = 0;
    while(i < stack->max_y)
    {
		j = 0;
		while(j < stack->max_x)
		{
		    t_pos pos;
			t_pos next_pos;
			t_pos bottom_pos;	

  		    pos = map[i][j].pos;
			//선긋기	
			set_scale(&pos, scale);
            set_isometric_projection(&pos);
			
			if (j < stack->max_x-1 )
			{
				next_pos = map[i][j+1].pos;
				set_scale(&next_pos, scale);
				set_isometric_projection(&next_pos);
				draw_line(mlx_ptr, win_ptr, pos, next_pos);
			}
			if(i  < stack->max_y - 1)
			{
				bottom_pos = map[i+1][j].pos;
				set_scale(&bottom_pos, scale);
				set_isometric_projection(&bottom_pos);
				draw_line(mlx_ptr, win_ptr, pos, bottom_pos);
			}
			printf("[%d][%d], ", i, j);
	        mlx_pixel_put(mlx_ptr, win_ptr, (pos.x) + 300, (pos.y) + 300, 0x00FFFF);
			j++;
		}
		printf("\n");
		i++;
     }
	mlx_loop(mlx_ptr);
}