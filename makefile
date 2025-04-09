# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmaizel <jmaizel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/28 14:37:22 by jmaizel           #+#    #+#              #
#    Updated: 2025/04/09 13:39:10 by jmaizel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler et flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Nom du programme
NAME = cub3D

# Répertoires
SRC_DIR = ./srcs
OBJ_DIR = ./objs
LIBFT_DIR = ./libft
MLX_DIR = ./minilibx-linux

# Includes
INCLUDES = -I$(LIBFT_DIR) -I$(SRC_DIR) -I$(MLX_DIR) -I./includes

# MLX FLAGS
MLX_FLAGS = $(MLX_DIR)/libmlx.a -lXext -lX11 -lm

# Fichiers source
MAIN_FILES = main.c draw1.c
PARSING_FILES = parsing_cub_file.c parsing_map.c is_map_valid.c utils.c
RAYCASTING_FILES = raycasting.c textures.c movement.c

SRC_FILES = $(addprefix main/, $(MAIN_FILES)) \
            $(addprefix parsing/, $(PARSING_FILES)) \
            $(addprefix raycasting/, $(RAYCASTING_FILES))

SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Libs
LIBFT = $(LIBFT_DIR)/libft.a

# Règle par défaut
all: $(NAME)

# Compilation du programme
$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) $(MLX_FLAGS)

# Compilation des .o dans obj/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Compilation de libft
$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

# Nettoyage
clean:
	rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re