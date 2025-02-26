#include "fdf.h"
#include "get_next_line.h"
#include <fcntl.h>

int		valid_map(char *file_name)
{
	int fd;
	int map_x_length;
	int prev_x_length;
	int flag;
	char *read_line;
	char **split_line;
	char *temp;

	fd = open(file_name, O_RDONLY);	
	read_line = get_next_line(fd);
	map_x_length = -1;	
	prev_x_length = -1;
	flag = 1;
	while(read_line)
	{
		temp = ft_strtrim(read_line, "\n");
		split_line = ft_split(temp, ' ');	
		map_x_length = get_map_x_length(split_line);
		if(prev_x_length != -1 && prev_x_length != map_x_length)
		{
			printf("size error\n");
			flag = 0;
		}
		if(!is_valid_elements(split_line))	
		{
			printf("overflow error\n");
			flag = 0;
		}

		free_arr(temp);	
		free_matrix(split_line);	
		free_arr(read_line);		
		prev_x_length = map_x_length;
		read_line = get_next_line(fd);	
	}
	free_arr(read_line);
	close(fd);
	if (flag)
		return 1;
	return 0;		
}
 