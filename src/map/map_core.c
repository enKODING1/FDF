#include "fdf.h"

/* 헬퍼 함수 프로토타입 */
static void init_mlx_and_window(t_mlx_env *env);
static void get_map_dimensions(char *file_name, int *x, int *y);
static void create_and_read_map(char *file_name, t_map_data *map);
static void render_map(t_mlx_env *env, t_map_data *map);
static void process_point(t_mlx_env *env, t_fdf point);
static void draw_adjacent_lines(t_mlx_env *env, t_map_data *map, int i, int j);

int create_fdf(char *file_name)
{
    int		fd;
    int     x;
    int     y;
    int     i;
    int     j;
	char	*read_line;
    char    *trim_line;
    char    **split_line;
	void	*mlx_ptr;
    void    *win_ptr;
	t_pos	*data;
	t_fdf	**map; 

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "title");
    x = 0;
    y = 0;
    set_map_size(file_name, &x, &y);
    printf("x: %d, y: %d\n", x, y);
    map = create_map(x, y);
    set_fdf_map(map, file_name);
    show_map(map, x, y);

    i = 0;

    while(i < y)
    {
		j = 0;
		while(j < x)
		{
		    t_fdf curr;
			t_fdf next;
			t_fdf bottom;	

  		    curr = map[i][j];
			//선긋기	
			set_scale(&curr.pos, MAP_SCALE);
            set_isometric_projection(&curr.pos);
			
			if (j < x-1 )
			{
				next = map[i][j+1];
				set_scale(&next.pos, MAP_SCALE);
				set_isometric_projection(&next.pos);
				draw_line(mlx_ptr, win_ptr, curr, next);
			}
			if(i  < y - 1)
			{
				bottom = map[i+1][j];
				set_scale(&bottom.pos, MAP_SCALE);
				set_isometric_projection(&bottom.pos);
				draw_line(mlx_ptr, win_ptr, curr, bottom);
			}
	        mlx_pixel_put(mlx_ptr, win_ptr, (curr.pos.x) + (WIN_WIDTH/MARGIN_RIGHT), (curr.pos.y) + (WIN_HEIGHT/MARGIN_BOTTOM), 0x00FFFF);
			j++;
		}
		// printf("\n");
		i++;
     }
	mlx_loop(mlx_ptr);

    // mlx_destroy_display(mlx_ptr);
    // mlx_destroy_window(mlx_ptr, win_ptr);
}





#include "fdf.h"

typedef struct s_mlx_env
{
    void    *mlx_ptr;
    void    *win_ptr;
}           t_mlx_env;

typedef struct s_map_data
{
    int     width;
    int     height;
    t_fdf   **map;
}           t_map_data;


int create_fdf(char *file_name)
{
    t_mlx_env   env;
    t_map_data  map_data;

    init_mlx_and_window(&env);
    get_map_dimensions(file_name, &map_data.width, &map_data.height);
    create_and_read_map(file_name, &map_data);
    render_map(&env, &map_data);
    mlx_loop(env.mlx_ptr);
    return (0);
}

/* MLX 초기화 및 윈도우 생성 */
static void init_mlx_and_window(t_mlx_env *env)
{
    env->mlx_ptr = mlx_init();
    env->win_ptr = mlx_new_window(env->mlx_ptr, 
                                WIN_WIDTH, 
                                WIN_HEIGHT, 
                                "FDF Projection");
}

/* 맵 차원 계산 */
static void get_map_dimensions(char *file_name, int *x, int *y)
{
    set_map_size(file_name, x, y);
    printf("Map dimensions: x:%d, y:%d\n", *x, *y);
}

/* 맵 생성 및 데이터 읽기 */
static void create_and_read_map(char *file_name, t_map_data *map)
{
    map->map = create_map(map->width, map->height);
    set_fdf_map(map->map, file_name);
    show_map(map->map, map->width, map->height);
}

/* 맵 렌더링 핸들러 */
static void render_map(t_mlx_env *env, t_map_data *map)
{
    for (int i = 0; i < map->height; i++)
    {
        for (int j = 0; j < map->width; j++)
        {
            process_point(env, map->map[i][j]);
            draw_adjacent_lines(env, map, i, j);
        }
    }
}

/* 개별 포인트 처리 */
static void process_point(t_mlx_env *env, t_fdf point)
{
    t_pos transformed = point.pos;
    
    set_scale(&transformed, MAP_SCALE);
    set_isometric_projection(&transformed);
    mlx_pixel_put(env->mlx_ptr, env->win_ptr,
                transformed.x + (WIN_WIDTH/MARGIN_RIGHT),
                transformed.y + (WIN_HEIGHT/MARGIN_BOTTOM),
                0x00FFFF);
}

/* 인접 점 연결선 그리기 */
static void draw_adjacent_lines(t_mlx_env *env, t_map_data *map, int i, int j)
{
    t_fdf   curr = map->map[i][j];
    t_fdf   next;
    t_fdf   bottom;

    if (j < map->width - 1)
    {
        next = map->map[i][j+1];
        set_scale(&curr.pos, MAP_SCALE);
        set_scale(&next.pos, MAP_SCALE);
        set_isometric_projection(&curr.pos);
        set_isometric_projection(&next.pos);
        draw_line(env->mlx_ptr, env->win_ptr, curr, next);
    }
    if (i < map->height - 1)
    {
        bottom = map->map[i+1][j];
        set_scale(&curr.pos, MAP_SCALE);
        set_scale(&bottom.pos, MAP_SCALE);
        set_isometric_projection(&curr.pos);
        set_isometric_projection(&bottom.pos);
        draw_line(env->mlx_ptr, env->win_ptr, curr, bottom);
    }
}
