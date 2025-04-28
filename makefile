# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cdedessu <cdedessu@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/28 14:37:22 by jmaizel           #+#    #+#              #
#    Updated: 2025/04/27 17:55:34 by cdedessu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I$(INCLUDES_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)

LIBFT_DIR = ./libft
MLX_DIR = ./minilibx-linux
INCLUDES_DIR = includes
OBJ_DIR = objs

MAIN_DIR = ./srcs/main
PARSING_DIR = ./srcs/parsing
RAYCASTING_DIR = ./srcs/raycasting
GAME_DIR = ./srcs/game
GRAPHICS_DIR = ./srcs/graphics

LIBS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -L$(LIBFT_DIR) -lft
LIBFT = $(LIBFT_DIR)/libft.a
MLX = $(MLX_DIR)/libmlx.a

MAIN_FILES = main.c utils.c
PARSING_FILES = parse_map.c parsing_cub_file.c validate_map.c
RAYCASTING_FILES = raycasting.c raycasting_utils.c
GAME_FILES = movement.c mouse.c
GRAPHICS_FILES = draw_minimap.c draw_weapon.c render_frame.c textures.c draw_enemies.c

SRC_FILES = $(addprefix $(MAIN_DIR)/, $(MAIN_FILES)) \
            $(addprefix $(PARSING_DIR)/, $(PARSING_FILES)) \
            $(addprefix $(RAYCASTING_DIR)/, $(RAYCASTING_FILES)) \
            $(addprefix $(GRAPHICS_DIR)/, $(GRAPHICS_FILES)) \
			$(addprefix $(GAME_DIR)/, $(GAME_FILES))

OBJS = $(SRC_FILES:./srcs/%.c=$(OBJ_DIR)/%.o)

TOTAL_FILES := $(words $(SRC_FILES))
COMPILED_FILES := 0

define progress_bar
	@$(eval COMPILED_FILES=$(shell echo $$(($(COMPILED_FILES) + 1))))
	@PROGRESS=$$(($(COMPILED_FILES) * 100 / $(TOTAL_FILES))); \
	BAR=$$(seq -s= $$(($$PROGRESS / 5)) | sed 's/[0-9]//g'); \
	printf "\rCompiling [%-20s] %d%%" "$$BAR" "$$PROGRESS"
endef

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)

$(OBJ_DIR)/%.o: ./srcs/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	$(call progress_bar)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)/main
	@mkdir -p $(OBJ_DIR)/parsing
	@mkdir -p $(OBJ_DIR)/raycasting
	@mkdir -p $(OBJ_DIR)/game
	@mkdir -p $(OBJ_DIR)/graphics

$(LIBFT):
	@make --no-print-directory -C $(LIBFT_DIR)

$(MLX):
	@make -s --no-print-directory -C $(MLX_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@make clean --no-print-directory -C $(LIBFT_DIR)
	@make clean --no-print-directory -C $(MLX_DIR)

fclean: clean
	@rm -f $(NAME)
	@make fclean --no-print-directory -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re