# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tle-saut <tle-saut@student.42perpignan>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/12 00:03:21 by tle-saut          #+#    #+#              #
#    Updated: 2025/06/12 11:51:28 by tle-saut         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# 🏷️ Nom du programme
NAME        = cub3d

# ⚙️ Compilateur et flags
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g -DDEBUG=$(DEBUG)

# 📁 Répertoires
SRC_DIR     = src/
VEC_DIR     = src/vector/
OBJ_DIR     = obj/

# 📄 Fichiers source
SRC         = cub3d.c check_file.c game.c debug.c draw.c debug_utils.c \
			  render.c map.c player.c texture.c raycasting.c\
			  init.c check_map.c check_border.c collision.c check_cub.c\
			  utils.c destroy.c draw2.c game2.c raycasting2.c\
			  raycasting3.c render2.c utils2.c split.c

VECTOR      = vector2d.c vector2d_math.c

# 🌐 Fichiers complets avec chemins
SRC_FILES   = $(addprefix $(SRC_DIR), $(SRC))
VEC_FILES   = $(addprefix $(VEC_DIR), $(VECTOR))

# 🧱 Fichiers objets avec chemins OBJ_DIR
OBJ         = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC_FILES)) \
			  $(patsubst $(VEC_DIR)%.c, $(OBJ_DIR)vector/%.o, $(VEC_FILES))

# 📚 Librairies
MLX_DIR     = minilibx-linux
MLX_LIB     = $(MLX_DIR)/libmlx.a

LIBFT_DIR   = libft
LIBFT_LIB   = $(LIBFT_DIR)/libft.a

FLAGS       = -lm -lXext -lX11 -L$(MLX_DIR) -lmlx
FLAGS_MAC   = -Lmlx -lmlx -framework OpenGL -framework AppKit

INCLUDES    = -Iinclude

# 🎨 Couleurs
GREEN   = \033[0;32m
YELLOW  = \033[1;33m
BLUE    = \033[1;34m
RED     = \033[0;31m
RESET   = \033[0m

# 🐞 Debug mode
DEBUG ?= 0

# 🔨 Compilation principale
all: $(NAME)

$(NAME): $(OBJ) $(MLX_LIB) $(LIBFT_LIB)
	@echo "$(BLUE)🔧 Linking: $(NAME)$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(MLX_LIB) $(LIBFT_LIB) $(FLAGS)
	@echo "$(GREEN)✅ Build complete!$(RESET)"

# ⚙️ Compilation des fichiers .c en .o dans OBJ_DIR
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)🛠️ Compiling: $<$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(OBJ_DIR)vector/%.o: $(VEC_DIR)%.c
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)🛠️   Compiling: $<$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

# 📦 Librairies
$(LIBFT_LIB):
	@echo "$(BLUE)📦 Building libft...$(RESET)"
	@make -C $(LIBFT_DIR) re

$(MLX_LIB):
	@echo "$(BLUE)📦 Building MLX...$(RESET)"
	@make -C $(MLX_DIR)

# 🧹 Nettoyage
clean:
	@echo "$(BLUE)🧽 Cleaning objects...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean
	@make -C $(MLX_DIR) clean

fclean: clean
	@echo "$(RED)🧨 Removing binary: $(NAME)$(RESET)"
	@rm -f $(NAME)

re: fclean all

debug:
	@$(MAKE) fclean
	@$(MAKE) DEBUG=1

mac:
	@$(MAKE) fclean
	@make -C $(LIBFT_DIR) re
	@make -C $(MLX_DIR) re
	@$(MAKE)

macdebug:
	@$(MAKE) fclean
	@make -C $(LIBFT_DIR) fclean
	@make -C $(LIBFT_DIR)
	@make -C $(MLX_DIR) re
	@$(MAKE) DEBUG=1

.PHONY: all clean fclean re debug mac
