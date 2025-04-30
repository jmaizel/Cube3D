# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmaizel <jmaizel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/28 14:37:22 by jmaizel           #+#    #+#              #
#    Updated: 2025/04/30 16:29:57 by jmaizel          ###   ########.fr        #
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
PLAYER_DIR = ./srcs/player
MONSTER_DIR = ./srcs/monster
TEXTURES_DIR = ./srcs/textures
GRAPHICS_DIR = ./srcs/graphics

LIBS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -L$(LIBFT_DIR) -lft
LIBFT = $(LIBFT_DIR)/libft.a
MLX = $(MLX_DIR)/libmlx.a

# Fichiers source principaux
MAIN_FILES = main.c utils.c

# Fichiers de parsing
PARSING_FILES = parse_cub_file.c parse_config.c parse_config_2.c parse_map.c validate_map.c validate_map_utils.c

# Fichiers de raycasting
RAYCASTING_FILES = raycasting.c raycasting_utils.c

# Fichiers des actions du joueur
PLAYER_FILES = movement.c rotation.c attack.c input.c

# Fichiers des monstres/ennemis
MONSTER_FILES = monster_init.c monster_render.c monster_render_utils.c

# Fichiers des textures
TEXTURES_FILES = textures.c textures_daw.c

# Fichiers graphiques
GRAPHICS_FILES = render_frame.c game_loop.c game_loop_extra.c draw_minimap.c draw_minimap_utils.c draw_weapon.c draw_ui.c

# Assemblage de tous les fichiers source
SRC_FILES = $(addprefix $(MAIN_DIR)/, $(MAIN_FILES)) \
            $(addprefix $(PARSING_DIR)/, $(PARSING_FILES)) \
            $(addprefix $(RAYCASTING_DIR)/, $(RAYCASTING_FILES)) \
            $(addprefix $(PLAYER_DIR)/, $(PLAYER_FILES)) \
            $(addprefix $(MONSTER_DIR)/, $(MONSTER_FILES)) \
            $(addprefix $(TEXTURES_DIR)/, $(TEXTURES_FILES)) \
            $(addprefix $(GRAPHICS_DIR)/, $(GRAPHICS_FILES))

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
	@echo ""

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
	@mkdir -p $(OBJ_DIR)/player
	@mkdir -p $(OBJ_DIR)/monster
	@mkdir -p $(OBJ_DIR)/textures
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