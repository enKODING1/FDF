#include "fdf.h"

int is_valid_elements(char **elements)
{
	int i;
	int j;

	i = 0 ;
	while(elements[i])
	{
		j = 0;
		// printf("[%s]", elements[i]);
		// number,color 가 아닐 경우 처리
		if (!is_valid_integer(elements[i]))
			return 0;
		i++;
	}
	// printf("\n");
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
		{
			// printf("[%s]", map[i]);
			i++;
		}
		// printf("\n");
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

void 	set_map_size(char *file_name, int *x, int *y)
{
	int fd;
	char *read_line;
	char *trim_line;
	char **split_line;

	fd = open(file_name, O_RDONLY);
	read_line = get_next_line(fd);
	while(read_line)	
	{
		printf("%s", read_line);
		trim_line = ft_strtrim(read_line, "\n");
		split_line = ft_split(trim_line, ' ');
		if (*x == 0)
			*x = get_map_x_length(split_line);
		free_arr(read_line);
		free_arr(trim_line);
		free_matrix(split_line);
		read_line = get_next_line(fd);
		*y += 1;
	}
	close(fd);
}

void	set_fdf_map(t_fdf **map, char *file_name)
{
	int fd;
	int x;
	int y;
	char *read_line;
	char *trim_line;
	char **split_line;

	fd = open(file_name, O_RDONLY);
	read_line = get_next_line(fd);
	x = 0;
	y = 0;
	while(read_line)
	{
		trim_line = ft_strtrim(read_line, "\n");
		split_line = ft_split(trim_line, ' ');
		while (split_line[x])	
		{
			map[y][x].pos.x = x;
			map[y][x].pos.y = y;
			map[y][x].pos.z = ft_atoi(split_line[x]);
			x++;
		}
		x=0;
		y++;
		free_arr(read_line);
		free_arr(trim_line);
		free_matrix(split_line);
		read_line = get_next_line(fd);
	}
	close(fd);
}