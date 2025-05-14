NAME = cub3d

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -DDEBUG=$(DEBUG)

SRC = $(addprefix src/, cub3d.c check_file.c game.c debug.c render.c map.c player.c texture.c \
		init.c check_map.c draw.c)
VECTOR = $(addprefix src/vector/, vector2d.c vector2d_math.c)

OBJ = $(SRC:.c=.o) $(VECTOR:.c=.o)

MLX_DIR = minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a

LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

FLAGS = -lm -lXext -lX11 -L$(MLX_DIR) -lmlx

INCLUDES = -Iinclude

DEBUG ?= 0

all : $(NAME) clean

$(NAME) : $(OBJ) $(MLX_LIB) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(MLX_LIB) $(LIBFT_LIB) $(FLAGS)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

src/vector/%.o: src/vector/%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(LIBFT_LIB):
	make -C $(LIBFT_DIR)
clean :
	rm -f $(OBJ)
	make -C $(LIBFT_DIR) clean

fclean : clean
	rm -f $(NAME)

debug :
	$(MAKE) DEBUG=1

re: fclean all
