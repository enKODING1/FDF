CC = gcc -g
# CFLAGS = -Wall -Wextra -Werror
NAME = fdf
SOURCES = ./src/args/check_args.c ./src/args/core_args.c ./src/args/overflow_checker.c ./src/args/element_utils.c\
		  ./src/map/map_utils.c ./src/map/map_core.c ./src/map/ft_atoi_base.c ./src/map/map_loader.c ./src/map/mlx_utils.c ./src/map/transform.c \
		  ./src/map/draw/draw_core.c ./src/map/draw/draw_utils.c \
		  ./src/mem/mem_utils.c \
		  ./src/main.c \
		  ./src/error.c
OBJECTS = $(SOURCES:.c=.o)

LIBFT_DIR = ./lib/libft/
GNL_DIR = ./lib/get_next_line/
MINILIBX_DIR = ./lib/minilibx-linux/
FDF_DIR = ./src/

LIBFT_LIB = $(LIBFT_DIR)/libft.a
GNL_LIB = $(GNL_DIR)/libgnl.a

all: $(NAME)

$(NAME): $(GNL_LIB) $(LIBFT_LIB) $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -lm -o $(NAME) \
		-I$(LIBFT_DIR) -I$(GNL_DIR) -I$(MINILIBX_DIR) -I$(FDF_DIR)\
		-L$(MINILIBX_DIR) -lmlx -lXext -lX11 \
		-L$(LIBFT_DIR) -lft \
		-L$(GNL_DIR) -lgnl

$(GNL_LIB):
	make -C $(GNL_DIR)

$(LIBFT_LIB):
	make -C $(LIBFT_DIR)
	make bonus -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ \
		 -I $(LIBFT_DIR) -I $(GNL_DIR) -I $(MINILIBX_DIR) -I $(FDF_DIR)

clean:
	make clean -C $(LIBFT_DIR)
	make clean -C $(GNL_DIR)
	rm -f $(OBJECTS)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	make fclean -C $(GNL_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
