# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmaizel <jmaizel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/28 14:37:22 by jmaizel           #+#    #+#              #
#    Updated: 2025/03/28 14:37:24 by jmaizel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler et flags
CC      = gcc
CFLAGS  = -Wall -Wextra -Werror

# Nom du programme
NAME    = cub3D

# Répertoires
SRC_DIR     = ./src
OBJ_DIR     = ./obj
LIBFT_DIR   = ./libft
MLX_FLAGS   = -lmlx -lXext -lX11 -lm

# Includes
INCLUDES    = -I$(LIBFT_DIR) -I$(SRC_DIR) -I.

# Fichiers source
SRC_FILES = 
SRC       = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ       = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Libs
LIBFT      = $(LIBFT_DIR)/libft.a

# Règle par défaut
all: $(NAME)

# Compilation du programme
$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) $(MLX_FLAGS)

# Compilation des .o dans obj/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
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
