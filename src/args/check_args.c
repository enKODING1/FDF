#include "fdf.h"

int		valid_format(char *file_name)
{
	char *start;	
	int value;
	
	start = ft_strrchr(file_name, '.');
	
	if(ft_strncmp(start, ".fdf\0", 5) == 0)
		return 1;
	return 0;
}