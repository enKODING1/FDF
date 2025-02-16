#include "mlx_int.h"
#include "mlx.h"
#include "get_next_line_bonus.h"
#include "libft.h"
#include <fcntl.h>


int main(int argc, char **argv)
{   
    if (argc < 2 || argc > 2) 
        return 0;
    
    int fd;
    char *read_line;

    fd = open(argv[1], O_RDONLY);
    
    while(1) 
    {
        read_line = get_next_line(fd);
        
        if (!read_line)
            break;
        printf("%s", read_line);
    }
    // void *mlx_ptr;
    // void *win_ptr;
    // mlx_ptr = mlx_init();
    // win_ptr = mlx_new_window(mlx_ptr, 500, 500, "title");
    // mlx_pixel_put(mlx_ptr, win_ptr, 10, 10, 0234);
    // mlx_pixel_put(mlx_ptr, win_ptr, 10, 11, 0234);
    // mlx_pixel_put(mlx_ptr, win_ptr, 10, 13, 0234);
    // mlx_pixel_put(mlx_ptr, win_ptr, 10, 14, 0234);
    // mlx_pixel_put(mlx_ptr, win_ptr, 10, 15, 0234);
    // mlx_loop(mlx_ptr);
    return 0;
}