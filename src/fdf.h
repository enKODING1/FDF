#ifndef FDF_H
# define FDF_H

#include "libft.h"

typedef struct s_pos{
    int x;
    int y;
    int z;
} t_pos;

typedef struct s_stack{
    t_list *top;
    int max_x;
    int max_y;
} t_stack;

typedef struct s_fdf{
    t_pos pos;
    int color;
} t_fdf;

#endif 