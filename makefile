NAME = cub3D
CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCLUDES_DIR = ./includes
LIBFT_DIR = ./libft
MLX_DIR = ./minilibx-linux

# Répertoires sources et objets
SRC_DIR = ./srcs
OBJ_DIR = ./objs
MAIN_DIR = $(SRC_DIR)/main
PARSING_DIR = $(SRC_DIR)/parsing
RAYCASTING_DIR = $(SRC_DIR)/raycasting

# Bibliothèques
LIBFT = $(LIBFT_DIR)/libft.a
MLX = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
LIBS = -L$(LIBFT_DIR) -lft $(MLX_FLAGS)

# Includes
INCLUDES = -I$(INCLUDES_DIR) -I$(LIBFT_DIR)/includes -I$(MLX_DIR)

# Fichiers sources
MAIN_FILES = main.c draw1.c
PARSING_FILES = parsing_cub_file.c parsing_map.c is_map_valid.c utils.c
RAYCASTING_FILES = raycasting.c textures.c movement.c


# Rassembler tous les fichiers source
SRC_FILES = $(addprefix $(MAIN_DIR)/, $(MAIN_FILES)) \
            $(addprefix $(PARSING_DIR)/, $(PARSING_FILES)) \
            $(addprefix $(RAYCASTING_DIR)/, $(RAYCASTING_FILES))

# Objets générés à partir des sources
OBJS = $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Comptage pour la barre de progression
TOTAL_FILES := $(words $(SRC_FILES))
COMPILED_FILES := 0

# Définition de la barre de progression
define progress_bar
	@$(eval COMPILED_FILES=$(shell echo $$(($(COMPILED_FILES) + 1))))
	@PROGRESS=$$(($(COMPILED_FILES) * 100 / $(TOTAL_FILES))); \
	BAR=$$(seq -s= $$(($$PROGRESS / 5)) | sed 's/[0-9]//g'); \
	printf "\rCompiling [%-20s] %d%%" "$$BAR" "$$PROGRESS"
endef

# Règles
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	@echo "\nLinking $(NAME)..."
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)
	@echo "\n$(NAME) successfully built!"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	$(call progress_bar)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)/main
	@mkdir -p $(OBJ_DIR)/parsing
	@mkdir -p $(OBJ_DIR)/ray_casting

$(LIBFT):
	@make --no-print-directory -C $(LIBFT_DIR)

$(MLX):
	@make --no-print-directory -C $(MLX_DIR)

clean:
	@echo "Cleaning object files..."
	@rm -rf $(OBJ_DIR)
	@make clean --no-print-directory -C $(LIBFT_DIR)
	@make clean --no-print-directory -C $(MLX_DIR)
	@echo "Object files cleaned!"

fclean: clean
	@echo "Cleaning executable..."
	@rm -f $(NAME)
	@make fclean --no-print-directory -C $(LIBFT_DIR)
	@echo "Executable cleaned!"

re: fclean all

.PHONY: all clean fclean re